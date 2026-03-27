#pragma once
#include <SDL3/SDL.h>
#include <iostream>
#include <vector>
#include <memory>
#include "rectangle.hpp"
#include "brick.hpp" // Se que no necessito aquesta llibreria que ho podria fer amb rectangles pero aixi es mes fàcil de llegir crec

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
void render(SDLState& state, std::shared_ptr<Rectangle> paddle, std::shared_ptr<Rectangle> ball, std::vector<std::vector<std::shared_ptr<Brick>>> gridOfBricks);

std::vector<std::vector<std::shared_ptr<Brick>>> createBricks(SDLState& state);

void paddleMovement(std::shared_ptr<Rectangle> paddle, float dt);
void paddleBorderCollisions(std::shared_ptr<Rectangle> paddle);
void brickCollisions(std::vector<std::vector<std::shared_ptr<Brick>>>& gridOfBricks, std::shared_ptr<Rectangle> ball);

float deltaTime(Uint64& lastTick);
void cleanUp(SDLState& state);

