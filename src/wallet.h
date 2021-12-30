// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2021/22)
// Department of Computer Science, Swansea University
//
// Author: Martin Porcheron
//         m.a.w.porcheron@swansea.ac.uk
//
// Canvas: https://canvas.swansea.ac.uk/courses/15581
// -----------------------------------------------------
// The root object that holds all data for 371pass. This
// class contains Categories, which in turn hold Items,
// which hold a mapping of entries.
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

  unsigned int inline size() const noexcept { return categories.size(); }

  unsigned int inline empty() const noexcept { return categories.empty(); }

  Category &newCategory(const std::string &cIdent);
  bool addCategory(Category category);
  Category &getCategory(const std::string &cIdent);
  bool deleteCategory(const std::string &cIdent);

  bool inline containsCategory(const std::string &ident) const noexcept {
    return categories.count(ident) != 0;
  }

  void load(const std::string &filePath);
  bool save(const std::string &filePath) const;

  nlohmann::json json() const;
  std::string str() const;

  friend bool operator==(const Wallet &lhs, const Wallet &rhs);

  // Wrappers for iterating over the nested container
  inline CategoryContainer::iterator find(const std::string &ident) {
    return categories.find(ident);
  }

  inline CategoryContainer::iterator begin() { return categories.begin(); }
  inline CategoryContainer::const_iterator cbegin() const {
    return categories.cbegin();
  }

  inline CategoryContainer::iterator end() { return categories.end(); }
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

struct FileIOError : public std::out_of_range {
  enum ACTION { READ, WRITE, PARSE };

  FileIOError(const ACTION &action, const std::string &filePath)
      : std::out_of_range(enumToStr(action) + filePath) {
    /* do nothing */
  }

  ~FileIOError() override = default;

  static std::string inline enumToStr(const ACTION &action) {
    switch (action) {
    case READ:
      return "error opening (for reading) ";
      break;

    case PARSE:
      return "error parsing ";
      break;

    case WRITE:
      return "error opening (for writing) ";
      break;

    default:
      return "unknown error with ";
    }
  }
};

struct AddCategoryError : public std::runtime_error {
  explicit AddCategoryError(const std::string &cIdent)
      : std::runtime_error("could not add category:" + cIdent) {
    /* do nothing */
  }

  ~AddCategoryError() override = default;
};

struct NoCategoryError : public std::out_of_range {
  explicit NoCategoryError(const std::string &cIdent)
      : std::out_of_range("unknown category:" + cIdent) {
    /* do nothing */
  }

  ~NoCategoryError() override = default;
};

#endif // WALLET_H
