# BSPTree

project (BSPTree VERSION 06.03.2022 LANGUAGES CXX)

add_library(BSPTree
	BSPTree.h
	BSPTree.cpp
	BSPNode.h
	BSPNode.cpp
)

target_include_directories(BSPTree
	PUBLIC
	../
	.
)

target_link_libraries(BSPTree
	PUBLIC
	Protocol
)