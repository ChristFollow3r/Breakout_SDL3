#include "menu.hpp"

void drawButton(SDLState state, Button* button) {

	button->draw(state, button->rect, button->color);
	button->AddText(state.renderer);
	button->Hovered();
}

// This file is leftovers from something that didn't work at all but right now im to scared to change anything so this is going to stay like this