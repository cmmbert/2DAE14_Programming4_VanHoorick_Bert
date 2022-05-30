#pragma once
#include <set>
class LevelSettings
{
public:
	static const int Scale{3};
	static std::set<int> m_LevelHeights;
	static std::set<int> m_LevelLadderCrossPoints;

};

