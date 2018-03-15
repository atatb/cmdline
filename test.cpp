#include "cmdline.h"
#include <cassert>

void REQUIRE(bool condition) {
  assert(condition);
}

void REQUIRE_FALSE(bool condition) {
  REQUIRE(!condition);
}

void test1() {
  char *argv_[] = {
      (char *) "--param-bool",
      (char *) "--param-str", (char *) "value",
      (char *) "--param-int", (char *) "123",
      (char *) "--param-float", (char *) "123.4",
      (char *) "--param-double", (char *) "123.45",
      (char *) "--param-bool1", (char *) "true",
      (char *) "--param-bool2", (char *) "on",
      (char *) "--param-bool3", (char *) "something else"
  };
  int argc_ = sizeof(argv_) / sizeof(*argv_);
  CmdLineParser cml(argc_, argv_);

  // bool
  REQUIRE(cml["--param-bool"]);
  REQUIRE(cml("--param-bool1", false));
  REQUIRE(cml("--param-bool2", false));
  REQUIRE_FALSE(cml("--param-bool3", true));
  REQUIRE(cml("--no-param", true));
  REQUIRE_FALSE(cml("--no-param", false));

  // string
  REQUIRE(cml("--param-str") == "value");
  REQUIRE(cml("--param-str", std::string("as string")) == "value");
  REQUIRE(cml("--param-str", "as *char") == "value");
  REQUIRE(cml("--no-param", std::string("def value")) == "def value");
  REQUIRE(cml("--no-param", "def value") == "def value");

  // int
  REQUIRE(cml("--param-int", 456) == 123);
  REQUIRE(cml("--no-param", 789) == 789);

  // float
  REQUIRE(cml("--param-float", 456.7f) == 123.4f);
  REQUIRE(cml("--no-param", 456.7f) == 456.7f);

  // double
  REQUIRE(cml("--param-double", 456.78) == 123.45);
  REQUIRE(cml("--no-param", 456.78) == 456.78);
}

void test2() {
  char *argv_[] = {(char *) "--param1", (char *) "value1", (char *) "--param2"};
  int argc_ = sizeof(argv_) / sizeof(*argv_);
  CmdLineParser cml(argc_, argv_);

  cml("--param1");
  cml["--param2"];
  cml["--no-param"];
  REQUIRE(cml.dump() == "\n--no-param : false\n--param1 : value1\n--param2 : true\n");
}

int main(int argc, char *argv[]) {
  test1();
  test2();
}
