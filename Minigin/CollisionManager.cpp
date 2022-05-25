#include "MiniginPCH.h"
#include "CollisionManager.h"

void CollisionManager::RegisterCollider(Collider* collider)
{
	m_Tags[collider->GetTag().GetName()].push_back(collider);
}

void CollisionManager::UnregisterCollider(Collider* collider)
{
	//TODO fix this map bug: map says its size is 1 without actually having any element inside it
	if (m_Tags.size() == 1) return;
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
				if (coll == second) continue;
				auto box1TL = (glm::ivec2)coll->GetTransform().GetPosition();
				box1TL.y += coll->GetTransform().GetSize().y;

				auto box1BR = (glm::ivec2)coll->GetTransform().GetPosition();
				box1BR.x += coll->GetTransform().GetSize().x;

				auto box2TL = (glm::ivec2)second->GetTransform().GetPosition();
				box2TL.y += second->GetTransform().GetSize().y;

				auto box2BR = (glm::ivec2)second->GetTransform().GetPosition();
				box2BR.x += second->GetTransform().GetSize().x;

				if(BoxCollision(box1TL, box1BR,	box2TL, box2BR))
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
