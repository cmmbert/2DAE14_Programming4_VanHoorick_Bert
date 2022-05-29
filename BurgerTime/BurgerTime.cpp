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
#include "Renderer.h"
#include "Scene.h"

std::shared_ptr<dae::GameObject> GeneratePeter(glm::ivec2 pos);
std::shared_ptr<dae::GameObject> GenerateHotdog(glm::ivec2 pos);
std::shared_ptr<dae::GameObject> GenerateBlockingField(Direction direction);
std::shared_ptr<dae::GameObject> GenerateLadder(glm::ivec2 pos, glm::ivec2 scale, dae::Scene& scene);
std::shared_ptr<dae::GameObject> GenerateFloorDark(glm::ivec2 pos);
std::shared_ptr<dae::GameObject> GenerateFloorLight(glm::ivec2 pos);
std::shared_ptr<dae::GameObject> GenerateBurgerPiece(glm::ivec2 pos, glm::ivec2 texCoord, dae::Scene& scene);
void ConstructTestScene(dae::Scene& scene);



int main(int, char* []) {
	auto& input = dae::InputManager::GetInstance();

	dae::Minigin engine;
	engine.Initialize();
	auto& scene = engine.LoadGame();

	auto left = GenerateBlockingField(Direction::Left);
	left->SetPosition(0, 0);
	left->SetSize(1, 1000);
	scene.Add(left);
	auto right = GenerateBlockingField(Direction::Right);
	right->SetPosition(dae::Renderer::GetInstance().ScreenSize().x, 0);
	right->SetSize(1, 1000);
	scene.Add(right);


	//Level 1
	std::shared_ptr<dae::GameObject> floor{};

	floor = GenerateFloorLight({ 0, 73 * LevelSettings::Scale });
	scene.Add(floor);
	floor = GenerateFloorDark({ 16 * LevelSettings::Scale,73 * LevelSettings::Scale });
	scene.Add(floor);
	floor = GenerateFloorLight({ 48 * LevelSettings::Scale, 73 * LevelSettings::Scale });
	scene.Add(floor);
	floor = GenerateFloorDark({ 64 * LevelSettings::Scale,73 * LevelSettings::Scale });
	scene.Add(floor);
	floor = GenerateFloorLight({ 96 * LevelSettings::Scale, 73 * LevelSettings::Scale });
	scene.Add(floor);
	floor = GenerateFloorDark({ 112 * LevelSettings::Scale,73 * LevelSettings::Scale });
	scene.Add(floor);
	auto block = GenerateBlockingField(Direction::Right);
	block->SetPosition(144 * LevelSettings::Scale, 73 * LevelSettings::Scale);
	block->SetSize(1, 16 * LevelSettings::Scale);
	scene.Add(block);

	std::shared_ptr<dae::GameObject> ladder{};
	ladder = GenerateLadder({ 0,42 * LevelSettings::Scale }, {16*LevelSettings::Scale, 34*LevelSettings::Scale}, scene);
	scene.Add(ladder);

	floor = GenerateFloorLight({ 0, 41 * LevelSettings::Scale });
	scene.Add(floor);
	floor = GenerateFloorDark({ 16 * LevelSettings::Scale,41 * LevelSettings::Scale });
	scene.Add(floor);
	floor = GenerateFloorLight({ 48 * LevelSettings::Scale, 41 * LevelSettings::Scale });
	scene.Add(floor);
	floor = GenerateFloorDark({ 64 * LevelSettings::Scale,41 * LevelSettings::Scale });
	scene.Add(floor);
	floor = GenerateFloorLight({ 96 * LevelSettings::Scale, 41 * LevelSettings::Scale });
	scene.Add(floor);
	floor = GenerateFloorDark({ 112 * LevelSettings::Scale,41 * LevelSettings::Scale });
	scene.Add(floor);
	floor = GenerateFloorLight({ 144 * LevelSettings::Scale, 41 * LevelSettings::Scale });
	scene.Add(floor);
	floor = GenerateFloorDark({ 160 * LevelSettings::Scale,41 * LevelSettings::Scale });
	scene.Add(floor);

	auto burger = GenerateBurgerPiece({ 16 * LevelSettings::Scale,73 * LevelSettings::Scale }, { 112,49 }, scene);
	scene.Add(burger);

	auto pepper = GeneratePeter({8 * LevelSettings::Scale, 44 * LevelSettings::Scale});
	auto pepComp = pepper->GetComponent<PeterPepperComp>();
	pepComp->AddLevelHeight(44 * LevelSettings::Scale);
	pepComp->AddLevelHeight(76 * LevelSettings::Scale);
	scene.Add(pepper);

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

std::shared_ptr<dae::GameObject> GenerateLadder(glm::ivec2 pos, glm::ivec2 scale, dae::Scene& scene)
{
	auto ladder = std::make_shared<dae::GameObject>();
	ladder->SetSize(scale.x, scale.y);
	ladder->SetPosition(pos);
	auto coll = std::make_shared<BoxColliderComp>(ladder.get(), "ladder");
	ladder->AddComponent(coll);
	auto ladrComp = std::make_shared<LadderComp>(ladder.get(), scene);
	ladder->AddComponent(ladrComp);
#if _DEBUGRENDERING
	auto debugtexture = std::make_shared<dae::TextureComponent>(ladder.get(), "Burgertime/spritesheet.png", glm::vec4{ 87,38,1,1 });
	ladder->AddComponent(debugtexture);
#endif

	return ladder;
}

std::shared_ptr<dae::GameObject> GenerateFloorDark(glm::ivec2 pos)
{
	auto floor = std::make_shared<dae::GameObject>();
	auto texture = std::make_shared<dae::TextureComponent>(floor.get(), "Burgertime/spritesheet.png", glm::vec4{ 202,141,32,3 });
	floor->AddComponent(texture);
	floor->SetSize(32 * LevelSettings::Scale, 3 * LevelSettings::Scale);
	floor->SetPosition(pos);
	return floor;
}

std::shared_ptr<dae::GameObject> GenerateFloorLight(glm::ivec2 pos)
{
	auto floor = std::make_shared<dae::GameObject>();
	auto texture = std::make_shared<dae::TextureComponent>(floor.get(), "Burgertime/spritesheet.png", glm::vec4{ 202,147,16,3 });
	floor->AddComponent(texture);
	floor->SetSize(16 * LevelSettings::Scale, 3 * LevelSettings::Scale);
	floor->SetPosition(pos);
	return floor;
}

void ConstructTestScene(dae::Scene& scene)
{
	auto ladder = GenerateLadder(
		{ 32 * LevelSettings::Scale, 8 * LevelSettings::Scale },
		{ 16 * LevelSettings::Scale, 32 * LevelSettings::Scale },
		scene);

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


	auto floor = GenerateFloorDark({ 24 * LevelSettings::Scale, 5 * LevelSettings::Scale });
	scene.Add(floor);
	floor = GenerateFloorDark({ 24 * LevelSettings::Scale, 37 * LevelSettings::Scale });
	scene.Add(floor);
	floor = GenerateFloorLight({ 8 * LevelSettings::Scale, 5 * LevelSettings::Scale });
	scene.Add(floor);






	auto burger = GenerateBurgerPiece({ 4 * LevelSettings::Scale,37 * LevelSettings::Scale }, { 112,49 }, scene);
	scene.Add(burger);

	auto pepper = GeneratePeter(glm::ivec2{ 42 * LevelSettings::Scale,8 * LevelSettings::Scale });
	scene.Add(pepper);

	auto hotdog = GenerateHotdog({ 8 * LevelSettings::Scale, 8 * LevelSettings::Scale });
	scene.Add(hotdog);
}

std::shared_ptr<dae::GameObject> GenerateBurgerPiece(glm::ivec2 pos, glm::ivec2 texCoord, dae::Scene& scene)
{
	auto burger = std::make_shared<dae::GameObject>();
	auto burgerComp = std::make_shared<BurgerPiece>(burger.get());
	burger->AddComponent(burgerComp);
	burger->SetPosition(pos);
	burgerComp->GenerateShards(texCoord, scene);
	return burger;
}