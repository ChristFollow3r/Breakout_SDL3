#include "ball.hpp"
#include "manager.hpp"


float timer = Ball::ballSpawnTimer;

void Ball::UpdateBallPhysics(std::shared_ptr<Rectangle> lPaddle, std::shared_ptr<Rectangle> mPaddle, std::shared_ptr<Rectangle> rPaddle, float dt) {


	if (this->rect.y > height + 100) {

		timer -= dt;

		if (timer < 0) {
			this->rect.x = 640;
			this->rect.y = 640;
			ballYSpeed = -abs(ballYSpeed);
			timer = 3.0f; // Fuck this shit bro
		}
	}

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

	else if (SDL_HasRectIntersectionFloat(&this->rect, &mPaddle->rect)) {
		ballXSpeed = 0.0f;
		ballYSpeed = -ballXConstSpeed - 155; // Yeah magic number but very much needed
		this->rect.y = height - ((height - lPaddle->rect.y) + ballSize);
	}

	else if (SDL_HasRectIntersectionFloat(&this->rect, &rPaddle->rect)) {
		ballXSpeed = abs(ballXConstSpeed);
		ballYSpeed = -abs(ballYSpeed); // This might seem stupid but, if the ballYSpeed is already negative, negating it won't do shit, this way we ensure the value remains negative
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