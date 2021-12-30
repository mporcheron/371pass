// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2021/22)
// Department of Computer Science, Swansea University
//
// Author: Martin Porcheron
//         m.a.w.porcheron@swansea.ac.uk
//
// Canvas: https://canvas.swansea.ac.uk/courses/15581
// -----------------------------------------------------
// The root object that holds all data for 371pass
// -----------------------------------------------------

#ifndef WALLET_H
#define WALLET_H

#include <map>
#include <string>

#include "lib_json.hpp"

#include "category.h"

using CategoryContainer = std::map<std::string, Category>;

class Wallet {
  CategoryContainer categories;

public:
  Wallet();
  ~Wallet() = default;

  unsigned int inline size() const noexcept {
    return categories.size();
  }

  unsigned int inline empty() const noexcept {
    return categories.empty();
  }

  Category& newCategory(const std::string& ident);
  bool addCategory(Category category);
  Category& getCategory(const std::string& ident);
  bool deleteCategory(const std::string& ident) noexcept;

  bool inline containsCategory(const std::string& ident) const noexcept {
    return categories.count(ident) != 0;
  }

  void load(const std::string& filePath);
  bool save(const std::string& filePath) const;

  nlohmann::json json() const;
  std::string str() const;

  // Wrappers for iterating over the nested container
  inline CategoryContainer::iterator find(const std::string& ident) {
    return categories.find(ident);
  }

  inline CategoryContainer::iterator begin() {
    return categories.begin();
  }
  inline CategoryContainer::const_iterator cbegin() const {
    return categories.cbegin();
  }

  inline CategoryContainer::iterator end() {
    return categories.end();
  }
  inline CategoryContainer::const_iterator cend() const {
    return categories.cend();
  }

  inline CategoryContainer::reverse_iterator rbegin() {
    return categories.rbegin();
  }
  inline CategoryContainer::const_reverse_iterator crbegin() const {
    return categories.crbegin();
  }

  inline CategoryContainer::reverse_iterator rend() {
    return categories.rend();
  }
  inline CategoryContainer::const_reverse_iterator crend() const {
    return categories.crend();
  }
};

#endif //WALLET_H
