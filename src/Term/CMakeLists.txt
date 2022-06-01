cmake_minimum_required(VERSION 3.2.0)
project (Term VERSION 05.23.2022 LANGUAGES CXX)

# source / header files specific to this project
FILE(GLOB Term_Headers
	*.cpp
)

FILE(GLOB Term_Sources
	*.h
)

FILE(GLOB Term_Library_Headers
	../Protocol/*.h
)

add_library(Term
	${Term_Headers}
	${Term_Sources}
	${Term_Library_Headers}
)

target_include_directories(Term
	PUBLIC
	"../Protocol/"
	.
)

target_link_libraries(Term
	PUBLIC
	Protocol
	WindowManager
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