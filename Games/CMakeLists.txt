project(MicroGames LANGUAGES CXX)

function(add_micro_game GAME_NAME)
    add_subdirectory(${GAME_NAME})
endfunction()

add_micro_game(Pong)
