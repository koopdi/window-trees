# xClient
#
cmake_minimum_required(VERSION 3.2.0)

project (xClient VERSION 05.21.2022 LANGUAGES CXX)

# use C++17 language standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

FILE(GLOB xClient_Headers
	*.h
)

FILE(GLOB xClient_Sources
	*.cpp
)

add_executable(xClient
${xClient_Headers}
${xClient_Sources}
${xClient_Library_Headers}
)

FILE(GLOB xClient_Library_Headers
	../*.h
)

target_include_directories(xClient
	PUBLIC
	.
)

target_link_libraries(xClient
PUBLIC
Protocol
WindowManager
XServer
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

# set a cmake variable
# set(WIN32 TRUE)

# set a preprocessor variable
# add_compile_definitions(
# 	VAR1
# 	VAR2=VALUE
# )
