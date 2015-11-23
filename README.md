retdec-cpp
==========

A C++ library and tools providing easy access to the
[retdec.com](https://retdec.com) decompilation service through their public
[REST API](https://retdec.com/api/).

Development Status
------------------

The library is in an **early stage of development.**

Usage Example
-------------

The following example creates a decompiler, starts a decompilation of the given
binary file, and prints the decompiled C code to the standard output.

``` cpp
#include <iostream>
#include <retdec/retdec.h>

using namespace retdec;

int main(int argc, char **argv) {
    if (argc != 3) {
        std::cerr << "usage: " << argv[0] << " API-KEY FILE\n";
        return 1;
    }

    try {
        Decompiler decompiler(
            Settings()
                .apiKey(argv[1])
        );
        auto decompilation = decompiler.runDecompilation(
            DecompilationArguments()
                .mode("bin")
                .inputFile(File::fromFilesystem(argv[2]))
        );
        decompilation->waitUntilFinished();
        std::cout << decompilation->getOutputHll();
        return 0;
    } catch (const Error &ex) {
        std::cerr << "error: " << ex.what() << "\n";
        return 1;
    }
}
```

Requirements
------------

To build the library and tools, you need:
* A compiler supporting C++14. Supported compilers are:
  * [GCC](https://gcc.gnu.org/) (version >= 4.9)
  * [Clang](http://clang.llvm.org/) (version >= 3.4)
  * [MS Visual Studio](https://www.visualstudio.com/) (version 2015)
* [CMake](https://cmake.org/) (version >= 2.8)
* [Boost](http://www.boost.org/) (version >= 1.55)
* [cpp-netlib](http://cpp-netlib.org/) (version >= 0.11)
* [OpenSSL](https://www.openssl.org/) (version >= 1.0)
* [JsonCpp](https://github.com/open-source-parsers/jsoncpp) (version >= 1.0)

The [Boost](http://www.boost.org/) and [OpenSSL](https://www.openssl.org/)
libraries have to be installed on your system. Other libraries are
automatically downloaded and built if they are not present on your system.

Build and Installation
----------------------

* Clone the repository or download the sources into a directory. Lets call the
  directory `retdec`.
* `cd retdec`
* `mkdir build && cd build`
* `cmake ..`
* `make && make install`

You can pass additional parameters to `cmake`:
* `-DRETDEC_DOC=1` to build with API documentation (requires
    [Doxygen](http://www.doxygen.org/), disabled by default).
* `-DRETDEC_TESTS=1` to build with unit tests (disabled by default).
* `-DRETDEC_TOOLS=1` to build with tools (disabled by default).
* `-DRETDEC_COVERAGE=1` to build with code coverage support (requires
    [LCOV](http://ltp.sourceforge.net/coverage/lcov.php), disabled by default).
* `-DCMAKE_BUILD_TYPE=Debug` to build with debugging information, which is
    useful during development. By default, the library is built in the
    `Release` mode.
* `-DCMAKE_INSTALL_PREFIX:PATH=/usr` to set a custom installation path.

The `make` call supports standard parameters, such as:
* `-j N` to build the library by using `N` processors.
* `VERBOSE=1` to show verbose output when building the library.

Use
---

If you use [CMake](https://cmake.org/), you can incorporate the library into
your project in the following way:

```
set(retdec_DIR "/path/to/installed/retdec/lib/cmake")
find_package(retdec)
include_directories(SYSTEM ${retdec_INCLUDE_DIR})

add_executable(your_app your_app.cpp)
target_link_libraries(your_app retdec)
```

API Documentation
-----------------

The latest API documentation is available
[here](http://projects.petrzemek.net/retdec-cpp/doc/).

License
-------

Copyright (c) 2015 Petr Zemek (<s3rvac@gmail.com>) and contributors.

Distributed under the MIT license. See the `LICENSE` file for more details.

Access from Other Languages
---------------------------

If you want to access the [retdec.com](https://retdec.com) decompilation
service from other languages, check out the following projects:

* [retdec-python](https://github.com/s3rvac/retdec-python) - A library and
  tools for accessing the service from Python.
* [retdec-sh](https://github.com/s3rvac/retdec-sh) - Scripts for accessing the
  service from shell.
