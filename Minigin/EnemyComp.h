#pragma once
#include "BaseComponent.h"
#include "Subject.h"

class EnemyComp : public dae::BaseComponent, public Subject
{
public:
	EnemyComp() = default;
	~EnemyComp() = default;
	EnemyComp(const EnemyComp& other) = delete;
	EnemyComp(EnemyComp&& other) noexcept = delete;
	EnemyComp& operator=(const EnemyComp& other) = delete;
	EnemyComp& operator=(EnemyComp&& other) noexcept = delete;

	void Start() override {};
	void OnDeath();
	void Update() override;
	void Render() const override;
};

