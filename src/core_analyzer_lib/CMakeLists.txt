add_library(core_analyzer STATIC
	parser.cpp
	parser.h
    lexer.cpp
	lexer.h
	reader.cpp
	reader.h
	token.cpp
	token.h
	inter.cpp 
	inter.h
	symbol_table.cpp
	symbol_table.h
)

target_include_directories(core_analyzer PUBLIC ${CMAKE_SOURCE_DIR}/src/core_analyzer_lib)

set_target_properties(core_analyzer PROPERTIES
    POSITION_INDEPENDENT_CODE ON
)

