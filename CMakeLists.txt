cmake_minimum_required(VERSION 3.5)
project(BCR VERSION 0.1 LANGUAGES CXX )

# set the compiling flags
set ( CMAKE_CXX_FLAGS "-Wall" )

#--------------------------------
# This is for old cmake versions
#set (CMAKE_CXX_STANDARD 11)
#--------------------------------

### [1] Application target
# set the include path
include_directories( src )

# Add the target
add_executable( bcr
                src/main.cpp )

# define C++11 standard
set_property(TARGET bcr PROPERTY CXX_STANDARD 11)

# The end
