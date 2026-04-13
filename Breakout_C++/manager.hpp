#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include <vector>
#include <memory>
#include "rectangle.hpp"
#include "brick.hpp"
#include "button.hpp"
#include "gameState.hpp"

const int width = 1280;
const int height = 720;

// Text Sutff
// ***************************************************************************************************************************************
static inline float loadScreenWaitingTime = 2.0f;
bool loadingScreen(SDLState state, float dt, TTF_Font* font, SDL_Texture* texture, SDL_FRect textRect);
std::unique_ptr<Button> createButton(TTF_Font* font, SDLState state, std::string buttonText, float xPosition, float yPosition);
// ***************************************************************************************************************************************

void initialize(SDLState& state);
void render(SDLState& state, std::unique_ptr<Rectangle> lPaddle, std::unique_ptr<Rectangle> mPaddle, std::unique_ptr<Rectangle> rPaddle, std::unique_ptr<Rectangle> ball, std::vector<std::vector<std::shared_ptr<Brick>>> gridOfBricks, GameState& gameState);
std::vector<std::vector<std::shared_ptr<Brick>>> createBricks(SDLState& state);



void cleanUp(SDLState& state);

