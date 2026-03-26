#include "rectangle.hpp"

class Ball : public Rectangle {

public:

	float ballSpeed = 120.0f;

	Ball(SDL_FRect rect, SDL_Renderer* renderer, SDL_Color color) : Rectangle(rect, renderer, color) {};

	void updateBallPhysics(float ballSpeed);

};
