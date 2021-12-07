// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2021/22)
// Department of Computer Science, Swansea University
//
// Author: Martin Porcheron
//         m.a.w.porcheron@swansea.ac.uk
//
// Canvas: https://canvas.swansea.ac.uk/courses/15581
// -----------------------------------------------------

#include "category.h"

#include <string>

// TODO Write a constructor that takes one parameter, a string identifer
//  and initialises the object and member data.
Category::Category(std::string ident) : ident(ident), items() { }

// TODO Write a function, addItem, that takes one parameter, an item identifier,
//  and returns the Item object as a reference. If an object with the same
//  identifier already exists, then the existing object should be returned.
//  Throw a std::runtime_error if the Item object cannot be inserted into the
//  container.
Item& Category::addItem(const std::string& ident) {
  const auto result = items.find(ident);

  if (result == items.end()) {
    Item i(ident);
    const auto [newResult, success] = items.insert(std::pair{ident, i});

    if (!success) {
      throw std::runtime_error("Could not insert item: " + ident);
    }

    return newResult->second;
  }

  return result->second;
}