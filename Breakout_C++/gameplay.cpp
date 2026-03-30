#include "gameplay.hpp"
#include "menu.hpp"
#include <string>

float pointAdder = 0.0f;

void breakoutGameplay(SDLState state,
	std::vector<std::vector<std::shared_ptr<Brick>>>& gridOfBricks,
	std::shared_ptr<Rectangle> lPaddle,
	std::shared_ptr<Rectangle> mPaddle,
	std::shared_ptr<Rectangle> rPaddle,
	std::shared_ptr<Ball> ball,
	float dt,
	int& lifes,
	int& points,
	GameState& gameState, 
	TTF_Font* font) {

	waitTimer += dt;
	pointAdder += dt;

	if (pointAdder > 1.0f) {
		points += 15;
		pointAdder = 0.0f;
	}


	SDL_Color black = { 0, 0, 0, 255 };

	paddleMovement(lPaddle, mPaddle, rPaddle, dt);
	paddleBorderCollisions(lPaddle, mPaddle, rPaddle);

	if (waitTimer > 1.0f) ball->UpdateBallPhysics(lPaddle, mPaddle, rPaddle, dt, lifes, gameState);
	if (brickCollisions(gridOfBricks, ball)) { // I made a bouncing on the sides version of this function but it was too unreliable so I scrapped it
		ball->ballYSpeed = -ball->ballYSpeed;
		points += 100;
	}

	render(state, lPaddle, mPaddle, rPaddle, ball, gridOfBricks);
	drawText(state, font, std::to_string(lifes), 38, width - 25,  0, black);
	drawText(state, font, std::to_string(points), 38, 75, 0, black);
	SDL_RenderPresent(state.renderer);

}
