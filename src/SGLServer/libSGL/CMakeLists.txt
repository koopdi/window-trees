# SGL Library

cmake_minimum_required(VERSION 3.2.0)
project (SGL VERSION 05.21.2022 LANGUAGES CXX)

# use C++17 language standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

# tell CMake to run the QT prepocessor (moc), when necessary
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
#set(CMAKE_AUTOUIC ON)

# as moc files are generated in the binary dir, tell CMake
# to always look for includes there:
if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

# Link to Qt5 graphical libraries
find_package(Qt5 COMPONENTS Widgets Multimedia Network REQUIRED)

add_compile_options(
	-DSGL_GRAPHICAL_CONSOLE_NO_TOOLBAR=1
)

# QT defines main and needs qMain, SGL defines qMain on
# windows and main on other platforms.
add_compile_options(
	-Dmain=qMain
)

# convenience variables to represent all source / header files to compile
FILE(GLOB sgl_HDRS
	*.cpp
)

FILE(GLOB sgl_SRCS
	*.h
)

add_library(SGL
	${sgl_HDRS}
	${sgl_SRCS}
)

target_include_directories(SGL
	PUBLIC
	.
)

target_link_libraries(SGL
	PUBLIC
	"-lpthread"
	Qt5::Widgets
	Qt5::Multimedia
	Qt5::Network
)

#