cmake_minimum_required (VERSION 3.00...3.31)
project(GLBox VERSION 1.0
              LANGUAGES CXX)

# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
# https://cmake.org/cmake/help/latest/manual/cmake-presets.7.html
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set (CMAKE_BUILD_TYPE "Debug")
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

set (src_dir "${PROJECT_SOURCE_DIR}/src/")
set (vendor_dir "${PROJECT_SOURCE_DIR}/src/vendor/")

# file (GLOB src_files "${src_dir}/*.cpp" "${src_dir}/*/*.cpp" "${src_dir}/*/*/*.cpp" "${vendor_dir}/*/*.cpp")
file(GLOB_RECURSE src_files 
    ${src_dir}/GLBox/Core/*.cpp     ${src_dir}/GLBox/Core/*.h
    ${src_dir}/GLBox/ImGui/*.cpp    ${src_dir}/GLBox/ImGui/*.h
    ${src_dir}/GLBox/Renderer/*.cpp ${src_dir}/GLBox/Renderer/*.h
    ${src_dir}/GLBox/Events/*.cpp   ${src_dir}/GLBox/Events/*.h
    ${src_dir}/ExampleLayers/*.cpp  ${src_dir}/ExampleLayers/*.h
)
file(GLOB vendor_files 
    ${vendor_dir}/glm/*.cpp ${vendor_dir}/glm/*.h ${vendor_dir}/glm/*.hpp
    ${vendor_dir}/stb/*.cpp ${vendor_dir}/stb/*.h
    ${vendor_dir}/imgui/*.cpp ${vendor_dir}/imgui/*.h
)

add_compile_definitions(GLEW_STATIC)
add_library(${PROJECT_NAME} ${src_files} ${vendor_files})
target_include_directories(${PROJECT_NAME} PUBLIC ${src_dir} ${vendor_dir} ${vendor_dir}/imgui)
target_link_libraries(${PROJECT_NAME} GL GLEW glfw)
