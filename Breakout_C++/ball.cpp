#include "ball.hpp"

void Ball::UpdateBallPhysics(float dt, std::shared_ptr<Rectangle> paddle) {
	this->rect.y += ballSpeed * dt;
	this->CheckCollisions(paddle);
}

void Ball::CheckCollisions(std::shared_ptr<Rectangle> paddle) {
	if (SDL_HasRectIntersectionFloat(&this->rect, &paddle->rect)) ballSpeed = -ballSpeed;
}