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
// This file contains tests adding, getting and deleting
// Categorys in the Wallet container.
// -----------------------------------------------------

#include "../src/lib_catch.hpp"

#include <string>

#include "../src/lib_cxxopts.hpp"
#include "../src/lib_cxxopts_argv.hpp"

#include "../src/wallet.h"

SCENARIO( "an empty Wallet can be constructed successfully", "[wallet][empty" ) {

  GIVEN( "nothing" ) {

    WHEN( "the Wallet object will contain zero items" ) {

      Wallet w;

      REQUIRE( w.size() == 0 );
      REQUIRE( w.empty() );

    } // WHEN

  } // GIVEN

} // SCENARIO

SCENARIO( "Category objects can be added to and retrieved from a Wallet", "[wallet]" ) {

  GIVEN( "a Wallet object" ) {

    Wallet w {};

    const std::string ident = "Test";

    WHEN( "a Category with identifier '" + ident + "' can be added" ) {

      Category c { ident };

      REQUIRE( w.addCategory(c) == true );

      THEN( "the Wallet contains 1 Category" ) {

        REQUIRE( w.size() == 1 );
        REQUIRE_FALSE( w.empty() );

      } // THEN

      THEN( "the Category can be retrieved by the ident '" + ident + "'" ) {

        REQUIRE( w.getCategory(ident) == c );

      } // THEN

      Category c2 { ident };

      THEN( "a second empty Category with the same ident, '" + ident + "', will not change the overall size of the Wallet" ) {

        REQUIRE( w.addCategory(c2) == true );
        REQUIRE( w.size() == 1 );
        REQUIRE_FALSE( w.empty() );

      } // THEN

      const std::string ident3 = "Test2";
      Category c3 { ident3 };

      THEN( "a third empty Category with a different ident, '" + ident3 + "', can be added" ) {

        REQUIRE( w.addCategory(ident3) == true );

        THEN( "the Wallet contains 2 Category objects" ) {

          REQUIRE( w.size() == 2 );
          REQUIRE_FALSE( w.empty() );

        } // THEN

        THEN( "the Category can be retrieved by the ident '" + ident3 + "'" ) {

          REQUIRE( w.getCategory(ident3) == c3 );

        } // THEN

      } // THEN

    } // WHEN

  } // GIVEN

} // SCENARIO

SCENARIO( "Category objects can be added to and deleted from a Wallet", "[wallet]" ) {

  GIVEN( "a Wallet object" ) {

    Wallet w {};

    const std::string ident = "Test";

    WHEN( "a Category with identifier '" + ident + "' can be added" ) {

      Category c { ident };

      REQUIRE( w.addCategory(c) == true );

      THEN( "the Wallet contains 1 Category" ) {

        REQUIRE( w.size() == 1 );
        REQUIRE_FALSE( w.empty() );

      } // THEN

      THEN( "the Category can be retrieved by the ident '" + ident + "'" ) {

        REQUIRE( w.getCategory(ident) == c );

      } // THEN

      THEN( "deleting the existent Category ('" + ident + "') will leave the Wallet empty" ) {

        REQUIRE( w.deleteCategory(ident) );
        REQUIRE_THROWS_AS( w.getCategory(ident), std::out_of_range );
        REQUIRE( w.size() == 0 );

      } // THEN

    } // WHEN

  } // GIVEN

} // SCENARIO
