[![MIT license](https://img.shields.io/badge/license-MIT-blue.svg)](https://opensource.org/licenses/MIT)

# Purpose

QML bindings for C

**This project is at a very early stage and not suitable for use yet.**

# Build dependencies

- CMake
- C++14 compiler
- [Optional] Doxygen to generate the documentation
- Qt 5.9 or newer
- [clue](https://github.com/stephaneyfx/clue)

# General notes

## Strings

All strings passed to or returned from the API are in UTF-8.

## Thread safety

Unless stated otherwise, the thread safety of functions is the same as the
corresponding functions in the Qt library.

## Exceptions

Exceptions thrown from C++ code are caught and logged.

# Build

The instructions below assume the Ninja generator is used, but any other generator ought to work. The `install` and `package` targets are also provided.

Install Qt5 and clue.

```sh
git clone --recursive https://github.com/stephaneyfx/qlue.git
cd qlue
mkdir build
cd build
# You may need to help cmake find Qt (`-D Qt5_DIR=...`) and clue
# (`-D clue_DIR=...`). These directories must contain the cmake configuration
# files for the libraries.
cmake -G Ninja ..
ninja
```

# Platform support

All, to the extent of the availability of the dependencies.
