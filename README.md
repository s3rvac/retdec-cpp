retdec-cpp
==========

A C++ library providing easy access to the [retdec.com](https://retdec.com)
decompilation service through their public [REST API](https://retdec.com/api/).

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

* [CMake](http://www.boost.org/) (version >= 3.0)
* [Boost](http://www.boost.org/) (any recent version)
* [cpp-netlib](http://cpp-netlib.org/) (version >= 0.11)
* [OpenSSL](https://www.openssl.org/) (version >= 1.0)
* [JsonCpp](https://github.com/open-source-parsers/jsoncpp) (version >= 1.0)

The [Boost](http://www.boost.org/) and [OpenSSL](https://www.openssl.org/)
libraries have to be installed on your system. Other libraries are
automatically downloaded and build if they are not present on your system.

Build and Installation
----------------------

* Clone the repository or download the sources into a directory. Lets call the directory `retdec`.
* `cd retdec`
* `cmake ..`
* `make && make install`

Use
---

If you use [CMake](http://www.boost.org/), you can incorporate the library into
your project in the following way.

```
set(retdec_DIR "/path/to/installed/retdec/lib/cmake")
find_package(retdec)
include_directories(SYSTEM ${retdec_INCLUDE_DIR})

add_executable(your_app your_app.cpp)
target_link_libraries(your_app retdec)
```

API Documentation
-----------------

The API documentation is available [here](http://projects.petrzemek.net/retdec-cpp/doc/).

License
-------

Copyright (c) 2015 Petr Zemek (<s3rvac@gmail.com>) and contributors.

Distributed under the MIT license. See the `LICENSE` file for more details.
