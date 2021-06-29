#pragma once
#include "Box.h"
#include "Ball.h"
#include <vector>

class Game
{
	Ball ball;
	Box paddle;

	// TODO #1 - Instead of storing 1 brick, store a vector of bricks (by value)
	Box brick;
	std::vector<Box> brickVector;

public:
	Game();
	bool Update();
	void Render();
	void Reset();
	void ResetBall();
	void CheckCollision();
};