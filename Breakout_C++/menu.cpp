#include "menu.hpp"

void menu(SDLState state, Button* playButton, Button* rankingButton, Button* exitButton) {

	




}

void drawButton(SDLState state, Button* button) {

	button->draw(state, button->rect, button->color);
	button->AddText(state.renderer);
	button->Hovered();
}
