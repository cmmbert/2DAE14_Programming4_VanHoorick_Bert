#pragma once
#include <map>

#include "BaseComponent.h"
#include "TextureComponent.h"

class AnimationComponent final : public dae::BaseComponent
{
	float m_TimeBetweenFrames;
	float m_TimeSinceLastFrame{};
	int m_CurrentFrame{};
	std::map<std::string, std::vector<glm::ivec2>> m_Animations;
	std::string m_CurrentAnimation;
	std::shared_ptr<dae::TextureComponent> m_TextureComp;
public:
	AnimationComponent() = delete;
	explicit AnimationComponent(dae::GameObject* gameObject, std::shared_ptr<dae::TextureComponent> textureComp, float timeBetweenFrames);

	void AddAnimationFrame(const std::string& animName, glm::ivec2 texCoords);
	void SetCurrentAnimation(const std::string& animName);
	void SetAnimationSpeed(float timeBetweenFrames);
	void Start() override;
	void Update() override;
	void Render() const override;
};

