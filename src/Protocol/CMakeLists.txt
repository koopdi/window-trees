# Protocol

cmake_minimum_required(VERSION 3.2.0)
project (Protocol VERSION 2022.05.21 LANGUAGES CXX)

# use C++17 language standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

# source / header files specific to this project
FILE(GLOB Protocol_Headers
	*.cpp
)

FILE(GLOB Protocol_Sources
	*.h
)

add_library(Protocol STATIC
	${Protocol_Headers}
	${Protocol_Sources}
)

target_include_directories(Protocol
	PUBLIC
	.
)

# Configure flags for the C++ compiler
# (In general, many warnings/errors are enabled to tighten compile-time checking.
# A few overly pedantic/confusing errors are turned off to avoid confusion.)
set(CMAKE_BUILD_TYPE Debug)
add_compile_options(
	-g
	-Wall
	-Wextra
	-Werror=return-type
	-Werror=uninitialized
	-Wunused-parameter
	-Wmissing-field-initializers
	-Wno-old-style-cast
	-Wno-sign-compare
	-Wno-sign-conversion
)
