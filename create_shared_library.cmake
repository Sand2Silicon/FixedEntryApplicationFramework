function(create_shared_library LIB_TARGET LIB_NAME )

#    add_library(${LIB_NAME} SHARED ${LIB_SOURCES} ${LIB_HEADERS})
#    add_library(Sand2Silicon::${LIB_NAME} ALIAS ${LIB_NAME})

target_include_directories( ${LIB_TARGET}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>  # For generated 'mytools_export.h'
#        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>  # Make headers available to consuming projects that include via 'add_subdirectory'
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${LIB_NAME}/include>
#    INTERFACE
#        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>    # Not needed if in INSTALL section.
)

### Version Number Management ##
set(${LIB_NAME}_LIB_MAJOR_VERSION ${DynamicLibraryClient_VERSION_MAJOR})
set(${LIB_NAME}_LIB_MINOR_VERSION ${DynamicLibraryClient_VERSION_MINOR})
set(${LIB_NAME}_LIB_PATCH_VERSION ${DynamicLibraryClient_VERSION_PATCH})
set(${LIB_NAME}_LIB_TWEAK_VERSION ${DynamicLibraryClient_VERSION_TWEAK})
set(${LIB_NAME}_LIB_FULL_VERSION  ${${LIB_NAME}_LIB_MAJOR_VERSION}.${${LIB_NAME}_LIB_MINOR_VERSION}.${${LIB_NAME}_LIB_PATCH_VERSION}.${${LIB_NAME}_LIB_TWEAK_VERSION})

set_target_properties(${LIB_TARGET} PROPERTIES
        VERSION   ${FOOEXDRIVER_LIB_FULL_VERSION}
        SOVERSION ${FOOEXDRIVER_LIB_MAJOR_VERSION}
)

message("Scoped FOOEXDRIVER_LIB_FULL_VERSION: ${FooExDriver_LIB_FULL_VERSION}")
endfunction()