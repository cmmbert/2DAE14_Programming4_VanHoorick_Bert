#include "MiniginPCH.h"
#include "Collider.h"

#include "CollisionManager.h"


ColliderTag::ColliderTag(const std::string& name) : m_Name(name)
{

}

Collider::Collider(const std::string& tag) : m_ColliderTag(tag)
{
	CollisionManager().GetInstance().RegisterCollider(this);
}

Collider::~Collider()
{
	CollisionManager().GetInstance().UnregisterCollider(this);
}

void Collider::OnCollision(Collider* other)
{
	auto go = other->m_pGameObject;
	for (auto comp : m_pGameObject->GetComponents())
	{
		comp->OnCollision(go);
	}
}
