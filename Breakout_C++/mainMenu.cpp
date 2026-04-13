#include "mainMenu.hpp"
#include "button.hpp"

MainMenu::MainMenu(SDLState& state, TTF_Font* font) : state(state), font(font) {
    int buttonWidth = 200;
    int buttonHeight = 100;
    int gap = 20;

    playButton = std::make_unique<Button>(font, state, "Play", (width - buttonWidth) / 2, buttonHeight);
    rankingButton = std::make_unique<Button>(font, state, "Ranking", (width - buttonWidth) / 2, (buttonHeight * 2) + gap);
    creditsButton = std::make_unique<Button>(font, state, "Credits", (width - buttonWidth) / 2, (buttonHeight * 3) + gap * 2);
    exitButton = std::make_unique<Button>(font, state, "Exit", (width - buttonWidth) / 2, (buttonHeight * 4) + gap * 3);
}

void MainMenu::HandleEvent(const SDL_Event& e) {
    if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN && e.button.button == SDL_BUTTON_LEFT) {
        if (playButton->Clicked()) gameState = GAME;
        if (rankingButton->Clicked()) gameState = RANKING;
        if (creditsButton->Clicked()) gameState = CREDITS;
        if (exitButton->Clicked()) gameState = EXIT;
    }
}

void MainMenu::Render() {
    SDL_SetRenderDrawColor(state.renderer, 15, 20, 40, 255);
    SDL_RenderClear(state.renderer);
    playButton->DrawButton(state);
    rankingButton->DrawButton(state);
    creditsButton->DrawButton(state);
    exitButton->DrawButton(state);
    SDL_RenderPresent(state.renderer);
}