cmake_minimum_required (VERSION 3.5)
project (OpenGL)

set (out main)
# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set (src_dir "${PROJECT_SOURCE_DIR}/src/")

file (GLOB src_files "${src_dir}/*.cpp" "${src_dir}/*.h" "${src_dir}/*.hpp")

add_compile_definitions(GLEW_STATIC)
add_executable(${out} main.cpp ${src_files})
target_link_libraries(${out} GL GLEW glfw)
