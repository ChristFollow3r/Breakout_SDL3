#include <SDL3/SDL_main.h>
#include <iostream>
#include <memory>
#include "manager.hpp"
#include "rectangle.hpp"
#include "ball.hpp"

int main(int arg, char* argv[]) {
	
	SDLState state;
	initialize(state);

	bool running = true;

	Uint64 lastTick = SDL_GetTicks();
	deltaTime(lastTick);

	std::vector<std::vector<std::shared_ptr<Brick>>> gridOfBricks = createBricks(state);
	
	SDL_Color paddleColor = { 255, 0, 0, 255 }; 
	SDL_FRect rect = { 640, 640, paddleLength, 10 };
	auto lPaddle = std::make_shared<Rectangle>(rect, state.renderer, paddleColor); // Not worth making a function just to create a pointer
	rect.x += paddleLength;
	auto mPaddle = std::make_shared<Rectangle>(rect, state.renderer, paddleColor);
	rect.x += paddleLength;
	auto rPaddle = std::make_shared<Rectangle>(rect, state.renderer, paddleColor);


	SDL_Color ballColor = { 0, 0, 0, 255 };
	rect = { 720, 550, Ball::ballSize , Ball::ballSize };
	auto ball = std::make_shared<Ball>(rect, state.renderer, ballColor);
	ball->ballYSpeed = -ball->ballYSpeed;
	
	float waitTimer = 0.0f;

	createBricks(state);	

	while (running) {

		SDL_Event event{0};
		float dt = deltaTime(lastTick);

		while (SDL_PollEvent(&event)) {
			switch (event.type) {

			case SDL_EVENT_QUIT:
				cleanUp(state);
				running = false;
				break;
			}
		}
		
		waitTimer += dt;

		if (waitTimer > 5.0f) ball->UpdateBallPhysics(dt, lPaddle);

		paddleMovement(lPaddle, mPaddle, rPaddle, dt);
		paddleBorderCollisions(lPaddle);
		if (brickCollisions(gridOfBricks, ball)) ball->ballYSpeed = -ball->ballYSpeed; // I made a bouncing on the sides version of this function but it was too unreliable so I scrapped it

		render(state, lPaddle, mPaddle, rPaddle, ball, gridOfBricks);

	}

	cleanUp(state);
	return 0;

}
