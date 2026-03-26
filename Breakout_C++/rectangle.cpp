#include "rectangle.hpp"
#include "manager.hpp"

void Rectangle::draw(SDLState state , SDL_FRect rect, SDL_Color color) {
	SDL_SetRenderDrawColor(state.renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(state.renderer, &rect);
}