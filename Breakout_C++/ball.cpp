#include "ball.hpp"
#include "manager.hpp"

void Ball::UpdateBallPhysics(float dt, std::shared_ptr<Rectangle> paddle) {
	this->rect.x += ballXSpeed * dt;
	this->rect.y += ballYSpeed * dt;
	this->CheckCollisions(paddle);
}

void Ball::CheckCollisions(std::shared_ptr<Rectangle> paddle) {
	if (SDL_HasRectIntersectionFloat(&this->rect, &paddle->rect)) {
		ballYSpeed = -ballYSpeed;
		this->rect.y = height - ((height - paddle->rect.y) + ballSize);
	}


	if (this->rect.y <= 0) {
		ballYSpeed = -ballYSpeed;
		this->rect.y = 0;
	}

	if (this->rect.x + ballSize >= width) {
		ballXSpeed = -ballXSpeed;
		this->rect.x = width - ballSize;
	}
	if (this->rect.x <= 0) {
		ballXSpeed = -ballXSpeed;
		this->rect.x = 0;
	}
}