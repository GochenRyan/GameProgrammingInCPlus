#include "AnimSpriteComponent.h"
#include "Math.h"

AnimSpriteComponent::AnimSpriteComponent(Actor* owner, int drawOrder) :
	SpriteComponent(owner, drawOrder),
	mCurrFrame(0.0f),
	mAnimFPS(24.0f),
	mLoop(true)
{
}

void AnimSpriteComponent::Update(float deltaTime) {
	SpriteComponent::Update(deltaTime);

	if (mAnimTextures[mAnimName].size() > 0) {
		// Update the current frame based on frame rate
		// and delta time
		mCurrFrame += mAnimFPS * deltaTime;

		if (mLoop) {
			// Wrap current frame if needed
			while (mCurrFrame >= mAnimTextures[mAnimName].size()) {
				mCurrFrame -= mAnimTextures[mAnimName].size();
			}
		}
		else {
			if (mCurrFrame >= mAnimTextures[mAnimName].size()) {
				mCurrFrame = mAnimTextures[mAnimName].size() - 1;
			}
		}

		// Set the current texture
		SetTexture(mAnimTextures[mAnimName][static_cast<int>(mCurrFrame)]);
	}
	else {
		mCurrFrame = 0.0f;
	}
}

void AnimSpriteComponent::SetAnimTextures(const std::string name, const std::vector<SDL_Texture*>& textures) {
	mAnimTextures[name] = textures;
	mAnimName = name;
	if (mAnimTextures.size() > 0) {
		// Set the active texture to first frame
		mCurrFrame = 0.0f;
		SetTexture(mAnimTextures[name][0]);
	}
}

void AnimSpriteComponent::PlayAnim(std::string name, bool loop) {
	if (mAnimTextures.find(name) != mAnimTextures.end()) {
		mAnimName = name;
	}
	mLoop = loop;
}

void AnimSpriteComponent::StopAnim() {
	mAnimName = "";
}

bool AnimSpriteComponent::IsLoop() {
	return mLoop;
}

void AnimSpriteComponent::SetLoop(bool loop) {
	mLoop = loop;
}