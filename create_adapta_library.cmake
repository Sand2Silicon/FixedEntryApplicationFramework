function(target_link_driver_libraries LIBNAME)
    target_link_libraries(${LIBNAME}
            PRIVATE UILibrary
            PRIVATE ftxui::screen
            PRIVATE ftxui::dom
            PRIVATE ftxui::component
    )

endfunction()

# Define a function to configure a new library
function(configure_library LIBNAME LIB_MAJOR_VERSION LIB_MINOR_VERSION LIB_PATCH_VERSION LIB_TWEAK_VERSION)
    # Define the full library name
    set(LIB_FULL_NAME "${LIBNAME} ${LIB_MAJOR_VERSION}.${LIB_MINOR_VERSION}.${LIB_PATCH_VERSION}.${LIB_TWEAK_VERSION}")
    set(LIB_FULL_VERSION "${LIB_MAJOR_VERSION}.${LIB_MINOR_VERSION}.${LIB_PATCH_VERSION}.${LIB_TWEAK_VERSION}")
    message("Configuring library: ${LIB_FULL_NAME}")

    # Define library sources and headers
#    set(LIB_SOURCES
#            ${LIBNAME}/src/ExDriver.cpp
#            # Add other source files here
#    )
#    set(LIB_HEADERS
#            ${LIBNAME}/include/ExDriver.h
#            # Add other header files here
#    )

    # Add a library target
#    add_library(${LIBNAME} SHARED ${LIB_SOURCES} ${LIB_HEADERS})
#    add_library(Sand2Silicon::${LIBNAME} ALIAS ${LIBNAME})

    # Link the library with its dependencies
#    target_link_libraries(${LIBNAME}
#            PRIVATE UILibrary
#            PRIVATE ftxui::screen
#            PRIVATE ftxui::dom
#            PRIVATE ftxui::component
#    )

    # Set include directories
    target_include_directories(${LIBNAME}
            PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${LIBNAME}/include>
    )

    # Set library version
    set_target_properties(${LIBNAME} PROPERTIES
            VERSION   ${LIB_FULL_VERSION}
            SOVERSION ${LIB_MAJOR_VERSION}
    )

    # Generate export header
    include(GenerateExportHeader)
    generate_export_header(${LIBNAME})

    # Install rules
    include(GNUInstallDirs)
#    install(TARGETS ${LIBNAME}
#            EXPORT ${LIBNAME}Package
#            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
#            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
#            INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${LIBNAME}
#    )

    install(TARGETS ${LIBNAME}
        EXPORT ${LIBNAME}Package DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}     # (ALL) Executable binaries.  (WIN) .dll's too.
                COMPONENT           ${LIBNAME}_RunTime
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}     # (UNIX) Shared Libraries.
                COMPONENT           ${LIBNAME}_RunTime
                NAMELINK_COMPONENT  ${LIBNAME}_Development
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}     # (ALL) Static libraries.  (WIN) 'import library' (.lib) for shared libaries.
                COMPONENT           ${LIBNAME}_Development
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${LIBNAME}
    #        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )

    # Install export package
    install(EXPORT ${LIBNAME}Package
            DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${LIBNAME}
            NAMESPACE Sand2Silicon::
            FILE ${LIBNAME}Config.cmake
    )
endfunction()