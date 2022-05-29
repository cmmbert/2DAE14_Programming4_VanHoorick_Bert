#include "MiniginPCH.h"

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
#include "Minigin.h"
#include "PeterCommands.h"
#include "Scene.h"

std::shared_ptr<dae::GameObject> GeneratePeter(glm::ivec2 pos);
std::shared_ptr<dae::GameObject> GenerateHotdog(glm::ivec2 pos);


int main(int, char* []) {
	auto& input = dae::InputManager::GetInstance();

	dae::Minigin engine;
	engine.Initialize();
	auto& scene = engine.LoadGame();

	auto burger = std::make_shared<dae::GameObject>();
	auto burgerComp = std::make_shared<BurgerPiece>(burger.get());
	burger->AddComponent(burgerComp);
	burger->SetPosition(glm::ivec2{ 40,325 });
	burgerComp->GenerateShards(glm::ivec2{ 112,49 }, scene);

	scene.Add(burger);
	
	auto pepper = GeneratePeter(glm::ivec2{ 400,100 });
	scene.Add(pepper);

	auto hotdog = GenerateHotdog({ 100, 100 });
	scene.Add(hotdog);

	auto ladder = std::make_shared<dae::GameObject>();


	ladder->SetSize(160, 100);
	ladder->SetPosition(50, 100);
	auto coll = std::make_shared<BoxColliderComp>(ladder.get(), "ladder");
	ladder->AddComponent(coll);
	auto ladrComp = std::make_shared<LadderComp>(ladder.get(), scene);
	ladder->AddComponent(ladrComp);

#if _DEBUG
	auto texture = std::make_shared<dae::TextureComponent>(ladder.get(), "Burgertime/spritesheet.png", glm::vec4{ 87,38,1,1 });
	ladder->AddComponent(texture);
#endif

	scene.Add(ladder);


	auto block = std::make_shared<dae::GameObject>();
	block->SetSize(160, 2);
	block->SetPosition(50, 101);

	auto blockComp = std::make_shared<BlockComp>(block.get(), (int)Direction::Down);
	block->AddComponent(blockComp);

	coll = std::make_shared<BoxColliderComp>(block.get(), "block");
	block->AddComponent(coll);
#if _DEBUG
	texture = std::make_shared<dae::TextureComponent>(block.get(), "Burgertime/spritesheet.png", glm::vec4{ 100,24,1,1 });
	block->AddComponent(texture);
#endif

	scene.Add(block);

	auto blockLeft = std::make_shared<dae::GameObject>();
	blockLeft->SetSize(5, 100);
	blockLeft->SetPosition(200, 100);
	auto blockLeftComp = std::make_shared<BlockComp>(blockLeft.get(), static_cast<int>(Direction::Left));
	blockLeft->AddComponent(blockLeftComp);
	coll = std::make_shared<BoxColliderComp>(block.get(), "block");
	blockLeft->AddComponent(coll);
	scene.Add(blockLeft);
#if _DEBUG
	texture = std::make_shared<dae::TextureComponent>(blockLeft.get(), "Burgertime/spritesheet.png", glm::vec4{ 100,24,1,1 });
	blockLeft->AddComponent(texture);
#endif
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
	hotdog->SetSize(160, 160);
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
	pepper->SetSize(160, 160);
	pepper->SetPosition(pos);
	pepper->AddComponent(texture);

	auto& input = dae::InputManager::GetInstance();
	input.AddOrChangeCommand(eControllerButton::DpadRight, std::make_shared<LateralMovementCommand>(pepComp, 1));
	input.AddOrChangeCommand(eControllerButton::DpadLeft, std::make_shared<LateralMovementCommand>(pepComp, -1));
	input.AddOrChangeCommand(eControllerButton::DpadUp, std::make_shared<VerticalMovementCommand>(pepComp, 1));
	input.AddOrChangeCommand(eControllerButton::DpadDown, std::make_shared<VerticalMovementCommand>(pepComp, -1));

	pepComp->AddLevelHeight(100);
	pepComp->AddLevelHeight(200);
	return pepper;
}

