#include "MiniginPCH.h"
#define _DEBUGRENDERING 1; //1 for debug collision boxes etc

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "AnimationComponent.h"
#include "BlockComp.h"
#include "BoxColliderComp.h"
#include "BurgerPiece.h"
#include "EnemyComponent.h"
#include "GameObject.h"
#include "InputManager.h"
#include "LadderComp.h"
#include "LevelSettings.h"
#include "Minigin.h"
#include "PeterCommands.h"
#include "Scene.h"

std::shared_ptr<dae::GameObject> GeneratePeter(glm::ivec2 pos);
std::shared_ptr<dae::GameObject> GenerateHotdog(glm::ivec2 pos);
std::shared_ptr<dae::GameObject> GenerateBlockingField(Direction direction);

//const int LevelSettings::Scale = 2;


int main(int, char* []) {
	auto& input = dae::InputManager::GetInstance();

	dae::Minigin engine;
	engine.Initialize();
	auto& scene = engine.LoadGame();


	auto ladder = std::make_shared<dae::GameObject>();


	ladder->SetSize(16 * LevelSettings::Scale, 32 * LevelSettings::Scale);
	ladder->SetPosition(32 * LevelSettings::Scale, 8 * LevelSettings::Scale);
	auto coll = std::make_shared<BoxColliderComp>(ladder.get(), "ladder");
	ladder->AddComponent(coll);
	auto ladrComp = std::make_shared<LadderComp>(ladder.get(), scene);
	ladder->AddComponent(ladrComp);

#if _DEBUGRENDERING
	auto debugtexture = std::make_shared<dae::TextureComponent>(ladder.get(), "Burgertime/spritesheet.png", glm::vec4{ 87,38,1,1 });
	ladder->AddComponent(debugtexture);
#endif

	scene.Add(ladder);



	auto block = GenerateBlockingField(Direction::Down);
	block->SetSize(16 * LevelSettings::Scale, 2);
	block->SetPosition(24 * LevelSettings::Scale, 8 * LevelSettings::Scale);
	scene.Add(block);
	block = GenerateBlockingField(Direction::Left);
	block->SetSize(5, 1000);
	block->SetPosition(8 * LevelSettings::Scale, 8 * LevelSettings::Scale);
	scene.Add(block);

	block = GenerateBlockingField(Direction::Right);
	block->SetSize(5, 10 * LevelSettings::Scale);
	block->SetPosition(56 * LevelSettings::Scale, 8 * LevelSettings::Scale);
	scene.Add(block);


	auto floor = std::make_shared<dae::GameObject>();
	auto texture = std::make_shared<dae::TextureComponent>(floor.get(), "Burgertime/spritesheet.png", glm::vec4{ 202,141,32,3 });
	floor->AddComponent(texture);
	floor->SetSize(32 * LevelSettings::Scale, 3 * LevelSettings::Scale);
	floor->SetPosition(24 * LevelSettings::Scale, 5 * LevelSettings::Scale);
	scene.Add(floor);

	floor = std::make_shared<dae::GameObject>();
	texture = std::make_shared<dae::TextureComponent>(floor.get(), "Burgertime/spritesheet.png", glm::vec4{ 202,147,16,3 });
	floor->AddComponent(texture);
	floor->SetSize(16 * LevelSettings::Scale, 3 * LevelSettings::Scale);
	floor->SetPosition(8 * LevelSettings::Scale, 5 * LevelSettings::Scale);
	scene.Add(floor);

	floor = std::make_shared<dae::GameObject>();
	texture = std::make_shared<dae::TextureComponent>(floor.get(), "Burgertime/spritesheet.png", glm::vec4{ 202,141,32,3 });
	floor->AddComponent(texture);
	floor->SetSize(32 * LevelSettings::Scale, 3 * LevelSettings::Scale);
	floor->SetPosition(24 * LevelSettings::Scale, 37 * LevelSettings::Scale);
	scene.Add(floor);




	auto burger = std::make_shared<dae::GameObject>();
	auto burgerComp = std::make_shared<BurgerPiece>(burger.get());
	burger->AddComponent(burgerComp);
	burger->SetPosition(glm::ivec2{ 4 * LevelSettings::Scale,37 * LevelSettings::Scale });
	burgerComp->GenerateShards(glm::ivec2{ 112,49 }, scene);

	scene.Add(burger);

	auto pepper = GeneratePeter(glm::ivec2{ 42 * LevelSettings::Scale,8 * LevelSettings::Scale });
	scene.Add(pepper);

	auto hotdog = GenerateHotdog({ 10 * LevelSettings::Scale, 8 * LevelSettings::Scale });
	scene.Add(hotdog);


	engine.Run();
	return 0;
}

std::shared_ptr<dae::GameObject> GenerateHotdog(glm::ivec2 pos)
{
	auto hotdog = std::make_shared<dae::GameObject>();
	auto enemy = std::make_shared<EnemyComponent>(hotdog.get());
	auto texture = std::make_shared<dae::TextureComponent>(hotdog.get(), "Burgertime/spritesheet.png", glm::vec4{ 32,32,16,16 });
	texture->m_Flipped = true;
	auto animComp = std::make_shared<AnimationComponent>(hotdog.get(), texture, 0.2f);
	animComp->AddAnimationFrame("run", { 32, 32 });
	animComp->AddAnimationFrame("run", { 48, 32 });
	animComp->SetCurrentAnimation("run");
	animComp->AddAnimationFrame("death", { 0, 48 });
	animComp->AddAnimationFrame("death", { 16, 48 });
	animComp->AddAnimationFrame("death", { 32, 48 });
	animComp->AddAnimationFrame("death", { 48, 48 });
	hotdog->SetSize(16 * LevelSettings::Scale, 16 * LevelSettings::Scale);
	hotdog->SetPosition(pos);
	hotdog->AddComponent(enemy);
	hotdog->AddComponent(texture);
	hotdog->AddComponent(animComp);

	auto collision = std::make_shared<BoxColliderComp>(hotdog.get(), "burgerPiece");
	hotdog->AddComponent(collision);

	return hotdog;
}

std::shared_ptr<dae::GameObject> GeneratePeter(glm::ivec2 pos)
{
	auto pepper = std::make_shared<dae::GameObject>();
	auto coll = std::make_shared<BoxColliderComp>(pepper.get(), "ladder");
	pepper->AddComponent(coll);
	coll = std::make_shared<BoxColliderComp>(pepper.get(), "burgerPiece");;
	pepper->AddComponent(coll);
	coll = std::make_shared<BoxColliderComp>(pepper.get(), "block");
	pepper->AddComponent(coll);
	auto texture = std::make_shared<dae::TextureComponent>(pepper.get(), "Burgertime/spritesheet.png", glm::vec4{ 0,0,16,16 });
	auto pepComp = std::make_shared<PeterPepperComp>(pepper.get());
	pepper->AddComponent(pepComp);
	auto animComp = std::make_shared<AnimationComponent>(pepper.get(), texture, 0.2f);
	animComp->AddAnimationFrame("run", { 48, 0 });
	animComp->AddAnimationFrame("run", { 64, 0 });
	animComp->AddAnimationFrame("run", { 80, 0 });
	animComp->SetCurrentAnimation("run");
	animComp->AddAnimationFrame("climb", { 96, 0 });
	animComp->AddAnimationFrame("climb", { 112, 0 });
	animComp->AddAnimationFrame("climb", { 128, 0 });
	animComp->SetCurrentAnimation("climb");

	pepper->AddComponent(animComp);
	pepper->SetSize(16 * LevelSettings::Scale, 16 * LevelSettings::Scale);
	pepper->SetPosition(pos);
	pepper->AddComponent(texture);

	auto& input = dae::InputManager::GetInstance();
	input.AddOrChangeCommand(eControllerButton::DpadRight, std::make_shared<LateralMovementCommand>(pepComp, 1));
	input.AddOrChangeCommand(eControllerButton::DpadLeft, std::make_shared<LateralMovementCommand>(pepComp, -1));
	input.AddOrChangeCommand(eControllerButton::DpadUp, std::make_shared<VerticalMovementCommand>(pepComp, 1));
	input.AddOrChangeCommand(eControllerButton::DpadDown, std::make_shared<VerticalMovementCommand>(pepComp, -1));

	pepComp->AddLevelHeight(8 * LevelSettings::Scale);
	pepComp->AddLevelHeight(40 * LevelSettings::Scale);
	return pepper;
}


std::shared_ptr<dae::GameObject> GenerateBlockingField(Direction direction)
{
	auto block = std::make_shared<dae::GameObject>();

	auto blockComp = std::make_shared<BlockComp>(block.get(), (int)direction);
	block->AddComponent(blockComp);

	auto coll = std::make_shared<BoxColliderComp>(block.get(), "block");
	block->AddComponent(coll);
#if _DEBUGRENDERING
	auto texture = std::make_shared<dae::TextureComponent>(block.get(), "Burgertime/spritesheet.png", glm::vec4{ 100,24,1,1 });
	block->AddComponent(texture);
#endif

	return block;
}
