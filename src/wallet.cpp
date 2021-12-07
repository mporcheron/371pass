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

#include "lib_json.hpp"

#include "category.h"
#include "wallet.h"

using json = nlohmann::json;

// TODO Write a Wallet constructor that takes no parameters and constructs an
//  empty wallet.
Wallet::Wallet() : categories() { }

// TODO Write a function, size, that takes no parameters and returns an unsigned
//  int of the number of categories the Wallet contains.

// TODO Write a function, empty, that takes no parameters and returns true
//  if the number of categories in the Wallet is zero, false otherwise.

// TODO Write a function, addCategory, that takes one parameter, a category
//  identifier, and returns the Category object as a reference. If an object
//  with the same identifier already exists, then the existing object should be
//  returned. Throw a std::runtime_error if the Category object cannot be
//  inserted into the container.
Category& Wallet::addCategory(const std::string& ident) {
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

// TODO Write a function, parse, that takes one parameter, a std::string,
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
//  w.parse("database.json");
void Wallet::parse(std::string& filePath) {
  std::ifstream fileStream;

  // Open the file
  try {
    fileStream.open(filePath, std::ifstream::in);
  } catch (const std::runtime_error &ex) {
    throw std::runtime_error("Failed to open file " + filePath);
  }

  if (!fileStream.is_open()) {
    throw std::runtime_error("Failed to open file " + filePath);
  }

  // Deserialize the JSON
  json j;
  try {
    fileStream >> j;
  } catch (const json::exception& ex) {
    const std::string err = "Invalid JSON: " +
                            std::string(ex.what());
    throw std::runtime_error(err);
  }

  // Import the data
  std::string itemIdent, entryIdent;
  for (auto& category : j.items()) {
    Category& c = addCategory(category.key());

    for (auto& item : category.value().items()) {
      Item& i = c.addItem(item.key());

      for (auto& entry : item.value().items()) {
        i.addEntry(entry.key(), entry.value());
      }
    }
  }
}

// TODO Write a function, str, that takes no parameters and returns a
//  std::string of the JSON representative of the data in the Wallet.
//
// Example:
//  Wallet w;
//  w.parse("{ "Category" : { "Item" : { "Entry" : "Value" ... } ... } ... });
//  std::string s = w.str();
std::string Wallet::str() const {
  json j;

  for (auto cIt = cbegin(); cIt != cend(); cIt++) {
    const auto &category = cIt->second;
    for (auto iIt = category.cbegin(); iIt != category.cend(); iIt++) {
      const auto &item = iIt->second;
      for (auto eIt = item.cbegin(); eIt != item.cend(); eIt++) {
        j[cIt->first][iIt->first][eIt->first] = eIt->second;
      }
    }
  }

  const std::string result = j.dump();

  if (result == "null") {
    return "{}";
  }

  return result;
}