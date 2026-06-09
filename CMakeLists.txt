cmake_minimum_required(VERSION 3.28)

project(FFV LANGUAGES C)

set(CMAKE_C_STANDARD 23)

set(INCLUDING_FOLDERS
    "assets"
    "includes"
    "src"
)

find_package(SDL3 REQUIRED)

add_executable(${PROJECT_NAME} src/main.c)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDING_FOLDERS})