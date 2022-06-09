
# SGL_Client

cmake_minimum_required(VERSION 3.2.0)
project (SGL_Client VERSION 05.21.2022 LANGUAGES CXX)

# tell CMake to run the QT prepocessor (moc), when necessary
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
#set(CMAKE_AUTOUIC ON)

# Link to Qt5 graphical libraries
find_package(Qt5 COMPONENTS Widgets Multimedia Network REQUIRED)

# as moc files are generated in the binary dir, tell CMake
# to always look for includes there:
if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()


# # # student writes ordinary main() function, but it must be called within a
# # # wrapper main() that handles library setup/teardown. Rename student's
# # # to distinguish between the two main() functions and avoid symbol clash
add_compile_options(
	-Dmain=studentMain
)

# SGL_Client -----------------------------------------------

add_executable(SGL_Client
	sglClientMain.cpp
)

target_include_directories(SGL_Client
	PUBLIC
	.
)

target_link_libraries(SGL_Client
	PUBLIC
	Protocol
	WindowManager
	SGL_Server
)

# Lemon_Fir_SGL --------------------------------------------

add_executable(Lemon_Fir_SGL
	lemonFirMain.cpp
)

target_include_directories(Lemon_Fir_SGL
	PUBLIC
	.
)

target_link_libraries(Lemon_Fir_SGL
	PUBLIC
	Protocol
	WindowManager
	LemonFir
	SGL_Server
)


# WinterFace_SGL_Client ----------------------------------------

add_executable(WinterFace_SGL_Client
winterFaceClientMain.cpp
)

target_include_directories(WinterFace_SGL_Client
PUBLIC
.
)

target_link_libraries(WinterFace_SGL_Client
PUBLIC
Protocol
WindowManager
LemonFir
HeapTree
SGL_Server
)