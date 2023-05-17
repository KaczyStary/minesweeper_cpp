cmake_minimum_required(VERSION 3.23)
project(minesweeper_ff)

set(CMAKE_CXX_STANDARD 17)

add_executable(minesweeper_ff main.cpp Game.cpp Game.h MinesweeperBoard.cpp MinesweeperBoard.h MouseInput.cpp MouseInput.h Button.cpp Button.h)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

INCLUDE_DIRECTORIES(C:/SFML/include)
TARGET_LINK_LIBRARIES(minesweeper_ff sfml-system sfml-window sfml-graphics sfml-audio)