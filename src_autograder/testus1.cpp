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
// This file contains tests case insensitivity for the
// action program argument.
// -----------------------------------------------------

#include "lib_catch.hpp"

#include <string>

#include "lib_cxxopts.hpp"
#include "lib_cxxopts_argv.hpp"

#include "371pass.h"

SCENARIO(
    "the action program argument can be parsed case insensitively correctly",
    "[args][extended]") {

  GIVEN("a --action program argument and value") {

    WHEN("the value is invalid ('invalid')") {

      Argv argv({"test", "--action", "invalid"});
      auto **actual_argv = argv.argv();
      auto argc = argv.argc();

      auto cxxopts = App::cxxoptsSetup();
      auto args = cxxopts.parse(argc, actual_argv);

      const std::string exceptionMessage = "action";

      THEN("a std::invalid_argument exception is thrown with the message '" +
           exceptionMessage + "'") {

        REQUIRE_THROWS_AS(App::parseActionArgument(args),
                          std::invalid_argument);
        REQUIRE_THROWS_WITH(App::parseActionArgument(args), exceptionMessage);

      } // THEN

    } // WHEN

    WHEN("the value is a create ('CrEaTe') and Action::CREATE is returned") {

      Argv argv({"test", "--action", "CrEaTe"});
      auto **actual_argv = argv.argv();
      auto argc = argv.argc();

      auto cxxopts = App::cxxoptsSetup();
      auto args = cxxopts.parse(argc, actual_argv);

      THEN("the argument value is parsed without exception") {

        REQUIRE_NOTHROW(App::parseActionArgument(args));

        AND_THEN("the response is Action::CREATE") {

          REQUIRE(App::parseActionArgument(args) == App::Action::CREATE);

        } // AND_THEN

      } // THEN

    } // WHEN

    WHEN("the value is a create ('READ') and Action::READ is returned") {

      Argv argv({"test", "--action", "READ"});
      auto **actual_argv = argv.argv();
      auto argc = argv.argc();

      auto cxxopts = App::cxxoptsSetup();
      auto args = cxxopts.parse(argc, actual_argv);

      THEN("the argument value is parsed without exception") {

        REQUIRE_NOTHROW(App::parseActionArgument(args));

        AND_THEN("the response is Action::READ") {

          REQUIRE(App::parseActionArgument(args) == App::Action::READ);

        } // AND_THEN

      } // THEN

    } // WHEN

    WHEN("the value is a create ('UPDate') and Action::UPDATE is returned") {

      Argv argv({"test", "--action", "UPDate"});
      auto **actual_argv = argv.argv();
      auto argc = argv.argc();

      auto cxxopts = App::cxxoptsSetup();
      auto args = cxxopts.parse(argc, actual_argv);

      THEN("the argument value is parsed without exception") {

        REQUIRE_NOTHROW(App::parseActionArgument(args));

        AND_THEN("the response is Action::UPDATE") {

          REQUIRE(App::parseActionArgument(args) == App::Action::UPDATE);

        } // AND_THEN

      } // THEN

    } // WHEN

    WHEN("the value is a create ('delete') and Action::DELETE is returned") {

      Argv argvObj({"test", "--action", "delete"});
      auto **argv = argvObj.argv();
      auto argc = argvObj.argc();

      auto cxxopts = App::cxxoptsSetup();
      auto args = cxxopts.parse(argc, argv);

      THEN("the argument value is parsed without exception") {

        REQUIRE_NOTHROW(App::parseActionArgument(args));

        AND_THEN("the response is Action::DELETE") {

          REQUIRE(App::parseActionArgument(args) == App::Action::DELETE);

        } // AND_THEN

      } // THEN

    } // WHEN

  } // GIVEN

} // SCENARIO