#include "ball.hpp"
#include "manager.hpp"
#include "gameplay.hpp"


float timer = Ball::ballSpawnTimer;
bool isDead = false;

void Ball::UpdateBallPhysics(std::shared_ptr<Rectangle> lPaddle, std::shared_ptr<Rectangle> mPaddle, std::shared_ptr<Rectangle> rPaddle, float dt, int& lifes, GameState& gameState) {

	if (this->rect.y > height + 40) {

		if (!isDead) {
			isDead = true;
			lifes--;
			if (lifes <= 0) {
				gameState = NAME_INPUT;
				return;
			}

		}

		timer -= dt;

		if (timer < 0) {
			this->rect.x = 640;
			this->rect.y = 640;
			ballYSpeed = -abs(ballYSpeed);
			timer = Ball::ballSpawnTimer;
			isDead = false;
		}

		return;
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
		ballYSpeed = -ballXConstSpeed - 155; // Yeah magic number but very much needed. It fucks up the making the ball faster mechanic but whatever, it's a feature now.
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