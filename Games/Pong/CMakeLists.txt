project(PongGameProject LANGUAGES CXX)

set(PONG_SOURCES
        Source/main.cpp
        Source/PongGame.cpp
        Source/PongGame.h
)

add_executable(Game_Pong ${PONG_SOURCES})

target_include_directories(Game_Pong
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Source
)

target_link_libraries(Game_Pong
        PRIVATE
        MicroLib
)