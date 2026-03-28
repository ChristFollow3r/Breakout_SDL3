#include "button.hpp"


//Regular: { 180, 160, 50, 255 } — muted yellow
//Hover : { 230, 210, 80, 255 } — brighter yellow
//Click : { 255, 240, 120, 255 } — almost white yellow

void Button::Hovered() {

	float x, y;
	SDL_GetMouseState(&x, &y);

	SDL_Color hoverColor = { 230, 210, 80, 255 };
	SDL_Color regularColor = { 180, 160, 50, 255 };

	if (x >= this->rect.x && x <= this->rect.x + this->rect.w && y >= this->rect.y && y <= this->rect.y + this->rect.h) this->color = hoverColor;
	else this->color = regularColor;

}


void Button::Clicked(bool clicked) {

	float x, y;
	SDL_GetMouseState(&x, &y);

	SDL_Color clickedColor = { 255, 240, 120, 255 };
	SDL_Color regularColor = { 180, 160, 50, 255 };

	if (x >= this->rect.x && x <= this->rect.x + this->rect.w && y >= this->rect.y && y <= this->rect.y + this->rect.h && clicked) this->color = clickedColor;
	else this->color = regularColor;

}