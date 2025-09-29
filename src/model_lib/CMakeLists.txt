add_library(ast_model SHARED
    ast_model.cpp
    ast_model.h
)

target_include_directories(ast_model PUBLIC ${CMAKE_SOURCE_DIR}/src/model_lib)

target_link_libraries(ast_model PRIVATE core_analyzer)
