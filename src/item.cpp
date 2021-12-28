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

#include "item.h"

using json = nlohmann::json;

// TODO Write a constructor that takes one parameter, a string identifer
//  and initialises the object and member data.
Item::Item(std::string ident) : ident(ident), entries() { /* do nothing */ }

// TODO Write a function, getIdent, that returns the identifier for the Item.

// TODO Write a function, addEntry, that takes two parameters, an entry
//  identifier and value and returns true if the entry was inserted into the
//  container or false otherwise.
bool Item::addEntry(std::string ident, std::string value) {
  entries[ident] = value;
  return true;
}

// TODO Write a function, getEntry, that takes one parameter, an entry
//  identifier and returns it's value. If no entry exists, throw an appropriate
//  exception.
const std::string& Item::getEntry(const std::string& ident) const {
  return entries.at(ident);
}

// TODO Write a function, deleteEntry, that takes one parameter, an entry
//  identifier, deletes it from the container, and returns true if the Item was
//  deleted. If no entry exists, return false.
bool Item::deleteEntry(const std::string& ident) {
  return entries.erase(ident) == 1;
}

// TODO Write an == operator overload for the Item class, such that two
//  Item objects are equal only if they have the same identifier and same
//  entries.
bool operator==(const Item& lhs, const Item& rhs) {
  return lhs.ident == rhs.ident &&
         lhs.entries.size() == rhs.entries.size() &&
         std::equal(lhs.entries.begin(), lhs.entries.end(),
                    rhs.entries.begin());
}

nlohmann::json Item::json() const {
  nlohmann::json j = nlohmann::json::object({});

  for (auto eIt = cbegin(); eIt != cend(); eIt++) {
    j[eIt->first] = eIt->second;
  }

  return j;
}

// TODO Write a function, str, that takes no parameters and returns a
//  std::string of the JSON representative of the data in the Item.
//
// Example:
//  Item i {"ident"};
//  std::string s = i.str();
std::string Item::str() const {
  return json().dump();
}