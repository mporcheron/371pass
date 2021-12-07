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

#include "item.h"

using ItemContainer = std::map<std::string, Item>;

class Category {
  std::string ident;
  ItemContainer items;

public:
  Category(std::string ident);
  ~Category() = default;

  unsigned int inline size() {
    return items.size();
  }

  unsigned int inline empty() {
    return items.empty();
  }

  Item& addItem(const std::string& ident);



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
