#pragma once

#include <cstdlib>

#include "core_server/internal/evaluation/minipool/minipool.hpp"
#include "state.hpp"

namespace CORE::Internal::CEA::Det {

const size_t MEMORY_POOL_STARTING_SIZE = 1;
const size_t MEMORY_POOL_MAX_SIZE = SIZE_MAX;
const float EVICT_PERCENTAGE = 0.2;

/**
 * The Node Manager class stores the pointers to all allocated
 * state nodes. When we need a state node, but we are out of memory,
 * we remove one of the existing nodes and reuse it.
 */
class StateManager {
  typedef MiniPool::MiniPool<State> StatePool;

 private:
  size_t amount_of_used_states {0};
  size_t amount_of_allowed_states;
  size_t amount_of_created_states {0};
  StatePool* minipool_head = nullptr;
  State* recyclable_state_head = nullptr;

 public:
  StateManager()
      : minipool_head(new StatePool(MEMORY_POOL_STARTING_SIZE)),
        amount_of_allowed_states(SIZE_MAX) {}

  StateManager(StateManager&& other) noexcept:
      amount_of_used_states(other.amount_of_used_states),
      amount_of_allowed_states(other.amount_of_allowed_states),
      amount_of_created_states(other.amount_of_created_states),
      minipool_head(other.minipool_head) {
    other.minipool_head = nullptr;
  }

  ~StateManager() {
    for (StatePool* mp = minipool_head; mp != nullptr;) {
      StatePool* next = mp->prev();
      delete mp;
      mp = next;
    }
  }

  template <class... Args>
  State* alloc(Args&&... args) {
    State* new_state;
    new_state = allocate_state_if_possible((args)...);
    if (new_state == nullptr) {
      // TODO: evict state
      // clean_states();
      // new_state = allocate_state_if_possible((args)...);
      // assert(new_state != nullptr);
      // return new_state;
      assert(false && "Evict state not implemented yet");
    }
    return new_state;
  }

 private:
  template <class... Args>
  State* allocate_state_if_possible(Args&&... args) {
    if (amount_of_created_states < amount_of_allowed_states) {
      if (minipool_head->is_full()) {
        increase_mempool_size();
      }
      amount_of_created_states++;
      amount_of_used_states++;
      return minipool_head->alloc((args)...);
    } else if (recyclable_state_head != nullptr) {
      amount_of_used_states++;
      State* out = recyclable_state_head;
      recyclable_state_head = recyclable_state_head->next_free_state;
      out->reset(std::forward<Args>(args)...);
      return out;
    } else {
      return nullptr;
    }
  }

  void increase_mempool_size() {
    StatePool* new_minipool = new StatePool(minipool_head->size() * 2);
    minipool_head->set_next(new_minipool);
    new_minipool->set_prev(minipool_head);

    minipool_head = new_minipool;
  }
};
}  // namespace CORE::Internal::CEA::Det
