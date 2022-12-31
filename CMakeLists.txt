cmake_minimum_required(VERSION 3.12)
project(cells)
set(CMAKE_CXX_STANDARD 11)

add_subdirectory(lib/piksel)

set(SOURCES
    src/main.cpp
    src/app.cpp
    src/game/cell.cpp
    src/game/food.cpp
    src/objects/world.cpp
    src/utils/geometry.cpp
)
add_executable(index ${SOURCES})
target_include_directories(index
    PUBLIC include
    PUBLIC lib/piksel/src
)
target_link_libraries(index
    piksel
)