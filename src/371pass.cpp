// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2021/22)
// Department of Computer Science, Swansea University
//
// Author: Martin Porcheron
//         m.a.w.porcheron@swansea.ac.uk
//
// Canvas: https://canvas.swansea.ac.uk/courses/15581
// -----------------------------------------------------

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <string>

#include "lib_cxxopts.hpp"
#include "371pass.h"
#include "wallet.h"

// TODO Complete this function. You have been provided some skeleton code which
//  retrieves the database file name from cxxopts.
//  1. Construct a DBFile object, open the file, retrieve the JSON text as a
//     string. If you have an issue opening or reading the file, it should be
//     be replaced. This is usually a **very bad idea** in normal application
//     development (as the user could lose data) but to keep things simple for
//     this coursework, we will do this.
//  2. Construct a Wallet object. If you were able to extract JSON data, pass
//     this to the Wallet constructor, otherwise construct an empty Wallet.
//  3. Take the appropriate action based on the program arguments (see the
//     coursework specification for details).
//  4. Save the updated Wallet object to the JSON file
//
// Some commented out code has been provided. Using some of this will be
// demonstrated in the coursework video on Canvas. Remember, this coursework is
// meant to be challenging and testing your understanding of programming in C++.
// Part of the challenge is figuring things out on your own. That is a major
// part of the software development.
int Pass::run(int argc, char *argv[]) {
  auto options = Pass::cxxoptsSetup();
  try {
    auto args = options.parse(argc, argv);

    // Print the help usage if requested
    if (args.count("help")) {
      std::cout << options.help() << '\n';
      return 0;
    }

    // Open the database and construct the Wallet
    const std::string db = args["db"].as<std::string>();
    Wallet wObj {};
    try {
      wObj.load(db);
    } catch (const std::runtime_error& ex) {
      throw std::invalid_argument("db");
    }

    const Action a = parseActionArgument(args);
    switch(a) {
      case Action::CREATE:
//        throw std::runtime_error("create not implemented");
        if (!performCreate(wObj, args)) {
          throw std::runtime_error("create failed due to unknown error");
        }
        if (!wObj.save(db)) {
          throw std::runtime_error("save to disk failed due to unknown error");
        }
        break;

      case Action::READ:
        if (!performRead(wObj, args)) {
          throw std::runtime_error("read failed due to unknown error");
        }
        break;

      case Action::UPDATE:
        throw std::runtime_error("update not implemented");
//        if (!performUpdate(wObj, args)) {
//          throw std::runtime_error("update failed due to unknown error");
//        }
        break;

      case Action::DELETE:
//        throw std::runtime_error("delete not implemented");
        if (!performDelete(wObj, args)) {
          throw std::runtime_error("delete failed due to unknown error");
        }
        if (!wObj.save(db)) {
          throw std::runtime_error("save to disk failed due to unknown error");
        }
        break;

      default:
        throw std::runtime_error("Unknown action not implemented");
        break;
    }

  } catch (const cxxopts::missing_argument_exception& ex) {
    std::cerr << "You have missing value for the " << ex.what() << " argument."
                                                                   "\n\n";
    std::cerr << options.help() << '\n';
    return 1;
  } catch (const std::invalid_argument& ex) {
    std::cerr << "The " << ex.what() << " argument is invalid.\n\n";
    std::cerr << options.help() << '\n';
    return 1;
  } catch (const std::exception& ex) {
    std::cerr << "Unexpected exception: " << ex.what() << "\n\n";
    std::cerr << options.help() << '\n';
    return 2;
  } catch (...) {
    std::cerr << "Unknown error\n";
    return 1;
  }

  return 0;
}

// Create a cxxopts instance
cxxopts::Options Pass::cxxoptsSetup() {
  cxxopts::Options cxxopts(
      "371pass",
      "Student ID: " + STUDENT_NUMBER + "\n");

  cxxopts.add_options()(
      "db",
      "Filename of the 371pass database",
      cxxopts::value<std::string>()->default_value("database.json"))(

      "action",
      "Action to take, can be: 'create', 'read', 'update', 'delete'.",
      cxxopts::value<std::string>())(

      "category",
      "Apply action to a category (e.g., if you want to add a category, set the"
      " action argument to 'add' and the category argument to your chosen"
      " category identifier).",
      cxxopts::value<std::string>())(

      "item",
      "Apply action to an item (e.g., if you want to add an item, set the "
      "action argument to 'add', the category argument to your chosen category "
      "identifier and the item argument to the item identifier).",
      cxxopts::value<std::string>())(

      "entry",
      "Apply action to an entry (e.g., if you want to add an entry, set the "
      "action argument to 'add', the category argument to your chosen category "
      "identifier, the item argument to your chosen item identifier, and the "
      "entry argument to the string 'key,value'). If there is no comma, an "
      "empty entry is inserted. If you are simply retrieving an entry, set the "
      "entry argument to the 'key'.",
      cxxopts::value<std::string>())(

      "h,help",
      "Print usage.");

  return cxxopts;
}

// TODO Check through, understand, and edit this function so that it works in a
//  case-insensitive way (e.g., an argument value of 'CREATE' would still work).
//  If an invalid value is given in a string, throw an std::invalid_argument
//  exception.
Pass::Action Pass::parseActionArgument(cxxopts::ParseResult& args) {
  try {
  std::string input = args["action"].as<std::string>();

  // TODO map remove this line
  std::transform(input.begin(), input.end(), input.begin(),
                 [](unsigned char c) { return std::tolower(c); });

  static std::unordered_map<std::string, Action> mapping = {
      {"create", Action::CREATE},
      {"read",   Action::READ},
      {"update", Action::UPDATE},
      {"delete", Action::DELETE}};

    return mapping.at(input);
  } catch(const cxxopts::option_has_no_value_exception& ex) {
    throw std::invalid_argument("action");
  } catch (const std::out_of_range& ex) {
    throw std::invalid_argument("action");
  }
}

// TODO Write a function, getJSON, that retrieves, as a std::string, the JSON
//  representation for a Wallet.
//
// This function has been implemented for you, but you may wish to adjust it.
const std::string Pass::getJSON(Wallet& wObj) {
  return wObj.str();
}

// TODO Write a function, getJSON, that retrieves, as a std::string, the JSON
//  representation for a specific Category in a Wallet.
//
// This function has been implemented for you, but you may wish to adjust it.
const std::string Pass::getJSON(Wallet& wObj,
                                const std::string& c) {
  auto cObj = wObj.getCategory(c);
  return cObj.str();
}

// TODO Write a function, getJSON, that retrieves, as a std::string, the JSON
//  representation for a specific Item in a Wallet.
//
// This function has been implemented for you, but you may wish to adjust it.
const std::string Pass::getJSON(Wallet& wObj,
                                const std::string& c,
                                const std::string& i) {
  auto cObj = wObj.getCategory(c);
  const auto iObj = cObj.getItem(i);
  return iObj.str();
}

// TODO Write a function, getJSON, that retrieves, as a std::string, the JSON
//  representation for a specific entry in a Wallet.
//
// This function has been implemented for you, but you may wish to adjust it.
const std::string Pass::getJSON(Wallet& wObj,
                                const std::string& c,
                                const std::string& i,
                                const std::string& e) {
  auto cObj = wObj.getCategory(c);
  auto iObj = cObj.getItem(i);
  return iObj.getEntry(e);
}

bool Pass::performCreate(Wallet& wObj, cxxopts::ParseResult& args) {
  if (args.count("category")) {
    const std::string c = args["category"].as<std::string>();
    Category& cObj = wObj.newCategory(c);

    if (args.count("item")) {
      const std::string i = args["item"].as<std::string>();
      Item& iObj = cObj.newItem(i);

      if (args.count("entry")) {
        const std::string e = args["entry"].as<std::string>();

        std::string key = e;
        std::string value;

        try {
          key = e.substr(0, e.find(','));
          value = e.substr(e.find(','));
        } catch (const std::out_of_range& ex) { /* do nothing */ }

        iObj.addEntry(key, value);
      }
    }

    return true;

  }

  throw std::runtime_error("must provide a category, item or entry to create");
}

bool Pass::performRead(Wallet& wObj, cxxopts::ParseResult& args) noexcept {
  if (args.count("category")) {
    const std::string c = args["category"].as<std::string>();

    if (args.count("item")) {
      const std::string i = args["item"].as<std::string>();

      if (args.count("entry")) {
        const std::string e = args["entry"].as<std::string>();

        std::cout << getJSON(wObj, c, i, e);
      } else {
        std::cout << getJSON(wObj, c, i);
      }
    } else {
      std::cout << getJSON(wObj, c);
    }
  } else {
    std::cout << getJSON(wObj);
  }

  return true;
}

// If there is a category, item, and entry key, delete just the entry
// If there is a category and item but NO entry key, delete the item (and all
//    entries)
// If there is only a category, delete the category (and all items and entries)
// If there is no category, throw a std::invalid_argument with message
//  'category'
// If a non-existant category, item, or entry key is supplied, throw a
//   std::invalid_argument with the message of the problematic argument
bool Pass::performDelete(Wallet& wObj, cxxopts::ParseResult& args) {
  if (args.count("category")) {
    const std::string c = args["category"].as<std::string>();

    if (!wObj.containsCategory(c)) {
      throw std::invalid_argument("category");
    }

    Category& cObj = wObj.getCategory(c);

    if (args.count("item")) {
      const std::string i = args["item"].as<std::string>();

      if (!cObj.containsItem(i)) {
        throw std::invalid_argument("item");
      }

      Item& iObj = cObj.getItem(i);

      if (args.count("entry")) {
        // delete entry
        const std::string e = args["entry"].as<std::string>();

        if (!iObj.containsEntry(e)) {
          throw std::invalid_argument("entry");
        }

        return iObj.deleteEntry(e);
      } else {
        // delete item
        return cObj.deleteItem(i);
      }
    } else {
      // delete category
      return wObj.deleteCategory(c);
    }
  }

  throw std::runtime_error("must provide a category, item or entry to delete");
}