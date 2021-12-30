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
// Items in the Category container.
// -----------------------------------------------------

#include "../src/lib_catch.hpp"

#include <string>

#include "../src/lib_cxxopts.hpp"
#include "../src/lib_cxxopts_argv.hpp"

#include "../src/category.h"

SCENARIO( "an empty Category can be constructed successfully", "[category]" ) {

  GIVEN( "the category identifier 'Test'" ) {

    WHEN( "the Category object will contain zero items" ) {

      Category c { "Test" };

      REQUIRE( c.size() == 0 );
      REQUIRE( c.empty() );

    } // WHEN

  } // GIVEN

} // SCENARIO

SCENARIO( "Items can be added to and retrieved from a Category", "[category]" ) {

  const std::string ident = "Test";

  GIVEN( "a Category object with identifier '" + ident + "'" ) {

    Category c { ident };

    WHEN( "an Item with identifier '" + ident + "' can be added" ) {

      Item i { ident };

      REQUIRE( c.addItem(i) == true );

      THEN( "the Category contains 1 Item" ) {

        REQUIRE( c.size() == 1 );
        REQUIRE_FALSE( c.empty() );

      } // THEN

      THEN( "the Item can be retrieved by the ident '" + ident + "'" ) {

        REQUIRE( c.getItem(ident) == i );

      } // THEN

      Item i2 { ident };

      THEN( "a second Item with the same ident, '" + ident + "', will not change the overall size of the Category" ) {

        REQUIRE( c.addItem(i2) == true );
        REQUIRE( c.size() == 1 );
        REQUIRE_FALSE( c.empty() );

      } // THEN

      const std::string ident3 = "Test2";
      Item i3 { ident3 };

      THEN( "a third Item with a different ident, '" + ident3 + "', can be added" ) {

        REQUIRE( c.addItem(i3) == true );

        THEN( "the Category contains 2 Items" ) {

          REQUIRE( c.size() == 2 );
          REQUIRE_FALSE( c.empty() );

        } // THEN

        THEN( "the Item can be retrieved by the ident '" + ident3 + "'" ) {

          REQUIRE( c.getItem(ident3) == i3 );

        } // THEN

      } // THEN

    } // WHEN

  } // GIVEN

} // SCENARIO

SCENARIO( "Items can be added to and deleted from a Category", "[category]" ) {

  const std::string ident = "Test";

  GIVEN( "a Category object with identifier '" + ident + "'" ) {

    Category c { ident };

    WHEN( "an Item with identifier '" + ident + "' can be added" ) {

      Item i { ident };

      REQUIRE( c.addItem(i) == true );

      THEN( "the Category contains 1 Item" ) {

        REQUIRE( c.size() == 1 );
        REQUIRE_FALSE( c.empty() );

      } // THEN

      THEN( "the Item can be retrieved by the ident '" + ident + "'" ) {

        REQUIRE( c.getItem(ident) == i );

      } // THEN

      THEN( "deleting a non-existent Item ('blah') will not change the Category" ) {

        REQUIRE_FALSE( c.deleteItem("blah") );
        REQUIRE( c.getItem(ident) == i );
        REQUIRE( c.size() == 1 );

      } // THEN

      THEN( "deleting the existent Item ('" + ident + "') will leave the Category empty" ) {

        REQUIRE( c.deleteItem(ident) );
        REQUIRE_THROWS_AS( c.getItem(ident), std::out_of_range );
        REQUIRE( c.size() == 0 );

      } // THEN

    } // WHEN

  } // GIVEN

} // SCENARIO
