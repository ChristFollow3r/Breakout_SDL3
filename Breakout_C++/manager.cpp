#include "manager.hpp"
#include "ball.hpp"

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

void render(SDLState& state, std::shared_ptr<Rectangle> lPaddle, std::shared_ptr<Rectangle> mPaddle, std::shared_ptr<Rectangle> rPaddle, std::shared_ptr<Rectangle> ball, std::vector<std::vector<std::shared_ptr<Brick>>> gridOfBricks, GameState& gameState) {
	SDL_SetRenderDrawColor(state.renderer, 255, 255, 255, 255);
	SDL_RenderClear(state.renderer);
	ball->draw(state, ball->rect, ball->color);
	lPaddle->draw(state, lPaddle->rect, lPaddle->color);
	mPaddle->draw(state, mPaddle->rect, mPaddle->color);
	rPaddle->draw(state, rPaddle->rect, rPaddle->color);
	int counter = 0;
	for (auto x : gridOfBricks)
	{
		if (x.empty()) counter++;
		if (counter >= gridOfBricks.size()) {
			gameState = NAME_INPUT;
			counter = 0;
		}
	}

	for (int i = 0; i < gridOfBricks.size(); i++) {
		for (auto x : gridOfBricks[i]) x->draw(state, x->rect, x->color);
	}
}

std::vector<std::vector<std::shared_ptr<Brick>>> createBricks(SDLState& state) {

	std::vector<std::vector<std::shared_ptr<Brick>>> gridOfBricks;

	float xStarterPosition = 25;

	float xUpdatedPosition = 25;
	float yUpdatedPosition = 40;

	int brickWidth = 90;
	int brickHeight = 40;

	float xOffset = 5;
	float yOffset = 5;


	for (int i = 0; i < 8; i++)
	{
		std::vector<std::shared_ptr<Brick>> temp;

		for (int j = 0; j < 13; j++)
		{
			SDL_Color brickColor = { rand() % 255, rand() % 255, rand() % 255, 255 }; // Random colors why not
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

float deltaTime(Uint64& lastTick) {
	Uint64 currentTick = SDL_GetTicks();
	Uint64 elapedTick = currentTick - lastTick;
	lastTick = currentTick;

	return static_cast<float>(elapedTick / 1000.0f);
}

bool loadingScreen(SDLState state, float dt, TTF_Font* font, SDL_Texture* texture, SDL_FRect textRect) {

	if (!font) SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Couldn't load the font", state.window);

	loadScreenWaitingTime -= dt;

	if (loadScreenWaitingTime > 0) {
		SDL_SetRenderDrawColor(state.renderer, 15, 20, 40, 255);
		SDL_RenderClear(state.renderer);
		SDL_RenderTexture(state.renderer, texture, nullptr, &textRect);
		SDL_RenderPresent(state.renderer);
		return true;
	}

	else return false;
}

std::unique_ptr<Button> createButton(TTF_Font* font, SDLState state, std::string buttonText, float xPosition, float yPosition) { // Theres a limit for the amount of text that can go to these buttons

TTF_SetFontSize(font, 24);

int buttonWidth = 200;
int buttonHeight = 100;
SDL_Color buttonColor = { 255, 255, 255, 255 };
SDL_FRect buttonRect = { xPosition, yPosition, buttonWidth, buttonHeight };

SDL_Surface* buttonSurface = TTF_RenderText_Blended(font, buttonText.c_str(), NULL, {0, 0, 0, 255}); // So the function asks for length but the documentation says to pass 0 like wtf. Basically it looks for the 0 at the end of a string to determine its length
SDL_Texture* buttonTexture = SDL_CreateTextureFromSurface(state.renderer, buttonSurface); 
SDL_DestroySurface(buttonSurface);
float buttonTextWidth, buttonTextHeight;
SDL_GetTextureSize(buttonTexture, &buttonTextWidth, &buttonTextHeight);
SDL_FRect playbuttonTextRect = { xPosition + (buttonWidth - buttonTextWidth) / 2, yPosition + (buttonHeight - buttonTextHeight) / 2, buttonTextWidth, buttonTextHeight };
return std::make_unique<Button>(buttonRect, state.renderer, buttonColor, buttonTexture, playbuttonTextRect);

}

void paddleMovement(std::shared_ptr<Rectangle> lPaddle, std::shared_ptr<Rectangle> mPaddle, std::shared_ptr<Rectangle> rPaddle, float dt) {
	const bool* keys = SDL_GetKeyboardState(nullptr);
	if (keys[SDL_SCANCODE_A]) {
		lPaddle->rect.x -= (paddleSpeed * dt);
		mPaddle->rect.x -= (paddleSpeed * dt);
		rPaddle->rect.x -= (paddleSpeed * dt);
	}
	if (keys[SDL_SCANCODE_D]) {
		lPaddle->rect.x += (paddleSpeed * dt);
		mPaddle->rect.x += (paddleSpeed * dt);
		rPaddle->rect.x += (paddleSpeed * dt);
	}
}

void paddleBorderCollisions(std::shared_ptr<Rectangle> lPaddle, std::shared_ptr<Rectangle> mPaddle, std::shared_ptr<Rectangle> rPaddle) {
	if (rPaddle->rect.x + paddleLength >= width) {
		rPaddle->rect.x = paddleRightLimit;
		mPaddle->rect.x = paddleRightLimit - mPaddle->rect.w;
		lPaddle->rect.x = paddleRightLimit - (2 * rPaddle->rect.w);
	}

	if (lPaddle->rect.x < 0) {
		lPaddle->rect.x = paddleLeftLimit;
		mPaddle->rect.x = paddleLeftLimit + mPaddle->rect.w;
		rPaddle->rect.x = paddleLeftLimit + (2 * mPaddle->rect.w);
	}
}

bool brickCollisions(std::vector<std::vector<std::shared_ptr<Brick>>>& gridOfBricks, std::shared_ptr<Rectangle> ball) {


	for (int i = 0; i < gridOfBricks.size(); i++) {

		for (auto it = gridOfBricks[i].begin(); it != gridOfBricks[i].end(); ++it) { 

			if (SDL_HasRectIntersectionFloat(&(*it)->rect, &ball->rect)) { // I asked I how to dereference it cause static_cast to int doesn't work.
			gridOfBricks[i].erase(it);
			return true;
			}
		}
	}

	return false;
}

void cleanUp(SDLState& state) {
	SDL_DestroyRenderer(state.renderer);
	SDL_DestroyWindow(state.window);
	SDL_Quit();
}