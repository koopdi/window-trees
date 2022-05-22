cmake_minimum_required(VERSION 3.1.0)
project (sgl VERSION 2021.04.03 LANGUAGES CXX)

# use C++11 language standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

# tell CMake to run moc when necessary
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

# student writes ordinary main() function, but it must be called within a
# wrapper main() that handles library setup/teardown. Rename student's
# to distinguish between the two main() functions and avoid symbol clash
add_compile_options(
	-Dmain=qMain
	-DqMain=studentMain
)

# convenience variables to represent all source / header files to compile
FILE(GLOB LibSources
	lib/*.cpp
)

FILE(GLOB LibHeaders
	lib/*.h
)

# non-sgl-library source / header files specific to this project
FILE(GLOB ProjectSources
	src/*.cpp
	src/WindowManager/*.cpp
	src/WinServer/*.cpp
	src/SGL_Server_Backend/*.cpp
	src/Protocol/*.cpp
	src/MiniDisplayServer/*.cpp
	src/XServer/*.cpp
)

FILE(GLOB ProjectHeaders
	src/*.h
	src/WindowManager/*.h
	src/SGL_Server_Backend/*.h
	src/Protocol/*.h
	src/MiniDisplayServer/*.h
	src/XServer/*.h
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
	-lX11
# )

# if (WIN32)
#     #do nothing
# else(
# 	set(sgl_LIBS
# 		-lX11
# 		#I added -lX11 for XServer (which is really an X client lol) - Chris
# 	) # modified to work for windows - Andrew
)
# endif (WIN32)

add_executable(WindowTrees
	${sgl_SRCS}
)

target_include_directories(WindowTrees
	PRIVATE
	lib/
	src/
	src/WindowManager/
	src/Protocol/
	src/SGL_Server_Backend/
	src/XServer/
)

target_link_libraries(WindowTrees
	${sgl_LIBS}
	Qt5::Widgets
	Qt5::Multimedia
	Qt5::Network
)

