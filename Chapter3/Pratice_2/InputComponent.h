#pragma once
#include "MoveComponent.h"
#include <cstdint>

class InputComponent : public MoveComponent
{
public:
	InputComponent(class Actor* owner);

	void ProcessInput(const uint8_t* keyState) override;

	float GetMaxForward() const { return mMaxForwardSpeed; }
	float GetMaxAngular() const { return mMaxAngularSpeed; }
	int GetFowardKey() const { return mForwardKey; }
	int GetBackKey() const { return mBackKey; }
	int GetClockwiseKey() const { return mClockwiseKey; }
	int GetCounterClockwiseKey() const { return mCounterClockwiseKey; }
	int GetConstantForceKey() const { return mConstantForceKey; }
	int GetPulseForceKey() const { return mImpulseForceKey; }

	void SetMaxForwardSpeed(float speed) { mMaxForwardSpeed = speed; }
	void SetMaxAngularSpeed(float speed) { mMaxAngularSpeed = speed; }
	void SetForwardKey(int key) { mForwardKey = key; }
	void SetBackKey(int key) { mBackKey = key; }
	void SetClockwiseKey(int key) { mClockwiseKey = key; }
	void SetCounterClockwiseKey(int key) { mCounterClockwiseKey = key; }
	void SetConstantForceKey(int key) { mConstantForceKey = key; }
	void SetImpulseForceKey(int key) { mImpulseForceKey = key; }
private:
	float mMaxForwardSpeed;
	float mMaxAngularSpeed;
	// Keys for forward/back movement
	int mForwardKey;
	int mBackKey;
	// Keys for angular movement
	int mClockwiseKey;
	int mCounterClockwiseKey;
	// Keys for force
	int mConstantForceKey;
	int mImpulseForceKey;
};