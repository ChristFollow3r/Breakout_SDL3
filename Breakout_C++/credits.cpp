#include "credits.hpp"

CreditsScene::CreditsScene(SDLState& state, TTF_Font* font) : state(state), font(font) {
    backButton = std::make_unique<Button>(font, state, "Back", width - 240, height - 140);
}

void CreditsScene::HandleEvent(const SDL_Event& event) {
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN && event.button.button == SDL_BUTTON_LEFT)
        if (backButton->Clicked()) gameState = MENU;
}

void CreditsScene::Update(float dt) {}

void CreditsScene::Render() {
    SDL_SetRenderDrawColor(state.renderer, 10, 35, 35, 255);
    SDL_RenderClear(state.renderer);
    backButton->DrawButton(state);
    drawText(state, font, "MADE BY", 68, width / 2, 150, { 255, 255, 255, 255 });
    drawText(state, font, "NIL BADIA GIMENEZ", 128, width / 2, height / 2 - 100, { 255, 255, 255, 255 });
    SDL_RenderPresent(state.renderer);
}