#include "rectangle.hpp"
#include <memory>

class Ball : public Rectangle {

public:

	static const int ballSize = 20;
	float ballYSpeed = 320.0f; // Should this be a struct called velocity or sm like that?
	float ballXSpeed = 320.0f;

	Ball(SDL_FRect rect, SDL_Renderer* renderer, SDL_Color color) : Rectangle(rect, renderer, color) {};

	void UpdateBallPhysics(float dt, std::shared_ptr<Rectangle> paddle);
	void CheckCollisions(std::shared_ptr<Rectangle> paddle);
	//int GetBallSize() { return ballSize; }

private:


};
