#include "stdafx.h"
#include "Game.h"

//STUDENT: MICHAEL DANKER

Game::Game()
{
	Reset();
}

void Game::Reset()
{
	Console::SetWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	Console::CursorVisible(false);
	paddle.width = 12;
	paddle.height = 2;
	paddle.x_position = 32;
	paddle.y_position = 30;

	ball.visage = 'O';
	ball.color = ConsoleColor::Cyan;
	ResetBall();

	// Add this brick and 4 more bricks to the vector
	for (size_t i = 0; i < 5; i++)
	{ 
		if (brickVector.empty() == true)
		{
			brick.x_position = 0;
			brick.y_position = 5;
		}
		brick.width = 10;
		brick.height = 2;
		brick.y_position = 5;
		brick.doubleThick = true;
		brick.color = ConsoleColor::DarkGreen;
		brickVector.push_back(brick);
		if (brickVector.empty() == false)
		{
			brick.x_position = brick.x_position + 11; 
		}
	}
}

void Game::ResetBall()
{
	ball.x_position = paddle.x_position + paddle.width / 2;
	ball.y_position = paddle.y_position - 1;
	ball.x_velocity = rand() % 2 ? 1 : -1;
	ball.y_velocity = -1;
	ball.moving = false;
}

bool Game::Update()
{
	if (GetAsyncKeyState(VK_ESCAPE) & 0x1)
		return false;

	if (GetAsyncKeyState(VK_RIGHT) && paddle.x_position < WINDOW_WIDTH - paddle.width)
		paddle.x_position += 2;

	if (GetAsyncKeyState(VK_LEFT) && paddle.x_position > 0)
		paddle.x_position -= 2;

	if (GetAsyncKeyState(VK_SPACE) & 0x1)
		ball.moving = !ball.moving;

	if (GetAsyncKeyState('R') & 0x1)
		Reset();

	ball.Update();
	CheckCollision();
	return true;
}

void Game::Render()
{
	Console::Lock(true);
	Console::Clear();

	// If no bricks remain, pause ball and display victory text with R to reset
	if (brickVector.empty() == true)
	{
		ball.moving = false;
		Console::SetCursorPosition(10, 10);
		printf("Victory!!!      PRESS R TO RESET");
	}

	// If ball touches bottom of window, pause ball and display defeat text with R to reset
	if (ball.y_position == Console::WindowHeight())
	{
		ball.moving = false;
		Console::SetCursorPosition(10, 10);
		printf("Defeat!!!      PRESS R TO RESET");
	}


	paddle.Draw();
	ball.Draw();

	// Update render to render all bricks
	for (size_t i = 0; i < brickVector.size(); i++)
	{
		brickVector[i].Draw();
	}
	Console::Lock(false);
}

void Game::CheckCollision()
{
	// Update collision to check all bricks
	for (size_t i = 0; i < brickVector.size(); i++)
	{
		if (brickVector[i].Contains(ball.x_position + ball.x_velocity, ball.y_position + ball.y_velocity))
		{
			brickVector[i].color = ConsoleColor(brickVector[i].color - 1);
			ball.y_velocity *= -1;
			// If the ball hits the same brick 3 times (color == black), remove it from the vector
			if (brickVector[i].color == ConsoleColor::Black)
			{
				brickVector.erase(brickVector.begin() + i);
			}
		}
	}




	if (paddle.Contains(ball.x_position + ball.x_velocity, ball.y_velocity + ball.y_position))
	{
		ball.y_velocity *= -1;
	}
}