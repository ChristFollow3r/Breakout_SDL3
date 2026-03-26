#pragma once
#include <SDL3/SDL.h>

struct SDLState {
	SDL_Window* window;
	SDL_Renderer* renderer;
};

void initialize(SDLState& state);
//void render(SDLState& state);
float deltaTime(Uint64& lastTick);
void cleanUp(SDLState& state);

const int width = 1280;
const int height = 720;
const float paddleSpeed = 500.0f;
