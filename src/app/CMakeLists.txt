add_executable(ast_visualizer
    app_controller.cpp
    app_controller.h
    main.cpp
)

target_link_libraries(ast_visualizer PRIVATE ast_model app_view core_analyzer)
