#pragma once
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include "gameState.hpp"

inline const int width = 1280;
inline const int height = 720;

inline float deltaTime(Uint64& lastTick) {
	Uint64 currentTick = SDL_GetTicks();
	Uint64 elapedTick = currentTick - lastTick;
	lastTick = currentTick;

	return static_cast<float>(elapedTick / 1000.0f);
}

inline void initialize(SDLState& state) {

	state.window = SDL_CreateWindow("Breakout", width, height, NULL);
	state.renderer = SDL_CreateRenderer(state.window, nullptr);

	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Unable to initialize SDL3", nullptr);
	}

	if (!state.window) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error creating window", nullptr);
	}

	if (!state.renderer) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error initializingh renderer.", nullptr);
	}
}

inline void cleanUp(SDLState& state) {
	SDL_DestroyRenderer(state.renderer);
	SDL_DestroyWindow(state.window);
	SDL_Quit();
}

inline void drawText(SDLState state, TTF_Font* font, std::string text, int fontSize, float x, float y, SDL_Color textColor) {

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