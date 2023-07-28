#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "node.hpp"
#include "node_manager.hpp"

namespace CORE::Internal::tECS {

class tECS {
 public:
  size_t get_amount_of_nodes_used() const {
    return node_manager.get_amount_of_nodes_used();
  }

  size_t amount_of_nodes_allocated() const {
    return node_manager.amount_of_nodes_allocated();
  }

 private:
  NodeManager node_manager;

 public:
  tECS() : node_manager(2048) {}

  ~tECS() = default;

  /**
   * The bottom node, also known as the terminal node, has no children and
   * tells us that we reached the end of an output
   */
  Node* new_bottom(uint64_t index) { return node_manager.alloc(index); }

  /**
   * Extend nodes, also known as content nodes store the opened and closed
   * variables and the position in the document that this annotation is
   * referring to.
   */
  Node* new_extend(Node* node, uint64_t index) {
    return node_manager.alloc(node, index);
  }

  /**
   * Union nodes allow us to enumerate multiple outputs starting from a
   * single node.
   */
  Node* new_union(Node* node_1, Node* node_2) {
    assert(node_1 != nullptr && node_2 != nullptr);
    assert(node_1->max() == node_2->max());
    if (!node_1->is_union()) {
      return node_manager.alloc(node_1, node_2);
    } else if (!node_2->is_union()) {
      return node_manager.alloc(node_2, node_1);
    } else {
      return create_union_of_two_non_output_nodes(node_1, node_2);
    }
  }

  /**
   * If the node is going to be used in another scope, it is necessary to
   * pin it so that the memory manager does not recycle its memory location.
   */
  Node* pin_node(Node* node) {
    node_manager.increase_ref_count(node);
    return node;
  }

  std::vector<Node*> new_ulist(Node* node) {
    assert(!node->is_union());
    return {node};
  }

  /// Inserts the node in the ulist, maintaining the max-sorted invariant.
  void insert(std::vector<Node*>& ulist, Node* node) {
    assert_required_properties_of_union_list(ulist);
    assert(node->max() <= ulist[0]->max());
    std::cout << "after asserting" << std::endl;
    if (ulist.size() == 1) {
      ulist.push_back(node);
      assert_required_properties_of_union_list(ulist);
      return;
    }
    // binary search would be better.
    std::cout << "Finding where to insert the node" << std::endl;
    for (size_t i = 1; i < ulist.size(); i++) {
      if (ulist[i]->max() == node->max()) {
        std::cout << "merging inside insert of a ulist. " << std::endl;
        ulist[i] = new_union(ulist[i], node);
        std::cout << "after creating union" << std::endl;
        break;
      }
      if (ulist[i]->max() < node->max()) {
        ulist.insert(ulist.begin() + 1, node);
        break;
      }
    }
    assert_required_properties_of_union_list(ulist);
  }

  /*       _\|/_
           (o o)
   +----oOO-{_}-OOo---------------------------------------+
   |From the union list: n0, n1, ... nk creates this node:|
   |     u                                                |
   |    / \                                               |
   |  n0   u1                                             |
   |      /  \                                            |
   |     n1   u2                                          |
   |         /  \                                         |
   |        n2   \                                        |
   |              uk-1                                    |
   |             /   \                                    |
   |           nk-1   nk                                  |
   +-----------------------------------------------------*/
  Node* merge(std::vector<Node*>&& ulist) {
    assert_required_properties_of_union_list(ulist);
    Node* tail = ulist.back();
    for (int i = ulist.size() - 2; i >= 0; i--) {
      tail = node_manager.alloc(ulist[i], tail);
    }
    return tail;
  }

  /**
   * If a node is no longer used, it should be unpinned, this allows the
   * memory manager to recycle the memory allocated to it.
   */
  void unpin_node(Node* node) { node_manager.decrease_ref_count(node); }

 private:
  void
  assert_required_properties_of_union_list(std::vector<Node*> union_list) {
    assert(union_list.size() >= 1);
    assert(union_list[0] != nullptr);
    assert(!union_list[0]->is_union());
    for (int i = 0; i < union_list.size(); i++) {
      assert(union_list[i] != nullptr);
      assert(union_list[0]->max() >= union_list[i]->max());
    }
    for (int i = 2; i < union_list.size(); i++) {
      assert(union_list[i - 1]->max() > union_list[i]->max());
    }
  }

  /*!       _\|/_
            (o o)
    +----oOO-{_}-OOo---------------------------------------+
    |           u                                          |
    |         /   \            The union of two nodes that |
    |        /    u1           are non output nodes creates|
    |       /      |\          the union that is shown on  |
    |      /       | u2        the left. If max(right(n1)) |
    |     /        |/  \       is >= than max(right(n2))   |
    |    /         |    \      then r(n1) is the left child|
    |   /         /|     \     of u2, if not, it is the    |
    |  /         / |      \    right child.                |
    | /  n1     /  |   n2\ |                               |
    || /   \   /   | /    \|                               |
    |l(n1) r(n1)  l(n2)   r(n2)                            |
    +----------------------------------------------------- +
  */
  Node* create_union_of_two_non_output_nodes(Node* node_1, Node* node_2) {
    std::cout << "Creating u2" << std::endl;
    Node* u2 = create_first_intermediate_union_node(node_1, node_2);
    std::cout << "Created u2" << std::endl;
    Node* u1 = create_second_intermediate_union_node(node_2, u2);
    std::cout << "Created u1" << std::endl;
    Node* new_node = create_union_of_output_and_intermediate_node(node_1,
                                                                  u1);
    std::cout << "Created new_node" << std::endl;
    return new_node;
  }

  Node* create_first_intermediate_union_node(Node* node_1, Node* node_2) {
    Node* u2;
    if (node_1->max() >= node_2->max()) {
      u2 = node_manager.alloc(node_1->right, node_2->right);
    } else {
      u2 = node_manager.alloc(node_2->right, node_1->right);
    }
    return u2;
  }

  Node* create_second_intermediate_union_node(Node* node_2, Node* u2) {
    Node* u1 = node_manager.alloc(node_2->left, u2);
    return u1;
  }

  Node*
  create_union_of_output_and_intermediate_node(Node* node_1, Node* u2) {
    Node* new_node = node_manager.alloc(node_1->left, u2);
    return new_node;
  }
};
}  // namespace CORE::Internal::tECS