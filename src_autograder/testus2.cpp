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
// This file contains tests for the merging in addItem
// in Category objects.
// -----------------------------------------------------

#include "lib_catch.hpp"

#include <string>

#include "lib_cxxopts.hpp"
#include "lib_cxxopts_argv.hpp"

#include "category.h"
#include "item.h"

SCENARIO("Multiple Items can be added to and merged in a Category",
         "[category][extended]") {

  const std::string ident = "Test";

  const std::string key1 = "TestKey1";
  const std::string key2 = "TestKey2";

  const std::string value1 = "TestValue1";
  const std::string value2 = "TestValue2";

  GIVEN("a empty Category object with identifier '" + ident + "'") {

    Category cObj1{ident};

    REQUIRE(cObj1.empty());

    AND_GIVEN("two Items with identifier '" + ident +
              "' and a different entry in each ('" + key1 + "', ''" + key2 +
              "')") {

      Item iObj1{ident};
      Item iObj2{ident};

      REQUIRE(iObj1.empty());
      REQUIRE(iObj2.empty());

      iObj1.addEntry(key1, value1);
      iObj2.addEntry(key2, value2);

      WHEN("adding one Item to the Category") {

        THEN("true is returned") {

          REQUIRE(cObj1.addItem(iObj1) == true);

          AND_THEN("the Category contains 1 Item") {

            REQUIRE(cObj1.size() == 1);
            REQUIRE_FALSE(cObj1.empty());

            AND_WHEN("adding the second Item to the Category") {

              THEN("false is returned") {

                REQUIRE(cObj1.addItem(iObj2) == false);

                AND_THEN("the Category contains 1 Item with ident '" + ident +
                         "'") {

                  REQUIRE(cObj1.size() == 1);
                  REQUIRE_FALSE(cObj1.empty());
                  REQUIRE_NOTHROW(cObj1.getItem(ident));

                } // AND_THEN

                AND_THEN("both entries are in the same Item") {

                  REQUIRE(cObj1.getItem(ident).size() == 2);
                  REQUIRE(cObj1.getItem(ident).getEntry(key1) == value1);
                  REQUIRE(cObj1.getItem(ident).getEntry(key2) == value2);

                } // AND_THEN

              } // THEN

            } // AND_THEN

          } // AND_THEN

        } // THEN

      } // WHEN

    } // AND_GIVEN

  } // GIVEN

} // SCENARIO