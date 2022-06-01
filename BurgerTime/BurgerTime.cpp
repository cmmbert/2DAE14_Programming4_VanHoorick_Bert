#include "MiniginPCH.h"
#define _DEBUGRENDERING 1 //1 for debug collision boxes etc

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif



#include "GameObject.h"
#include "InputManager.h"
#include "LevelGen.h"
#include "LevelSettings.h"
#include "Minigin.h"
#include "Renderer.h"
#include "Scene.h"




int main(int, char* []) {
	auto& input = dae::InputManager::GetInstance();

	dae::Minigin engine;
	engine.Initialize();
	auto& scene = engine.LoadGame();

	auto left = LevelGen::GenerateBlockingField(Direction::Left);
	left->SetPosition(0, 0);
	left->SetSize(1, 1000);
	scene.Add(left);
	auto right = LevelGen::GenerateBlockingField(Direction::Right);
	right->SetPosition(static_cast<float>(dae::Renderer::GetInstance().ScreenSize().x), 0);
	right->SetSize(1, 1000);
	scene.Add(right);


	//Level 1
	std::shared_ptr<dae::GameObject> floor{};

	floor = LevelGen::GenerateFloorLight({ 0, 121 * LevelSettings::Scale });
	scene.Add(floor);
	floor = LevelGen::GenerateFloorDark({ 16 * LevelSettings::Scale,121 * LevelSettings::Scale });
	scene.Add(floor);
	floor = LevelGen::GenerateFloorLight({ 48 * LevelSettings::Scale, 121 * LevelSettings::Scale });
	scene.Add(floor);
	auto block = LevelGen::GenerateBlockingField(Direction::Right);
	block->SetPosition(64 * LevelSettings::Scale, 121 * LevelSettings::Scale);
	block->SetSize(1, 16 * LevelSettings::Scale);
	scene.Add(block);
	LevelSettings::m_LevelHeights.insert(124 * LevelSettings::Scale);


	floor = LevelGen::GenerateFloorLight({ 0, 73 * LevelSettings::Scale });
	scene.Add(floor);
	floor = LevelGen::GenerateFloorDark({ 16 * LevelSettings::Scale,73 * LevelSettings::Scale });
	scene.Add(floor);
	floor = LevelGen::GenerateFloorLight({ 48 * LevelSettings::Scale, 73 * LevelSettings::Scale });
	scene.Add(floor);
	floor = LevelGen::GenerateFloorDark({ 64 * LevelSettings::Scale,73 * LevelSettings::Scale });
	scene.Add(floor);
	floor = LevelGen::GenerateFloorLight({ 96 * LevelSettings::Scale, 73 * LevelSettings::Scale });
	scene.Add(floor);
	floor = LevelGen::GenerateFloorDark({ 112 * LevelSettings::Scale,73 * LevelSettings::Scale });
	scene.Add(floor);
	block = LevelGen::GenerateBlockingField(Direction::Right);
	block->SetPosition(144 * LevelSettings::Scale, 73 * LevelSettings::Scale);
	block->SetSize(1, 16 * LevelSettings::Scale);
	scene.Add(block);
	LevelSettings::m_LevelHeights.insert(76 * LevelSettings::Scale);

	std::shared_ptr<dae::GameObject> ladder{};
	ladder = LevelGen::GenerateLadder({ 0,42 * LevelSettings::Scale }, {16*LevelSettings::Scale, 80*LevelSettings::Scale}, scene);
	scene.Add(ladder);
	ladder = LevelGen::GenerateLadder({ 192 * LevelSettings::Scale, 42 * LevelSettings::Scale }, {16*LevelSettings::Scale, 32*LevelSettings::Scale}, scene);
	scene.Add(ladder);
	//ladder = GenerateLadder({ 48 * LevelSettings::Scale, 42 * LevelSettings::Scale }, {16*LevelSettings::Scale, 146 *LevelSettings::Scale}, scene);
	//scene.Add(ladder);

	floor = LevelGen::GenerateFloorLight({ 0, 41 * LevelSettings::Scale });
	scene.Add(floor);
	floor = LevelGen::GenerateFloorDark({ 16 * LevelSettings::Scale,41 * LevelSettings::Scale });
	scene.Add(floor);
	floor = LevelGen::GenerateFloorLight({ 48 * LevelSettings::Scale, 41 * LevelSettings::Scale });
	scene.Add(floor);
	floor = LevelGen::GenerateFloorDark({ 64 * LevelSettings::Scale,41 * LevelSettings::Scale });
	scene.Add(floor);
	floor = LevelGen::GenerateFloorLight({ 96 * LevelSettings::Scale, 41 * LevelSettings::Scale });
	scene.Add(floor);
	floor = LevelGen::GenerateFloorDark({ 112 * LevelSettings::Scale,41 * LevelSettings::Scale });
	scene.Add(floor);
	floor = LevelGen::GenerateFloorLight({ 144 * LevelSettings::Scale, 41 * LevelSettings::Scale });
	scene.Add(floor);
	floor = LevelGen::GenerateFloorDark({ 160 * LevelSettings::Scale,41 * LevelSettings::Scale });
	scene.Add(floor);
	floor = LevelGen::GenerateFloorLight({ 192 * LevelSettings::Scale, 41 * LevelSettings::Scale });
	scene.Add(floor);

	LevelSettings::m_LevelHeights.insert(44 * LevelSettings::Scale);


	auto burger = LevelGen::GenerateBurgerPiece({ 16 * LevelSettings::Scale,121 * LevelSettings::Scale }, { 112,49 }, scene);
	scene.Add(burger);
	burger = LevelGen::GenerateBurgerPiece({ 16 * LevelSettings::Scale,73 * LevelSettings::Scale }, { 112,73 }, scene);
	scene.Add(burger);
	burger = LevelGen::GenerateBurgerPiece({ 16 * LevelSettings::Scale,41 * LevelSettings::Scale }, { 112, 57 }, scene);
	scene.Add(burger);

	auto pepper = LevelGen::GeneratePeter({8 * LevelSettings::Scale, 44 * LevelSettings::Scale});
	scene.Add(pepper);

	auto hotdog = LevelGen::GenerateHotdog({ 192 * LevelSettings::Scale, 44 * LevelSettings::Scale }, pepper);
	scene.Add(hotdog);

	auto tray = LevelGen::GenerateBurgerTray({ 13 * LevelSettings::Scale,5 * LevelSettings::Scale }, scene, 4);
	scene.Add(tray);
	engine.Run();
	return 0;
}
