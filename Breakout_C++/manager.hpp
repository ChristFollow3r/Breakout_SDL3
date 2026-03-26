#pragma once
#include <SDL3/SDL.h>

struct SDLState {
	SDL_Window* window;
	SDL_Renderer* renderer;
};

void initialize(SDLState& state);
//void render(SDLState& state);
void cleanUp(SDLState& state);