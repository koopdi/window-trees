# HeapTree

project (HeapTree VERSION 06.03.2022 LANGUAGES CXX)

add_library(HeapTree
	HeapTree.h
	HeapTree.cpp
	WindowNode.h
	WindowNode.cpp
)

target_include_directories(HeapTree
	PUBLIC
	../
	.
)

target_link_libraries(HeapTree
	PUBLIC
	Protocol
	WindowManager
)
