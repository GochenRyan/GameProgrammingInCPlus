#include "InputComponent.h"
#include "Actor.h"

InputComponent::InputComponent(class Actor *owner)
	:MoveComponent(owner),
	mForwardKey(0),
	mBackKey(0),
	mClockwiseKey(0),
	mCounterClockwiseKey(0),
	mConstantForceKey(0),
	mImpulseForceKey(0)
{

}

void InputComponent::ProcessInput(const uint8_t* keyState)
{
	float fowardSpeed = 0.0f;
	if (keyState[mForwardKey])
	{
		fowardSpeed += mMaxForwardSpeed;
	}
	if (keyState[mBackKey])
	{
		fowardSpeed -= mMaxForwardSpeed;
	}
	SetForwardSpeed(fowardSpeed);

	float angularSpeed = 0.0f;
	if (keyState[mClockwiseKey])
	{
		angularSpeed += mMaxAngularSpeed;
	}
	if (keyState[mCounterClockwiseKey])
	{
		angularSpeed -= mMaxAngularSpeed;
	};
	SetAngularSpeed(angularSpeed);

	if (keyState[mConstantForceKey])
	{
		AddForce(Vector2(100.0f, 100.0f));
	}
	if (keyState[mImpulseForceKey])
	{
		AddImpulse(Vector2(100.0f, 100.0f));
	}
}