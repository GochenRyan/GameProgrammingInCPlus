#include "Ship.h"
#include "AnimSpriteComponent.h"
#include "Game.h"
#include "InputComponent.h"
#include "Laser.h"
#include "CircleComponent.h"
#include "Asteroid.h"
#include <iostream>

Ship::Ship(Game* game) :
	Actor(game),
	mLaserCooldown(0.0f)
{
	CreateComponent();
}

void Ship::CreateComponent()
{
	// Create a sprite component
	SpriteComponent* sc = new SpriteComponent(this, 150);
	sc->SetTexture(GetGame()->GetTexture("Assets/Ship.png"));

	// Create an input component and set keys/speed
	InputComponent* ic = new InputComponent(this);
	ic->SetForwardKey(SDL_SCANCODE_W);
	ic->SetBackKey(SDL_SCANCODE_S);
	ic->SetClockwiseKey(SDL_SCANCODE_A);
	ic->SetCounterClockwiseKey(SDL_SCANCODE_D);
	ic->SetMaxForwardSpeed(300.0f);
	ic->SetConstantForceKey(SDL_SCANCODE_F);
	ic->SetImpulseForceKey(SDL_SCANCODE_I);
	ic->SetMaxAngularSpeed(Math::TwoPi);
	ic->SetMass(2.0f);

	// Create a circle component (for collision)
	mCircle = new CircleComponent(this);
	mCircle->SetRadius(30.0f);
}


void Ship::UpdateActor(float deltaTime)
{
	mLaserCooldown -= deltaTime;
	for (auto ast : GetGame()->GetAsteroids())
	{
		if (Intersect(*mCircle, *(ast->GetCircle())))
		{
			this->SetPosition(Vector2(512.0f, 384.0f));
		}
	}
}

void Ship::ActorInput(const uint8_t* state)
{
	if (state[SDL_SCANCODE_SPACE] && mLaserCooldown <= 0.0f)
	{
		// Create a laser and set its position/rotation to mine
		Laser* laser = new Laser(GetGame());
		laser->SetPosition(GetPosition());
		laser->SetRotation(GetRotation());

		// Reset laser cooldown (half second)
		mLaserCooldown = 0.5f;
	}
}

