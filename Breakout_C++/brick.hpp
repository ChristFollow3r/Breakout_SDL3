#pragma once
#include "rectangle.hpp"

class Brick : public Rectangle {

public:

	bool hasBeenHit = false;

	Brick(SDL_FRect rect, SDL_Renderer* renderer, SDL_Color color) : Rectangle(rect, renderer, color) {};

};