#include "MiniginPCH.h"

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "AnimationComponent.h"
#include "BoxColliderComp.h"
#include "BurgerPiece.h"
#include "EnemyComponent.h"
#include "GameObject.h"
#include "InputManager.h"
#include "Minigin.h"
#include "PeterCommands.h"
#include "Scene.h"

std::shared_ptr<dae::GameObject> GeneratePeter(glm::ivec2 pos);


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
	
	auto pepper = GeneratePeter(glm::ivec2{ 400,325 });
	scene.Add(pepper);

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
	hotdog->SetPosition({100, 100});
	hotdog->AddComponent(enemy);
	hotdog->AddComponent(texture);
	hotdog->AddComponent(animComp);

	auto collision = std::make_shared<BoxColliderComp>(hotdog.get(), "burgerPiece");
	hotdog->AddComponent(collision);

	scene.Add(hotdog);

	engine.Run();
	return 0;
}

std::shared_ptr<dae::GameObject> GeneratePeter(glm::ivec2 pos)
{
	auto pepper = std::make_shared<dae::GameObject>();
	auto collision = std::make_shared<BoxColliderComp>(pepper.get(), "burgerPiece");
	auto texture = std::make_shared<dae::TextureComponent>(pepper.get(), "Burgertime/spritesheet.png", glm::vec4{ 0,0,16,16 });
	auto pepComp = std::make_shared<PeterPepperComp>(pepper.get());
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
	pepper->AddComponent(collision);
	pepper->SetSize(160, 160);
	pepper->SetPosition(pos);
	pepper->AddComponent(texture);

	auto& input = dae::InputManager::GetInstance();
	input.AddOrChangeCommand(eControllerButton::DpadRight, std::make_shared<LateralMovementCommand>(pepComp, 1));
	input.AddOrChangeCommand(eControllerButton::DpadLeft, std::make_shared<LateralMovementCommand>(pepComp, -1));

	return pepper;
}

