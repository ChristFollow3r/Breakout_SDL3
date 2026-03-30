#pragma once
#include "manager.hpp"
#include "gameState.hpp"
#include "button.hpp"

void drawButton(SDLState state, Button* button);
GameState menu(SDLState state, Button* playButton, Button* rankingButton, Button* exitButton);

//void rankingScreen();
