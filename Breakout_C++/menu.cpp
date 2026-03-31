#include "menu.hpp"

void drawButton(SDLState state, Button* button) {

	button->draw(state, button->rect, button->color);
	button->AddText(state.renderer);
	button->Hovered();
}

void drawText(SDLState state, TTF_Font* font, std::string text, int fontSize, float x, float y, SDL_Color textColor) {

	TTF_SetFontSize(font, fontSize);
	SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), NULL, textColor);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(state.renderer, surface);
	SDL_DestroySurface(surface);
	float textWidth, textHeight;
	SDL_GetTextureSize(texture, &textWidth, &textHeight); // This part I don't understand. AI gave me this (same comment is written somewhere else, I don't remember where).
	SDL_FRect textRect = { x - textWidth / 2, y, textWidth, textHeight };
	SDL_RenderTexture(state.renderer, texture, NULL, &textRect);
	SDL_DestroyTexture(texture);
}