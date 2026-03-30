#include "gameplay.hpp"
#include "menu.hpp"
#include <string>

void breakoutGameplay(SDLState state,
	std::vector<std::vector<std::shared_ptr<Brick>>>& gridOfBricks,
	std::shared_ptr<Rectangle> lPaddle,
	std::shared_ptr<Rectangle> mPaddle,
	std::shared_ptr<Rectangle> rPaddle,
	std::shared_ptr<Ball> ball,
	float dt,
	int& lifes,
	GameState& gameState, TTF_Font* font) {

	waitTimer += dt;
	SDL_Color lifesColor = { 0, 0, 0, 255 };

	paddleMovement(lPaddle, mPaddle, rPaddle, dt);
	paddleBorderCollisions(lPaddle, mPaddle, rPaddle);

	if (waitTimer > 1.0f) ball->UpdateBallPhysics(lPaddle, mPaddle, rPaddle, dt, lifes, gameState);
	if (brickCollisions(gridOfBricks, ball)) ball->ballYSpeed = -ball->ballYSpeed; // I made a bouncing on the sides version of this function but it was too unreliable so I scrapped it

	render(state, lPaddle, mPaddle, rPaddle, ball, gridOfBricks);
	drawText(state, font, std::to_string(lifes), 38, width - 25,  0, lifesColor);
	SDL_RenderPresent(state.renderer);

}
