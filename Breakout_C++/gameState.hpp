#pragma once

struct SDLState {
	SDL_Window* window;
	SDL_Renderer* renderer;
};

enum GameState {
    MENU,
    GAME,
    RANKING,
    NAME_INPUT,
    CREDITS,
    EXIT
};