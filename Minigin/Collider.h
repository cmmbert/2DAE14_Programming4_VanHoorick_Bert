#pragma once
#include "BaseComponent.h"
#include "GameObject.h"

class ColliderTag
{
    std::string m_Name;
public:
    ColliderTag(const std::string& name);
	std::string GetName() const { return m_Name; }
};


class Collider :
    public dae::BaseComponent
{
    ColliderTag m_ColliderTag;
public:
    Collider(dae::GameObject* gameObject, const std::string& tag);
    ~Collider();
    const ColliderTag& GetTag() const { return m_ColliderTag; };

    void OnCollision(Collider* other);
};

