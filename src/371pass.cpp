// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2021/22)
// Department of Computer Science, Swansea University
//
// Author: Martin Porcheron
//         m.a.w.porcheron@swansea.ac.uk
//
// Canvas: https://canvas.swansea.ac.uk/courses/15581
// -----------------------------------------------------

#include <iostream>

#include "371pass.h"
#include "wallet.h"

// TODO Complete this function. You have been provided some skeleton code which
//  retrieves the database file name from cxxopts.
//  1. Construct a DBFile object, open the file, retrieve the JSON text as a
//     string. If you have an issue opening or reading the file, it should be
//     be replaced. This is usually a **very bad idea** in normal application
//     development (as the user could lose data) but to keep things simple for
//     this coursework, we will do this.
//  2. Construct a Wallet object. If you were able to extract JSON data, pass
//     this to the Wallet constructor, otherwise construct an empty Wallet.
//  3. Take the appropriate action based on the program arguments (see the
//     coursework specification for details).
//  4. Save the updated Wallet object to the JSON file.
int Pass::run(int argc, char *argv[]) {
  auto cxxopts = Pass::cxxoptsSetup();
  try {
    auto args = cxxopts.parse(argc, argv);

    // Print the help usage if requested
    if (args.count("help")) {
      std::cout << cxxopts.help() << std::endl;
      return 0;
    }

    // Read arguments
    std::string db = args["db"].as<std::string>();

    // Open the database and construct the Wallet
    Wallet w {};
    try {
      w.parse(db);
    } catch (const std::runtime_error& ex) {
      // Do nothing ... again don't do this normally in software development
    }

    std::cout << w.str();

//    Wallet w(db, key);
//
//    if (args.count("json")) {
//      // The output as JSON
//      std::cout << data.toJSON() << std::endl;
//    } else {
//      // The output as tables
//      std::cout << data << std::endl;
//    }

  } catch (const cxxopts::missing_argument_exception& ex) {
    std::cerr << "Missing value for argument:" << ex.what() << '\n';
    return 1;
  } catch (const std::invalid_argument& ex) {
    std::cerr << ex.what() << std::endl;
    return 1;
  } catch (const std::exception& ex) {
    std::cerr << "Unexpected exception: " << ex.what() << '\n';
    return 2;
  } catch (...) {
    std::cerr << "Unknown error\n";
    return 1;
  }

    return 0;
}

// Create a cxxopts instance
cxxopts::Options Pass::cxxoptsSetup() {
  cxxopts::Options cxxopts(
      "371pass",
      "Student ID: " + STUDENT_NUMBER + "\n");

  cxxopts.add_options()(
      "db",
      "Filename of the 371pass database",
      cxxopts::value<std::string>()->default_value("database.json"))(

      "key",
      "Encrypt/decrypt the database using the specified key. If no key is "
      "provided then encryption is disabled.",
      cxxopts::value<std::vector<std::string>>())(

      "j,json",
      "Print the output as JSON instead of text.")(

      "h,help",
      "Print usage.");

  return cxxopts;
}
