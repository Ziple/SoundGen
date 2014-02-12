cmake_minimum_required( VERSION 2.6 )

# --------------------------------------------
# Project name definition
# --------------------------------------------
project( "Sound Gen" )

cmake_policy( SET CMP0015 NEW )

# --------------------------------------------
# Add the compiler include / lib paths
# to the default CMake paths
# --------------------------------------------
set(CMAKE_INCLUDE_PATH $CMAKE_INCLUDE_PATH $ENV{INCLUDE})
set(CMAKE_LIBRARY_PATH $CMAKE_LIBRARY_PATH $ENV{LIB})

# --------------------------------------------
# Add the folder to the compilation includes path
# --------------------------------------------
include_directories( include )

file(
    GLOB_RECURSE
    proc_source_files
    src/*.cpp
)

file(
    GLOB_RECURSE
    proc_header_files
    include/*.hpp
)

add_executable(
    SoundGen
    ${proc_source_files}
    ${proc_header_files}
)

target_link_libraries( SoundGen optimized sfml-main )
target_link_libraries( SoundGen optimized sfml-system )
target_link_libraries( SoundGen optimized sfml-audio )

target_link_libraries( SoundGen debug sfml-main-d )
target_link_libraries( SoundGen debug sfml-system-d )
target_link_libraries( SoundGen debug sfml-audio-d )