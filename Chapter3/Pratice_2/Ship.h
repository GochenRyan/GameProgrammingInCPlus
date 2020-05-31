#pragma once
#include "Actor.h"

class Ship : public Actor {
public:
	Ship(class Game* game);
	void UpdateActor(float deltaTime) override;
	void ActorInput(const uint8_t* state) override;
	void CreateComponent();
private:
	float mLaserCooldown;
	class CircleComponent* mCircle;
	float mDeadCooldown;
};