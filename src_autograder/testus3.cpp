// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2021/22)
// Department of Computer Science, Swansea University
//
// Author: Martin Porcheron
//         m.a.w.porcheron@swansea.ac.uk
//
// Canvas: https://canvas.swansea.ac.uk/courses/24793
// -----------------------------------------------------
// Catch2 — https://github.com/catchorg/Catch2
// Catch2 is licensed under the BOOST license
// -----------------------------------------------------
// This file contains tests for the newItem function
// in Category objects.
// -----------------------------------------------------

#include "lib_catch.hpp"

#include <string>

#include "lib_cxxopts.hpp"
#include "lib_cxxopts_argv.hpp"

#include "category.h"
#include "item.h"

SCENARIO("An empty Item can be constructed successfully in an empty Category",
         "[category][extended]") {

  const std::string ident = "Test";

  GIVEN("the item identifier '" + ident + "' and an empty Category object") {

    Category cObj1{ident};
    REQUIRE(cObj1.empty());

    WHEN("a new Item object is constructed") {

      cObj1.newItem(ident);

      THEN("the Category will contain 1 Item, retrievable by the ident") {

        REQUIRE(cObj1.size() == 1);
        REQUIRE_NOTHROW(cObj1.getItem(ident));

      } // THEN

    } // WHEN

  } // GIVEN

} // SCENARIO

SCENARIO("Creating an Item in a Category with an Item with the same ident will "
         "return the existing object",
         "[category][extended]") {

  const std::string ident = "Test";

  GIVEN("the item identifier '" + ident + "' and an empty Category object") {

    Category cObj1{ident};
    REQUIRE(cObj1.empty());

    WHEN("a new Item object is constructed") {

      Item &iObj1 = cObj1.newItem(ident);

      THEN("the Category will contain 1 Item, retrievable by the ident") {

        REQUIRE(cObj1.size() == 1);
        REQUIRE(cObj1.getItem(ident) == iObj1);

      } // THEN

      WHEN("another new Item object is constructed with the same ident is "
           "attempted to be added") {

        Item &iObj2 = cObj1.newItem(ident);

        THEN("the same Item object will be returned") {

          REQUIRE(&iObj1 == &iObj2);

        } // THEN

      } // WHEN

    } // WHEN

  } // GIVEN

} // SCENARIO