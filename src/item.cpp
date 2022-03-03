// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2021/22)
// Department of Computer Science, Swansea University
//
// Author: Martin Porcheron
//         m.a.w.porcheron@swansea.ac.uk
//
// Canvas: https://canvas.swansea.ac.uk/courses/24793
// -----------------------------------------------------

#include <string>
#include <utility>

#include "item.h"

using json = nlohmann::json;

// TODO Write a constructor that takes one parameter, a string identifier
//  and initialises the object and member data.
//
// Example:
//  Item iObj{"identIdent"};
Item::Item(std::string ident) : ident(std::move(ident)), entries() {
  /* do nothing */
}

// TODO Write a function, getIdent, that returns the identifier for the Item.
//
// Example:
//  Item iObj{"identIdent"};
//  auto ident = iObj.getIdent();

// TODO Write a function, setIdent, that takes one parameter, a string for a new
//  Item identifier, and updates the member variable. It returns nothing.
//
// Example:
//  Item iObj{"identIdent"};
//  iObj.setIdent("identIdent2");

// TODO Write a function, addEntry, that takes two parameters, an entry
//  key and value and returns true if the entry was inserted into the
//  container or false if the entry already existed and was replaced.
//
// Example:
//  Item iObj{"identIdent"};
//  iObj.addEntry("key", "value");
bool Item::addEntry(std::string key, std::string value) noexcept {
  try {
    getEntry(key);
    entries[std::move(key)] = std::move(value);
    return false;
 } catch(const NoEntryError &ex) {
   entries.insert({std::move(key), std::move(value)});
   return true;
 }
}

// TODO Write a function, getEntry, that takes one parameter, an entry
//  key and returns it's value. If no entry exists, throw an appropriate
//  exception.
//
// Example:
//  Item iObj{"identIdent"};
//  iObj.addEntry("key", "value");
//  auto value = iObj.getEntry("key");
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
//
// Example:
//  Item iObj{"identIdent"};
//  iObj.addEntry("key", "value");
//  iObj.deleteEntry("key");
bool Item::deleteEntry(const std::string &key) {
	if (entries.count(key) == 0 || entries.erase(key) == 0) {
    throw NoEntryError(key);
	}
	return true;
}

// TODO Write an == operator overload for the Item class, such that two
//  Item objects are equal only if they have the same identifier and same
//  entries.
//
// Example:
//  Item iObj1{"identIdent"};
//  iObj1.addEntry("key", "value");
//  Item iObj2{"identIdent2"};
//  if(iObj1 == iObj2) {
//    ...
//  }
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
//  Item iObj{"itemIdent"};
//  std::string s = iObj.str();
std::string Item::str() const { return json().dump(); }