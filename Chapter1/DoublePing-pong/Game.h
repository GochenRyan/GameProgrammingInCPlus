#pragma once
#include "SDL.h"

struct Vector2
{
	float x;
	float y;
};

class Game {
public:
	Game();
	bool Initialize();
	void RunLoop();
	void ShutDown();
private:
	// Helper function for the game loop
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	// Window created by SDL
	SDL_Window* mWindow;
	// Renderer for 2D drawing
	SDL_Renderer* mRenderer;
	// Number of ticks since start of game
	Uint32 mTicksCount;
	// Game should continue to run
	bool mIsRunning;

	// Pong specific
	// Direction of left paddle
	int mLeftPaddleDir;
	// Position of left paddle
	Vector2 mLeftPaddlePos;
	// Direction of right paddle
	int mRightPaddleDir;
	// Position of right paddle
	Vector2 mRightPaddlePos;
	// Position of ball
	Vector2 mBallPos;
	// Velocity of ball
	Vector2 mBallVel;
};