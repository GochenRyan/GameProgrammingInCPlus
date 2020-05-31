#pragma once
#include "Component.h"
#include "Math.h"
#include <vector>

class MoveComponent : public Component
{
public:
	MoveComponent(class Actor *owner, int updateOrder = 10);
	void Update(float deltaTime) override;

	float GetAngularSpeed() const { return mAngularSpeed; }
	float GetForwardSpeed() const { return mForwardSpeed; }
	float GetMass() const { return mMass; }
	void SetAngularSpeed(float speed) { mAngularSpeed = speed; }
	void SetForwardSpeed(float speed) { mForwardSpeed = speed; }
	void AddForce(const Vector2 force) { mForces.push_back(force); }
	void AddImpulse(const Vector2 impulse) { mImpulses.push_back(impulse); }
	void SetMass(const float mass) { mMass = mass; }
private:
	// Controls rotation (radians/second)
	float mAngularSpeed;
	// Controls forward movement (units/second)
	float mForwardSpeed;
	// list of constant force
	std::vector<Vector2> mForces;
	// list of impulse force
	std::vector<Vector2> mImpulses;
	Vector2 mVelocity;
	float mMass;
};