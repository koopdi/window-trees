# Project Root
# WindowTrees
#
cmake_minimum_required(VERSION 3.2.0)

project (WindowTrees VERSION 05.21.2022 LANGUAGES CXX)

# use C++17 language standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

add_subdirectory("src/Protocol/")
add_subdirectory("src/WindowManager/")
add_subdirectory("src/XServer/")
add_subdirectory("src/SGLServer/")
add_subdirectory("src/SDLServer/")
add_subdirectory("src/Tiles")

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

if(NOT WIN32)
file(CREATE_LINK
	${CMAKE_SOURCE_DIR}/res
	${CMAKE_BINARY_DIR}/src/SGLServer/res
	SYMBOLIC
)
endif()

# set a cmake variable
# set(WIN32 TRUE)

# set a preprocessor variable
# add_compile_definitions(
# 	VAR1
# 	VAR2=VALUE
# )
