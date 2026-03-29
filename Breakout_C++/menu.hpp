#pragma once
#include "manager.hpp"
#include "button.hpp"
#include "ball.hpp"

void drawButton(SDLState state, Button* button);

void menu(SDLState state, Button* playButton, Button* rankingButton, Button* exitButton);

void rankingScreen();
