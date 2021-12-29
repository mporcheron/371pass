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
// This file contains tests for the Item container you
// must set up in your coursework.
// -----------------------------------------------------

#include "../src/lib_catch.hpp"

#include <string>

#include "../src/lib_cxxopts.hpp"
#include "../src/lib_cxxopts_argv.hpp"

#include "../src/item.h"

SCENARIO( "an empty Item can be constructed successfully", "[item]" ) {

  GIVEN( "the item identifier 'Test'" ) {

    WHEN( "the Item object will contain zero entries" ) {

      Item i { "Test" };

      REQUIRE( i.size() == 0 );
      REQUIRE( i.empty() );

    } // WHEN

  } // GIVEN

} // SCENARIO

SCENARIO( "Entries can be added to a Item", "[item]" ) {

  GIVEN( "an Item object with identifier 'Test'" ) {

    Item i { "Test" };

    std::string key = "url";
    std::string value = "https://www.google.com/";

    WHEN( "an entry with key '" + key + "' and value '" + value + "' can be added" ) {

      REQUIRE( i.addEntry(key, value) == true );

      THEN( "the Item contains 1 entry" ) {

        REQUIRE( i.size() == 1 );
        REQUIRE_FALSE( i.empty() );

      } // THEN

      THEN( "the entry can be retrieved by the key '" + key + "'" ) {

        REQUIRE( i.getEntry(key) == value );

      } // THEN

      THEN( "a second entry with the same key, '" + key + "', will not change the overall size of the Item" ) {

        REQUIRE( i.addEntry(key, value) == true );
        REQUIRE( i.size() == 1 );
        REQUIRE_FALSE( i.empty() );

      } // THEN

      key = "username";
      value = "myusername";

      THEN( "a third entry with a different key, '" + key + "', and value '" + value + "' can be added" ) {

        REQUIRE( i.addEntry(key, value) == true );

        THEN( "the Item contains 2 entries" ) {

          REQUIRE( i.size() == 2 );
          REQUIRE_FALSE( i.empty() );

        } // THEN

        THEN( "the entry can be retrieved by the key '" + key + "'" ) {

          REQUIRE( i.getEntry(key) == value );

        } // THEN

      } // THEN

    } // WHEN

  } // GIVEN

} // SCENARIO