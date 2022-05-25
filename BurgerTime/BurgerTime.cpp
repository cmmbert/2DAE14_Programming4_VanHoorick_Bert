#include "MiniginPCH.h"

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "BoxColliderComp.h"
#include "BurgerPiece.h"
#include "GameObject.h"
#include "Minigin.h"
#include "Scene.h"

int main(int, char* []) {

	dae::Minigin engine;
	engine.Initialize();
	auto& scene = engine.LoadGame();

	auto burger = std::make_shared<dae::GameObject>();
	auto burgerComp = std::make_shared<BurgerPiece>();
	burger->AddComponent(burgerComp);
	//burgerComp->GenerateShards(glm::ivec2{ 112,49 }, scene);
	//scene.Add(burger);

	auto texLeft = std::make_shared<dae::TextureComponent>("Burgertime/spritesheet.png", 80, 80, glm::vec4{ 112,49,8,8 });
	auto go = std::make_shared<dae::GameObject>();
	go->SetPosition({ 10,-10 });
	go->AddComponent(texLeft);
	scene.Add(go);

	/*auto test = std::make_shared<dae::GameObject>();
	auto collision = std::make_shared<BoxColliderComp>("burgerPiece");
	test->AddComponent(collision);
	test->SetSize(4, 3);
	test->SetPosition(glm::ivec2{ 1,6 });
	scene.Add(test);

	test = std::make_shared<dae::GameObject>();
	collision = std::make_shared<BoxColliderComp>("burgerPiece");
	test->AddComponent(collision);
	test->SetSize(4, 3);
	test->SetPosition(glm::ivec2{ 4,4 });
	scene.Add(test);*/


	engine.Run();
	return 0;
}

