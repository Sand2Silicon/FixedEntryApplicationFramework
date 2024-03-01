DynamicLibraryClient - Example Program space
2024-02-18, Sunday
--------------------------------


PURPOSE: Intent is to prototype a single 'main.cpp' driver program that can:
    - Link against multiple different dynamic libraries implementing common interface to provide different behavior.
    - Different libraries can BUILD and INSTALL.
    - Different driver-programs (from same main.cpp) can BUILD, carrying their depnedencies with them, and run.
    - Different driver-programs (from same main.cpp) can INSTALL, carrying their depnedencies with them, and run.


 SOURCE TREEE                BUILD TREE                             INSTALL TREEE
-----------------           -----------------                       -----------------
./CMakeLists.txt            ./_build/                               /opt/rubix/                     ('rubix' is a placeholder name)
./src/main.cpp              ./_build/bin/FooDriver.exe              /opt/rubix/bin/FooDriver.exe
                            ./_build/bin/BarDriver.exe              /opt/rubix/bin/BarDriver.exe
                            ./_build/bin/*.dll                      /opt/rubix/bin//bin/*.dll

./FooLib/                   ./FooLib/                               /opt/rubix/FooLib/              (not needed is it? why would these libraries be installed 
./FooLib/include/           <no headers>                            /opt/rubix/FooLib/include/       for a developer outside of the main solution?)
./FooLib/lib/               ./FooLib/lib/ ( n/a for shared libs)    /opt/rubix/FooLib/lib/
./FooLib/src/               ./FooLib/bin/ ( .dll or .so)            /opt/rubix/FooLib/bin/

./BarLib/                   ./BarLib/                               /opt/rubix/BarLib/
./BarLib/include/           <no headers>                            /opt/rubix/BarLib/include/      (not needed is it? ...)
./BarLib/lib/               ./BarLib/lib/ ( n/a for shared libs)    /opt/rubix/BarLib/lib/
./BarLib/src/               ./BarLib/bin/ ( .dll or .so)            /opt/rubix/BarLib/bin/


2024-03-01, Friday
--------------------------------
Significant updates have been made to do the argument parsing with CLI11 library and DYNAMICALLY generate the
FTXUI Config screen at runtime based on the parameters. Some of this design was aided by AdaptaGPT (ChatGPT 4.0),
which provides this approximated class diagram.

-ExProgramArgs is the class that holds a list of ArgumentBase pointers, which can point to any TypedArgument<T> instances.
-ArgumentBase is the base class for all argument types. It contains the common interface for adding arguments to the CLI and generating GUI components.
-TypedArgument<T> is a template class derived from ArgumentBase. It represents a typed argument and holds the value and default value for that argument.
-Specializations such as TypedArgument<bool>, TypedArgument<std::string>, TypedArgument<int>, and TypedArgument<float> represent specific argument types.
-CLIManager uses ExProgramArgs to set up and parse command-line arguments.
-GUIManager uses ExProgramArgs to generate a GUI representation with FTXUI components.
-ScreenInteractive is a class from the FTXUI library, used by GUIManager to display and manage the GUI.

This simplified UML-like diagram gives a high-level overview of the class structure and relationships.

Here's a simplified representation of the main classes and their relationships:

 [ExProgramArgs]
      |
      | - - - - - - - - - - - - - - - - - - - -> [ArgumentBase] <|-- [TypedArgument<T>]
      |                                               ^                   |
      |                                               |                   |
      |                                               |                   |
      |                                               |                   +--> [TypedArgument<bool>]
      |                                               |                   |
      |                                               |                   +--> [TypedArgument<std::string>]
      |                                               |                   |
      |                                               |                   +--> [TypedArgument<int>]
      |                                               |                   |
      |                                               |                   +--> [TypedArgument<float>]
      |                                               |
      +--------------------+                          |
                           |                          |
                           |                          |
                           v                          |
                    [CLIManager]                      |
                           |                          |
                           |                          |
                           +--------------------------+
                           |
                           |
                           v
                    [GUIManager]
                           |
                           |
                           v
                    [ScreenInteractive] (from FTXUI)


----------

The design and organization of the C++ program involving , , and related components reflect a modular and extensible architecture. Here is an analysis of the key aspects of its design:

Separation of Concerns:
The program separates responsibilities into distinct components. is responsible for defining and storing program arguments, while handles the command-line interface setup and parsing. This separation allows for focused modification and testing of each aspect without affecting the other.

Encapsulation:
The program encapsulates related functionalities into classes and structs, which helps in managing complexity. For instance, wraps the logic for a single command-line argument, including its type, value, and how it interacts with the CLI and UI.

Reusability:
By encapsulating functionalities, the code promotes reusability. For example, once defined, can be used for any type of argument that needs to be parsed from the command line and potentially represented in a UI.

Extensibility:
The template-based design of makes it easy to extend the program to handle new types of arguments. Developers can add new specializations or use existing ones without modifying the underlying CLI or UI management code.

Abstraction:
provides an abstraction layer over the specific command-line parsing library (CLI11) and UI library (FTXUI). This means that changes in these libraries, or even switching to different libraries, would require minimal changes to the rest of the program.

Dependency Management:
The program demonstrates good dependency management practices by using namespaces and forward declarations, which reduce coupling. For example, forward-declares and uses a namespace to avoid symbol conflicts.

Use of Modern C++ Features:
The program leverages modern C++ features such as smart pointers, lambda expressions, and template specialization, which contribute to safer and more efficient code.

Error Handling:
The use of exceptions in and the function to handle parsing errors and other exceptions showcases the importance given to robust error handling and user feedback.

Build and Configuration Management:
The use of CMake functions to configure and manage libraries demonstrates an understanding of build automation and configuration management, which is essential for maintaining complex projects.

Interaction between Components:
and interact seamlessly, demonstrating a well-thought-out interface between components. relies on to set up the CLI, and can generate UI components based on the arguments it contains, showing a clear flow of data and control.

Areas for Further Improvement:
While the current design is robust, areas for further improvement could include introducing interfaces (abstract base classes) for even greater decoupling, implementing unit tests for each component, and considering the use of design patterns like Factory or Strategy for creating and managing argument types.

In summary, the design of the program adheres to several best practices in software engineering, resulting in a codebase that is organized, maintainable, and adaptable to future requirements or changes.