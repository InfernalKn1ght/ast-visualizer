cmake_minimum_required(VERSION 3.28)
project(ast_visualizer VERSION 0.1.0 LANGUAGES C CXX)
set (CMAKE_CXX_STANDARD 20)

add_executable(ast_visualizer 
	src/main.cpp
	src/lexer.cpp
	src/lexer.h
	src/reader.cpp
	src/reader.h
	src/token.cpp
	src/token.h
	src/inter.cpp 
	src/inter.h
	src/symbol_table.cpp
	src/symbol_table.h
	src/parser.cpp
	src/parser.h
)

