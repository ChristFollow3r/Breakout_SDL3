#include "menu.hpp"

void drawButton(SDLState state, Button* button) {

	button->draw(state, button->rect, button->color);
	button->AddText(state.renderer);
	button->Hovered();
}

void bigEnterTextDisplay(SDLState state, TTF_Font* font) {
	TTF_SetFontSize(font, 68);
	SDL_Surface* surface = TTF_RenderText_Blended(font, "ENTER YOUR NAME", NULL, { 255, 255, 255, 255 });
	SDL_Texture* texture = SDL_CreateTextureFromSurface(state.renderer, surface);
	SDL_DestroySurface(surface);
	float inputTextWidth, inputTextHeight;
	SDL_GetTextureSize(texture, &inputTextWidth, &inputTextHeight);
	//SDL_FRect bigEnterTextDisplayRect = { (width / 2 - inputTextWidth / 2), (height / 2 + height / 2), inputTextWidth, inputTextHeight };
	SDL_FRect bigEnterTextDisplayRect = { (width / 2 - inputTextWidth / 2), (200), inputTextWidth, inputTextHeight }; // The y is hardcoded but I don't care
	SDL_RenderTexture(state.renderer, texture, NULL, &bigEnterTextDisplayRect);
	SDL_DestroyTexture(texture);
}

void drawInputText(SDLState state, TTF_Font* font, std::string playerName) { // I should do an override of this function but lazines has one this battle.
	TTF_SetFontSize(font, 24); // Reset the font so it doesn't have the size of the loading scene thing
	SDL_Surface* surface = TTF_RenderText_Blended(font, playerName.c_str(), 0, { 0, 0, 0, 255 }); // We get the playerName string as the const string for the surface
	SDL_Texture* texture = SDL_CreateTextureFromSurface(state.renderer, surface); // Btw blended makes it so it has antializing (I think thats how you write it) so that the text isn't pixelated.
	SDL_DestroySurface(surface); // Destroy the surface cause it's not needed once the texture is created
	float inputTextWidth, inputTextHeight;
	SDL_GetTextureSize(texture, &inputTextWidth, &inputTextHeight); // AI gave me this I still struggle to understand it
	SDL_FRect textRect = { (width / 2 - inputTextWidth / 2), (height / 2 - inputTextHeight / 2), inputTextWidth, inputTextHeight };
	SDL_RenderTexture(state.renderer, texture, NULL, &textRect);
	SDL_DestroyTexture(texture);
}