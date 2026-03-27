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

void render(SDLState& state, std::shared_ptr<Rectangle> paddle, std::shared_ptr<Rectangle> ball, std::vector<std::vector<std::shared_ptr<Brick>>> gridOfBricks) {
	SDL_SetRenderDrawColor(state.renderer, 255, 255, 255, 255);
	SDL_RenderClear(state.renderer);
	ball->draw(state, ball->rect, ball->color);
	paddle->draw(state, paddle->rect, paddle->color);

	for (int i = 0; i < gridOfBricks.size(); i++) {
		for (auto x : gridOfBricks[i]) x->draw(state, x->rect, x->color);
	}

	SDL_RenderPresent(state.renderer);
}

std::vector<std::vector<std::shared_ptr<Brick>>> createBricks(SDLState& state) {

	std::vector<std::vector<std::shared_ptr<Brick>>> gridOfBricks;

	float xStarterPosition = 70;

	float xUpdatedPosition = 70;
	float yUpdatedPosition = 40;

	int brickWidth = 72;
	int brickHeight = 30;

	float xOffset = 10;
	float yOffset = 5;

	SDL_Color brickColor = { 126, 67, 12, 255 };

	for (int i = 0; i < 12; i++)
	{
		std::vector<std::shared_ptr<Brick>> temp;

		for (int j = 0; j < 14; j++)
		{
			SDL_FRect brickRect = { xUpdatedPosition, yUpdatedPosition, brickWidth, brickHeight };
			auto brick = std::make_shared<Brick>(brickRect, state.renderer, brickColor);

			xUpdatedPosition = xUpdatedPosition + brickWidth + xOffset;
			temp.push_back(brick);
		}

		gridOfBricks.push_back(temp);
		xUpdatedPosition = xStarterPosition;
		yUpdatedPosition = yUpdatedPosition + brickHeight + yOffset;
	}

	return gridOfBricks;
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