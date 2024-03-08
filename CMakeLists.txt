cmake_minimum_required(VERSION 3.27)
project(Cpp_Game_from_Scratch)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(LIGHT_YEARS_GAME_TARGET_NAME LightYearsGame)

add_subdirectory(LightYears)

include(FetchContent)
set(SFML_LIB_NAME SFML)

FetchContent_Declare(
        ${SFML_LIB_NAME}
        GIT_REPOSITORY https://github.com/SFML/SFML
        GIT_TAG 2.6.1
        GIT_SHALLOW FALSE
)

FetchContent_MakeAvailable(${SFML_LIB_NAME})

target_link_libraries(${LIGHT_YEARS_GAME_TARGET_NAME} PUBLIC sfml-graphics)
target_link_libraries(${LIGHT_YEARS_GAME_TARGET_NAME} PUBLIC sfml-window)
target_link_libraries(${LIGHT_YEARS_GAME_TARGET_NAME} PUBLIC sfml-system)
target_link_libraries(${LIGHT_YEARS_GAME_TARGET_NAME} PUBLIC sfml-audio)