cmake_minimum_required(VERSION 3.28)

project(FFV LANGUAGES C)

set(CMAKE_C_STANDARD 23)

set(INCLUDING_FOLDERS
    assets/data
    assets/pal
    assets/textures
    assets/txt/jp
    includes
)

set(INCLUDING_SRC
    src/main.c
    src/battle.c
    src/btlgfx.c
    src/cutscene.c
    src/display.c
    src/field.c
    src/menu.c
    src/sound.c
)

find_package(SDL3 REQUIRED)

add_executable(${PROJECT_NAME} ${INCLUDING_SRC})

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDING_FOLDERS})