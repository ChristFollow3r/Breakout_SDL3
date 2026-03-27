#include "ball.hpp"
#include "manager.hpp"

void Ball::UpdateBallPhysics(std::shared_ptr<Rectangle> lPaddle, std::shared_ptr<Rectangle> mPaddle, std::shared_ptr<Rectangle> rPaddle, float dt) {
	this->rect.x += ballXSpeed * dt;
	this->rect.y += ballYSpeed * dt;
	this->CheckCollisions(lPaddle, mPaddle, rPaddle);
}

void Ball::CheckCollisions(std::shared_ptr<Rectangle> lPaddle, std::shared_ptr<Rectangle> mPaddle, std::shared_ptr<Rectangle> rPaddle) {

	if (SDL_HasRectIntersectionFloat(&this->rect, &lPaddle->rect)) {
		ballXSpeed = -abs(ballXConstSpeed); // abs returns an absolute value
		ballYSpeed = -abs(ballYSpeed); 
		this->rect.y = height - ((height - lPaddle->rect.y) + ballSize);
	}

	if (SDL_HasRectIntersectionFloat(&this->rect, &mPaddle->rect)) {
		ballXSpeed = 0.0f;
		ballYSpeed = -abs(ballYSpeed); // Fix this ball goes slow
		this->rect.y = height - ((height - lPaddle->rect.y) + ballSize);
	}

	if (SDL_HasRectIntersectionFloat(&this->rect, &rPaddle->rect)) {
		ballXSpeed = abs(ballXConstSpeed);
		ballYSpeed = -abs(ballYSpeed); 
		this->rect.y = height - ((height - lPaddle->rect.y) + ballSize);
	}

	if (this->rect.y <= 0) { // Top side
		ballYSpeed = -ballYSpeed;
		this->rect.y = 0;
	}

	if (this->rect.x + ballSize >= width) { // Right side
		ballXSpeed = -ballXSpeed;
		this->rect.x = width - ballSize;
	}
	if (this->rect.x <= 0) { // Left side
		ballXSpeed = -ballXSpeed;
		this->rect.x = 0;
	}
}