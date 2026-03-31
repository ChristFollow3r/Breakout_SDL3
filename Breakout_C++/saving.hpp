#pragma once
#include <string>
#include <fstream>
#include <vector>
#include "manager.hpp"
#include "menu.hpp"

void saveToBinary(std::string playerName, int points, SDLState state);
std::vector<std::pair<std::string, int>> getBinaryInfo(SDLState state); // State here cause I want an error message box if the binary doesn't open
std::vector<std::pair<std::string, int>> sortRanking(SDLState state); 
void displayRanking(SDLState state, TTF_Font* font);

// THE AMOUNT OF TIMES I CHANGED THIS FILE AND THE .CPP IS INSANE.