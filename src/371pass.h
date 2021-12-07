// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2021/22)
// Department of Computer Science, Swansea University
//
// Author: Martin Porcheron
//         m.a.w.porcheron@swansea.ac.uk
//
// Canvas: https://canvas.swansea.ac.uk/courses/15581
// -----------------------------------------------------
// This file contains declarations for the helper
// functions used for initialising and running 371pass
// -----------------------------------------------------

#include <string>

#include "lib_cxxopts.hpp"

namespace Pass {

// TODO: Enter your student number here!
const std::string STUDENT_NUMBER = "987654";

int run(int argc, char *argv[]);

cxxopts::Options cxxoptsSetup();

std::istream& parseFileArgument(cxxopts::ParseResult& args);

}; // namespace Pass