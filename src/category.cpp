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

#include "category.h"

// TODO Write a constructor that takes one parameter, a string identifer
//  and initialises the object and member data.
Category::Category(std::string ident) : ident(ident), items() { }

// TODO Write a function, getIdent, that returns the identifier for the
//  Category.

// TODO Write a function, setIdent, that takes one parameter, a string for a new
//  Category identifier, and updates the member variable. It returns nothing.

// TODO Write a function, newItem, that takes one parameter, an item identifier,
//  and returns the Item object as a reference. If an object with the same
//  identifier already exists, then the existing object should be returned.
//  Throw a std::runtime_error if the Item object cannot be inserted into the
//  container.
Item& Category::newItem(const std::string& ident) {
  const auto& result = items.find(ident);

  if (result == items.end()) {
    Item i(ident);
    const auto& [newResult, success] = items.insert(std::pair{ident, i});

    if (!success) {
      throw std::runtime_error("Could not insert item: " + ident);
    }

    return newResult->second;
  }

  return result->second;
}

// TODO Write a function, addItem, that takes one parameter, an Item object,
//  and returns true if the object was successfully inserted. If an object with
//  the same identifier already exists, then the contents should be merged but
//  still return true.
bool Category::addItem(Item item) {
  const auto result = items.find(item.getIdent());

  if (result == items.end()) {
    const std::string& ident = item.getIdent();
    const auto [newResult, success] = items.insert(std::pair{ident, item});
    return success;
  }

  Item& existingItem = result->second;
  for (auto entry = item.begin(); entry != item.end(); entry++) {
    existingItem.addEntry(entry->first, entry->second);
  }

  return true;
}

// TODO Write a function, getItem, that takes one parameter, an Item
//  identifier and returns the Item. If no Item exists, throw an appropriate
//  exception.
Item& Category::getItem(const std::string& ident) {
  return items.at(ident);
}

// TODO Write a function, deleteItem, that takes one parameter, an Item
//  identifier, deletes it from the container, and returns true if the Item was
//  deleted. If no Item exists, return false.
bool Category::deleteItem(const std::string& ident) {
  return items.erase(ident) == 1;
}

// TODO Write an == operator overload for the Category class, such that two
//  Category objects are equal only if they have the same identifier and same
//  Items.
bool operator==(const Category& lhs, const Category& rhs) {
  return lhs.ident == rhs.ident &&
         lhs.items.size() == rhs.items.size() &&
         std::equal(lhs.items.begin(), lhs.items.end(), rhs.items.begin());
}

nlohmann::json Category::json() const {
  nlohmann::json j = nlohmann::json::object({});

  for (auto iIt = cbegin(); iIt != cend(); iIt++) {
    j[iIt->first] = iIt->second.json();
  }

  return j;
}

// TODO Write a function, str, that takes no parameters and returns a
//  std::string of the JSON representative of the data in the Category.
//
// Example:
//  Category c {"ident"};
//  std::string s = c.str();
std::string Category::str() const {
  return json().dump();
}