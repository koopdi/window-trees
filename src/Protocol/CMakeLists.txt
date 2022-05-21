cmake_minimum_required(VERSION 3.2.0)
project (Protocol VERSION 2022.05.21 LANGUAGES CXX)

# use C++17 language standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

# source / header files specific to this project
FILE(GLOB Protocol_Headers
	*.cpp
)

FILE(GLOB Protocol_Sources
	*.h
)

add_library(Protocol STATIC
	${Protocol_Headers}
	${Protocol_Sources}
)

# target_include_directories(Protocol
#                            PUBLIC
#                            "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
#                            "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
# )

# install(TARGETS Protocol
#         EXPORT ProtocolTargets
#         LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#         ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
#         RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
#         INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
# )

# export(EXPORT libProtocol)
# ADD_LIBRARY(mylib SHARED ${mylibSRCS})

# PROJECT(myproject)
# CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# SET(mylibSRCS lib.c)
# SET(myprogSRCS client.c)

# ADD_LIBRARY(mylib ${mylibSRCS})
# ADD_EXECUTABLE(myprog ${myprogSRCS})

# TARGET_LINK_LIBRARIES(myprog mylib)

# What is a moc and do we need it?
# tell CMake to run moc when necessary
# set(CMAKE_AUTOMOC ON)
# set(CMAKE_AUTORCC ON)
#set(CMAKE_AUTOUIC ON)

# Yes, but what is this actually for...?
# as moc files are generated in the binary dir, tell CMake
# to always look for includes there:
# if(CMAKE_VERSION VERSION_LESS "3.7.0")
#     set(CMAKE_INCLUDE_CURRENT_DIR ON)
# endif()

# Find packages for linking.
#find_package()

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

# add_compile_options(
# )


# # resource files (images, input files, etc.) for this project
# FILE(GLOB ProjectResources
# 	res/*
# )

# set(WindowManager_Headers
# 	${ProjectHeaders}
# )

# set(WindowManager_Sources
# 	${ProjectSources}
# )

# # all libraries to link
# set(sgl_LIBS
# )

# add_executable(WindowManager
# 	${WindowManager}
# )

# target_include_directories(WindowTrees
# 	PRIVATE
# 	lib/
# 	src/
# 	src/WindowManager/
# 	src/Protocol/
# 	src/SGL_Server_Backend/
# 	src/XServer/
# )

# target_link_libraries(WindowTrees
# 	${sgl_LIBS}
# 	Qt5::Widgets
# 	Qt5::Multimedia
# 	Qt5::Network
# )

# stack overflow example -----------------------------------
# project(myproject)
# I am not sure how you get cmake to use clang++ over g++
# CXX = clang++

# add_definitions(-std=c++11)
# set(COMMON_SOURCES file1.cpp file2.cpp)
# set(TARGET_SOURCES main.cpp)
# set(TEST_SOURCES  run_tests.cpp test_file1.cpp test_file2.cpp)
# add_executable(application ${COMMON_SOURCES} ${TARGET_SOURCES})
# add_executable(tests ${COMMON_SOURCES} ${TEST_SOURCES})

# ----------------------------------------------------------
# example 2
# add_custom_target(tests) # Note: without 'ALL'
# add_executable(test_executable ...) # Note: without 'ALL'
# add_dependencies(tests test_executable)
# ----------------------------------------------------------

