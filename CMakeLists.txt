cmake_minimum_required(VERSION 3.8)
project(a1)

set(CMAKE_CXX_STANDARD 11)


set(SOURCE_FILES
        snake-basic.cpp Displayable.h Text.cpp Text.h Fruit.cpp Fruit.h Block.cpp Block.h Snake.cpp Snake.h common.h Controller.cpp Controller.h)

add_executable(a1 ${SOURCE_FILES})

find_package(X11 REQUIRED)
include_directories(${X11_INCLUDE_DIR})
target_link_libraries(a1 ${X11_LIBRARIES})
