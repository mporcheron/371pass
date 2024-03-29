// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2021/22)
// Department of Computer Science, Swansea University
//
// Author: Martin Porcheron
//         m.a.w.porcheron@swansea.ac.uk
//
// Canvas: https://canvas.swansea.ac.uk/courses/24793
// -----------------------------------------------------

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>

#include "371pass.h"
#include "lib_cxxopts.hpp"
#include "wallet.h"

// TODO Complete this function. You have been provided some skeleton code which
//  retrieves the database file name from cxxopts.
//  1. Load the database file by calling load() on a Wallet object
//  2. Parse the 'action' argument to decide what action should be taken (
//     create, read, update, or delete). Read is the easiest to implement, and
//     update is the hardest. The details of how these arguments work is in the
//     coursework specification.
//  4. Save the updated Wallet object to the JSON file if there have been
//     changes (calling save() on the Wallet object).
//
// Some commented out code has been provided. Using some of this will be
// demonstrated in the coursework video on Canvas. Remember, this coursework is
// meant to be challenging and testing your understanding of programming in C++.
// Part of the challenge is figuring things out on your own. That is a major
// part of software development.
//
// Example:
//  int main(int argc, char *argv[]) { return App::run(argc, argv); }
int App::run(int argc, char *argv[]) {
  auto options = App::cxxoptsSetup();
  try {
    auto args = options.parse(argc, argv);

    // Print the help usage if requested
    if (args.count("help")) {
      std::cout << options.help() << '\n';
      return 0;
    }

    // Open the database and construct the Wallet
    const std::string db = args["db"].as<std::string>();
    Wallet wObj{};
    try {
      wObj.load(db);
    } catch (const std::runtime_error &ex) {
      throw std::invalid_argument("db");
    }

    const Action a = parseActionArgument(args);
    switch (a) {
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
      //        throw std::runtime_error("read not implemented");
      if (!performRead(wObj, args)) {
        throw std::runtime_error("read failed due to unknown error");
      }
      break;

    case Action::UPDATE:
      //        throw std::runtime_error("update not implemented");
      if (!performUpdate(wObj, args)) {
        throw std::runtime_error("update failed due to unknown error");
      }
      if (!wObj.save(db)) {
        throw std::runtime_error("save to disk failed due to unknown error");
      }
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
    }

  } catch (const cxxopts::missing_argument_exception &ex) {
    std::cerr << "Error: missing " << ex.what() << " argument(s).\n";
    return 1;
  } catch (const MissingArgumentError &ex) {
    std::cerr << "Error: missing " << ex.what() << " argument(s).\n";
    return 1;
  } catch (const InvalidArgumentError &ex) {
    std::cerr << "Error: invalid " << ex.what() << " argument(s).\n";
    return 1;
  } catch (const std::exception &ex) {
    std::cerr << "Unexpected error: " << ex.what() << '\n';
    return 2;
  } catch (...) {
    std::cerr << "Unknown error!\n";
    return 2;
  }

  return 0;
}

// Create a cxxopts instance. You do not need to modify this function.
//
// Example:
//  auto options = App::cxxoptsSetup();
//  auto args = options.parse(argc, argv);
cxxopts::Options App::cxxoptsSetup() {
  cxxopts::Options cxxopts("371pass", "Student ID: " + STUDENT_NUMBER + "\n");

  cxxopts.add_options()(
      "db", "Filename of the 371pass database",
      cxxopts::value<std::string>()->default_value("database.json"))(

      "action", "Action to take, can be: 'create', 'read', 'update', 'delete'.",
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
      "entry argument to the 'key'. If you are updating an entry key, use a : "
      "e.g., oldkey:newkey,newvalue.",
      cxxopts::value<std::string>())(

      "h,help", "Print usage.");

  return cxxopts;
}

// TODO Rewrite this function so that it works. This function should
//  case-insensitively check the action argument retrieved from cxxopts and
//  convert this to a value from the ACTION enum. If an invalid value is given
//  in a string, throw an std::invalid_argument exception.
//
// Example:
//  auto options = App::cxxoptsSetup();
//  auto args = options.parse(argc, argv);
//  App::Action action = parseActionArgument(args);
App::Action App::parseActionArgument(cxxopts::ParseResult &args) {
  try {
    std::string input = args["action"].as<std::string>();

    // TODO map remove this line (write a version of it in the video!)
    std::transform(input.begin(), input.end(), input.begin(),
                   [](unsigned char c) { return std::tolower(c); });

    static std::unordered_map<std::string, Action> mapping = {
        {"create", Action::CREATE},
        {"read", Action::READ},
        {"update", Action::UPDATE},
        {"delete", Action::DELETE}};

    return mapping.at(input);

    // TODO map: use this in the framework: return Action::READ;
  } catch (const cxxopts::option_has_no_value_exception &ex) {
    throw MissingArgumentError("action");
  } catch (const std::out_of_range &ex) {
    throw InvalidArgumentError("action");
  }
}

// TODO Write a function, getJSON, that returns a std::string containing the
//  JSON representation of a Wallet object.
//
// This function has been implemented for you, but you may wish to adjust it.
// You will have to uncomment the code, which has been left commented to ensure
// the coursework framework compiles (i.e., it calls functions that you must
// implement, once you have implemented them you may uncomment this function).
//
// Example:
//  Wallet wObj{};
//  std::cout << getJSON(wObj);
std::string App::getJSON(Wallet &wObj) { return wObj.str(); }

// TODO Write a function, getJSON, that returns a std::string containing the
//  JSON representation of a specific Category in a Wallet object.
//
// This function has been implemented for you, but you may wish to adjust it.
// You will have to uncomment the code, which has been left commented to ensure
// the coursework framework compiles (i.e., it calls functions that you must
// implement, once you have implemented them you may uncomment this function).
//
// Example:
//  Wallet wObj{};
//  std::string c = "category argument value";
//  std::cout << getJSON(wObj, c);
std::string App::getJSON(Wallet &wObj, const std::string &c) {
  auto cObj = wObj.getCategory(c);
  return cObj.str();
}

// TODO Write a function, getJSON, that returns a std::string containing the
//  JSON representation of a specific Item in a Wallet object.
//
// This function has been implemented for you, but you may wish to adjust it.
// You will have to uncomment the code, which has been left commented to ensure
// the coursework framework compiles (i.e., it calls functions that you must
// implement, once you have implemented them you may uncomment this function).
//
// Example:
//  Wallet wObj{};
//  std::string c = "category argument value";
//  std::string i = "item argument value";
//  std::cout << getJSON(wObj, c, i);
std::string App::getJSON(Wallet &wObj, const std::string &c,
                         const std::string &i) {
  auto cObj = wObj.getCategory(c);
  const auto iObj = cObj.getItem(i);
  return iObj.str();
}

// TODO Write a function, getJSON, that returns a std::string containing the
//  JSON representation of a specific Entry in a Wallet object.
//
// This function has been implemented for you, but you may wish to adjust it.
// You will have to uncomment the code, which has been left commented to ensure
// the coursework framework compiles (i.e., it calls functions that you must
// implement, once you have implemented them you may uncomment this function).
//
// Example:
//  Wallet wObj{};
//  std::string c = "category argument value";
//  std::string i = "item argument value";
//  std::string e = "entry argument value";
//  std::cout << getJSON(wObj, c, i, e);
std::string App::getJSON(Wallet &wObj, const std::string &c,
                         const std::string &i, const std::string &e) {
  auto cObj = wObj.getCategory(c);
  auto iObj = cObj.getItem(i);
  return iObj.getEntry(e);
}

bool App::performCreate(Wallet &wObj, cxxopts::ParseResult &args) {
  if (args.count("category")) {
    const std::string c = args["category"].as<std::string>();
    Category &cObj = wObj.newCategory(c);

    if (args.count("item")) {
      const std::string i = args["item"].as<std::string>();
      Item &iObj = cObj.newItem(i);

      if (args.count("entry")) {
        const std::string e = args["entry"].as<std::string>();

        std::string key = e;
        std::string value;

        try {
          auto ePos = e.find(',');
          if (ePos != std::string::npos) {
            key = e.substr(0, ePos);
            value = e.substr(ePos + 1);
          } else {
            value = "";
          }
        } catch (const std::out_of_range &ex) {
          throw InvalidArgumentError("entry");
        }

        if (key.empty()) {
          throw InvalidArgumentError("entry");
        }

        iObj.addEntry(key, value);
      }
    }

    return true;
  }

  throw MissingArgumentError("category, item or entry");
}

bool App::performRead(Wallet &wObj, cxxopts::ParseResult &args) {
  const bool hasCategory = args.count("category");
  const bool hasItem = args.count("item");
  const bool hasEntry = args.count("entry");

  try {
    if (hasCategory) {
      const std::string c = args["category"].as<std::string>();

      if (c.empty()) {
        throw InvalidArgumentError("category");
      }

      if (hasItem) {
        const std::string i = args["item"].as<std::string>();

        if (i.empty()) {
          throw InvalidArgumentError("item");
        }

        if (hasEntry) {
          const std::string e = args["entry"].as<std::string>();

          if (e.empty()) {
            throw InvalidArgumentError("entry");
          }

            std::cout << getJSON(wObj, c, i, e);
        } else {
          std::cout << getJSON(wObj, c, i);
        }
      } else {
        if (hasEntry) {
          throw MissingArgumentError("item");
        }

        std::cout << getJSON(wObj, c);
      }
    } else {
      if (hasItem || hasEntry) {
        throw MissingArgumentError("category");
      }

      std::cout << getJSON(wObj);
    }
  } catch(const NoCategoryError &ex) {
    throw InvalidArgumentError("category");
  } catch(const NoItemError &ex) {
    throw InvalidArgumentError("item");
  } catch(const NoEntryError &ex) {
    throw InvalidArgumentError("entry");
  }

  return true;
}

// if updating category ident:
//  --action update --category oldident:newident
// if updating item ident:
//  --action update --category ident --item oldident:newident
// if updating entry ident:
//  --action update --category ident --item ident --entry oldident:newident
// if updating entry value:
//  --action update --category ident --item ident --entry ident,newvalue
//
// You can update more than one thing at the same time
//
// Throws std::out_of_range for unknown values
bool App::performUpdate(Wallet &wObj, cxxopts::ParseResult &args) {
  if (args.count("category") > 0) {
    std::string old_, new_;

    // update category ident?
    std::string c = args["category"].as<std::string>();
    auto cPos = c.find(':');
    if (cPos != std::string::npos) {
      try {
        old_ = c.substr(0, cPos);
        new_ = c.substr(cPos + 1);
      } catch (const std::out_of_range &ex) {
        throw std::runtime_error("could not extract new category ident");
      }

      if (new_.empty()) {
        throw InvalidArgumentError("category");
      }

      try {
        Category &cObj = wObj.getCategory(old_);
        cObj.setIdent(new_);
        if (!wObj.addCategory(cObj) || !wObj.deleteCategory(old_)) {
          return false;
        }
        c = new_;
      } catch (const std::out_of_range &ex) {
        throw InvalidArgumentError("category");
      }
    } else if (!wObj.containsCategory(c)) {
      throw InvalidArgumentError("category");
    }

    Category &cObj = wObj.getCategory(c);

    // update item ident?
    if (args.count("item") > 0) {
      std::string i = args["item"].as<std::string>();
      auto iPos = i.find(':');
      if (iPos != std::string::npos) {
        try {
          old_ = i.substr(0, iPos);
          new_ = i.substr(iPos + 1);
        } catch (const std::out_of_range &ex) {
          throw std::runtime_error("could not extract new item ident");
        }

        if (new_.empty()) {
          throw InvalidArgumentError("item");
        }

        Item &iObj = cObj.getItem(old_);
        iObj.setIdent(new_);
        if (!cObj.addItem(iObj) || !cObj.deleteItem(old_)) {
          return false;
        }
        i = new_;
      } else if (!cObj.containsItem(i)) {
        throw InvalidArgumentError("item");
      }

      Item &iObj = cObj.getItem(i);

      // update entry value or ident?
      if (args.count("entry") > 0) {
        std::string e = args["entry"].as<std::string>();
        auto ePos = e.find(':');
        auto evPos = e.find(',');

        if (ePos != std::string::npos) {
          // change key (or key and value)
          std::string newkey_, val_;
          if (evPos != std::string::npos) {
            old_ = e.substr(0, ePos);
            newkey_ = e.substr(ePos + 1, evPos - ePos - 1);
            val_ = e.substr(evPos + 1);
          } else {
            old_ = e.substr(0, ePos);
            newkey_ = e.substr(ePos + 1);
            val_ = iObj.getEntry(old_);
          }

          if (newkey_.empty()) {
            throw InvalidArgumentError("entry");
          }

          try {
            // this will overwrite anything at newkey_
            iObj.addEntry(newkey_, val_);
            iObj.deleteEntry(old_);
          } catch(const std::exception& ex) {
            throw std::runtime_error("could not update entry key or key and value");
          }
        } else if (evPos != std::string::npos) {
          // change value only
          try {
            std::string key_ = e.substr(0, evPos);
            new_ = e.substr(evPos + 1);

            try {
              iObj.addEntry(key_, new_);
            } catch(const std::exception& ex) {
              throw std::runtime_error("could not update entry value");
            }
          } catch (const std::out_of_range &ex) {
            throw std::runtime_error("could not extract new entry value");
          }
        }
      }
    }

    return true;
  }

  throw MissingArgumentError("category, item or entry");
}

// If there is a category, item, and entry key, delete just the entry
// If there is a category and item but NO entry key, delete the item (and all
//    entries)
// If there is only a category, delete the category (and all items and entries)
// If there is no category, throw a std::invalid_argument with message
//  'category'
// If a non-existant category, item, or entry key is supplied, throw a
//   std::invalid_argument with the message of the problematic argument
bool App::performDelete(Wallet &wObj, cxxopts::ParseResult &args) {
  if (args.count("category")) {
    const std::string c = args["category"].as<std::string>();

    if (c.empty() ||!wObj.containsCategory(c)) {
        throw InvalidArgumentError("category");
    }

    Category &cObj = wObj.getCategory(c);

    if (args.count("item")) {
      const std::string i = args["item"].as<std::string>();

      if (c.empty() ||!cObj.containsItem(i)) {
        throw InvalidArgumentError("item");
      }

      Item &iObj = cObj.getItem(i);

      if (args.count("entry")) {
        // delete entry
        const std::string e = args["entry"].as<std::string>();

        if (e.empty() || !iObj.containsEntry(e)) {
          throw InvalidArgumentError("entry");
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

  throw MissingArgumentError("category, item or entry");
}