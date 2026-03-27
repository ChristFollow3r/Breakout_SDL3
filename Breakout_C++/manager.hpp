#pragma once
#include <SDL3/SDL.h>
#include <iostream>
#include <memory>
#include "rectangle.hpp"

const int width = 1280;
const int height = 720;
const float paddleSpeed = 500.0f;
const int paddleLength = 100;
const int paddleRightLimit = width - paddleLength;
const int paddleLeftLimit = 0;

struct SDLState {
	SDL_Window* window;
	SDL_Renderer* renderer;
};

void initialize(SDLState& state);
void render(SDLState& state, std::shared_ptr<Rectangle> paddle, std::shared_ptr<Rectangle> ball);

void paddleMovement(std::shared_ptr<Rectangle> paddle, float dt);
void paddleBorderCollisions(std::shared_ptr<Rectangle> paddle);

float deltaTime(Uint64& lastTick);
void cleanUp(SDLState& state);

