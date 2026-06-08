cmake_minimum_required(VERSION 3.28)

project(FFV LANGUAGES C)

set(CMAKE_C_STANDARD 23)

set(INCLUDING_FOLDERS
    assets
    includes
    src
)

add_executable(${PROJECT_NAME} src/main.c)

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDING_FOLDERS})