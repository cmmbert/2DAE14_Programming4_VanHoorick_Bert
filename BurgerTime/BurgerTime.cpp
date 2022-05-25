#include "MiniginPCH.h"

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "BoxColliderComp.h"
#include "BurgerPiece.h"
#include "BurgerShardComp.h"
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

	auto test = std::make_shared<dae::GameObject>();
	auto collision = std::make_shared<BoxColliderComp>("burgerPiece");
	auto texLeft = std::make_shared<dae::TextureComponent>("Burgertime/spritesheet.png", glm::vec4{ 112,49,8,8 });
	auto shard = std::make_shared<BurgerShardComp>();
	test->AddComponent(shard);
	test->AddComponent(collision);
	test->SetSize(80, 80);
	test->SetPosition(glm::ivec2{ 0,0 });
	test->AddComponent(texLeft);
	scene.Add(test);

	test = std::make_shared<dae::GameObject>();
	collision = std::make_shared<BoxColliderComp>("burgerPiece");
	texLeft = std::make_shared<dae::TextureComponent>("Burgertime/spritesheet.png", glm::vec4{ 0,0,16,16 });
	test->AddComponent(collision);
	test->SetSize(160, 160);
	test->SetPosition(glm::ivec2{ 80,4 });
	test->AddComponent(texLeft);
	scene.Add(test);


	engine.Run();
	return 0;
}

