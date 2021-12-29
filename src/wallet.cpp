// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2021/22)
// Department of Computer Science, Swansea University
//
// Author: Martin Porcheron
//         m.a.w.porcheron@swansea.ac.uk
//
// Canvas: https://canvas.swansea.ac.uk/courses/15581
// -----------------------------------------------------

#include <exception>
#include <fstream>
#include <iostream>
#include <stdexcept>

#include "category.h"
#include "wallet.h"

// TODO Write a Wallet constructor that takes no parameters and constructs an
//  empty wallet.
Wallet::Wallet() : categories() { }

// TODO Write a function, size, that takes no parameters and returns an unsigned
//  int of the number of categories the Wallet containsEntry.

// TODO Write a function, empty, that takes no parameters and returns true
//  if the number of categories in the Wallet is zero, false otherwise.

// TODO Write a function, newCategory, that takes one parameter, a category
//  identifier, and returns the Category object as a reference. If an object
//  with the same identifier already exists, then the existing object should be
//  returned. Throw a std::runtime_error if the Category object cannot be
//  inserted into the container.
Category& Wallet::newCategory(const std::string& ident) {
  const auto result = categories.find(ident);

  if (result == categories.end()) {
    Category c(ident);
    const auto [newResult, success] = categories.insert(std::pair{ident, c});

    if (!success) {
      throw std::runtime_error("Could not insert category: " + ident);
    }

    return newResult->second;
  }

  return result->second;
}

// TODO Write a function, addCategory, that takes one parameter, a Category
//  object, and returns true if the object was successfully inserted. If an
//  object with the same identifier already exists, then the contents should be
//  merged but still return true.
bool Wallet::addCategory(Category category) {
  const auto result = categories.find(category.getIdent());

  if (result == categories.end()) {
    const std::string& ident = category.getIdent();
    const auto[newResult, success] = categories.insert(std::pair{ident,
                                                                    category});
    return success;
  }

  Category& existingCategory = result->second;
  for (auto item = category.begin(); item != category.end(); item++) {
    existingCategory.addItem(item->second);
  }

  return true;
}

// TODO Write a function, getCategory, that takes one parameter, a Category
//  identifier and returns the Category. If no Category exists, throw an
//  appropriate exception.
Category& Wallet::getCategory(const std::string& ident) {
  return categories.at(ident);
}

// TODO Write a function, deleteEntry, that takes one parameter, a Category
//  identifier, and deletes it from the container, and returns true if the
//  Category was deleted. If no category exists, return false.
bool Wallet::deleteCategory(const std::string& ident) {
  return categories.erase(ident) == 1;
}

// TODO Write a function, load, that takes one parameter, a std::string,
//  containing the filename for the database. Open the file, read the contents,
//  and populates the container for this Wallet.
//
// If the file does open throw an appropriate exception (either
//  std::runtime_error or a derived class).
//
//  The JSON file has the following format (see the sample database.json file
//  also provided with the coursework framework):
//    {
//      "Category 1" : {
//        "Item 1":  {
//          "detail 1 key": "detail 1 value",
//          "detail 2 key": "detail 2 value",
//          ...
//        },
//        "Item 2":  {
//          "detail 1 key": "detail 1 value",
//          "detail 2 key": "detail 2 value"
//        },
//        ...
//      },
//      "Category 2": {
//        "Item 1": {
//          "detail 1 key": "detail 1 value"
//        }
//        ...
//      }
//    }
//
// To help you with this function, I've selected the nlohmann::json
// library that you must use for your coursework. Read up on how to use it
// here: https://github.com/nlohmann/json
//
// Understanding how to use external libraries is part of this coursework! You
// will need to use this file to deserialize the JSON from string
// to the JSON object provided by this library.
//
// Once you have deserialized the JSON string into an object, you will need to
// loop through this object, constructing Category and Item objects according
// to the JSON data in the file.
//
// If you encounter two categories with the same key, the categories should be
// merged (not replaced!). If you encounter two items with the same key in the
// same category, the items should be merged (not replaced!). If you encounter
// two details with the same key in the same item, the details should be merged
// (not replaced!). Two items in different categories can have the same key, as
// can two details in different items.
//
// Example:
//  Wallet w;
//  w.load("database.json");
void Wallet::load(const std::string& filePath) {
  std::ifstream fileStream;

  // Open the file
  try {
    fileStream.open(filePath, std::ifstream::in);
  } catch (const std::runtime_error& ex) {
    throw std::runtime_error("Failed to open file for reading: " + filePath);
  }

  if (!fileStream.is_open()) {
    throw std::runtime_error("Failed to open file for reading: " + filePath);
  }

  // Deserialize the JSON
  nlohmann::json j;
  try {
    fileStream >> j;
  } catch (const nlohmann::json::exception& ex) {
    const std::string err = "Invalid JSON: " +
                            std::string(ex.what());
    throw std::runtime_error(err);
  }

  // Import the data
  std::string itemIdent, entryIdent;
  for (auto& category : j.items()) {
    Category& c = newCategory(category.key());

    for (auto& item : category.value().items()) {
      Item& i = c.newItem(item.key());

      for (auto& entry : item.value().items()) {
        i.addEntry(entry.key(), entry.value());
      }
    }
  }
}

bool Wallet::save(const std::string& filePath) const {
  std::ofstream fileStream;

  // Open the file
  try {
    fileStream.open(filePath, std::ifstream::out);
  } catch (const std::runtime_error& ex) {
    throw std::runtime_error("Failed to open file for writing: " + filePath);
  }

  if (!fileStream.is_open()) {
    throw std::runtime_error("Failed to open file for writing: " + filePath);
  }

  // Write the JSON
  fileStream << json();

  return true;
}

nlohmann::json Wallet::json() const {
  nlohmann::json j = nlohmann::json::object({});

  for (auto cIt = cbegin(); cIt != cend(); cIt++) {
    j[cIt->first] = cIt->second.json();
  }

  return j;
}

// TODO Write a function, str, that takes no parameters and returns a
//  std::string of the JSON representative of the data in the Wallet.
//
// Example:
//  Wallet w;
//  w.load("{ "Category" : { "Item" : { "Entry" : "Value" ... } ... } ... });
//  std::string s = w.str();
std::string Wallet::str() const {
  return json().dump();
}