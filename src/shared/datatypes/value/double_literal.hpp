#pragma once

#include <string>

#include "shared/datatypes/value/value.hpp"

namespace CORETypes {
struct DoubleLiteral final : public Value {
  double value;

  DoubleLiteral() noexcept {}

  DoubleLiteral(double value) noexcept : value(value) {}

  ~DoubleLiteral() noexcept override {}

  std::string to_string() const noexcept override { return std::to_string(value); }

  bool operator==(const DoubleLiteral& other) const noexcept {
    return value == other.value;
  }

  bool equals(Value* val) const noexcept override {
    if (DoubleLiteral* double_lit = dynamic_cast<DoubleLiteral*>(val)) {
      return *this == *double_lit;
    } else
      return false;
  }

  std::unique_ptr<Value> clone() const noexcept override {
    return std::make_unique<DoubleLiteral>(value);
  }

  template <class Archive>
  void serialize(Archive& archive) {
    archive(value);
  }
};
}  // namespace CORETypes
