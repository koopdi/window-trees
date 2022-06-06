# Master : Stack layout

project (MasterAndStack VERSION 06.03.2022 LANGUAGES CXX)

add_library(MasterAndStack
	MasterStack.h
	MasterStack.cpp
	MasterStackNode.h
	MasterStackNode.cpp
)

target_include_directories(MasterAndStack
	PUBLIC
	../
	.
)

target_link_libraries(MasterAndStack
	PUBLIC
	Protocol
	WindowManager
)