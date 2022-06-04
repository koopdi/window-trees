cmake_minimum_required(VERSION 3.2.0)
project (WindowManager VERSION 2022.05.21 LANGUAGES CXX)

# use C++17 language standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

add_subdirectory(LemonFir)
add_subdirectory(BSPTree)

# source / header files specific to this project
FILE(GLOB WindowManager_Headers
	*.cpp
)

FILE(GLOB WindowManager_Sources
	*.h
)

# FILE(GLOB WindowManager_Library_Headers
# 	../Protocol/*.h
# )

add_library(WindowManager
	${WindowManager_Headers}
	${WindowManager_Sources}
	${WindowManager_Library_Headers}
)

target_include_directories(WindowManager
	PUBLIC
	# "../Protocol/"
	.
)
target_link_libraries(WindowManager
	PUBLIC
	Protocol
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
