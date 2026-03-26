#pragma once
#include <SDL3/SDL.h>
#include <memory>
#include "rectangle.hpp"

struct SDLState {
	SDL_Window* window;
	SDL_Renderer* renderer;
};

void initialize(SDLState& state);
void render(SDLState& state, std::shared_ptr<Rectangle> paddle); // I don't know if doing a function for this is the right move
float deltaTime(Uint64& lastTick);
void cleanUp(SDLState& state);

const int width = 1280;
const int height = 720;
const float paddleSpeed = 500.0f;
