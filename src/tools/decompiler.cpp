///
/// @file      tools/decompiler.cpp
/// @copyright (c) 2015-2017 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     A sample application that uses the library to decompile binary
///            files.
///

#include <iostream>

#include "retdec/retdec.h"

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
