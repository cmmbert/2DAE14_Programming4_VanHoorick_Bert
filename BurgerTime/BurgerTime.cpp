#include "MiniginPCH.h"

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

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
	burgerComp->GenerateShards(glm::ivec2{ 112,49 }, scene);
	scene.Add(burger);


	engine.Run();
	return 0;
}

