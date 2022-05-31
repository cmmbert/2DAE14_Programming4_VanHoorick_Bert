#include "MiniginPCH.h"
#include "Collider.h"

#include "CollisionManager.h"


ColliderTag::ColliderTag(const std::string& name) : m_Name(name)
{

}

Collider::Collider(dae::GameObject* gameObject, const std::string& tag) : BaseComponent(gameObject), m_ColliderTag(tag)
{
	CollisionManager::GetInstance().RegisterCollider(this);
}

Collider::~Collider()
{
	//TODO fix this map bug: map says its size is 1 without actually having any element inside it
	CollisionManager::GetInstance().UnregisterCollider(this);
	m_pGameObject = nullptr;
}

void Collider::OnCollision(Collider* other)
{
	auto go = other->m_pGameObject;
	for (auto comp : m_pGameObject->GetComponents())
	{
		comp->OnCollision(go);
	}
}
