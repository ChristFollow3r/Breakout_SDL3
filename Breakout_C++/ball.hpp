#include "rectangle.hpp"

class Ball : public Rectangle {

public:

	float ballSpeed = 360.0f;

	Ball(SDL_FRect rect, SDL_Renderer* renderer, SDL_Color color) : Rectangle(rect, renderer, color) {};

	void UpdateBallPhysics(float dt);

};
