# UILibrary.cmake

# Define the project for the UI library
#project(UILibrary VERSION 1.0.0 LANGUAGES CXX)
#
## Specify the C++ standard
#set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find the FTXUI package required for the library
#find_package(FTXUI REQUIRED)

# Define the source files for the UI library
set(UI_LIBRARY_SOURCES
        UILibrary/src/ExProgramArgs.cpp
        UILibrary/src/GUIManager.cpp
        # Add other source files related to the UI library here
)

# Define the header files for the UI library
set(UI_LIBRARY_HEADERS
        UILibrary/include/ExProgramArgs.h
        UILibrary/include/CLIManager.h
        UILibrary/include/GUIManager.h
        # Add other header files related to the UI library here
)

# Add a library target for the UI library
add_library(UILibrary SHARED
        ${UI_LIBRARY_SOURCES}
        ${UI_LIBRARY_HEADERS}
)

# Specify include directories for the UI library
target_include_directories(UILibrary
        PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>  # For generated 'mytools_export.h'
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/UILibrary/include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Link the UI library with the FTXUI library
target_link_libraries(UILibrary
        PRIVATE
        ftxui::screen
        ftxui::dom
        ftxui::component
)

# Specify the definition for the export of symbols
target_compile_definitions(UILibrary
        PRIVATE
        "UI_LIBRARY_EXPORTS"
)

# Install rules for the UI library
install(TARGETS UILibrary
        EXPORT UILibraryTargets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
)

install(FILES ${UI_LIBRARY_HEADERS} DESTINATION include)

# Generate and install the export file for the UI library
install(EXPORT UILibraryTargets
        FILE UILibraryConfig.cmake
        DESTINATION lib/cmake/UILibrary
)

include(GenerateExportHeader)
generate_export_header(UILibrary)