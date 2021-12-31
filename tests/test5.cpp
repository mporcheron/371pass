// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2021/22)
// Department of Computer Science, Swansea University
//
// Author: Martin Porcheron
//         m.a.w.porcheron@swansea.ac.uk
//
// Canvas: https://canvas.swansea.ac.uk/courses/15581
// -----------------------------------------------------
// Catch2 — https://github.com/catchorg/Catch2
// Catch2 is licensed under the BOOST license
// -----------------------------------------------------
// This file contains tests loading JSON files into
// the Wallet.
// -----------------------------------------------------

#include "../src/lib_catch.hpp"

#include <fstream>
#include <string>

#include "../src/lib_cxxopts.hpp"
#include "../src/lib_cxxopts_argv.hpp"

#include "../src/wallet.h"

SCENARIO("A Wallet object can load a JSON file", "[wallet]") {

  const std::string filePath = "./tests/testdatabase.json";

  auto fileExists = [](const std::string &path) {
    return std::ifstream(path).is_open();
  };

  GIVEN("a valid path to a database JSON file") {

    REQUIRE(fileExists(filePath));

    WHEN("a new empty Wallet object is constructed") {

      Wallet w{};
      REQUIRE(w.empty());

      AND_WHEN("the load function is called with the file path") {

        THEN("the file will be imported without an exception") {

          REQUIRE_NOTHROW(w.load(filePath));
          REQUIRE(w.size() == 2);

          REQUIRE_NOTHROW(w.getCategory("Websites"));
          REQUIRE(w.getCategory("Websites").size() == 3);

          REQUIRE_NOTHROW(w.getCategory("Websites").getItem("Google"));
          REQUIRE(w.getCategory("Websites").getItem("Google").size() == 3);
          REQUIRE(w.getCategory("Websites").getItem("Google").getEntry("url") ==
                  "https://www.google.com/");
          REQUIRE(w.getCategory("Websites")
                      .getItem("Google")
                      .getEntry("username") == "example@gmail.com");
          REQUIRE(w.getCategory("Websites")
                      .getItem("Google")
                      .getEntry("password") == "pass1234");

          REQUIRE_NOTHROW(w.getCategory("Websites").getItem("Facebook"));
          REQUIRE(w.getCategory("Websites").getItem("Facebook").size() == 3);
          REQUIRE(
              w.getCategory("Websites").getItem("Facebook").getEntry("url") ==
              "https://www.facebook.com/");
          REQUIRE(w.getCategory("Websites")
                      .getItem("Facebook")
                      .getEntry("username") == "example@gmail.com");
          REQUIRE(w.getCategory("Websites")
                      .getItem("Facebook")
                      .getEntry("password") == "pass1234fb");

          REQUIRE_NOTHROW(w.getCategory("Websites").getItem("Twitter"));
          REQUIRE(w.getCategory("Websites").getItem("Twitter").size() == 3);
          REQUIRE(
              w.getCategory("Websites").getItem("Twitter").getEntry("url") ==
              "https://www.twitter.com/");
          REQUIRE(w.getCategory("Websites")
                      .getItem("Twitter")
                      .getEntry("username") == "example@gmail.com");
          REQUIRE(w.getCategory("Websites")
                      .getItem("Twitter")
                      .getEntry("password") == "r43rfsffdsfdsf");

          REQUIRE_NOTHROW(w.getCategory("Bank Accounts"));
          REQUIRE(w.getCategory("Bank Accounts").size() == 1);
          REQUIRE_NOTHROW(w.getCategory("Bank Accounts").getItem("Starling"));
          REQUIRE(w.getCategory("Bank Accounts").getItem("Starling").size() ==
                  3);
          REQUIRE(w.getCategory("Bank Accounts")
                      .getItem("Starling")
                      .getEntry("Name") == "Mr John Doe");
          REQUIRE(w.getCategory("Bank Accounts")
                      .getItem("Starling")
                      .getEntry("Account Number") == "12345678");
          REQUIRE(w.getCategory("Bank Accounts")
                      .getItem("Starling")
                      .getEntry("Sort Code") == "12-34-56");

        } // THEN

      } // AND_WHEN

    } // WHEN

  } // GIVEN

} // SCENARIO
