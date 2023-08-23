#pragma once

#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

namespace CORE::Internal::MiniPool {

/**
 * The NodeManager class stores its nodes through a linked list of MiniPools.
 */
template <typename item>
class MiniPool {
 private:
  size_t capacity_;
  std::vector<item> item_container{};
  MiniPool* next_{nullptr};
  MiniPool* prev_{nullptr};

 public:
  MiniPool(size_t cap) : capacity_(cap) {
    item_container.reserve(capacity_);
  }

  size_t capacity() const { return item_container.capacity(); }

  size_t size() const { return item_container.size(); }

  bool is_full() const { return item_container.size() >= capacity_; }

  MiniPool* next() const { return next_; }

  void set_next(MiniPool* mp) { next_ = mp; }

  MiniPool* prev() const { return prev_; }

  void set_prev(MiniPool* mp) { prev_ = mp; }

  template <class... Args>
  item* alloc(Args... args) {
    item_container.emplace_back(std::forward<Args>(args)...);
    return &item_container.back();
  }
};
}  // namespace CORE::Internal::MiniPool
