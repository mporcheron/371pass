// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2021/22)
// Department of Computer Science, Swansea University
//
// Author: Martin Porcheron
//         m.a.w.porcheron@swansea.ac.uk
//
// Canvas: https://canvas.swansea.ac.uk/courses/15581
// -----------------------------------------------------
// A category contains one or more Items, each with
// their own identifier ('ident').
// -----------------------------------------------------

#ifndef CATEGORY_H
#define CATEGORY_H

#include <map>
#include <string>
#include <utility>

#include "lib_json.hpp"

#include "item.h"

using ItemContainer = std::map<std::string, Item>;

class Category {
  std::string ident;
  ItemContainer items;

public:
  explicit Category(std::string ident);
  ~Category() = default;

  inline const std::string &getIdent() const noexcept { return ident; }

  inline void setIdent(std::string iIdent) noexcept {
    this->ident = std::move(iIdent);
  }

  unsigned int inline size() const noexcept { return items.size(); }

  unsigned int inline empty() const noexcept { return items.empty(); }

  Item &newItem(const std::string &iIdent);
  bool addItem(Item item);
  Item &getItem(const std::string &iIdent);
  bool deleteItem(const std::string &iIdent);

  bool inline containsItem(const std::string &iIdent) const noexcept {
    return items.count(iIdent) != 0;
  }

  nlohmann::json json() const;
  std::string str() const;

  friend bool operator==(const Category &c1, const Category &c2);

  // Wrappers for iterating over the nested container
  inline ItemContainer::iterator begin() { return items.begin(); }
  inline ItemContainer::const_iterator cbegin() const { return items.cbegin(); }

  inline ItemContainer::iterator end() { return items.end(); }
  inline ItemContainer::const_iterator cend() const { return items.cend(); }

  inline ItemContainer::reverse_iterator rbegin() { return items.rbegin(); }
  inline ItemContainer::const_reverse_iterator crbegin() const {
    return items.crbegin();
  }

  inline ItemContainer::reverse_iterator rend() { return items.rend(); }
  inline ItemContainer::const_reverse_iterator crend() const {
    return items.crend();
  }
};

struct AddItemError : public std::runtime_error {
  explicit AddItemError(const std::string &iIdent)
      : std::runtime_error("could not add item:" + iIdent) {
    /* do nothing */
  }

  ~AddItemError() override = default;
};

struct NoItemError : public std::out_of_range {
  explicit NoItemError(const std::string &iIdent)
      : std::out_of_range("unknown item:" + iIdent) {
    /* do nothing */
  }

  ~NoItemError() override = default;
};

#endif // CATEGORY_H
