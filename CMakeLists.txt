cmake_minimum_required(VERSION 3.28)

project(ast_visualizer VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set (CMAKE_CXX_STANDARD 20)


find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

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
	src/ast_model_creator.cpp
	src/ast_model_creator.h
	src/app_window.cpp
	src/app_window.h
)

target_link_libraries(ast_visualizer Qt${QT_VERSION_MAJOR}::Widgets)

include(GNUInstallDirs)
install(TARGETS ast_visualizer
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
