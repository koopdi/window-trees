# Lemon_Fir

cmake_minimum_required(VERSION 3.2.0)
project (LemonFir VERSION 05.21.2022 LANGUAGES CXX)

add_library(LemonFir
	LemonFir.h
	LemonFir.cpp
)

target_include_directories(LemonFir
	PUBLIC
	.
)

target_link_libraries(LemonFir
	PUBLIC
	Protocol
	WindowManager
)
