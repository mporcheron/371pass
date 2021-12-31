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
// This file contains tests for the merging in
// addCategory in Wallet objects.
// -----------------------------------------------------

#include "lib_catch.hpp"

#include <string>

#include "lib_cxxopts.hpp"
#include "lib_cxxopts_argv.hpp"

#include "category.h"
#include "item.h"
#include "wallet.h"

SCENARIO("Multiple Category objects can be added to and merged in a Wallet",
         "[wallet][extended]") {

  const std::string ident = "TestIdentX";

  const std::string iIdent1 = "TestIdent1";
  const std::string iIdent2 = "TestIdent2";

  GIVEN("a empty Wallet object") {

    Wallet wObj1{};

    REQUIRE(wObj1.empty());

    AND_GIVEN("two Category objects with identifier '" + ident +
              "' and a different Item in each ('" + iIdent1 + "', ''" +
              iIdent2 + "')") {

      Category cObj1{ident};
      Category cObj2{ident};

      REQUIRE(cObj1.empty());
      REQUIRE(cObj2.empty());

      cObj1.addItem(Item{iIdent1});
      cObj2.addItem(Item{iIdent2});

      WHEN("adding one Category to the Wallet") {

        THEN("true is returned") {

          REQUIRE(wObj1.addCategory(cObj1) == true);

          AND_THEN("the Wallet contains 1 Category") {

            REQUIRE(wObj1.size() == 1);
            REQUIRE_FALSE(wObj1.empty());

            AND_WHEN("adding the second Category to the Wallet") {

              THEN("false is returned") {

                REQUIRE(wObj1.addCategory(cObj2) == false);

                AND_THEN("the Wallet contains 1 Category with ident '" + ident +
                         "'") {

                  REQUIRE(wObj1.size() == 1);
                  REQUIRE_FALSE(wObj1.empty());
                  REQUIRE_NOTHROW(wObj1.getCategory(ident));

                } // AND_THEN

                AND_THEN("both Items are in the same Category") {

                  REQUIRE(wObj1.getCategory(ident).size() == 2);
                  REQUIRE_NOTHROW(wObj1.getCategory(ident).getItem(iIdent1));
                  REQUIRE_NOTHROW(wObj1.getCategory(ident).getItem(iIdent1));

                } // AND_THEN

              } // THEN

            } // AND_THEN

          } // AND_THEN

        } // THEN

      } // WHEN

    } // AND_GIVEN

  } // GIVEN

} // SCENARIO