#pragma once

#include "core_server/internal/stream/ring_tuple_queue/value.hpp"
#include "math_expr.hpp"

namespace InternalCORECEA {

template <typename Type>
class Modulo : public MathExpr<Type> {
 public:
  std::unique_ptr<MathExpr<Type>> left;
  std::unique_ptr<MathExpr<Type>> right;
  virtual ~Modulo() = default;

  Modulo(std::unique_ptr<MathExpr<Type>>&& left,
         std::unique_ptr<MathExpr<Type>>&& right)
      : left(std::move(left)), right(std::move(right)) {}

  std::unique_ptr<MathExpr<Type>> clone() const override {
    return std::make_unique<Modulo<Type>>(left->clone(), right->clone());
  }

  virtual Type eval(RingTupleQueue::Tuple& tuple) {
    if constexpr (std::is_same_v<Type, double>) {
      throw std::runtime_error("Cannot eval a modulo on double types");
    } else {
      return left->eval(tuple) % right->eval(tuple);
    }
  }

  std::string to_string() const override {
    return "(" + left->to_string() + " % " + right->to_string() + ")";
  }
};
}  // namespace InternalCORECEA