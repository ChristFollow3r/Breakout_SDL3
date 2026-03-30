#pragma once
#include "manager.hpp"
#include "gameState.hpp"
#include "button.hpp"

void drawButton(SDLState state, Button* button);
void drawText(SDLState state, TTF_Font* font, std::string text, int fontSize, float x, float y, SDL_Color textColor);

//void rankingScreen();
