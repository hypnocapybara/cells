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
add_executable(main ${SOURCES})
target_include_directories(main
    PUBLIC include
    PUBLIC lib/piksel/src
)
target_link_libraries(main
    piksel
)
