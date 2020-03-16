#include "Game.h"

const int thickness = 15;
const float paddleH = 100.0f;

Game::Game() :mWindow(nullptr), mRenderer(nullptr), mTicksCount(0), mIsRunning(true), mLeftPaddleDir(0), mRightPaddleDir(0){
}

bool Game::Initialize() {
	// Initialize SDL
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	// Create an SDL Window
	mWindow = SDL_CreateWindow(
		"Game Programming in C++ (Chapter 1)", // window title
		100,    // top left x-coordinate of window
		100,    // top left y-coordinate of window
		1024,   // Width of window
		768,    // Height of window
		0      // Flags (0 for no flags set)
	);

	if (!mWindow) {
		SDL_Log("Fail to create window: %s", SDL_GetError());
		return false;
	}

	// Create SDL renderer
	mRenderer = SDL_CreateRenderer(
		mWindow, // Window to create renderer for
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);

	if (!mRenderer) {
		SDL_Log("Fail to create renderer: %s", SDL_GetError());
		return false;
	}

	mLeftPaddlePos.x = 10.0f;
	mLeftPaddlePos.y = 768.0f / 2.0f;
	mRightPaddlePos.x = 999.0f;
	mRightPaddlePos.y = 768.0f / 2.0f;
	mBallPos.x = 1024.0f / 2.0f;
	mBallPos.y = 768.0f / 2.0f;
	mBallVel.x = -200.0f;
	mBallVel.y = 235.0f;
	return true;
}

void Game::RunLoop() {
	while (mIsRunning) {
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::ProcessInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			//If we get an SDL_QUIT event, end loop
		case SDL_QUIT:
			mIsRunning = false;
			break;
		}
	}

	// Get state of keyboard
	const Uint8* state = SDL_GetKeyboardState(NULL);
	// If escape is pressed, also end loop
	if (state[SDL_SCANCODE_ESCAPE]) {
		mIsRunning = false;
	}

	// Update left paddle direction based on W/S keys
	mLeftPaddleDir = 0;
	if (state[SDL_SCANCODE_W]) {
		mLeftPaddleDir -= 1;
	}
	if (state[SDL_SCANCODE_S]) {
		mLeftPaddleDir += 1;
	}

	// Update right paddle direction based on W/S keys
	mRightPaddleDir = 0;
	if (state[SDL_SCANCODE_I]) {
		mRightPaddleDir -= 1;
	}
	if (state[SDL_SCANCODE_K]) {
		mRightPaddleDir += 1;
	}
}

void Game::UpdateGame() {
	// Wait until 16ms has elapsed since last frame
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

	// Clamp maximum delta time value
	if (deltaTime > 0.05f) {
		deltaTime = 0.05f;
	}

	mTicksCount = SDL_GetTicks();


	// Update left paddle position based on direction
	if (mLeftPaddleDir != 0) {
		mLeftPaddlePos.y += mLeftPaddleDir * 300.0f * deltaTime;
		// Make sure paddle doesn't move off screen
		if (mLeftPaddlePos.y < (paddleH / 2.0f + thickness)) {
			mLeftPaddlePos.y = paddleH / 2.0f + thickness;
		}
		else if (mLeftPaddlePos.y > (768.0f - paddleH / 2.0f - thickness)) {
			mLeftPaddlePos.y = 768.0f - paddleH / 2.0f - thickness;
		}
	}

	// Update right paddle position based on direction
	if (mRightPaddleDir != 0) {
		mRightPaddlePos.y += mRightPaddleDir * 300.0f * deltaTime;
		// Make sure paddle doesn't move off screen
		if (mRightPaddlePos.y < (paddleH / 2.0f + thickness)) {
			mRightPaddlePos.y = paddleH / 2.0f + thickness;
		}
		else if (mRightPaddlePos.y > (768.0f - paddleH / 2.0f - thickness)) {
			mRightPaddlePos.y = 768.0f - paddleH / 2.0f - thickness;
		}
	}


	// Update ball position based on ball velocity
	mBallPos.x += mBallVel.x * deltaTime;
	mBallPos.y += mBallVel.y * deltaTime;

	// Bounce if needed
	float leftDiff = mLeftPaddlePos.y - mBallPos.y;
	leftDiff = (leftDiff > 0.0f) ? leftDiff : -leftDiff;
	if (leftDiff <= paddleH / 2.0f && mBallPos.x <= 25.0f && mBallPos.x >= 20.0f && mBallVel.x < 0.0f) {
		mBallVel.x *= -1.0f;
	}
	else if (mBallPos.x < 0.0f) {
		mIsRunning = false;
	}

	float RightDiff = mRightPaddlePos.y - mBallPos.y;
	RightDiff = (RightDiff > 0.0f) ? RightDiff : -RightDiff;
	if (RightDiff <= paddleH / 2.0f && mBallPos.x >= 999.0f && mBallPos.x <= 1004.0f && mBallVel.x > 0.0f) {
		mBallVel.x *= -1.0f;
	}
	else if (mBallPos.x > 1024.0f) {
		mIsRunning = false;
	}


	if (mBallPos.y <= thickness && mBallVel.y < 0.0f) {
		mBallVel.y *= -1.0f;
	}
	else if (mBallPos.y >= (768 - thickness) && mBallVel.y > 0.0f) {
		mBallVel.y *= -1.0f;
	}
}

void Game::GenerateOutput() {
	// Set draw color to blue
	SDL_SetRenderDrawColor(
		mRenderer,
		0,		// R
		0,		// G
		255,	// B
		255		// A
	);

	// Clear back buffer
	SDL_RenderClear(mRenderer);

	// Draw walls
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);

	// Draw top wall
	SDL_Rect wall{
		0,			// Top left x
		0,			// Top left y
		1024,		// width
		thickness	// Height
	};
	SDL_RenderFillRect(mRenderer, &wall);

	// Draw bottom wall
	wall.y = 768 - thickness;
	SDL_RenderFillRect(mRenderer, &wall);

	//Draw left paddle
	SDL_Rect leftPaddle{
		static_cast<int>(mLeftPaddlePos.x),
		static_cast<int>(mLeftPaddlePos.y - thickness / 2),
		thickness,
		static_cast<int>(paddleH)
	};
	SDL_RenderFillRect(mRenderer, &leftPaddle);

	//Draw right paddle
	SDL_Rect rightPaddle{
		static_cast<int>(mRightPaddlePos.x),
		static_cast<int>(mRightPaddlePos.y - thickness / 2),
		thickness,
		static_cast<int>(paddleH)
	};
	SDL_RenderFillRect(mRenderer, &rightPaddle);


	// Draw ball
	SDL_Rect ball{
		static_cast<int>(mBallPos.x - thickness / 2),
		static_cast<int>(mBallPos.y - thickness / 2),
		thickness,
		thickness
	};
	SDL_RenderFillRect(mRenderer, &ball);

	// Swap front buffer and back buffer
	SDL_RenderPresent(mRenderer);
}

void Game::ShutDown() {
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}