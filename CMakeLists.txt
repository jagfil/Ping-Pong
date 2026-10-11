cmake_minimum_required(VERSION 3.27)
project(PingPong)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML
        GIT_TAG        2.6.1
)

set(BUILD_SHARED_LIBS FALSE CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(SFML)

add_executable(PingPong
        main.cpp
        Paddle.hpp
        Ball.hpp
)

target_compile_definitions(PingPong PRIVATE SFML_STATIC)

target_link_libraries(PingPong PRIVATE sfml-graphics sfml-window sfml-system)

