#include "gameScene.hpp"

GameScene::GameScene(SDLState& state, TTF_Font* font) : state(state), font(font) {
    SDL_Color paddleColor = { 255, 0, 0, 255 };
    SDL_FRect rect = { 640, 640, paddleLength, 10 }; // Why is this monkey IDE saying that paddleLength isn't defined wtf
    lPaddle = std::make_unique<Rectangle>(rect, state.renderer, paddleColor);
    rect.x += paddleLength;
    mPaddle = std::make_unique<Rectangle>(rect, state.renderer, paddleColor);
    rect.x += paddleLength;
    rPaddle = std::make_unique<Rectangle>(rect, state.renderer, paddleColor);

    SDL_Color ballColor = { 0, 0, 0, 255 };
    rect = { width / 2, 550, Ball::ballSize, Ball::ballSize };
    ball = std::make_unique<Ball>(rect, state.renderer, ballColor);

    Reset();
}

std::vector<std::vector<std::unique_ptr<Brick>>> GameScene::CreateBricks() {

    std::vector<std::vector<std::unique_ptr<Brick>>> gridOfBricks;

    float xStarterPosition = 25;

    float xUpdatedPosition = 25;
    float yUpdatedPosition = 40;

    int brickWidth = 90;
    int brickHeight = 40;

    float xOffset = 5;
    float yOffset = 5;


    for (int i = 0; i < 8; i++)
    {
        std::vector<std::unique_ptr<Brick>> temp;

        for (int j = 0; j < 13; j++)
        {
            SDL_Color brickColor = { rand() % 255, rand() % 255, rand() % 255, 255 }; // Random colors why not
            SDL_FRect brickRect = { xUpdatedPosition, yUpdatedPosition, brickWidth, brickHeight };

            temp.push_back(std::make_unique<Brick>(brickRect, state.renderer, brickColor));

            xUpdatedPosition += brickWidth + xOffset;
        }

        gridOfBricks.push_back(std::move(temp));
        xUpdatedPosition = xStarterPosition;
        yUpdatedPosition = yUpdatedPosition + brickHeight + yOffset;
    }

    return gridOfBricks;
}

void GameScene::PaddleMovement(float dt) {
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

void GameScene::PaddleBorderCollisions() {
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

bool GameScene::BrickCollisions() {


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


void GameScene::Reset() {
    ball->rect.x = width / 2;
    ball->rect.y = 550;
    ball->ballYSpeed = -320.0f;
    ball->ballXSpeed = 320.0f;

    lPaddle->rect.x = 640;
    mPaddle->rect.x = 640 + paddleLength;
    rPaddle->rect.x = 640 + (paddleLength * 2);

    gridOfBricks = CreateBricks();

    lifes = 3;
    points = 0;
}

void GameScene::HandleEvent(const SDL_Event& event) {
    // I DONT KNOW
}

void GameScene::Update(float dt) {

    waitTimer += dt;
    pointAdder += dt;

    if (pointAdder > 1.0f) {
        points += 15;
        pointAdder = 0.0f;
    }

    PaddleMovement(dt);
    PaddleBorderCollisions();

    if (waitTimer > 1.0f) ball->UpdateBallPhysics(lPaddle.get(), mPaddle.get(), rPaddle.get(), dt, lifes);
    if (BrickCollisions()) {
        ball->ballYSpeed = -ball->ballYSpeed;
        points += 100;
    }
}

void GameScene::Render() {
    SDL_Color black = { 0, 0, 0, 255 };
    SDL_SetRenderDrawColor(state.renderer, 255, 255, 255, 255);
    SDL_RenderClear(state.renderer);

    lPaddle->draw(state, lPaddle->rect, lPaddle->color);
    mPaddle->draw(state, mPaddle->rect, mPaddle->color);
    rPaddle->draw(state, rPaddle->rect, rPaddle->color);
    ball->draw(state, ball->rect, ball->color);

    for (auto& row : gridOfBricks)
        for (auto& brick : row)
            brick->draw(state, brick->rect, brick->color);

    drawText(state, font, std::to_string(lifes), 38, width - 25, 0, black);
    drawText(state, font, std::to_string(points), 38, 75, 0, black);
    SDL_RenderPresent(state.renderer);
}