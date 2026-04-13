#pragma once
#include <fstream>
#include <vector>
#include <string>
#include <SDL3/SDL.h>
#include "gameState.hpp"

void saveToBinary(std::string playerName, int points, SDLState state);