#pragma once
#include "BaseComponent.h"

class SoundComponent : public dae::BaseComponent
{
public:
	SoundComponent() = default;
	SoundComponent(int soundId) : m_SoundId(soundId) {
	}

	virtual ~SoundComponent() = default;
	SoundComponent(const SoundComponent& other) = delete;
	SoundComponent(SoundComponent&& other) = delete;
	SoundComponent& operator=(const SoundComponent& other) = delete;
	SoundComponent& operator=(SoundComponent&& other) = delete;
	void Update() override {}
	void Render() const override {}
	void Play(float volumePerc = 0.5f);
	void SetSoundId(int soundId) { m_SoundId = soundId; }
private:
	int m_SoundId = 0;
};

