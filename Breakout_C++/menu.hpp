#pragma once
#include "manager.hpp"
#include "gameState.hpp"
#include "button.hpp"

void drawButton(SDLState state, Button* button);
void bigEnterTextDisplay(SDLState state,  TTF_Font* font);
void drawInputText(SDLState state, TTF_Font* font, std::string playerName);

//void rankingScreen();
