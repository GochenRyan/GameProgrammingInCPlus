#pragma once
#include "SpriteComponent.h"
#include <vector>
#include <unordered_map>
#include <string>
class AnimSpriteComponent : public SpriteComponent {
public:
	AnimSpriteComponent(class Actor* owner, int drawOrder = 100);
	// Update animation every frame (overriden from component)
	void Update(float deltaTime) override;
	// Set the textures used for animation
	void SetAnimTextures(const std::string name, const std::vector<SDL_Texture*>& textures);
	// Get the animation name
	std::string GetAnimName() const { return mAnimName; }
	// Set/get the animation FPS
	float GetAnimFPS() const { return mAnimFPS; }
	void SetAnimFPS(float fps) { mAnimFPS = fps; }
	// Play the animation by name
	void PlayAnim(std::string name);
	// Stop the animation
	void StopAnim();
private:
	// All the animations
	std::unordered_map<std::string, std::vector<SDL_Texture*>> mAnimTextures;
	// Current frame displayed
	float mCurrFrame;
	// Animation frame rate
	float mAnimFPS;
	// Current frame name
	std::string mAnimName;
};