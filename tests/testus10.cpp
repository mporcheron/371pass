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
// This file tests that the conversion to JSON functions
// do not return null for empty objects.
// -----------------------------------------------------

#include "../src/lib_catch.hpp"

#include <fstream>
#include <iostream>
#include <string>

#include "../src/lib_cxxopts.hpp"
#include "../src/lib_cxxopts_argv.hpp"

#include "../src/wallet.h"
#include "../src/category.h"
#include "../src/item.h"

SCENARIO("When converted to JSON, an empty Wallet will be represented as {}",
         "[wallet][extended]") {

  GIVEN("an empty Wallet object") {

    Wallet wObj1 {};
    REQUIRE(wObj1.empty());

    WHEN("converted to a JSON string representation") {

      THEN("the value will be '{}'") {

        REQUIRE(wObj1.str().find("{}") == 0);

      } // THEN

    } // WHEN

  } // GIVEN

} // SCENARIO

SCENARIO("When converted to JSON, an empty Category will be represented as {}",
         "[category][extended]") {

  GIVEN("an empty Category object") {

    Category cObj1 {"test"};
    REQUIRE(cObj1.empty());

    WHEN("converted to a JSON string representation") {

      THEN("the value will be '{}'") {

        REQUIRE(cObj1.str().find("{}") == 0);

      } // THEN

    } // WHEN

  } // GIVEN

} // SCENARIO

SCENARIO("When converted to JSON, an empty Item will be represented as {}",
         "[item][extended]") {

  GIVEN("an empty Item object") {

    Item iObj1 {"test"};
    REQUIRE(iObj1.empty());

    WHEN("converted to a JSON string representation") {

      THEN("the value will be '{}'") {

        REQUIRE(iObj1.str().find("{}") == 0);

      } // THEN

    } // WHEN

  } // GIVEN

} // SCENARIO