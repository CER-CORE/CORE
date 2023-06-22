#pragma once

#include "cassert"
#include "comparison_type.hpp"
#include "core_server/internal/stream/ring_tuple_queue/tuple.hpp"
#include "core_server/internal/stream/ring_tuple_queue/value.hpp"
#include "physical_predicate.hpp"

namespace InternalCORECEA {

class CheckTypePredicate : public PhysicalPredicate {
 public:
  CheckTypePredicate(int64_t event_type_id)
      : PhysicalPredicate(event_type_id) {}

  ~CheckTypePredicate() override = default;

  bool eval(RingTupleQueue::Tuple& tuple) override {
    // The Base class checks for the type.
    return true;
  }
};

}  // namespace InternalCORECEA
