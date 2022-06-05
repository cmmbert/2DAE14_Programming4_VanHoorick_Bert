#pragma once
#include <set>

enum class GameMode
{
	Solo,
	Coop,
	Versus
};
class LevelSettings
{
public:
	static const int Scale{3};
	static GameMode GameMode;
	static int CurrentLevel;
	static std::set<int> m_LevelHeights;
	static std::set<int> m_LevelLadderCrossPoints;

};

