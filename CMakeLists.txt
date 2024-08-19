cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(
    Imgui3DViewer
    VERSION 0.0.0
    LANGUAGES C CXX
)

find_package(OpenGL)

set(IMGUI_SOURCE_DIR ${CMAKE_SOURCE_DIR}/imgui)
set(IMGUI_BACKENDS_DIR ${IMGUI_SOURCE_DIR}/backends)
set(IMGUI_MISC_CPP_DIR ${IMGUI_SOURCE_DIR}/misc/cpp)

set(IMGUI_LIBS_DIR ${IMGUI_SOURCE_DIR}/examples/libs)
set(GLFW_LIB ${IMGUI_LIBS_DIR}/glfw/lib-vc2010-64)
set(GLFW_INCLUDE_DIR ${IMGUI_LIBS_DIR}/glfw/include)

set(GLM_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/glm)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(SOURCE_FILES
    main.cpp
    camera.hpp
    ${IMGUI_BACKENDS_DIR}/imgui_impl_opengl3.cpp
    ${IMGUI_BACKENDS_DIR}/imgui_impl_glfw.cpp
    ${IMGUI_SOURCE_DIR}/imgui.cpp
    ${IMGUI_SOURCE_DIR}/imgui_tables.cpp
    ${IMGUI_SOURCE_DIR}/imgui_widgets.cpp
    ${IMGUI_SOURCE_DIR}/imgui_demo.cpp
    ${IMGUI_SOURCE_DIR}/imgui_draw.cpp
    ${IMGUI_MISC_CPP_DIR}/imgui_stdlib.cpp
)

add_executable(
    Imgui3DViewer
    ${SOURCE_FILES}
)

target_compile_definitions(
    Imgui3DViewer PUBLIC
    IMGUI_DEFINE_MATH_OPERATORS
    "ImDrawIdx=unsigned int"
)

target_include_directories(
    Imgui3DViewer PUBLIC
    ${IMGUI_SOURCE_DIR}
    ${IMGUI_MISC_CPP_DIR}
    ${IMGUI_BACKENDS_DIR}
    ${GLFW_INCLUDE_DIR}
    ${GLM_INCLUDE_DIR}
    happly
)

target_link_libraries(
    Imgui3DViewer
    ${GLFW_LIB}/glfw3.lib
    OpenGL::GL
)

add_custom_command(
    TARGET Imgui3DViewer POST_BUILD
    COMMAND
        ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/sample/bunny.ply ${CMAKE_BINARY_DIR}/Debug/ &
        ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/sample/bunny.ply ${CMAKE_BINARY_DIR}/Release/ &
)