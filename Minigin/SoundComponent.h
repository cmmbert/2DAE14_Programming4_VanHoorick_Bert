#pragma once
#include "BaseComponent.h"

class SoundComponent : public dae::BaseComponent
{
public:
	SoundComponent() = delete;
	SoundComponent(dae::GameObject* gameObject, int soundId) : BaseComponent(gameObject), m_SoundId(soundId) {}

	virtual ~SoundComponent() = default;
	SoundComponent(const SoundComponent& other) = delete;
	SoundComponent(SoundComponent&& other) = delete;
	SoundComponent& operator=(const SoundComponent& other) = delete;
	SoundComponent& operator=(SoundComponent&& other) = delete;
	void Play(float volumePerc = 0.5f);
	void SetSoundId(int soundId) { m_SoundId = soundId; }
private:
	int m_SoundId = 0;
};

