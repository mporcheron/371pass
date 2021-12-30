// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2021/22)
// Department of Computer Science, Swansea University
//
// Author: Martin Porcheron
//         m.a.w.porcheron@swansea.ac.uk
//
// Canvas: https://canvas.swansea.ac.uk/courses/15581
// -----------------------------------------------------

#include <string>
#include <utility>

#include "item.h"

using json = nlohmann::json;

// TODO Write a constructor that takes one parameter, a string identifier
//  and initialises the object and member data.
Item::Item(std::string ident) : ident(std::move(ident)), entries() {
  /* do nothing */
}

// TODO Write a function, getIdent, that returns the identifier for the Item.

// TODO Write a function, setIdent, that takes one parameter, a string for a new
//  Item identifier, and updates the member variable. It returns nothing.

// TODO Write a function, addEntry, that takes two parameters, an entry
//  key and value and returns true if the entry was inserted into the
//  container or false if the entry already existed and was replaced.
bool Item::addEntry(const std::string &key, std::string value) noexcept {
  return entries.insert_or_assign(key, std::move(value)).second;
}

// TODO Write a function, getEntry, that takes one parameter, an entry
//  key and returns it's value. If no entry exists, throw an appropriate
//  exception.
const std::string &Item::getEntry(const std::string &key) const {
  try {
    return entries.at(key);
  } catch (const std::out_of_range &ex) {
    throw NoEntryError(key);
  }
}

// TODO Write a function, deleteEntry, that takes one parameter, an entry
//  key, deletes it from the container, and returns true if the Item was
//  deleted. If no entry exists, throw an appropriate exception.
bool Item::deleteEntry(const std::string &key) {
  try {
    return entries.erase(key) == 1;
  } catch (const std::out_of_range &ex) {
    throw NoEntryError(key);
  }
}

// TODO Write an == operator overload for the Item class, such that two
//  Item objects are equal only if they have the same identifier and same
//  entries.
bool operator==(const Item &lhs, const Item &rhs) {
  return lhs.ident == rhs.ident && lhs.entries.size() == rhs.entries.size() &&
         std::equal(lhs.entries.begin(), lhs.entries.end(),
                    rhs.entries.begin());
}

nlohmann::json Item::json() const {
  nlohmann::json j = nlohmann::json::object({});

  for (const auto &eIt : entries) {
    j[eIt.first] = eIt.second;
  }

  return j;
}

// TODO Write a function, str, that takes no parameters and returns a
//  std::string of the JSON representation of the data in the Item.
//
// See the coursework specification for how this JSON should look.
//
// Example:
//  Item i {"ident"};
//  std::string s = i.str();
std::string Item::str() const { return json().dump(); }