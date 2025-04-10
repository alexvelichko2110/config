cmake_minimum_required (VERSION 3.0)

set (PROJECT test-config)

# set project name
project (${PROJECT})

# pkg-config
# include (FindPkgConfig)

add_definitions(-c -pipe -O0 -g -Wall)


# set search include path
include_directories(".")


# The project version number.
set(VERSION_MAJOR   0   CACHE STRING "Project major version number.")
set(VERSION_MINOR   0   CACHE STRING "Project minor version number.")
set(VERSION_PATCH   1   CACHE STRING "Project patch version number.")
mark_as_advanced(VERSION_MAJOR VERSION_MINOR VERSION_PATCH)

# build
add_definitions(-std=c++17)

set (HEADERS
)


set (SOURCES
)

add_executable (${PROJECT} main.cpp config.cpp)

target_link_libraries (${PROJECT} jsoncpp)


add_custom_target(clean-all
    COMMAND rm -f Makefile
    COMMAND rm -f cmake_install.cmake
    COMMAND rm -f install_manifest.txt
    COMMAND rm -f CMakeCache.txt
    COMMAND rm -R -f CMakeFiles
    COMMAND rm -R -f ${PROJECT}
)
