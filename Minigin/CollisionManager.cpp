#include "MiniginPCH.h"
#include "CollisionManager.h"

void CollisionManager::RegisterCollider(Collider* collider)
{
	m_Tags[collider->GetTag().GetName()].push_back(collider);
}

void CollisionManager::UnregisterCollider(Collider* collider)
{
	if (m_Tags.size() == 0 || m_IsDestructed) return;
	auto tagName = collider->GetTag().GetName();
	auto idx = std::find(m_Tags[tagName].begin(), m_Tags[tagName].end(), collider);
	m_DeletedTags[tagName].push_back(static_cast<int>(std::distance(m_Tags[tagName].begin(), idx)));
}

void CollisionManager::Update()
{
	if(m_DeleteAll)
	{
		m_Tags.clear();
		m_DeletedTags.clear();
		m_DeleteAll = false;
		return;
	}

	for (auto& tag : m_Tags)
	{
		for (size_t i = 0; i < tag.second.size(); ++i)
		{
			auto coll = tag.second[i];
			for (size_t j = 0; j < tag.second.size(); ++j)
			{
				bool valid = true;
				for (size_t d = 0; d < m_DeletedTags[tag.first].size(); ++d)
				{
					if (m_DeletedTags[tag.first][d] == j) valid = false;
					if (m_DeletedTags[tag.first][d] == i) valid = false;
				}
				if (!valid) continue;

				auto second = tag.second[j];
				if (coll == second) continue;
				

				auto box1TL = (glm::ivec2)coll->GetGameObject()->GetWorldPosition();
				box1TL.y += coll->GetGameObject()->GetTransform().GetSize().y;

				auto box1BR = (glm::ivec2)coll->GetGameObject()->GetWorldPosition();
				box1BR.x += coll->GetGameObject()->GetTransform().GetSize().x;

				auto box2TL = (glm::ivec2)second->GetGameObject()->GetWorldPosition();
				box2TL.y += second->GetGameObject()->GetTransform().GetSize().y;

				auto box2BR = (glm::ivec2)second->GetGameObject()->GetWorldPosition();
				box2BR.x += second->GetGameObject()->GetTransform().GetSize().x;

				if(BoxCollision(box1TL, box1BR,	box2TL, box2BR))
				{
					coll->OnCollision(second);
				}
			}
		}
	}

	for (auto& deletedTag : m_DeletedTags)
	{
		for (auto delIdx : deletedTag.second)
		{
			m_Tags[deletedTag.first].erase(m_Tags[deletedTag.first].begin() + delIdx);
		}

	}
	m_DeletedTags.clear();
}

void CollisionManager::UnregisterAll()
{
	m_DeleteAll = true;
}

bool CollisionManager::BoxCollision(glm::ivec2 box1TL, glm::ivec2 box1BR, glm::ivec2 box2TL, glm::ivec2 box2BR)
{
	if (box1TL.x < box2BR.x && box1BR.x > box2TL.x &&
		box1TL.y > box2BR.y && box1BR.y < box2TL.y)
		return true;

	return false;
}
