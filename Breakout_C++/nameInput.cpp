#include "nameInput.hpp"

NameInput::NameInput(SDLState& state, TTF_Font* font, int points)
    : state(state), font(font), points(points) {
    SDL_StartTextInput(state.window);
}

void NameInput::HandleEvent(const SDL_Event& event) {
    if (event.type == SDL_EVENT_TEXT_INPUT)
        playerName += event.text.text;

    if (event.type == SDL_EVENT_KEY_DOWN) {
        if (event.key.key == SDLK_BACKSPACE && !playerName.empty())
            playerName.pop_back();
        if (event.key.key == SDLK_RETURN) {
            saveToBinary(playerName, points, state);
            gameState = MENU;
        }
    }
}
    
void NameInput::Update(float dt) {}

void NameInput::Render() {
    SDL_SetRenderDrawColor(state.renderer, 15, 20, 40, 255);
    SDL_RenderClear(state.renderer);
    drawText(state, font, "ENTER YOUR NAME", 68, width / 2, 150, { 255, 255, 255, 255 });
    if (!playerName.empty()) drawText(state, font, playerName, 24, width / 2, height / 2, { 255, 255, 255, 255 });
    SDL_RenderPresent(state.renderer);
}