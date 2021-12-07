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

// TODO Write a constructor that takes one parameter, a string identifer
//  and initialises the object and member data.
Item::Item(std::string ident) : ident(ident), entries() {

}

// TODO Write a function, addEntry, that takes two parameters, a detail
//  identifier and value and returns true if the detail was inserted into the
//  container or false otherwise.
bool Item::addEntry(std::string ident, std::string value) {
  entries[ident] = value;
  return true;
}
