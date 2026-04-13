#include "ranking.hpp"

RankingScene::RankingScene(SDLState& state, TTF_Font* font) : state(state), font(font) {
    backButton = std::make_unique<Button>(font, state, "Back", width - 240, height - 140);
}

void RankingScene::HandleEvent(const SDL_Event& event) {
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN && event.button.button == SDL_BUTTON_LEFT)
        if (backButton->Clicked()) request = MENU;
}

void RankingScene::Update(float dt) {}

void RankingScene::Render() {
    SDL_SetRenderDrawColor(state.renderer, 10, 25, 45, 255);
    SDL_RenderClear(state.renderer);
    backButton->DrawButton(state);
    displayRanking(state, font);
    SDL_RenderPresent(state.renderer);
}