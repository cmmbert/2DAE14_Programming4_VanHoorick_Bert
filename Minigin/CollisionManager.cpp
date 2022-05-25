#include "MiniginPCH.h"
#include "CollisionManager.h"

void CollisionManager::RegisterCollider(Collider* collider)
{
	m_Tags[collider->GetTag().GetName()].push_back(collider);
}

void CollisionManager::UnregisterCollider(Collider* collider)
{
	auto& col = m_Tags[collider->GetTag().GetName()];
	col.erase(std::remove(col.begin(), col.end(), collider), col.end());
}

void CollisionManager::Update()
{
	for (auto& tag : m_Tags)
	{
		for (auto coll : tag.second)
		{
			for (auto second : tag.second)
			{
				auto box1BR = coll->GetTransform().GetSize();
				box1BR.x += (int)coll->GetTransform().GetPosition().x;
				box1BR.y += (int)coll->GetTransform().GetPosition().y;

				auto box2BR = second->GetTransform().GetSize();
				box2BR.x += (int)second->GetTransform().GetPosition().x;
				box2BR.y += (int)second->GetTransform().GetPosition().y;
				if(BoxCollision(coll->GetTransform().GetPosition(), box1BR,
					second->GetTransform().GetPosition(), box2BR))
				{
					coll->OnCollision(second);
				}
			}
		}
	}
}

bool CollisionManager::BoxCollision(glm::ivec2 box1TL, glm::ivec2 box1BR, glm::ivec2 box2TL, glm::ivec2 box2BR)
{
	if (box1TL.x < box2BR.x && box1BR.x > box2TL.x &&
		box1TL.y > box2BR.y && box1BR.y < box2TL.y)
		return true;

	return false;
}
