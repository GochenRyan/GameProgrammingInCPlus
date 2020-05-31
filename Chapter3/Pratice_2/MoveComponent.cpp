#include "MoveComponent.h"
#include "Actor.h"
#include <iostream>

MoveComponent::MoveComponent(class Actor* owner, int updateOrder)
	:Component(owner, updateOrder),
	mAngularSpeed(0.0f),
	mForwardSpeed(0.0f),
	mMass(0.0f),
	mVelocity(Vector2(0.0f, 0.0f))
{

}

void MoveComponent::Update(float deltaTime)
{
	if (!Math::NearZero(mAngularSpeed))
	{
		float rot = mOwner->GetRotation();
		rot += mAngularSpeed * deltaTime;
		mOwner->SetRotation(rot);
	}

	if (!Math::NearZero(mForwardSpeed))
	{
		Vector2 pos = mOwner->GetPosition();
		pos += mOwner->GetForward() * mForwardSpeed * deltaTime;

		if (pos.x < 0.0f) { pos.x = 1022.0f; }
		else if (pos.x > 1024.0f) { pos.x = 2.0f; }

		if (pos.y < 0.0f) { pos.y = 766.0f; }
		else if (pos.y > 768.0f) { pos.y = 2.0f; }

		mOwner->SetPosition(pos);
	}

	Vector2 sumOfForce = Vector2(0.0f, 0.0f);
	// Calculate constant force
	for (auto iter = mForces.begin(); iter != mForces.end(); ++iter)
	{
		sumOfForce += *iter;
	}
	// Calculate impulse force
	for (auto iter = mImpulses.begin(); iter != mImpulses.end(); ++iter)
	{
		sumOfForce += *iter;
	}
	mImpulses.clear();

	std::cout << "the sum of force is: " << sumOfForce.x << sumOfForce.y << std::endl;

	if (mMass > 0.0f)
	{
		// Euler Integration
		Vector2 acceleration = Vector2(sumOfForce.x / mMass, sumOfForce.y / mMass) ;
		// Update velocity
		mVelocity += acceleration * deltaTime;
		// Update position
		Vector2 pos = mOwner->GetPosition();
		pos += mVelocity * deltaTime;

		if (pos.x < 0.0f) { pos.x = 1022.0f; }
		else if (pos.x > 1024.0f) { pos.x = 2.0f; }

		if (pos.y < 0.0f) { pos.y = 766.0f; }
		else if (pos.y > 768.0f) { pos.y = 2.0f; }

		mOwner->SetPosition(pos);
	}
}
