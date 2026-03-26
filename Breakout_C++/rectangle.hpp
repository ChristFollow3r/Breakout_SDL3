#pragma once
#include <SDL3/SDL.h>

struct SDLState; // I had to ask AI this. I was having truble with circular libraries

class Rectangle {

public:

	SDL_FRect rect;
	SDL_Renderer* renderer;
	SDL_Color color;

	Rectangle(SDL_FRect rect, SDL_Renderer* renderer, SDL_Color color) : rect(rect), renderer(renderer), color(color) {};

	void draw(SDLState state, SDL_FRect rect, SDL_Color color);
};