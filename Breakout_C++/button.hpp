#pragma once
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include "rectangle.hpp"
#include "gameState.hpp"

class Button : public Rectangle {

public:

	SDL_Texture* texture;
	SDL_FRect buttonTextRect;

	Button(SDL_FRect rect, SDL_Renderer* renderer, SDL_Color color, SDL_Texture* texture, SDL_FRect buttonTextRect)
	: Rectangle(rect, renderer, color), texture(texture), buttonTextRect(buttonTextRect) {};

	Button(TTF_Font* font, SDLState& state, std::string text, float x, float y)
		: Rectangle({ x, y, 200, 100 }, state.renderer, { 255, 255, 255, 255 }) {
		TTF_SetFontSize(font, 24);
		SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), 0, { 0, 0, 0, 255 });
		texture = SDL_CreateTextureFromSurface(state.renderer, surface);
		SDL_DestroySurface(surface);
		float tw, th;
		SDL_GetTextureSize(texture, &tw, &th);
		buttonTextRect = { x + (200 - tw) / 2, y + (100 - th) / 2, tw, th };
	}

	void Hovered();
	bool Clicked();
	
	void DrawButton(SDLState& state);
	void AddText(SDL_Renderer* renderer);

};