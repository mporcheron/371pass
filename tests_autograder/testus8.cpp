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
// This file tests 371pass for creating an entry, Item
// and Category all in one go.
// -----------------------------------------------------

#include "../src/lib_catch.hpp"

#include <fstream>
#include <iostream>
#include <string>

#include "../src/lib_cxxopts.hpp"
#include "../src/lib_cxxopts_argv.hpp"

#include "../src/371pass.h"

SCENARIO("An entry, Item, and Category can be created all in one go.",
         "[args][extended]") {

  const std::string filePath = "./testdatabasealt.json";

  auto fileExists = [](const std::string &path) {
    return std::ifstream(path).is_open();
  };

  auto writeFileContents = [](const std::string &path,
                              const std::string &contents) {
    // Not a robust way to do this, but here it doesn't matter so much, if it
    // goes wrong we'll fail the test anyway…
    std::ofstream f{path};
    f << contents;
  };

  GIVEN("a valid path to a reset database JSON file") {

    // Reset the file...
    REQUIRE(fileExists(filePath));
    REQUIRE_NOTHROW(writeFileContents(filePath, "{}"));

    const std::string testCategory = "TestCategory";
    const std::string testItem = "TestItem";
    const std::string testEntryKey = "TestEntryKey";
    const std::string testEntryValue = "TestEntryValue";
    const std::string testEntry = testEntryKey + "," + testEntryValue;

    WHEN("the db program argument is '" + filePath +
         "', the action program argument is 'create'") {

      AND_WHEN("and the category program argument is '" + testCategory + "'") {

        AND_WHEN("and the item program argument is '" + testItem + "'") {

          AND_WHEN("and the entry program argument is '" + testEntry + "'") {

            Argv argvObj({
                "test",
                "--db",
                filePath.c_str(),
                "--action",
                "create",
                "--category",
                testCategory.c_str(),
                "--item",
                testItem.c_str(),
                "--entry",
                testEntry.c_str(),
            });
            auto **argv = argvObj.argv();
            auto argc = argvObj.argc();

            THEN("no exception is thrown") {

              REQUIRE_NOTHROW(App::run(argc, argv));

              AND_WHEN("loading the saved file into a new Wallet "
                       "object") {

                Wallet wObj1{};
                REQUIRE(wObj1.empty());
                REQUIRE_NOTHROW(wObj1.load(filePath));

                THEN("the new Wallet will contain the Category and "
                     "Item objects and entry") {

                  REQUIRE_NOTHROW(wObj1.getCategory(testCategory));
                  REQUIRE(wObj1.getCategory(testCategory).size() == 1);
                  REQUIRE_NOTHROW(
                      wObj1.getCategory(testCategory).getItem(testItem));
                  REQUIRE(wObj1.getCategory(testCategory)
                              .getItem(testItem)
                              .size() == 1);
                  REQUIRE(wObj1.getCategory(testCategory)
                              .getItem(testItem)
                              .getEntry(testEntryKey) == testEntryValue);

                } // THEN

              } // AND_WHEN

            } // AND_WHEN

          } // AND_WHEN

        } // AND_WHEN

      } // AND_WHEN

    } // WHEN

  } // GIVEN

} // SCENARIO