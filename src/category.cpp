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

#include "category.h"

// TODO Write a constructor that takes one parameter, a string identifier
//  and initialises the object and member data.
//
// Example:
//  Category c{"categoryIdent"};
Category::Category(std::string ident) : ident(std::move(ident)), items() {
  /* do nothing */
}

// TODO Write a function, getIdent, that returns the identifier for the
//  Category.
//
// Example:
//  Category cObj{"categoryIdent"};
//  auto ident = cObj.getIdent();

// TODO Write a function, setIdent, that takes one parameter, a string for a new
//  Category identifier, and updates the member variable. It returns nothing.
//
// Example:
//  Category cObj{"categoryIdent"};
//  cObj.setIdent("categoryIdent2");

// TODO Write a function, newItem, that takes one parameter, an Item identifier,
//  (a string) and returns the Item object as a reference. If an object with the
//  same identifier already exists, then the existing object should be returned.
//  Throw a std::runtime_error if the Item object cannot be inserted into the
//  container for whatever reason.
//
// Example:
//  Category cObj{"categoryIdent"};
//  cObj.newItem("itemIdent");
Item &Category::newItem(const std::string &iIdent) {
  const auto &result = items.find(iIdent);

  if (result == items.end()) {
    Item i(iIdent);
    const auto &insertResult = items.insert({iIdent, i});

    if (!insertResult.second) {
      throw AddItemError(iIdent);
    }

    return insertResult.first->second;
  }

  return result->second;
}

// TODO Write a function, addItem, that takes one parameter, an Item object,
//  and returns true if the object was successfully inserted. If an object with
//  the same identifier already exists, then the contents should be merged and
//  return false.
//
// Example:
//  Category cObj{"categoryIdent"};
//  Item iObj{"itemIdent"};
//  cObj.addItem(iObj);
bool Category::addItem(Item item) {
  try {
    const auto result = items.find(item.getIdent());

    if (result == items.end()) {
      const std::string &iIdent = item.getIdent();
      const auto &insertResult = items.insert({iIdent, item});
      return insertResult.second;
    }

    Item &existingItem = result->second;
    for (auto &entry : item) {
      existingItem.addEntry(entry.first, entry.second);
    }

    return false;
  } catch (const std::exception &ex) {
    throw AddItemError(item.getIdent());
  }
}

// TODO Write a function, getItem, that takes one parameter, an Item
//  identifier (a string) and returns the Item as a reference. If no Item
//  exists, throw an appropriate exception.
//
// Hint:
//  See the test scripts for the exception expected.
//
// Example:
//  Category cObj{"categoryIdent"};
//  cObj.newItem("itemIdent");
//  auto iObj = cObj.getItem("itemIdent");
Item &Category::getItem(const std::string &iIdent) {
  try {
    return items.at(iIdent);
  } catch (const std::out_of_range &ex) {
    throw NoItemError(iIdent);
  }
}

// TODO Write a function, deleteItem, that takes one parameter, an Item
//  identifier (a string), deletes it from the container, and returns true if
//  the Item was deleted. If no Item exists, throw an appropriate exception.
//
// Example:
//  Category cObj{"categoryIdent"};
//  cObj.newItem("itemIdent");
//  bool result = cObj.deleteItem("itemIdent");
bool Category::deleteItem(const std::string &iIdent) {
  if (items.count(iIdent) == 0 || items.erase(iIdent) == 0) {
    throw NoItemError(iIdent);
  }
  return true;
}

// TODO Write an == operator overload for the Category class, such that two
//  Category objects are equal only if they have the same identifier and same
//  Items.
//
// Example:
//  Category cObj1{"categoryIdent1"};
//  cObj1.newItem("itemIdent");
//  Category cObj2{"categoryIdent2"};
//  if(cObj1 == cObj2) {
//    ...
//  }
bool operator==(const Category &lhs, const Category &rhs) {
  return lhs.ident == rhs.ident && lhs.items.size() == rhs.items.size() &&
         std::equal(lhs.items.begin(), lhs.items.end(), rhs.items.begin());
}

nlohmann::json Category::json() const {
  nlohmann::json j = nlohmann::json::object({});

  for (const auto &iIt : items) {
    j[iIt.first] = iIt.second.json();
  }

  return j;
}

// TODO Write a function, str, that takes no parameters and returns a
//  std::string of the JSON representation of the data in the Category.
//
// See the coursework specification for how this JSON should look.
//
// Example:
//  Category cObj{"categoryIdent"};
//  std::string s = cObj.str();
std::string Category::str() const { return json().dump(); }