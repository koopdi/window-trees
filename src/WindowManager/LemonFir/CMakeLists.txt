# Lemon_Fir

project (LemonFir VERSION 06.03.2022 LANGUAGES CXX)

add_library(LemonFir
	LemonFir.h
	LemonFir.cpp

	LemonFirNode.h
	LemonFirNode.cpp
)

target_include_directories(LemonFir
	PUBLIC
	../
	.
)

target_link_libraries(LemonFir
	PUBLIC
	Protocol
	WindowManager
)
