// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2021/22)
// Department of Computer Science, Swansea University
//
// Author: Martin Porcheron
//         m.a.w.porcheron@swansea.ac.uk
//
// Canvas: https://canvas.swansea.ac.uk/courses/15581
// -----------------------------------------------------
// Catch2 test script — https://github.com/catchorg/Catch2
// Catch2 is licensed under the BOOST license
// -----------------------------------------------------
// This file contains tests for the program arguments.
// -----------------------------------------------------

#include "../src/lib_catch.hpp"

#include <string>

#include "../src/lib_cxxopts.hpp"
#include "../src/lib_cxxopts_argv.hpp"

#include "../src/371pass.h"

SCENARIO( "the action program argument can be parsed correctly", "[args][action]" ) {

  GIVEN( "a --action program argument and value" ) {

    WHEN( "the value is invalid ('invalid')" ) {

      Argv argv({"test", "--action", "invalid"});
      auto** actual_argv = argv.argv();
      auto argc          = argv.argc();

      auto cxxopts = Pass::cxxoptsSetup();
      auto args    = cxxopts.parse(argc, actual_argv);

      const std::string exceptionMessage = "action";

      THEN( "a std::invalid_argument exception is thrown with the message '" + exceptionMessage + "'" ) {

        REQUIRE_THROWS_AS(   Pass::parseActionArgument(args), std::invalid_argument );
        REQUIRE_THROWS_WITH( Pass::parseActionArgument(args), exceptionMessage );

      } // THEN

    } // WHEN

    WHEN( "the value is a create ('create') and Action::CREATE is returned" ) {

      Argv argv({"test", "--action", "create"});
      auto** actual_argv = argv.argv();
      auto argc          = argv.argc();

      auto cxxopts = Pass::cxxoptsSetup();
      auto args    = cxxopts.parse(argc, actual_argv);

      THEN( "the argument value is parsed without exception" ) {

        REQUIRE_NOTHROW( Pass::parseActionArgument(args) );

        AND_THEN( "the response is Action::CREATE" ) {

          REQUIRE( Pass::parseActionArgument(args) == Pass::Action::CREATE );

        } // AND_THEN

      } //THEN

    } // WHEN

    WHEN( "the value is a create ('read') and Action::READ is returned" ) {

      Argv argv({"test", "--action", "read"});
      auto** actual_argv = argv.argv();
      auto argc          = argv.argc();

      auto cxxopts = Pass::cxxoptsSetup();
      auto args    = cxxopts.parse(argc, actual_argv);

      THEN( "the argument value is parsed without exception" ) {

        REQUIRE_NOTHROW( Pass::parseActionArgument(args) );

        AND_THEN( "the response is Action::READ" ) {

          REQUIRE( Pass::parseActionArgument(args) == Pass::Action::READ );

        } // AND_THEN

      } //THEN

    } // WHEN

    WHEN( "the value is a create ('update') and Action::UPDATE is returned" ) {

      Argv argv({"test", "--action", "update"});
      auto** actual_argv = argv.argv();
      auto argc          = argv.argc();

      auto cxxopts = Pass::cxxoptsSetup();
      auto args    = cxxopts.parse(argc, actual_argv);

      THEN( "the argument value is parsed without exception" ) {

        REQUIRE_NOTHROW( Pass::parseActionArgument(args) );

        AND_THEN( "the response is Action::UPDATE" ) {

          REQUIRE( Pass::parseActionArgument(args) == Pass::Action::UPDATE );

        } // AND_THEN

      } //THEN

    } // WHEN

    WHEN( "the value is a create ('delete') and Action::DELETE is returned" ) {

      Argv argv({"test", "--action", "delete"});
      auto** actual_argv = argv.argv();
      auto argc          = argv.argc();

      auto cxxopts = Pass::cxxoptsSetup();
      auto args    = cxxopts.parse(argc, actual_argv);

      THEN( "the argument value is parsed without exception" ) {

        REQUIRE_NOTHROW( Pass::parseActionArgument(args) );

        AND_THEN( "the response is Action::DELETE" ) {

          REQUIRE( Pass::parseActionArgument(args) == Pass::Action::DELETE );

        } // AND_THEN

      } //THEN

    } // WHEN

  } // GIVEN

} // SCENARIO