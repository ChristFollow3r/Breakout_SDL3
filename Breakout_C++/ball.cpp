#include "ball.hpp"
#include "manager.hpp"

void Ball::UpdateBallPhysics(float dt, std::shared_ptr<Rectangle> paddle) {
	this->rect.x += ballXSpeed * dt;
	this->rect.y += ballYSpeed * dt;
	this->CheckCollisions(paddle);
}

void Ball::CheckCollisions(std::shared_ptr<Rectangle> paddle) {
	if (SDL_HasRectIntersectionFloat(&this->rect, &paddle->rect)) ballYSpeed = -ballYSpeed;
	if (this->rect.y < 0) ballYSpeed = -ballYSpeed;

	if (this->rect.x + GetBallSize() > width) ballXSpeed = -ballXSpeed;
	if (this->rect.x < 0) ballXSpeed = -ballXSpeed;
}