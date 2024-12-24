cmake_minimum_required (VERSION 3.00...3.31)
project(GLBox VERSION 1.0
              LANGUAGES CXX)

# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)
set (src_dir "${PROJECT_SOURCE_DIR}/src/")
set (vendor_dir "${PROJECT_SOURCE_DIR}/src/vendor/")

# file (GLOB src_files "${src_dir}/*.cpp" "${src_dir}/*/*.cpp" "${src_dir}/*/*/*.cpp" "${vendor_dir}/*/*.cpp")
file(GLOB_RECURSE src_files ${src_dir}*.cpp ${src_dir}*.h)

add_compile_definitions(GLEW_STATIC)
add_library(${PROJECT_NAME} ${src_files})
target_include_directories(${PROJECT_NAME} PUBLIC ${src_dir} ${vendor_dir})
target_link_libraries(${PROJECT_NAME} GL GLEW glfw)
