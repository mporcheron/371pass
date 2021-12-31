// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2021/22)
// Department of Computer Science, Swansea University
//
// Author: Martin Porcheron
//         m.a.w.porcheron@swansea.ac.uk
//
// Canvas: https://canvas.swansea.ac.uk/courses/24793
// -----------------------------------------------------

#include <exception>
#include <fstream>
#include <iostream>
#include <stdexcept>

#include "category.h"
#include "wallet.h"

// TODO Write a Wallet constructor that takes no parameters and constructs an
//  empty wallet.
//
// Example:
//  Wallet wObj{};
Wallet::Wallet() : categories() {
  /* do nothing */
}

// TODO Write a function, size, that takes no parameters and returns an unsigned
//  int of the number of categories the Wallet contains.
//
// Example:
//  Wallet wObj{};
//  auto size = wObj.size();

// TODO Write a function, empty, that takes no parameters and returns true
//  if the number of categories in the Wallet is zero, false otherwise.
//
// Example:
//  Wallet wwObj{};
//  auto isEmpty = wObj.empty();

// TODO Write a function, newCategory, that takes one parameter, a category
//  identifier, and returns the Category object as a reference. If an object
//  with the same identifier already exists, then the existing object should be
//  returned. Throw a std::runtime_error if the Category object cannot be
//  inserted into the container.
//
// Example:
//  Wallet wObj{};
//  wObj.newCategory("categoryIdent");
Category &Wallet::newCategory(const std::string &cIdent) {
  const auto result = categories.find(cIdent);

  if (result == categories.end()) {
    Category c(cIdent);
    const auto &insertResult = categories.insert({cIdent, c});

    if (!insertResult.second) {
      throw AddCategoryError(cIdent);
    }

    return insertResult.first->second;
  }

  return result->second;
}

// TODO Write a function, addCategory, that takes one parameter, a Category
//  object, and returns true if the object was successfully inserted. If an
//  object with the same identifier already exists, then the contents should be
//  merged and then return false. Throw a std::runtime_error if the Category
//  object cannot be inserted into the container for whatever reason.
//
// Example:
//  Wallet wObj{};
//  Category cObj{"categoryIdent"};
//  wObj.addCategory(cObj);
bool Wallet::addCategory(Category category) {
  try {
    const auto result = categories.find(category.getIdent());

    if (result == categories.end()) {
      const std::string &ident = category.getIdent();
      const auto &insertResult =
          categories.insert({ident, category});
      return insertResult.second;
    }

    Category &existingCategory = result->second;
    for (auto &item : category) {
      existingCategory.addItem(item.second);
    }

    return false;
  } catch (const std::exception &ex) {
    throw AddCategoryError(category.getIdent());
  }
}

// TODO Write a function, getCategory, that takes one parameter, a Category
//  identifier and returns the Category. If no Category exists, throw an
//  appropriate exception.
//
// Example:
//  Wallet wObj{};
//  wObj.newCategory("categoryIdent");
//  auto cObj = wObj.getCategory("categoryIdent");
Category &Wallet::getCategory(const std::string &cIdent) {
  try {
    return categories.at(cIdent);
  } catch (const std::out_of_range &ex) {
    throw NoCategoryError(cIdent);
  }
}

// TODO Write a function, deleteEntry, that takes one parameter, a Category
//  identifier, and deletes it from the container, and returns true if the
//  Category was deleted. If no Category exists, throw an appropriate exception.
//
// Example:
//  Wallet wObj{};
//  wObj.newCategory("categoryIdent");
//  wObj.deleteCategory("categoryIdent");
bool Wallet::deleteCategory(const std::string &cIdent) {
  if (categories.erase(cIdent) == 0) {
    throw NoCategoryError(cIdent);
  }
  return true;
}

// TODO Write a function, load, that takes one parameter, a std::string,
//  containing the filename for the database. Open the file, read the contents,
//  and populates the container for this Wallet. If the file does open throw an
//  appropriate exception (either std::runtime_error or a derived class).
//
// A note on clashes:
//  If you encounter two categories with the same key, the categories should be
//  merged (not replaced!). If you encounter two items with the same key in the
//  same category, the items should be merged (not replaced!). If you encounter
//  two entries with the same key in the same item, the entries should be merged
//  (undefined as to which value is picked). Two items in different categories
//  can have the same key, as can two entries in different items.
//
// JSON formatting:
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
// More help:
//  To help you with this function, I've selected the nlohmann::json
//  library that you must use for your coursework. Read up on how to use it
//  here: https://github.com/nlohmann/json. You may not use any other external
//  library other than the one I have provided. You may choose to process the
//  JSON yourself without the help of the library but I guarantee this will be
//  more work.
//
//  Understanding how to use external libraries is part of this coursework! You
//  will need to use this file to deserialize the JSON from string
//  to the JSON object provided by this library. Don't just look at the code
//  provided below, or in the README on the GitHub and despair. Google search,
//  look around, try code out in a separate file to all figure out how to use
//  this library.
//
//  Once you have deserialized the JSON string into an object, you will need to
//  loop through this object, constructing Category and Item objects according
//  to the JSON data in the file.
//
// Example:
//  Wallet wObj{};
//  wObj.load("database.json");
void Wallet::load(const std::string &filePath) {
  std::ifstream fileStream;

  // Open the file
  try {
    fileStream.open(filePath, std::ifstream::in);
  } catch (const std::runtime_error &ex) {
    throw FileIOError(FileIOError::READ, filePath);
  }

  if (!fileStream.is_open()) {
    throw FileIOError(FileIOError::READ, filePath);
  }

  // Deserialize the JSON
  nlohmann::json j;
  try {
    fileStream >> j;
  } catch (const nlohmann::json::exception &ex) {
    const std::string err = "Invalid JSON: " + std::string(ex.what());
    throw FileIOError(FileIOError::PARSE, filePath);
  }

  // Import the data
  std::string itemIdent, entryIdent;
  for (auto &category : j.items()) {
    Category &c = newCategory(category.key());

    for (auto &item : category.value().items()) {
      Item &i = c.newItem(item.key());

      for (auto &entry : item.value().items()) {
        i.addEntry(entry.key(), entry.value());
      }
    }
  }
}

// TODO Write a function ,save, that takes one parameter, the path of the file
//  to write the database to. The function should serialise the Wallet object
//  as JSON.
//
// Example:
//  Wallet wObj{};
//  wObj.load("database.json");
//  ...
//  wObj.save("database.json");
bool Wallet::save(const std::string &filePath) const {
  std::ofstream fileStream;

  // Open the file
  try {
    fileStream.open(filePath, std::ofstream::out);
  } catch (const std::runtime_error &ex) {
    throw FileIOError(FileIOError::WRITE, filePath);
  }

  if (!fileStream.is_open()) {
    throw FileIOError(FileIOError::WRITE, filePath);
  }

  // Write the JSON
  fileStream << json();

  return true;
}

// TODO Write an == operator overload for the Wallet class, such that two
//  Wallet objects are equal only if they have the exact same data.
//
// Example:
//  Wallet wObj1{};
//  Wallet wObj2{};
//  if(wObj1 == wObj2) {
//    ...
//  }
bool operator==(const Wallet &lhs, const Wallet &rhs) {
  return lhs.categories.size() == rhs.categories.size() &&
         std::equal(lhs.categories.begin(), lhs.categories.end(),
                    rhs.categories.begin());
}

nlohmann::json Wallet::json() const {
  nlohmann::json j = nlohmann::json::object({});

  for (const auto &cIt : categories) {
    j[cIt.first] = cIt.second.json();
  }

  return j;
}

// TODO Write a function, str, that takes no parameters and returns a
//  std::string of the JSON representation of the data in the Wallet.
//
// Hint:
//  See the coursework specification for how this JSON should look.
//
// Example:
//  Wallet wObj{};
//  std::string s = wObj.str();
std::string Wallet::str() const { return json().dump(); }