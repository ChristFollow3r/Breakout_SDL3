#include <SDL3/SDL_main.h>
#include <iostream>
#include <memory>
#include "manager.hpp"
#include "rectangle.hpp"

int main(int arg, char* argv[]) {
	
	SDLState state;
	initialize(state);

	bool running = true;
	int paddleLength = 100;
	int rightLimit = width - paddleLength;
	int leftLimit = 0;

	Uint64 lastTick = SDL_GetTicks();
	deltaTime(lastTick);
	
	SDL_Color color = { 255, 0, 0, 255 };
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

		const bool* keys = SDL_GetKeyboardState(nullptr);
		if (keys[SDL_SCANCODE_A]) paddle->rect.x -= (paddleSpeed * dt);
		if (keys[SDL_SCANCODE_D]) paddle->rect.x += (paddleSpeed * dt);

		if (paddle->rect.x + paddleLength >= width) paddle->rect.x = rightLimit;
		if (paddle->rect.x < 0) paddle->rect.x = leftLimit;

		render(state, paddle);

	}

	cleanUp(state);
	return 0;

}
