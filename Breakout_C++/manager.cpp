#include "manager.hpp"

void initialize(SDLState& state){

	state.window = SDL_CreateWindow("Breakout", width, height, NULL);
	state.renderer = SDL_CreateRenderer(state.window, nullptr);

	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Unable to initialize SDL3", nullptr);
	}

	if (!state.window) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error creating window", nullptr);
	}

	if (!state.renderer) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error initializingh renderer.", nullptr);
	}
}

void render(SDLState& state, std::shared_ptr<Rectangle> paddle, std::shared_ptr<Rectangle> ball) {
	SDL_SetRenderDrawColor(state.renderer, 255, 255, 255, 255);
	SDL_RenderClear(state.renderer);
	ball->draw(state, ball->rect, ball->color);
	paddle->draw(state, paddle->rect, paddle->color);
	SDL_RenderPresent(state.renderer);
}

void paddleMovement(std::shared_ptr<Rectangle> paddle, float dt) {
	const bool* keys = SDL_GetKeyboardState(nullptr);
	if (keys[SDL_SCANCODE_A]) paddle->rect.x -= (paddleSpeed * dt);
	if (keys[SDL_SCANCODE_D]) paddle->rect.x += (paddleSpeed * dt);
}

void paddleBorderCollisions(std::shared_ptr<Rectangle> paddle) {
	if (paddle->rect.x + paddleLength >= width) paddle->rect.x = paddleRightLimit;
	if (paddle->rect.x < 0) paddle->rect.x = paddleLeftLimit;
}

float deltaTime(Uint64& lastTick) {
	Uint64 currentTick = SDL_GetTicks();
	Uint64 elapedTick = currentTick - lastTick;
	lastTick = currentTick;

	return static_cast<float>(elapedTick / 1000.0f);
}

void cleanUp(SDLState& state) {
	SDL_DestroyRenderer(state.renderer);
	SDL_DestroyWindow(state.window);
	SDL_Quit();
}