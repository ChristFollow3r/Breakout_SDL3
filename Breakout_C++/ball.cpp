#include "ball.hpp"

void Ball::UpdateBallPhysics(float dt) {
	this->rect.y += ballSpeed * dt;
}