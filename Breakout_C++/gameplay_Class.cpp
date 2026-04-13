#include <SDL3/SDL.h>
#include <iostream>
#include "scene.hpp"

class GamePlay {
	
	// SDLState state;
	Scene* currentScene;

public:
	void Run();
	void SwitchScene(Scene* nextScene);

};