function(example_exe arg)
    message("Setting up OpenGL Example '${arg}'")
    file(GLOB EXAMPLE_SRC_FILES src/${arg}/*.cpp)
    file(GLOB EXAMPLE_HDR_FILES src/${arg}/*.hpp)

    add_executable(
        ${arg}
        ${EXAMPLE_SRC_FILES}
        ${EXAMPLE_HDR_FILES}
        ${imgui_bindings}
    )
    set_target_properties(
        ${arg}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/examples"
        LINKER_LANGUAGE CXX
    )
    target_link_libraries(
        ${arg}
        PUBLIC dk
        SDL2::SDL2main
        SDL2::SDL2-static
        SDL2_image::SDL2_image
        spdlog::spdlog
        glfw
    )
endfunction()
