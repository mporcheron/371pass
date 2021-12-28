// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2021/22)
// Department of Computer Science, Swansea University
//
// Author: Martin Porcheron
//         m.a.w.porcheron@swansea.ac.uk
//
// Canvas: https://canvas.swansea.ac.uk/courses/15581
// -----------------------------------------------------
// This file containsEntry declarations for the helper
// functions used for initialising and running 371pass
// -----------------------------------------------------

#include <string>

#include "lib_cxxopts.hpp"
#include "wallet.h"

namespace Pass {

  // TODO: Enter your student number here!
  const std::string STUDENT_NUMBER = "987654";

  enum Action {
    CREATE,
    READ,
    UPDATE,
    DELETE
  };

  int run(int argc, char *argv[]);

  cxxopts::Options cxxoptsSetup();

  Pass::Action parseActionArgument(cxxopts::ParseResult& args);

  bool performCreate(Wallet& wObj, cxxopts::ParseResult& args);
  bool performRead(Wallet& wObj, cxxopts::ParseResult& args) noexcept;
  bool performUpdate(Wallet& w, cxxopts::ParseResult& args);
  bool performDelete(Wallet& w, cxxopts::ParseResult& args);

  const std::string getJSON(Wallet& w);
  const std::string getJSON(Wallet& w,
                            const std::string& c);
  const std::string getJSON(Wallet& w,
                            const std::string& c,
                            const std::string& i);
  const std::string getJSON(Wallet& wObj,
                            const std::string& c,
                            const std::string& i,
                            const std::string& e);

}; // namespace Pass