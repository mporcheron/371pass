// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2021/22)
// Department of Computer Science, Swansea University
//
// Author: Martin Porcheron
//         m.a.w.porcheron@swansea.ac.uk
//
// Canvas: https://canvas.swansea.ac.uk/courses/15581
// -----------------------------------------------------

#ifndef CATEGORY_H
#define CATEGORY_H

#include <map>
#include <string>

#include "lib_json.hpp"

#include "item.h"

using ItemContainer = std::map<std::string, Item>;

class Category {
  std::string ident;
  ItemContainer items;

public:
  Category(std::string ident);
  ~Category() = default;

  inline const std::string& getIdent() const noexcept {
    return ident;
  }

  inline void setIdent(std::string ident) noexcept {
    this->ident = ident;
  }

  unsigned int inline size() const noexcept {
    return items.size();
  }

  unsigned int inline empty() const noexcept {
    return items.empty();
  }

  Item& newItem(const std::string& ident);
  bool addItem(Item ident);
  Item& getItem(const std::string& ident);
  bool deleteItem(const std::string& ident) noexcept;

  bool inline containsItem(const std::string& ident) const noexcept {
    return items.count(ident) != 0;
  }

  nlohmann::json json() const;
  std::string str() const;

  friend bool operator==(const Category& c1, const Category& c2);

  // Wrappers for iterating over the nested container
  inline ItemContainer::iterator begin() {
    return items.begin();
  }
  inline ItemContainer::const_iterator cbegin() const {
    return items.cbegin();
  }

  inline ItemContainer::iterator end() {
    return items.end();
  }
  inline ItemContainer::const_iterator cend() const {
    return items.cend();
  }

  inline ItemContainer::reverse_iterator rbegin() {
    return items.rbegin();
  }
  inline ItemContainer::const_reverse_iterator crbegin() const {
    return items.crbegin();
  }

  inline ItemContainer::reverse_iterator rend() {
    return items.rend();
  }
  inline ItemContainer::const_reverse_iterator crend() const {
    return items.crend();
  }
};

#endif //CATEGORY_H
