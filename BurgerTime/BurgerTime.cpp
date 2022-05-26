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
#include "GameObject.h"
#include "InputManager.h"
#include "Minigin.h"
#include "PeterCommands.h"
#include "Scene.h"

int main(int, char* []) {
	auto& input = dae::InputManager::GetInstance();

	dae::Minigin engine;
	engine.Initialize();
	auto& scene = engine.LoadGame();

	auto burger = std::make_shared<dae::GameObject>();
	auto burgerComp = std::make_shared<BurgerPiece>(burger.get());
	burger->AddComponent(burgerComp);
	burger->SetPosition(glm::ivec2{ 40,4 });
	burgerComp->GenerateShards(glm::ivec2{ 112,49 }, scene);

	scene.Add(burger);
	
	auto pepper = std::make_shared<dae::GameObject>();
	auto collision = std::make_shared<BoxColliderComp>(pepper.get(), "burgerPiece");
	auto texture = std::make_shared<dae::TextureComponent>(pepper.get(), "Burgertime/spritesheet.png", glm::vec4{ 0,0,16,16 });
	auto pepComp = std::make_shared<PeterPepperComp>(pepper.get());
	auto animComp = std::make_shared<AnimationComponent>(pepper.get(), texture, 0.2f);
	animComp->AddAnimationFrame("run", { 48, 0 });
	animComp->AddAnimationFrame("run",{ 64, 0 });
	animComp->AddAnimationFrame("run",{ 80, 0 });
	animComp->SetCurrentAnimation("run");
	animComp->AddAnimationFrame("climb", { 96, 0 });
	animComp->AddAnimationFrame("climb", { 112, 0 });
	animComp->AddAnimationFrame("climb", { 128, 0 });
	animComp->SetCurrentAnimation("climb");

	pepper->AddComponent(animComp);
	pepper->AddComponent(collision);
	pepper->SetSize(160, 160);
	pepper->SetPosition(glm::ivec2{ 400,50 });
	pepper->AddComponent(texture);
	scene.Add(pepper);

	input.AddOrChangeCommand(eControllerButton::DpadRight, std::make_shared<LateralMovementCommand>(pepComp, 1));
	input.AddOrChangeCommand(eControllerButton::DpadLeft,  std::make_shared<LateralMovementCommand>(pepComp, -1));

	engine.Run();
	return 0;
}

