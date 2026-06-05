cmake_minimum_required(3.28)

project(FFV LANGUAGES C)

set(CMAKE_C_STANDARD 23)

add_executable(ffv src/main.c)

target_include_directories(ffv
    PRIVATE assets
    PRIVATE includes
    PRIVATE src
)