cmake_minimum_required(VERSION 3.15)
project(sdk)

# TICPP
add_subdirectory(external/ticpp)
add_library(sdk::ticpp ALIAS ticpp)

find_package(wxWidgets 3.0.3 REQUIRED core)
if(${wxWidgets_FOUND})
    include(${wxWidgets_USE_FILE})
    include(CMakeDependentOption)

    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)

    if(MSVC)
        add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    endif()

    # Plugin Interface
    set(wxWEAVER_PLUGIN_INTERFACE_SOURCE_FILES
        plugin_interface/component.h
        plugin_interface/fontcontainer.h
        plugin_interface/plugin.h
        plugin_interface/xrcconv.h
        plugin_interface/xrcconv.cpp
        plugin_interface/forms/wizard.h
        plugin_interface/forms/wizard.cpp
        plugin_interface/forms/wizard.fbp
    )
    add_library(plugin_interface STATIC ${wxWEAVER_PLUGIN_INTERFACE_SOURCE_FILES})
    if(MSVC)
        # Workaround to unwanted build-type directory added by MSVC
        set_target_properties(plugin_interface PROPERTIES
            SUFFIX ".lib"
            ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<0:>"
        )
    endif()
    target_include_directories(plugin_interface PUBLIC "plugin_interface")
    target_link_libraries(plugin_interface sdk::ticpp ${wxWidgets_LIBRARIES})

    # Don't show build information when building a different project
    if(CMAKE_PROJECT_NAME STREQUAL ${PROJECT_NAME})
        message(STATUS "
CMake Generator:             ${CMAKE_GENERATOR}

Project name:                ${PROJECT_NAME}
Project version:             ${PROJECT_VERSION}
Build type:                  ${CMAKE_BUILD_TYPE}
Build processor:             ${wxWEAVER_SYSTEM_PROCESSOR}
Use clang libc++:            ${wxWEAVER_USE_LIBCPP}
Install prefix:              ${CMAKE_INSTALL_PREFIX}
Output directory:            ${CMAKE_BINARY_DIR}

wxWidgets version:           ${wxWidgets_VERSION_STRING}
wxWidgets static:            ${wxWidgets_DEFAULT_STATIC}
wxWidgets debug:             ${wxWidgets_DEFAULT_DEBUG}
wxWidgets unicode:           ${wxWidgets_DEFAULT_UNICODE}
wxWidgets CXX flags:         ${wxWidgets_CXX_FLAGS_LIST}

Compiler CXX debug flags:    ${CMAKE_CXX_FLAGS_DEBUG}
Compiler CXX release flags:  ${CMAKE_CXX_FLAGS_RELEASE}
Compiler CXX min size flags: ${CMAKE_CXX_FLAGS_MINSIZEREL}
")
    endif()
endif()
