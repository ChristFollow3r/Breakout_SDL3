#pragma once
#include "rectangle.hpp"

class Button : public Rectangle {

public:

	SDL_Texture* texture;
	SDL_FRect buttonTextRect;

	Button(SDL_FRect rect, SDL_Renderer* renderer, SDL_Color color, SDL_Texture* texture, SDL_FRect buttonTextRect)
	: Rectangle(rect, renderer, color), texture(texture), buttonTextRect(buttonTextRect) {};

	void Hovered();
	bool Clicked();
	void AddText(SDL_Renderer* renderer);

};