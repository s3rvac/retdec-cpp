///
/// @file      doxygen.h
/// @copyright (c) 2015-2016 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Documentation of the main page and the used namespaces.
///

namespace retdec {

/**
@mainpage

This is an automatically generated API documentation for the <a
href="https://github.com/s3rvac/retdec-cpp">retdec-cpp library</a>.

@section SectionNamingConventions Naming Conventions

The library uses the following naming conventions.
<ul>
	<li>Include files are named by using <code>snake_case</code>, e.g. <code>%decompilation.h</code> and <code>%fwd_decls.h</code>.</li>
	<li>Functions and variables are named by using <code>camelCase</code>, e.g. <code>%waitUntilFinished()</code>.</li>
	<li>Classes and constants are named by using <code>CamelCase</code>, e.g. <code>%DecompilationArguments</code>.</li>
</ul>
Moreover, no name contains two or more successive uppercase letters, even if it corresponds to an abbreviation. That is, the library uses <code>%withApiUrl()</code> instead of <code>%withAPIURL()</code> and <code>%IoError</code> instead of <code>%IOError</code>.

When a class represents a structure-like object, getters are named directly after the property, e.g. <code>%Settings::mode()</code> instead of <code>%Settings::getMode()</code>. In other cases, getters are prefixed with <code>%get</code>, e.g. <code>%Decompilation::getOutputHll()</code> instead of <code>%Decompilation::outputHll()</code>.

@section SectionIncludes Includes

The easiest way to use the library is to include the general header file <code>retdec.h</code> that includes all the necessary header files:
@code
#include <retdec/retdec.h>
@endcode
However, if you use only specific parts of the library, you can include just the used header files:
@code
#include <retdec/settings.h>
#include <retdec/decompiler.h>
// ...
@endcode
Furthermore, the library provides header file <code>fwd_decls.h</code>, containing forward declarations for the used classes. It may be used in your header files to increase compilation speed.

@section SectionNamespaces Namespaces

All the classes, functions, and constants the library provides are in the <code>::retdec</code> namespace.

For simplicity, in this API documentation, this namespace is omitted, e.g. it uses <code>Decompilation</code> instead of <code>retdec::Decompilation</code>.

@section SectionAvailableServices Available Services

The library currently provides basic support for the <a href="https://retdec.com/api/docs/fileinfo.html" title="File-analyzing service API">file-analyzing</a> and <a href="https://retdec.com/api/docs/decompiler.html" title="Decompilation service API">decompilation</a> services. For simplicity, in the rest of this page, we will solely focus on decompilations. The use of the file-analyzing service through <code>Fileinfo</code> is analogical.

@section SectionCreatingSettings Creating Library Settings

At the very beginning, you need to create settings for the library. They are represented by an instance of class <code>Settings</code>. You have to provide at least your API key:
@code
Settings settings;
settings.apiKey("YOUR-SECRET-API-KEY");
@endcode
The class provides also a fluent interface, which allows you to chain the setting of multiple options:
@code
auto settings = Settings()
	.apiKey("YOUR-SECRET-API-KEY")
@endcode

See the description of <code>Settings</code> for a list of all the available options.

@section SectionCreatingDecompiler Creating a Decompiler

To create a decompiler, instantiate class <code>Decompiler</code> and provide the settings constructed in the previous step:
@code
Decompiler decompiler(settings);
@endcode
It is of course possible to build the settings inline:
@code
Decompiler decompiler(
	Settings()
		.apiKey("YOUR-SECRET-API-KEY")
);
@endcode
This is handy if you want to use the settings only in a single place.

@section SectionStartingDecompilations Starting Decompilations

After you have created a decompiler, you can run decompilations. To start a decompilation, call <code>Decompiler::runDecompilation()</code> and provide its arguments, represented by an instance of class <code>DecompilationArguments</code>. This class also provides a fluent interface. Example:
@code
auto decompilation = decompiler.runDecompilation(
	DecompilationArguments()
		.mode("c")
		.inputFile(
			File::fromContentWithName("int main() {}", "empty.c")
		)
);
@endcode
The above example starts a decompilation of a C file <code>empty.c</code> and returns a handle to the decompilation. The file is created from the given content. In this way, you do not need to create regular files just to pass them as arguments to the decompilation. If you want to pass a regular file, use <code>File::fromFilesystem()</code> instead, which takes a path to the file.

@section SectionQueryingDecompilations Querying Decompilations

After a decompilation is started, you can query its state. For example, to check if the decompilation has finished, call <code>Decompilation::hasFinished()</code>:
@code
if (decompilation->hasFinished()) {
	// ...
}
@endcode
To effectively wait until the decompilation is finished, call <code>Decompilation::waitUntilFinished()</code>:
@code
decompilation->waitUntilFinished();
@endcode
It will return once the decompilation finishes. You can also pass a callback that will be called whenever a change in the decompilation status is detected:
@code
decompilation->waitUntilFinished([](const Decompilation &d) {
	std::cout << "Currently completed: " << d.getCompletion() << "%\n";
});
@endcode
The above code prints the completion status (in percentages) everytime a change is detected. Since the decompilation is passed to the callback via a parameter, you can have a generic callback and pass it to <code>waitUntilFinished()</code> without a need to capture the current decompilation via lambda captures.

To check whether the decompilation finished successfuly, call <code>Decompilation::hasSucceeded()</code>.

@section SectionObtainingOutputs Obtaining Outputs From Decompilations

Once a decompilation has successfully finished, you can obtain the produced outputs. To get the contents of the generated high-level language (HLL) in a string, call <code>Decompilation::getOutputHll()</code>:
@code
std::cout << decompilation->getOutputHll();
@endcode
To get the file with the HLL, call <code>Decompilation::getOutputHllFile()</code>, which returns a handle to a <code>File</code>. With it, you can, for example, store the file to the filesystem by calling <code>File::saveCopyTo()</code>:
@code
decompilation->getOutputHllFile()->saveCopyTo("/some/directory/");
@endcode
The copied file is given a proper name based on the name of the input file to the decompilation.

@section SectionErrorHandling Error Handling

Errors are reported via exceptions. The base class of all custom exceptions thrown by the library is <code>Error</code>, which itself inherits from <code>std::runtime_error</code>. If you simply want to catch all the custom exceptions thrown by the library, catch this base class:
@code
try {
	// Use the library.
} catch (const Error &ex) {
	// Handle the error.
}
@endcode
Its subclasses include:
<ul>
	<li><code>IoError</code> - Thrown when there is an I/O error. Its subclasses are:</li>
		<ul>
			<li><code>FilesystemError</code> - Thrown when there is a filesystem error, e.g. a file cannot be read.</li>
			<li><code>ConnectionError</code> - Thrown when there is a connection error, e.g. the server providing the API is not available.</li>
		</ul>
	<li><code>ApiError</code> - Thrown when the API is used incorrectly, e.g. the supplied decompilation arguments are invalid.</li>
	<li><code>ResourceError</code> - Thrown when a resource fails. Its subclasses are:</li>
		<ul>
			<li><code>AnalysisError</code> - Thrown when a file analysis fails.</li>
			<li><code>DecompilationError</code> - Thrown when a decompilation fails.</li>
		</ul>
	</li>
</ul>
For a complete list, see the inheritance diagram for <code>Error</code>. Catch these subclasses if you want to handle different types of errors separately.

%Resource errors are special. The waiting functions (e.g. <code>Decompilation::waitUntilFinished()</code>) take an optional parameter <code>onError</code> that specifies whether e.g. <code>DecompilationError</code> should be thrown when a decompilation fails. By default, they throw an exception.

@section SectionCompleteExample A Complete Example

The following example creates a decompiler, starts a decompilation of the given binary file, and prints the decompiled C code to the standard output.
@code
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
@endcode

@section SectionContact Contact

If you have any remarks or questions concerning the library, feel free to <a href="https://petrzemek.net" title="Contact me">contact me</a>.
*/

// Document the used namespaces (there is no better place).
/// @namespace retdec The namespace of the library.
/// @namespace retdec::internal Internal parts of the library.

} // namespace retdec
