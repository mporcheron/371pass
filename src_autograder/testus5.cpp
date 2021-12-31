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
// This file contains tests for the newCategory
// function in Wallet objects.
// -----------------------------------------------------

#include "lib_catch.hpp"

#include <string>

#include "lib_cxxopts.hpp"
#include "lib_cxxopts_argv.hpp"

#include "wallet.h"
#include "category.h"

SCENARIO("An empty Category can be constructed successfully in an empty Wallet",
         "[wallet][extended]") {

  const std::string ident = "Test";

  GIVEN("an empty Wallet object") {

    Wallet wObj1{};
    REQUIRE(wObj1.empty());

    WHEN("a new Category object is constructed with identifier '" + ident + "'") {

      wObj1.newCategory(ident);

      THEN("the Wallet will contain 1 Category, retrievable by the ident") {

        REQUIRE(wObj1.size() == 1);
        REQUIRE_NOTHROW(wObj1.getCategory(ident));

      } // THEN

    } // WHEN

  } // GIVEN

} // SCENARIO

SCENARIO("Creating a Category in a Wallet with a Category with the same ident will "
         "return the existing object",
         "[wallet][extended]") {

  const std::string ident = "Test";

  GIVEN("an empty Wallet object") {

    Wallet wObj1{};
    REQUIRE(wObj1.empty());

    WHEN("a new Category object is constructed with identifier '" + ident + "'") {

      Category &cObj1 = wObj1.newCategory(ident);

      THEN("the Wallet will contain 1 Item, retrievable by the ident") {

        REQUIRE(wObj1.size() == 1);
        REQUIRE(wObj1.getCategory(ident) == cObj1);

      } // THEN

      WHEN("another new Category object is constructed with the same ident is "
           "attempted to be added") {

        Category &cObj2 = wObj1.newCategory(ident);

        THEN("the same Category object will be returned") {

          REQUIRE(&cObj1 == &cObj2);

        } // THEN

      } // WHEN

    } // WHEN

  } // GIVEN

} // SCENARIO