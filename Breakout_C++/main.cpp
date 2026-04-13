#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include <memory>
#include <fstream>
#include "gameState.hpp"
#include "manager.hpp"
#include "mainMenu.hpp"
#include "gameScene.hpp"
#include "ranking.hpp"
#include "credits.hpp"
#include "nameInput.hpp"

int main(int arg, char* argv[]) {

    std::fstream file("ranking.bin", std::ios::app | std::ios::binary);
    file.close();

    srand(time(NULL));
    SDLState state;
    initialize(state);

    TTF_Init();
    TTF_Font* font = TTF_OpenFont("Roboto.ttf", 142);

    bool running = true;
    Uint64 lastTick = SDL_GetTicks();
    deltaTime(lastTick);

    GameState currentState = MENU;

    MainMenu menu(state, font);
    std::unique_ptr<GameScene> game;
    std::unique_ptr<RankingScene> ranking;
    std::unique_ptr<CreditsScene> credits;
    std::unique_ptr<NameInput> nameInput;

    while (running) {

        SDL_Event event{ 0 };
        float dt = deltaTime(lastTick);

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) running = false;

            switch (currentState) {
            case MENU:    menu.HandleEvent(event); break;
            case GAME:    if (game)    game->HandleEvent(event); break;
            case RANKING: if (ranking) ranking->HandleEvent(event); break;
            case CREDITS: if (credits) credits->HandleEvent(event); break;
            case NAME_INPUT: if (nameInput) nameInput->HandleEvent(event); break;
            default: break;
            }
        }

        switch (currentState) {
        case MENU:
            menu.Update(dt);
            menu.Render();
            if (menu.gameState == GAME) {
                game = std::make_unique<GameScene>(state, font);
                currentState = GAME;
                menu.gameState = MENU;
            }
            if (menu.gameState == RANKING) {
                ranking = std::make_unique<RankingScene>(state, font);
                currentState = RANKING;
                menu.gameState = MENU;
            }
            if (menu.gameState == CREDITS) {
                credits = std::make_unique<CreditsScene>(state, font);
                currentState = CREDITS;
                menu.gameState = MENU;
            }
            if (menu.gameState == EXIT) running = false;
            break;

        case GAME:
            if (game) {
                game->Update(dt);
                game->Render();
                if (game->gameState == NAME_INPUT) {
                    nameInput = std::make_unique<NameInput>(state, font, game->points);
                    currentState = NAME_INPUT;
                    game->gameState = GAME;
                }
            }
            break;

        case RANKING:
            if (ranking) {
                ranking->Update(dt);
                ranking->Render();
                if (ranking->gameState == MENU) {
                    currentState = MENU;
                    ranking.reset();
                }
            }
            break;

        case CREDITS:
            if (credits) {
                credits->Update(dt);
                credits->Render();
                if (credits->gameState == MENU) {
                    currentState = MENU;
                    credits.reset();
                }
            }
            break;

        case NAME_INPUT:
            if (nameInput) {
                nameInput->Update(dt);
                nameInput->Render();
                if (nameInput->gameState == MENU) {
                    currentState = MENU;
                    nameInput.reset();
                    game.reset();
                }
            }
            break;

        default: break;
        }
    }

    cleanUp(state);
    return 0;
}