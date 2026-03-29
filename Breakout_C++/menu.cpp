#include "menu.hpp"

void menu(SDLState state, Button* playButton, Button* rankingButton, Button* exitButton) {

	




}

void drawButton(SDLState state, Button* button) {

	SDL_SetRenderDrawColor(state.renderer, 0, 0, 0, 255); 
	SDL_RenderClear(state.renderer);
	button->draw(state, button->rect, button->color);
	button->AddText(state.renderer);
	button->Hovered();
	SDL_RenderPresent(state.renderer);
}