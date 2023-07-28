#pragma once
#include <cwchar>
#include <memory>

#include "cassert"
#include "comparison_type.hpp"
#include "core_server/internal/stream/ring_tuple_queue/tuple.hpp"
#include "core_server/internal/stream/ring_tuple_queue/value.hpp"
#include "math_expr/math_expr_headers.hpp"
#include "physical_predicate.hpp"

namespace CORE::Internal::CEA {

template <ComparisonType Comp, typename ValueType>
class CompareMathExprs : public PhysicalPredicate {
 private:
  std::unique_ptr<MathExpr<ValueType>> left;
  std::unique_ptr<MathExpr<ValueType>> right;

 public:
  CompareMathExprs(uint64_t event_type_id,
                   std::unique_ptr<MathExpr<ValueType>>&& left,
                   std::unique_ptr<MathExpr<ValueType>>&& right)
      : PhysicalPredicate(event_type_id),
        left(std::move(left)),
        right(std::move(right)) {}

  CompareMathExprs(std::set<uint64_t> admissible_event_types,
                   std::unique_ptr<MathExpr<ValueType>>&& left,
                   std::unique_ptr<MathExpr<ValueType>>&& right)
      : PhysicalPredicate(admissible_event_types),
        left(std::move(left)),
        right(std::move(right)) {}

  ~CompareMathExprs() override = default;

  bool eval(RingTupleQueue::Tuple& tuple) override {
    if constexpr (Comp == ComparisonType::EQUALS) {
      std::cout << "Left: " << left->eval(tuple)
                << " == Right: " << right->eval(tuple) << std::endl;
      return left->eval(tuple) == right->eval(tuple);
    } else if constexpr (Comp == ComparisonType::GREATER)
      return left->eval(tuple) > right->eval(tuple);
    else if constexpr (Comp == ComparisonType::GREATER_EQUALS)
      return left->eval(tuple) >= right->eval(tuple);
    else if constexpr (Comp == ComparisonType::LESS_EQUALS)
      return left->eval(tuple) <= right->eval(tuple);
    else if constexpr (Comp == ComparisonType::LESS)
      return left->eval(tuple) < right->eval(tuple);
    else if constexpr (Comp == ComparisonType::NOT_EQUALS)
      return left->eval(tuple) != right->eval(tuple);
    else
      assert(false && "Operator() not implemented for some ComparisonType");
  }

  std::string to_string() const override {
    if constexpr (Comp == ComparisonType::EQUALS)
      return left->to_string() + "==" + right->to_string();
    else if constexpr (Comp == ComparisonType::GREATER)
      return left->to_string() + ">" + right->to_string();
    else if constexpr (Comp == ComparisonType::GREATER_EQUALS)
      return left->to_string() + ">=" + right->to_string();
    else if constexpr (Comp == ComparisonType::LESS_EQUALS)
      return left->to_string() + "<=" + right->to_string();
    else if constexpr (Comp == ComparisonType::LESS)
      return left->to_string() + "<" + right->to_string();
    else if constexpr (Comp == ComparisonType::NOT_EQUALS)
      return left->to_string() + "!=" + right->to_string();
    else
      assert(false && "to_string() not implemented for some ComparisonType");
  }
};
}  // namespace CORE::Internal::CEA
