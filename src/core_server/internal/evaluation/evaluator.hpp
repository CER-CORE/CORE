#pragma once
#include <cwchar>
#include <optional>
#include <unordered_map>

#include "core_server/internal/ceql/query/consume_by.hpp"
#include "det_cea/det_cea.hpp"
#include "det_cea/state.hpp"
#include "enumeration/tecs/enumerator.hpp"
#include "enumeration/tecs/tecs.hpp"
#include "predicate_evaluator.hpp"
#include "tracy/Tracy.hpp"

namespace CORE::Internal::Evaluation {
class Evaluator {
 private:
  using UnionList = std::vector<tECS::Node*>;
  using State = CEA::Det::State;
  using States = CEA::Det::State::States;
  using Node = tECS::Node;
  //                                   // Name in paper
  CEA::DetCEA cea;                     // A
  PredicateEvaluator tuple_evaluator;  // t generator
  uint64_t time_window;                // ε

  std::unordered_map<State*, UnionList> historic_union_list_map;  // T
  std::vector<State*> historic_ordered_keys;
  std::unordered_map<State*, UnionList> current_union_list_map;  // T'
  std::vector<State*> current_ordered_keys;

  std::vector<State*> final_states;

  uint64_t actual_time;

  uint64_t current_iteration = 0;  // Current iteration of the algorithm as seen by next().

  /**
   * All events less than event_time_of_expiration can have it's children
   * recycled and marked as a dead node. Note that this uint64_t is passed
   * by reference to the tECS, and the tECS manages this behavior. This
   * uint64_t is a reference of the uint64_t stored at the mediator.
   */
  std::atomic<uint64_t>& event_time_of_expiration;

  // Other auxiliary objects

  tECS::tECS tecs;

  CEQL::ConsumeBy::ConsumptionPolicy consumption_policy;

// Only in debug, check tuples are being sent in ascending order.
#ifdef CORE_DEBUG
  uint64_t last_tuple_time = 0;
#endif

 public:
  Evaluator(CEA::DetCEA&& cea,
            PredicateEvaluator&& tuple_evaluator,
            uint64_t time_bound,
            std::atomic<uint64_t>& event_time_of_expiration,
            CEQL::ConsumeBy::ConsumptionPolicy consumption_policy)
      : cea(std::move(cea)),
        tuple_evaluator(std::move(tuple_evaluator)),
        time_window(time_bound),
        event_time_of_expiration(event_time_of_expiration),
        tecs(event_time_of_expiration),
        consumption_policy(consumption_policy) {}

  std::optional<tECS::Enumerator>
  next(RingTupleQueue::Tuple tuple, uint64_t current_time) {
    ZoneScopedN("Evaluator::next");
// If in debug, check tuples are being sent in ascending order.
#ifdef CORE_DEBUG
    assert(current_time >= last_tuple_time);
    last_tuple_time = current_time;
#endif
    // current_time is j in the algorithm.
    event_time_of_expiration = current_time < time_window ? 0 : current_time - time_window;
    mpz_class predicates_satisfied = tuple_evaluator(tuple);
    current_union_list_map = {};
    current_ordered_keys = {};
    final_states.clear();
    actual_time = current_time;
    UnionList ul = tecs.new_ulist(tecs.new_bottom(tuple, current_time));
    State* q0 = get_initial_state();
    exec_trans(tuple, q0, std::move(ul), predicates_satisfied, current_time);

    for (State* p : historic_ordered_keys) {
      assert(historic_union_list_map.contains(p));
      exec_trans(tuple,
                 p,
                 std::move(historic_union_list_map[p]),
                 predicates_satisfied,
                 current_time);  // Send the tuple in exec_trans.
    }
    // Update last used q0 so it can be used in the next iteration.
    cea.state_manager.update_last_used_iteration_state(q0, current_iteration);
    // Update the evicted states.
    cea.state_manager.update_evicted_states(historic_ordered_keys, current_iteration);
    historic_union_list_map = std::move(current_union_list_map);
    historic_ordered_keys = std::move(current_ordered_keys);
    current_iteration++;

    bool has_output = !final_states.empty();

    if (has_output) {
      tECS::Enumerator enumerator = output();
      // TODO: uncomment assert and remove condition from if after fixing has_output bug on empty enumerator
      // assert(enumerator.begin() != enumerator.end() && (enumerator.reset(), true));
      if (consumption_policy == CEQL::ConsumeBy::ConsumptionPolicy::ANY && enumerator.begin() != enumerator.end()) {
        historic_ordered_keys.clear();
        for (auto& [state, ul] : historic_union_list_map) {
          tecs.unpin(ul);
        }
      }
      enumerator.reset();
      return std::move(enumerator);
    }
    return {};
  }

 private:
  State* get_initial_state() { return cea.initial_state; }

  void exec_trans(RingTupleQueue::Tuple& tuple,
                  State* p,
                  UnionList&& ul,
                  mpz_class& t,
                  uint64_t current_time) {
    // exec_trans places all the code of add into exec_trans.
    assert(p != nullptr);
    States next_states = cea.next(p, t, current_iteration);
    auto marked_state = next_states.marked_state;
    auto unmarked_state = next_states.unmarked_state;
    assert(marked_state != nullptr && unmarked_state != nullptr);
    bool recycle_ulist = false;
    if (!marked_state->is_empty) {
      Node* new_node = tecs.new_extend(tecs.merge(ul), tuple, current_time);
      if (current_union_list_map.contains(marked_state)) {
        current_union_list_map[marked_state] = tecs.insert(
          std::move(current_union_list_map[marked_state]), new_node);
      } else {
        UnionList new_ulist = tecs.new_ulist(new_node);
        current_ordered_keys.push_back(marked_state);
        current_union_list_map[marked_state] = new_ulist;
        if (marked_state->is_final) {
          final_states.push_back(marked_state);
        }
      }
    }
    if (!unmarked_state->is_empty) {
      if (current_union_list_map.contains(unmarked_state)) {
        Node* new_node = tecs.merge(ul);
        current_union_list_map[unmarked_state] = tecs.insert(
          std::move(current_union_list_map[unmarked_state]), new_node);
      } else {
        current_ordered_keys.push_back(unmarked_state);
        current_union_list_map[unmarked_state] = ul;
        recycle_ulist = true;
        if (unmarked_state->is_final) {
          final_states.push_back(unmarked_state);
        }
      }
    }
    if (!recycle_ulist) {
      tecs.unpin(ul);
    }
  }

  // Change to tECS::Enumerator.
  tECS::Enumerator output() {
    ZoneScopedN("Evaluator::output");
    Node* out = nullptr;
    for (auto it = final_states.rbegin(); it != final_states.rend(); ++it) {
      State* p = *it;
      // If using ANY consumption policy, this assert will always fail due resetting state
      assert(historic_union_list_map.contains(p));
      Node* n = tecs.merge(historic_union_list_map[p]);
      // Aca hacer el union del nodo antiguo (si hay) con el nuevo nodo.
      if (out == nullptr) {
        out = n;
      } else {
        out = tecs.new_direct_union(n, out);
      }
    }
    // TODO: Take off the if statement when fixing online_query_evaluator empty enumerator problem
    if (out == nullptr) {
      return {};
    } else {
      tecs.pin(out);
      return {out, actual_time, time_window, tecs, tecs.time_reservator};
    }
  }
};

}  // namespace CORE::Internal::Evaluation
