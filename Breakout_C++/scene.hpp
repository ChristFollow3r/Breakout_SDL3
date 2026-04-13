#include <SDL3/SDL.h>
#include <iostream>

class Scene {

protected:

	virtual void HandleEvent(const SDL_Event& event) = 0;
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;

};