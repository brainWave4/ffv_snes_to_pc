cmake_minimum_required(VERSION 3.28)

project(FFV LANGUAGES C)

set(CMAKE_C_STANDARD 23)

add_executable(${PROJECT_NAME} src/main.c)

target_include_directories(${PROJECT_NAME}
    PRIVATE assets
    PRIVATE includes
    PRIVATE src
)