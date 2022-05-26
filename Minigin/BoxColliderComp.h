#pragma once
#include "MiniginPCH.h"
#include "Collider.h"


class BoxColliderComp : public Collider 
{
public:
	BoxColliderComp() = delete;
	explicit BoxColliderComp(dae::GameObject* gameObject, const std::string& tag);
	
};

