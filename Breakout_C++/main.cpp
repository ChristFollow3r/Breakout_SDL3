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
	auto rectangleTest = std::make_shared<Rectangle>(rect, state.renderer, color);

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
		if (keys[SDL_SCANCODE_A]) rectangleTest->rect.x -= (paddleSpeed * dt);
		if (keys[SDL_SCANCODE_D]) rectangleTest->rect.x += (paddleSpeed * dt);


		if (rectangleTest->rect.x + paddleLength >= width) rectangleTest->rect.x = rightLimit;
		if (rectangleTest->rect.x < 0) rectangleTest->rect.x = leftLimit;

		SDL_SetRenderDrawColor(state.renderer, 0, 0, 0, 255);
		SDL_RenderClear(state.renderer);
		rectangleTest->draw(state, rectangleTest->rect, color);
		SDL_RenderPresent(state.renderer);

		//render(state);

	}

	cleanUp(state);
	return 0;

}
