cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(
    Imgui3DViewer
    VERSION 0.0.0
    LANGUAGES C CXX
)

find_package(OpenGL)

set(IMGUI_SOURCE_DIR ${CMAKE_SOURCE_DIR}/imgui)
set(GLFW_LIB_DIR ${CMAKE_SOURCE_DIR}/glfw/lib-vc2010-64)
set(GLFW_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/glfw/include)
set(GLM_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/glm)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_executable(
    Imgui3DViewer
    main.cpp
    camera.hpp
    ${IMGUI_SOURCE_DIR}/imgui_impl_opengl3.cpp
    ${IMGUI_SOURCE_DIR}/imgui_impl_glfw.cpp
    ${IMGUI_SOURCE_DIR}/imgui.cpp
    ${IMGUI_SOURCE_DIR}/imgui_tables.cpp
    ${IMGUI_SOURCE_DIR}/imgui_widgets.cpp
    ${IMGUI_SOURCE_DIR}/imgui_draw.cpp
    ${IMGUI_SOURCE_DIR}/imgui_demo.cpp
    ${IMGUI_SOURCE_DIR}/imgui_stdlib.cpp
)

target_include_directories(
    Imgui3DViewer PUBLIC
    ${IMGUI_SOURCE_DIR}
    ${GLFW_INCLUDE_DIR}
    ${GLM_INCLUDE_DIR}
    happly
)

target_link_libraries(
    Imgui3DViewer
    ${GLFW_LIB_DIR}/glfw3.lib
    OpenGL::GL
)

add_custom_command(
    TARGET Imgui3DViewer POST_BUILD
    COMMAND
        ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/sample/bunny.ply ${CMAKE_BINARY_DIR}/Debug/ &
        ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/sample/bunny.ply ${CMAKE_BINARY_DIR}/Release/ &
)