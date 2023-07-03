#include "and_predicate.hpp"

#include <memory>

#include "or_predicate.hpp"

namespace CORE {
namespace Internal {
namespace CEQL {
std::unique_ptr<Predicate> AndPredicate::negate() const {
  std::vector<std::unique_ptr<Predicate>> negated;
  for (auto& predicate : predicates) {
    auto neg = predicate->negate();
    negated.push_back(std::move(neg));
  }
  return std::make_unique<OrPredicate>(std::move(negated));
}
}  // namespace CEQL
}  // namespace Internal
}  // namespace CORE
