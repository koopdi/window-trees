cmake_minimum_required(VERSION 3.2.0)
project (SGL_Server_Backend VERSION 05.21.2022 LANGUAGES CXX)

# use C++11 language standard
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

add_compile_options(
	-DSGL_GRAPHICAL_CONSOLE_NO_TOOLBAR=1
)

#this is now a library, use this for a main that runs sgl
# # student writes ordinary main() function, but it must be called within a
# # wrapper main() that handles library setup/teardown. Rename student's
# # to distinguish between the two main() functions and avoid symbol clash
# add_compile_options(
# 	-Dmain=qMain
# 	-DqMain=studentMain
# )

# convenience variables to represent all source / header files to compile
FILE(GLOB LibSources
	lib/*.cpp
)

FILE(GLOB LibHeaders
	lib/*.h
)

# non-sgl-library source / header files specific to this project
FILE(GLOB ProjectSources
	*.cpp
)

FILE(GLOB ProjectHeaders
	*.h
)

set(sgl_HDRS
	${LibHeaders}
	${ProjectHeaders}
)

set(sgl_SRCS
	${LibSources}
	${ProjectSources}
)

# all libraries to link
set(sgl_LIBS
	-lpthread
)

add_library(SGL_Server_Backend
	${sgl_SRCS}
)

target_include_directories(SGL_Server_Backend
	PUBLIC
	"../Protocol/"
	lib/
)

target_link_libraries(SGL_Server_Backend
	Protocol
	${sgl_LIBS}
	Qt5::Widgets
	Qt5::Multimedia
	Qt5::Network
)

