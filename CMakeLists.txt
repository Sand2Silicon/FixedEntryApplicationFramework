cmake_minimum_required(VERSION 3.21)
project(DynamicLibraryClient LANGUAGES CXX VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 20)

if (LINUX)
    add_compile_options(-W _wall)
elseif (MSVC)
    add_compile_options(/W3)
endif()

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    if(WIN32)
        set(CMAKE_INSTALL_PREFIX "c:/opt/sand2silicon/${PROJECT_NAME}")
    else()
        set(CMAKE_INSTALL_PREFIX "/opt/sand2silicon/${PROJECT_NAME}}")
    endif()
endif()

# Symbol Visibility
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN YES)


# -------- Begin Dependencies ----------

# Set the CMAKE_PREFIX_PATH to include the FTXUI library
set(CMAKE_PREFIX_PATH "C:\\opt\\lib\\FTXUI;${CMAKE_PREFIX_PATH}")

# Use find_package to locate the FTXUI library
find_package(FTXUI REQUIRED)

# Include the UI library CMake configuration
include(UILibrary.cmake)
# -------- Begin Libraries ----------

## Define Library ##
set(FOO_LIBNAME "FooExDriver")
# List Library Sources
set(HEADERS
        ${FOO_LIBNAME}/include/ExDriver.h
#        ${FOO_LIBNAME}/include/ExProgramArgs.h
        ${FOO_LIBNAME}/include/CLIManager.h
        include/CLI11.hpp
)

set(SOURCES
        ${FOO_LIBNAME}/src/ExDriver.cpp
        #${FOO_LIBNAME}/src/ExProgramArgs.cpp
        ${FOO_LIBNAME}/src/CLIManager.cpp
)

add_library(FooExDriver SHARED ${SOURCES} ${HEADERS})
add_library(Sand2Silicon::FooExDriver ALIAS FooExDriver)

# Link the FTXUI library to your target
target_link_libraries(FooExDriver
        PRIVATE ftxui::screen
        PRIVATE ftxui::dom
        PRIVATE ftxui::component # Not needed for this example.
)

target_include_directories(FooExDriver
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>  # For generated 'mytools_export.h'
#        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>  # Make headers available to consuming projects that include via 'add_subdirectory'
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${FOO_LIBNAME}/include>
#    INTERFACE
#        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>    # Not needed if in INSTALL section.
)


## Version Number Management ##

set(FOOEXDRIVER_LIB_MAJOR_VERSION ${DynamicLibraryClient_VERSION_MAJOR})
set(FOOEXDRIVER_LIB_MINOR_VERSION ${DynamicLibraryClient_VERSION_MINOR})
set(FOOEXDRIVER_LIB_PATCH_VERSION ${DynamicLibraryClient_VERSION_MPATCH})
set(FOOEXDRIVER_LIB_FULL_VERSION  ${FOOEXDRIVER_LIB_MAJOR_VERSION}.${FOOEXDRIVER_LIB_MINOR_VERSION}.${FOOEXDRIVER_LIB_PATCH_VERSION})

set_target_properties(FooExDriver PROPERTIES
        VERSION   ${FOOEXDRIVER_LIB_FULL_VERSION}
        SOVERSION ${FOOEXDRIVER_LIB_MAJOR_VERSION}
)

# Embed version-info in the .dll
# TODO:
#target_source(FooExDriver PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/version.rc)

#configure_file(
#        ${CMAKE_CURRENT_SOURCE_DIR}/version.rc.in
#        ${CMAKE_CURRENT_BINARY_DIR}/version.rc
#        @ONLY
#)


## Shared Library Exports ##

# Generate __declspec(export)/(import) header.
include(GenerateExportHeader)
generate_export_header(FooExDriver)


## Install Section ##

include(GNUInstallDirs)
set(CMAKE_INSTALL_DOCDIR "${CMAKE_INSTALL_PREFIX}/doc")

# RPATH FIXES for *inx platforms    (ProCmake pg. 385)`
file(RELATIVE_PATH relDir
        ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}
        ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}
)
set(CMAKE_INSTALL_RPATH $ORIGIN $ORIGIN/${relDir})

install(TARGETS FooExDriver
        EXPORT FooExDriverPackage DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}     # (ALL) Executable binaries.  (WIN) .dll's too.
                COMPONENT           FooExDriver_RunTime
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}     # (UNIX) Shared Libraries.
                COMPONENT           FooExDriver_RunTime
                NAMELINK_COMPONENT  FooExDriver_Development
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}     # (ALL) Static libraries.  (WIN) 'import library' (.lib) for shared libaries.
                COMPONENT           FooExDriver_Development
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${FOO_LIBNAME}
#        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Copy the include/ directories
# This is required to be done like so.
install(
        DIRECTORY ./FooExDriver/include/
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${FOO_LIBNAME}"
        FILES_MATCHING PATTERN "*.h"
        PATTERN "doc" EXCLUDE
        # TODO: Exclude 'doc/' subdir that is a part of the source directory 'deepCmakeLibrary/'
)

install(
        FILES "${CMAKE_CURRENT_BINARY_DIR}/fooexdriver_export.h"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

# Install the Documentation
#install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/doc/
#        DESTINATION ${CMAKE_INSTALL_DOCDIR}
#        FILES_MATCHING
#        PATTERN "*.md"
#        PATTERN "*.DS_Store" EXCLUDE
#        PATTERN "*.svn" EXCLUDE
#)


install (EXPORT FooExDriverPackage
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/FooExDriver
        NAMESPACE Sand2Silicon::
        FILE FooExDriverConfig.cmake
)


# -------- Begin Executables ----------

add_executable(FooDemo src/main.cpp)
target_link_libraries(FooDemo
        PRIVATE FooExDriver
        UILibrary
)
target_include_directories(FooDemo PRIVATE include)

# Link the FTXUI library to your target
target_link_libraries(FooDemo
        PRIVATE ftxui::screen
        PRIVATE ftxui::dom
        PRIVATE ftxui::component # Not needed for this example.
)

install(TARGETS FooDemo)
install(IMPORTED_RUNTIME_ARTIFACTS FooExDriver)       # (This copies dependent .dll's at INSTALL time) # TODO: Prevent duplicate copy!

# -------------------------------------


include(BarLib.cmake)