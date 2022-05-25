#pragma once
#include "MiniginPCH.h"
#include "Collider.h"


class BoxColliderComp : public Collider 
{
public:
	BoxColliderComp() = delete;
	explicit BoxColliderComp(const std::string& tag);

	void Start() override;
	void Update() override;
	void Render() const override;
	void OnCollision(Collider* other) override;
	~BoxColliderComp() override;
};

