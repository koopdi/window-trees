
# ye ol' Tiles Project from 132

cmake_minimum_required(VERSION 3.2.0)
project (Tiles VERSION 05.21.2022 LANGUAGES CXX)

# # # student writes ordinary main() function, but it must be called within a
# # # wrapper main() that handles library setup/teardown. Rename student's
# # # to distinguish between the two main() functions and avoid symbol clash
add_compile_options(
	-Dmain=studentMain
)

# source / header files specific to this project
FILE(GLOB Tiles_Headers
	src/*.cpp
)

FILE(GLOB Tiles_Sources
	src/*.h
)

add_executable(Tiles
${Tiles_Headers}
${Tiles_Sources}
${Tiles_Library_Headers}
)

target_include_directories(Tiles
	PUBLIC
	.
)

target_link_libraries(Tiles
	PUBLIC
	SGL
)
