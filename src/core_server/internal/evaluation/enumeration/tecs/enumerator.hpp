#include <set>
#include <stack>

#include "node.hpp"

namespace CORE::Internal::tECS {

class Enumerator {
  std::stack<std::pair<Node*, std::set<uint64_t>>> stack;
  uint64_t original_pos;
  uint64_t last_time_to_consider;
  std::pair<std::pair<uint64_t, uint64_t>, std::set<uint64_t>> next_value;

  Enumerator(Node* node, uint64_t original_pos, int64_t time_window)
      : original_pos(original_pos),
        last_time_to_consider(original_pos - time_window) {
    if (node->max() >= last_time_to_consider) {
      stack.push({node, {}});
    }
  }

  bool has_next() {
    while (!stack.empty()) {
      Node* current_node = stack.top().first;
      std::set<uint64_t> positions = stack.top().second;
      stack.pop();
      while (true) {
        if (current_node->is_bottom()) {
          next_value = {{current_node->pos(), original_pos}, positions};
          return true;
        } else if (current_node->is_output()) {
          positions.insert(current_node->pos());
          current_node = current_node->next();
        } else if (current_node->is_union()) {
          if (current_node->right->max() >= last_time_to_consider) {
            stack.push({current_node->right, positions});
          }
          current_node = current_node->left;
        }
      }
    }
    return false;
  }

  /// It requires has_next to be evaluated before.
  std::pair<std::pair<uint64_t, uint64_t>, std::set<uint64_t>> next() {
    return next_value;
  }
};
}  // namespace CORE::Internal::tECS