#include "menu.hpp"

GameState menu(SDLState state, Button* playButton, Button* rankingButton, Button* exitButton) {

	GameState gameState;

	if (playButton->Clicked()) {
		gameState = GAME;
		return gameState;
	}

	if (rankingButton->Clicked()) {
		gameState = RANKING;
		return gameState;
	}

	if (exitButton->Clicked()) {
		gameState = EXIT;
		return gameState;
	}

}

void drawButton(SDLState state, Button* button) {

	button->draw(state, button->rect, button->color);
	button->AddText(state.renderer);
	button->Hovered();
}
