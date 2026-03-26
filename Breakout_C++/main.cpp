#include <SDL3/SDL_main.h>
#include <iostream>
#include <memory>
#include "manager.hpp"
#include "rectangle.hpp"

int main(int arg, char* argv[]) {
	
	SDLState state;
	initialize(state);

	bool running = true;

	Uint64 lastTick = SDL_GetTicks();
	deltaTime(lastTick);
	
	SDL_Color color = { 255, 0, 0, 255 }; // Not worth making a function just to create a pointer
	SDL_FRect rect = { 640, 640, paddleLength, 10 };
	auto paddle = std::make_shared<Rectangle>(rect, state.renderer, color);

	while (running) {

		SDL_Event event{0};

		while (SDL_PollEvent(&event)) {
			switch (event.type) {

			case SDL_EVENT_QUIT:
				cleanUp(state);
				running = false;
				break;
			}
		}

		float dt = deltaTime(lastTick);

		paddleMovement(paddle, dt);
		paddleBorderCollisions(paddle);

		render(state, paddle);

	}

	cleanUp(state);
	return 0;

}
