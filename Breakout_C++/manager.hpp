#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include <vector>
#include <memory>
#include "rectangle.hpp"
#include "brick.hpp"
#include "button.hpp"

const int width = 1280;
const int height = 720;
struct SDLState {
	SDL_Window* window;
	SDL_Renderer* renderer;
};

// Text Sutff
// ***************************************************************************************************************************************
static inline float loadScreenWaitingTime = 5.0f;
bool loadingScreen(SDLState state, float dt, TTF_Font* font, SDL_Texture* texture, SDL_FRect textRect);
std::unique_ptr<Button> createButton(TTF_Font* font, SDLState state, std::string buttonText, float xPosition, float yPosition);
// ***************************************************************************************************************************************

// Breakout stuff
// ***************************************************************************************************************************************
const float paddleSpeed = 600.0f;
const int paddleLength = 33;
const int paddleRightLimit = width - paddleLength;
const int paddleLeftLimit = 0;

void initialize(SDLState& state);
void render(SDLState& state, std::shared_ptr<Rectangle> lPaddle, std::shared_ptr<Rectangle> mPaddle, std::shared_ptr<Rectangle> rPaddle, std::shared_ptr<Rectangle> ball, std::vector<std::vector<std::shared_ptr<Brick>>> gridOfBricks);
std::vector<std::vector<std::shared_ptr<Brick>>> createBricks(SDLState& state);
float deltaTime(Uint64& lastTick);

void paddleMovement(std::shared_ptr<Rectangle> lPaddle, std::shared_ptr<Rectangle> mPaddle, std::shared_ptr<Rectangle> rPaddle, float dt);
void paddleBorderCollisions(std::shared_ptr<Rectangle> lPaddle, std::shared_ptr<Rectangle> mPaddle, std::shared_ptr<Rectangle> rPaddle);
bool brickCollisions(std::vector<std::vector<std::shared_ptr<Brick>>>& gridOfBricks, std::shared_ptr<Rectangle> ball);

// ***************************************************************************************************************************************


void cleanUp(SDLState& state);

