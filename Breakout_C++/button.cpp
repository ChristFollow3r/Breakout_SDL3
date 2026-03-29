#include "button.hpp"

void Button::Hovered() {

	float x, y;
	SDL_GetMouseState(&x, &y);

	SDL_Color hoverColor = { 200, 200, 200, 255 };
	SDL_Color regularColor = { 255, 255, 255, 255 };

	if (x >= this->rect.x && x <= this->rect.x + this->rect.w && y >= this->rect.y && y <= this->rect.y + this->rect.h) this->color = hoverColor;
	else this->color = regularColor;

}


bool Button::Clicked() {

	float x, y;
	SDL_GetMouseState(&x, &y);

	return (x >= this->rect.x && x <= this->rect.x + this->rect.w && y >= this->rect.y && y <= this->rect.y + this->rect.h);

}

void Button::AddText(SDL_Renderer* renderer) {
	SDL_RenderTexture(renderer, this->texture, nullptr, &this->buttonTextRect);
}