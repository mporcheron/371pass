// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2021/22)
// Department of Computer Science, Swansea University
//
// Author: Martin Porcheron
//         m.a.w.porcheron@swansea.ac.uk
//
// Canvas: https://canvas.swansea.ac.uk/courses/15581
// -----------------------------------------------------
// An Item class containsEntry multiple 'entries' as
// key/value pairs (e.g., a key might be 'username'
// and a value would be the username, another might be
// 'url' and the value is the website address the
// username is for.
// -----------------------------------------------------

#ifndef ITEM_H
#define ITEM_H

#include <map>
#include <string>
#include <tuple>

#include "lib_json.hpp"

using EntriesContainer = std::map<std::string, std::string>;

class Item {
  std::string ident;
  EntriesContainer entries;

public:
  Item(std::string ident);
  ~Item() = default;

  inline const std::string& getIdent() const noexcept {
    return ident;
  }

  unsigned int inline size() const noexcept {
    return entries.size();
  }

  unsigned int inline empty() const noexcept {
    return entries.empty();
  }

  bool addEntry(std::string ident, std::string value);
  const std::string& getEntry(const std::string& ident) const;
  bool deleteEntry(const std::string& ident);

  bool inline containsEntry(const std::string& ident) const noexcept {
    return entries.count(ident) != 0;
  }

  nlohmann::json json() const;
  std::string str() const;

  friend bool operator==(const Item& lhs, const Item& rhs);

  // Wrappers for iterating over the nested container
  inline EntriesContainer::iterator begin() {
    return entries.begin();
  }
  inline EntriesContainer::const_iterator cbegin() const {
    return entries.cbegin();
  }

  inline EntriesContainer::iterator end() {
    return entries.end();
  }
  inline EntriesContainer::const_iterator cend() const {
    return entries.cend();
  }

  inline EntriesContainer::reverse_iterator rbegin() {
    return entries.rbegin();
  }
  inline EntriesContainer::const_reverse_iterator crbegin() const {
    return entries.crbegin();
  }

  inline EntriesContainer::reverse_iterator rend() {
    return entries.rend();
  }
  inline EntriesContainer::const_reverse_iterator crend() const {
    return entries.crend();
  }
};

#endif //ITEM_H
