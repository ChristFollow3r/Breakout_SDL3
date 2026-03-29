#pragma once
#include "manager.hpp"
#include "button.hpp"
#include "ball.hpp"

enum GameState {
	MENU,
	GAME,
	RANKING,
	CREDITS,
	EXIT
};

void drawButton(SDLState state, Button* button);
GameState menu(SDLState state, Button* playButton, Button* rankingButton, Button* exitButton);

//void rankingScreen();
