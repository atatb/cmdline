#include "cmdline.h"
#include <iostream>

int main(int argc, char *argv[]) {
  CmdLineParser cmd(argc, argv);

  // bool
  const bool b = cmd("--bool", false);
  const bool bnv = cmd["--bool-no-value"];

  // string
  const std::string s = cmd("--str", "default string");

  // int
  const int i = cmd("--int", 789);

  // float
  const float f = cmd("--float", 789.12f);

  // double
  const double d = cmd("--double", 789.123);

  std::cout << cmd.dump() << std::endl;
}
