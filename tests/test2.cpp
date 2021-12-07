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
// This file contains test for the containers you must
// set up in your coursework.
// -----------------------------------------------------

#include "../src/lib_catch.hpp"

#include <string>

#include "../src/lib_cxxopts.hpp"
#include "../src/lib_cxxopts_argv.hpp"

#include "../src/wallet.h"
#include "../src/category.h"
#include "../src/item.h"

SCENARIO( "an empty Wallet can be constructed successfully", "[wallet][empty" ) {

  GIVEN( "nothing" ) {

    WHEN( "the Wallet object will contain zero items" ) {

      Wallet w;

      REQUIRE( w.size() == 0 );
      REQUIRE( w.empty() );

    } // THEN

  } // WHEN

} // SCENARIO

SCENARIO( "an empty Category can be constructed successfully", "[category][empty" ) {

  GIVEN( "nothing" ) {

    WHEN( "the Category object will contain zero items" ) {

      Category c;

      REQUIRE( c.size() == 0 );
      REQUIRE( c.empty() );

    } // THEN

  } // WHEN

} // SCENARIO

SCENARIO( "an empty Item can be constructed successfully", "[item][empty]" ) {

  GIVEN( "nothing" ) {

    WHEN( "the Item object will contain zero entries" ) {

      Item i;

      REQUIRE( i.size() == 0 );
      REQUIRE( i.empty() );

    } // THEN

  } // WHEN

} // SCENARIO