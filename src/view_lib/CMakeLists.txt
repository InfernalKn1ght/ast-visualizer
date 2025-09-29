find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_library(app_view SHARED
    app_view.cpp
    app_view.h
    ast_model_creator.cpp
    ast_model_creator.h
    main_layout.cpp
    main_layout.h
)

target_include_directories(app_view PUBLIC ${CMAKE_SOURCE_DIR}/src/view_lib)

target_link_libraries(app_view PUBLIC Qt6::Widgets PRIVATE core_analyzer)