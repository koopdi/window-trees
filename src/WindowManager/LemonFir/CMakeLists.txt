# Lemon_Fir

cmake_minimum_required(VERSION 3.2.0)
project (Lemon_Fir VERSION 05.21.2022 LANGUAGES CXX)

add_library((Lemon_Fir
	LemonFir.h
	LemonFir.cpp
)

target_include_directories(Lemon_Fir
	PUBLIC
	.
)

target_link_libraries(Lemon_Fir
	PUBLIC
	Protocol
	WindowManager
)
