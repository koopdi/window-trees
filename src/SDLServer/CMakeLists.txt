cmake_minimum_required(VERSION 3.2.0)
project (SDLServer VERSION 05.23.2022 LANGUAGES CXX)

add_subdirectory("SDLClient")

# source / header files specific to this project
FILE(GLOB SDL_Headers
	*.cpp
)

FILE(GLOB SDL_Sources
	*.h
)

FILE(GLOB SDL_Library_Headers
	../Protocol/*.h
)

add_library(SDLServer
	${SDL_Headers}
	${SDL_Sources}
	${SDL_Library_Headers}
)

target_include_directories(SDLServer
	PUBLIC
	"../Protocol/"
	.
)

target_link_libraries(SDLServer
	PUBLIC
	Protocol
	WindowManager
	"-lSDL"
	"-lpthread"
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