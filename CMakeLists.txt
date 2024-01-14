cmake_minimum_required (VERSION 3.5)
project (OpenGL)

set (out main)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
set (src_dir "${PROJECT_SOURCE_DIR}/src/")
set (dep_dir "${PROJECT_SOURCE_DIR}/deps/")
set (GLFW ${dep_dir}/GLFW)

file (GLOB src_files "${src_dir}/*.cpp" "${GLFW}/*.h")

add_executable(${out} ${src_files})

target_include_directories(${out} PRIVATE ${dep_dir})
target_link_libraries(${out} ${GLFW}/libglfw.so ${GLFW}/libGL.so)

# target_link_libraries(${out} GL glfw)

