#include "rectangle.hpp"

void Rectangle::draw(SDLState state , SDL_FRect rect) {
	SDL_RenderFillRect(state.renderer, &rect);
}