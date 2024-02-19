## Define Library ##
set(BAR_LIBNAME "BarExDriver")

# List Library Sources
set(HEADERS ${BAR_LIBNAME}/include/ExDriver.h)
set(SOURCES ${BAR_LIBNAME}/src/ExDriver.cpp)

add_library(BarExDriver SHARED ${SOURCES} ${HEADERS})
add_library(Sand2Silicon::BarExDriver ALIAS BarExDriver)

target_include_directories(BarExDriver
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>  # For generated 'mytools_export.h'
        #        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>  # Make headers available to consuming projects that include via 'add_subdirectory'
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${BAR_LIBNAME}/include>
        #    INTERFACE
        #        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>    # Not needed if in INSTALL section.
)


## Version Number Management ##

set(BarEXDRIVER_LIB_MAJOR_VERSION ${DynamicLibraryClient_VERSION_MAJOR})
set(BarEXDRIVER_LIB_MINOR_VERSION ${DynamicLibraryClient_VERSION_MINOR})
set(BarEXDRIVER_LIB_PATCH_VERSION ${DynamicLibraryClient_VERSION_MPATCH})
set(BarEXDRIVER_LIB_FULL_VERSION  ${BarEXDRIVER_LIB_MAJOR_VERSION}.${BarEXDRIVER_LIB_MINOR_VERSION}.${BarEXDRIVER_LIB_PATCH_VERSION})

set_target_properties(BarExDriver PROPERTIES
        VERSION   ${BarEXDRIVER_LIB_FULL_VERSION}
        SOVERSION ${BarEXDRIVER_LIB_MAJOR_VERSION}
)

# Embed version-info in the .dll
# TODO:
#target_source(BarExDriver PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/version.rc)

#configure_file(
#        ${CMAKE_CURRENT_SOURCE_DIR}/version.rc.in
#        ${CMAKE_CURRENT_BINARY_DIR}/version.rc
#        @ONLY
#)


## Shared Library Exports ##

# Generate __declspec(export)/(import) header.
include(GenerateExportHeader)
generate_export_header(BarExDriver)


## Install Section ##

include(GNUInstallDirs)
set(CMAKE_INSTALL_DOCDIR "${CMAKE_INSTALL_PREFIX}/doc")

# RPATH FIXES for *inx platforms    (ProCmake pg. 385)`
file(RELATIVE_PATH relDir
        ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}
        ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}
)
set(CMAKE_INSTALL_RPATH $ORIGIN $ORIGIN/${relDir})

install(TARGETS BarExDriver
        EXPORT BarExDriverPackage DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}     # (ALL) Executable binaries.  (WIN) .dll's too.
        COMPONENT           BarExDriver_RunTime
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}     # (UNIX) Shared Libraries.
        COMPONENT           BarExDriver_RunTime
        NAMELINK_COMPONENT  BarExDriver_Development
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}     # (ALL) Static libraries.  (WIN) 'import library' (.lib) for shared libaries.
        COMPONENT           BarExDriver_Development
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${BAR_LIBNAME}
        #        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Copy the include/ directories
# This is required to be done like so.
install(
        DIRECTORY ./BarExDriver/include/
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${BAR_LIBNAME}"
        FILES_MATCHING PATTERN "*.h"
        PATTERN "doc" EXCLUDE
        # TODO: Exclude 'doc/' subdir that is a part of the source directory 'deepCmakeLibrary/'
)

install(
        FILES "${CMAKE_CURRENT_BINARY_DIR}/Barexdriver_export.h"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

# Install the Documentation     # todo WHY doesn't THIS work???...
#install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/doc/
#        DESTINATION ${CMAKE_INSTALL_DOCDIR}
#        FILES_MATCHING
#        PATTERN "*.md"
#        PATTERN "*.DS_Store" EXCLUDE
#        PATTERN "*.svn" EXCLUDE
#)


install (EXPORT BarExDriverPackage
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/BarExDriver
        NAMESPACE Sand2Silicon::
        FILE BarExDriverConfig.cmake
)


# -------- Begin Executables ----------

add_executable(BarDemo src/main.cpp)
target_link_libraries(BarDemo BarExDriver)

install(TARGETS BarDemo)
install(IMPORTED_RUNTIME_ARTIFACTS BarExDriver)       # (This copies dependent .dll's at INSTALL time) # TODO: Prevent duplicate copy!
