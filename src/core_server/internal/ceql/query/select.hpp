#pragma once
#include <set>
#include <string>

namespace CORE::Internal::CEQL {

struct Select {
  enum class Strategy {
    ALL,
    ANY,
    LAST,
    MAX,
    NEXT,
    STRICT,
    DEFAULT = Strategy::ALL
  };

  Strategy strategy;
  std::set<std::string> variable_names;
  bool is_star;

  Select(Strategy&& strategy,
         std::set<std::string>&& variable_names,
         bool is_star)
      : strategy(std::move(strategy)),
        variable_names(std::move(variable_names)),
        is_star(is_star) {}
};
}  // namespace CORE::Internal::CEQL
