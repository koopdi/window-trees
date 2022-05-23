cmake_minimum_required(VERSION 3.2.0)
project (XServer VERSION 05.23.2022 LANGUAGES CXX)

# source / header files specific to this project
FILE(GLOB XServer_Headers
	*.cpp
)

FILE(GLOB XServer_Sources
	*.h
)

FILE(GLOB XServer_Library_Headers
	../Protocol/*.h
)

add_library(XServer
	${XServer_Headers}
	${XServer_Sources}
	${XServer_Library_Headers}
)

target_include_directories(XServer
	PUBLIC
	"../Protocol/"
)
target_link_libraries(XServer
	PUBLIC
	Protocol
	"-lX11"
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