#pragma once
#include <glm/vec2.hpp>

#include "BaseComponent.h"

enum class Direction
{
	Up =	0x1000,
	Down =	0x2000,
	Left =  0x4000,
	Right = 0x8000,
};

class BlockComp final : public dae::BaseComponent 
{
	int m_Direction;
public:
	explicit BlockComp(::dae::GameObject* gameObject, int direction)
		: BaseComponent(gameObject), m_Direction(direction)
	{
	}
	bool IsBlockingDirection(Direction direction)
	{
		return m_Direction & static_cast<int>(direction);
	}
};

