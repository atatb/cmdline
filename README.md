cmdline - a tiny command line utility for c++
--------------------------------------------

cmdline is a tiny simple command line utility for C++ (C++11 or more).
cmdline parses given arguments by each operator() (operator[]) methods on demand,
so no need to define strict type of variable for parsing beforehand.

- Header-only
- Tiny
- Simple

Installation
-------------

#### Include using CMake

See [`CMakeLists.txt`](./CMakeLists.txt) in this repository.

#### Include to source codes directry

Put the [`cmdline.h`](./include/cmdline.h) file to somewhere from the root directory,
for example in the `include` directory on root, then specify the `#include` directive with the relative path from the souce code.

```c++
// In source code file
#include "./include/cmdline.h"
...
...
```

#### Include using compiler options

Use `-I` option, the directory to be added to the list of directories searched for include files.

See the below sample.

Usage
-------------

### Sample Code

Save as `sample.cpp`

```c++
#include "cmdline.h"
#include <iostream>

int main(int argc, char *argv[]) {
  CmdLineParser cmd(argc, argv);

  // bool
  const bool b = cmd("--bool", false);
  const bool bnv = cmd["--bool-no-arg"];

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
```

### Compile `sample.cpp` with g++ (C++11)

```
$ g++ -std=c++11 -I./include sample.cpp -o sample
```

### Play

##### No arguments

```
$ ./sample

--bool : false
--bool-no-arg : false
--double : 789.123000
--float : 789.119995
--int : 789
--str : default string

```

##### With arguments

```
$ ./sample --bool true --bool-no-arg --double 123.456 --float 123.456 --int 123 --str value

--bool : true
--bool-no-arg : true
--double : 123.456000
--float : 123.456001
--int : 123
--str : value

```
