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
// This file tests 371pass output for the database
// argument and 'update' value of the action argument.
// This test works by calling on your program to update
// a category, item, and an entry, and each time
// calls upon your program to load the JSON file to
// check the category/item/entry exists.
// -----------------------------------------------------

#include "../src/lib_catch.hpp"

#include <fstream>
#include <iostream>
#include <string>

#include "../src/lib_cxxopts.hpp"
#include "../src/lib_cxxopts_argv.hpp"

#include "../src/371pass.h"

SCENARIO("The database and action program arguments can be parsed correctly "
         "such that a file can be opened, read, parsed, data updated, and "
         "written to",
         "[args][extended]") {

  const std::string filePath = "./tests/testdatabasealt.json";

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
    REQUIRE_NOTHROW(writeFileContents(
        filePath, "{\"Bank Accounts\":{\"Starling\":{\"Account "
                  "Number\":\"12345678\",\"Name\":\"Mr John Doe\",\"Sort "
                  "Code\":\"12-34-56\"}},\"Websites\":{\"Facebook\":{"
                  "\"password\":\"pass1234fb\",\"url\":\"https://"
                  "www.facebook.com/"
                  "\",\"username\":\"example@gmail.com\"},\"Google\":{"
                  "\"password\":\"pass1234\",\"url\":\"https://www.google.com/"
                  "\",\"username\":\"example@gmail.com\"},\"Twitter\":{"
                  "\"password\":\"r43rfsffdsfdsf\",\"url\":\"https://"
                  "www.twitter.com/\",\"username\":\"example@gmail.com\"}}}"));

    const std::string testCategoryOld = "Websites";
    const std::string testItemOld = "Facebook";
    const std::string testEntryKeyOld = "username";
    const std::string testEntryValueOld = "example@gmail.com";

    const std::string testCategoryNew = "Social Media";
    const std::string testItemNew = "Ugh Facebook";
    const std::string testEntryKeyNew = "email";
    const std::string testEntryValueNew = "example@swansea.ac.uk";

    const std::string testCategory = testCategoryOld + ":" + testCategoryNew;
    const std::string testItem = testItemOld + ":" + testItemNew;

    const std::string testEntryKeyChange =
        testEntryKeyOld + ":" + testEntryKeyNew;
    const std::string testEntryValueChange =
        testEntryKeyNew + "," + testEntryValueNew;

    WHEN("the db program argument is '" + filePath +
         "', the action program argument is 'update'") {

      AND_WHEN("and the category program argument is '" + testCategory + "'") {

        Argv argvObj({"test", "--db", filePath.c_str(), "--action", "update",
                      "--category", testCategory.c_str()});
        auto **argv = argvObj.argv();
        auto argc = argvObj.argc();

        THEN("no exception is thrown") {

          REQUIRE_NOTHROW(App::run(argc, argv));

          AND_WHEN("loading the saved file into a new Wallet object") {

            Wallet wObj1{};
            REQUIRE(wObj1.empty());
            REQUIRE_NOTHROW(wObj1.load(filePath));

            THEN("the new Wallet will contain the Category object") {

              REQUIRE_NOTHROW(wObj1.getCategory(testCategoryNew));
              REQUIRE(wObj1.getCategory(testCategoryNew).size() == 3);
              REQUIRE_NOTHROW(
                  wObj1.getCategory(testCategoryNew).getItem(testItemOld));

            } // THEN

            AND_WHEN("and the item program argument is '" + testItem + "'") {

              Argv argvObj({"test", "--db", filePath.c_str(), "--action",
                            "update", "--category", testCategoryNew.c_str(),
                            "--item", testItem.c_str()});
              auto **argv = argvObj.argv();
              auto argc = argvObj.argc();

              THEN("no exception is thrown") {

                REQUIRE_NOTHROW(App::run(argc, argv));

                AND_WHEN("loading the saved file into a new Wallet object") {

                  Wallet wObj2{};
                  REQUIRE(wObj2.empty());
                  REQUIRE_NOTHROW(wObj2.load(filePath));

                  THEN("the new Wallet will contain the Category and Item "
                       "objects") {

                    REQUIRE_NOTHROW(wObj2.getCategory(testCategoryNew));
                    REQUIRE(wObj2.getCategory(testCategoryNew).size() == 3);
                    REQUIRE_NOTHROW(wObj2.getCategory(testCategoryNew)
                                        .getItem(testItemNew));
                    REQUIRE(wObj2.getCategory(testCategoryNew)
                                .getItem(testItemNew)
                                .size() == 3);
                    REQUIRE(wObj2.getCategory(testCategoryNew)
                                .getItem(testItemNew)
                                .getEntry(testEntryKeyOld) ==
                            testEntryValueOld);

                  } // THEN

                  AND_WHEN("and the entry program argument is '" +
                           testEntryKeyChange + "'") {

                    Argv argvObj({
                        "test",
                        "--db",
                        filePath.c_str(),
                        "--action",
                        "update",
                        "--category",
                        testCategoryNew.c_str(),
                        "--item",
                        testItemNew.c_str(),
                        "--entry",
                        testEntryKeyChange.c_str(),
                    });
                    auto **argv = argvObj.argv();
                    auto argc = argvObj.argc();

                    THEN("no exception is thrown") {

                      REQUIRE_NOTHROW(App::run(argc, argv));

                      AND_WHEN("loading the saved file into a new Wallet "
                               "object") {

                        Wallet wObj3{};
                        REQUIRE(wObj3.empty());
                        REQUIRE_NOTHROW(wObj3.load(filePath));

                        THEN("the new Wallet will contain the Category and "
                             "Item objects and updated entry key") {

                          REQUIRE_NOTHROW(wObj3.getCategory(testCategoryNew));
                          REQUIRE(wObj3.getCategory(testCategoryNew).size() ==
                                  3);
                          REQUIRE_NOTHROW(wObj3.getCategory(testCategoryNew)
                                              .getItem(testItemNew));
                          REQUIRE(wObj3.getCategory(testCategoryNew)
                                      .getItem(testItemNew)
                                      .size() == 3);
                          REQUIRE(wObj3.getCategory(testCategoryNew)
                                      .getItem(testItemNew)
                                      .getEntry(testEntryKeyNew) ==
                                  testEntryValueOld);

                        } // THEN

                        AND_WHEN("and the entry program argument is '" +
                                 testEntryValueChange + "'") {

                          Argv argvObj({
                              "test",
                              "--db",
                              filePath.c_str(),
                              "--action",
                              "update",
                              "--category",
                              testCategoryNew.c_str(),
                              "--item",
                              testItemNew.c_str(),
                              "--entry",
                              testEntryValueChange.c_str(),
                          });
                          auto **argv = argvObj.argv();
                          auto argc = argvObj.argc();

                          THEN("no exception is thrown") {

                            REQUIRE_NOTHROW(App::run(argc, argv));

                            AND_WHEN("loading the saved file into a new Wallet "
                                     "object") {

                              Wallet wObj4{};
                              REQUIRE(wObj4.empty());
                              REQUIRE_NOTHROW(wObj4.load(filePath));

                              THEN("the new Wallet will contain the Category "
                                   "and Item objects and updated entry key and "
                                   "value") {

                                REQUIRE_NOTHROW(
                                    wObj4.getCategory(testCategoryNew));
                                REQUIRE(
                                    wObj4.getCategory(testCategoryNew).size() ==
                                    3);
                                REQUIRE_NOTHROW(
                                    wObj4.getCategory(testCategoryNew)
                                        .getItem(testItemNew));
                                REQUIRE(wObj4.getCategory(testCategoryNew)
                                            .getItem(testItemNew)
                                            .size() == 3);
                                REQUIRE(wObj4.getCategory(testCategoryNew)
                                            .getItem(testItemNew)
                                            .getEntry(testEntryKeyNew) ==
                                        testEntryValueNew);

                              } // THEN

                            } // AND_WHEN

                          } // THEN

                        } // AND_WHEN

                      } // THEN

                    } // AND_WHEN

                  } // THEN

                } // AND_WHEN

              } // THEN

            } // AND_WHEN

          } // AND_WHEN

        } // THEN

      } // AND_WHEN

    } // WHEN

  } // GIVEN

} // SCENARIO