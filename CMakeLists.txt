cmake_minimum_required(VERSION 3.2.0)

project (WindowTrees VERSION 05.21.2022 LANGUAGES CXX)

# use C++17 language standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

set(WIN32 TRUE)

if (WIN32)
#do this
	FILE(GLOB WindowTree_Headers
		src/*.h
	)

	FILE(GLOB WindowTree_Sources
		src/*.cpp
	)

	FILE(GLOB WindowTree_Library_Headers
		src/WindowManager/*.h
		src/SGL_Server_Backend/*.h
		src/Protocol/*.h
		# src/XServer/*.h
	)

	add_executable(WindowTrees
		${WindowTree_Headers}
		${WindowTree_Sources}
		${WindowTree_Library_Headers}
	)

	target_include_directories(WindowTrees
		PUBLIC
		src/
		src/WindowManager/
		src/Protocol/
		src/SGL_Server_Backend/
		# src/XServer/
	)

	add_subdirectory("src/Protocol/")
	add_subdirectory("src/WindowManager/")
	add_subdirectory("src/SGL_Server_Backend/")
	# add_subdirectory("src/XServer/")


	target_link_libraries(WindowTrees
		PUBLIC
		Protocol
		WindowManager
		SGL_Server_Backend
		# XServer
	)

else()
# do that
# use C++11 language standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

FILE(GLOB WindowTree_Headers
	src/*.h
)

FILE(GLOB WindowTree_Sources
	src/*.cpp
)

FILE(GLOB WindowTree_Library_Headers
	src/WindowManager/*.h
	src/SGL_Server_Backend/*.h
	src/Protocol/*.h
	src/XServer/*.h
)

add_executable(WindowTrees
	${WindowTree_Headers}
	${WindowTree_Sources}
	${WindowTree_Library_Headers}
)

target_include_directories(WindowTrees
	PUBLIC
	src/
	src/WindowManager/
	src/Protocol/
	src/SGL_Server_Backend/
	src/XServer/
)

add_subdirectory("src/Protocol/")
add_subdirectory("src/WindowManager/")
add_subdirectory("src/SGL_Server_Backend/")
add_subdirectory("src/XServer/")


target_link_libraries(WindowTrees
	PUBLIC
	Protocol
	WindowManager
	SGL_Server_Backend
	XServer
)

endif (WIN32)

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

# this might come in handy for the sgl build
# student writes ordinary main() function, but it must be called within a
# wrapper main() that handles library setup/teardown. Rename student's
# to distinguish between the two main() functions and avoid symbol clash
# add_compile_options(
# 	-Dmain=qMain
# 	-DqMain=studentMain
# )
