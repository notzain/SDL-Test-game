set(GAME_SRC
    src/main.cpp
)

add_executable(SDL_Game ${GAME_SRC})

target_link_libraries(SDL_Game engine)