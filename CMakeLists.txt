cmake_minimum_required(VERSION 3.15)
set(CMAKE_EXPORT_COMPILE_COMMANDS On)

project(OceanBattle)

add_executable(OceanBattle main.cpp

    "src/WindowService.cpp"
    "src/LocalMap.cpp"
    "src/Map.cpp"
    "src/read.cpp"
)

include_directories(
    "inc"
)

target_link_libraries( OceanBattle
    sfml-graphics
    sfml-window
    sfml-system
    GL
    GLEW
)