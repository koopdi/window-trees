
# SDL_Client

cmake_minimum_required(VERSION 3.7)
project(sdlClient VERSION 0.0.1)

find_package(SDL2)
include_directories(sdlClient ${SDL2_INCLUDE_DIRS})

add_executable(sdlClient SDLClient.cpp)
target_link_libraries(sdlClient
	SDLServer
	${SDL2_LIBRARIES}
)

# use C++11 language standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

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
