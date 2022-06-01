#pragma once
#include <map>

#include "Collider.h"
#include "Singleton.h"

class CollisionManager : public dae::Singleton<CollisionManager>
{
private:
	bool m_IsDestructed{};
	std::map<std::string, std::vector<Collider*>> m_Tags{};
	std::map<std::string, std::vector<int>> m_DeletedTags{};
public:
	void RegisterCollider(Collider* collider);
	void UnregisterCollider(Collider* collider);
	void Update();

	bool BoxCollision(glm::ivec2 box1TL, glm::ivec2 box1BR, glm::ivec2 box2TL, glm::ivec2 box2BR);
	~CollisionManager() override { m_IsDestructed = true; };
};

