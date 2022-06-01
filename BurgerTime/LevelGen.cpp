#include "LevelGen.h"

#include "BurgerPiece.h"
#include "BurgerTray.h"
#include "InputManager.h"
#include "LadderComp.h"
#include "PeterCommands.h"
#include "PeterPepperComp.h"

std::shared_ptr<dae::GameObject> LevelGen::GenerateHotdog(glm::ivec2 spawnPoint,
                                                          std::shared_ptr<dae::GameObject> target)
{
	auto hotdog = std::make_shared<dae::GameObject>();
	auto enemy = std::make_shared<EnemyComponent>(hotdog.get(), target, spawnPoint);
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
	animComp->AddAnimationFrame("climbup", { 64, 32 });
	animComp->AddAnimationFrame("climbup", { 80, 32 });
	animComp->AddAnimationFrame("climbdown", { 0, 32 });
	animComp->AddAnimationFrame("climbdown", { 16, 32 });
	hotdog->SetSize(16 * LevelSettings::Scale, 16 * LevelSettings::Scale);
	hotdog->SetPosition(spawnPoint);
	hotdog->AddComponent(enemy);
	hotdog->AddComponent(texture);
	hotdog->AddComponent(animComp);

	auto collision = std::make_shared<BoxColliderComp>(hotdog.get(), "fallingBurger");
	hotdog->AddComponent(collision);
	collision = std::make_shared<BoxColliderComp>(hotdog.get(), "ladder");
	hotdog->AddComponent(collision);

	return hotdog;
}

std::shared_ptr<dae::GameObject> LevelGen::GeneratePeter(glm::ivec2 pos)
{
	auto pepper = std::make_shared<dae::GameObject>();
	auto coll = std::make_shared<BoxColliderComp>(pepper.get(), "ladder");
	pepper->AddComponent(coll);
	coll = std::make_shared<BoxColliderComp>(pepper.get(), "burgerPiece");;
	pepper->AddComponent(coll);
	coll = std::make_shared<BoxColliderComp>(pepper.get(), "block");
	pepper->AddComponent(coll);
	auto texture = std::make_shared<dae::TextureComponent>(pepper.get(), "Burgertime/spritesheet.png", glm::vec4{ 16,0,16,16 });
	auto pepComp = std::make_shared<PeterPepperComp>(pepper.get());
	pepper->AddComponent(pepComp);
	auto animComp = std::make_shared<AnimationComponent>(pepper.get(), texture, 0.2f);
	animComp->AddAnimationFrame("run", { 48, 0 });
	animComp->AddAnimationFrame("run", { 64, 0 });
	animComp->AddAnimationFrame("run", { 80, 0 });
	animComp->AddAnimationFrame("climbup", { 96, 0 });
	animComp->AddAnimationFrame("climbup", { 112, 0 });
	animComp->AddAnimationFrame("climbup", { 128, 0 });
	animComp->AddAnimationFrame("climbdown", { 0, 0 });
	animComp->AddAnimationFrame("climbdown", { 16, 0 });
	animComp->AddAnimationFrame("climbdown", { 32, 0 });

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

std::shared_ptr<dae::GameObject> LevelGen::GenerateBlockingField(Direction direction)
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

std::shared_ptr<dae::GameObject> LevelGen::GenerateLadder(glm::ivec2 pos, glm::ivec2 scale, dae::Scene& scene)
{
	auto ladder = std::make_shared<dae::GameObject>();
	ladder->SetSize(scale.x, scale.y + 2 * LevelSettings::Scale);
	ladder->SetPosition(pos);
	auto coll = std::make_shared<BoxColliderComp>(ladder.get(), "ladder");
	ladder->AddComponent(coll);
	auto ladrComp = std::make_shared<LadderComp>(ladder.get(), scene);
	ladder->AddComponent(ladrComp);
#if _DEBUGRENDERING
	auto debugtexture = std::make_shared<dae::TextureComponent>(ladder.get(), "Burgertime/spritesheet.png", glm::vec4{ 87,38,1,1 });
	ladder->AddComponent(debugtexture);
#endif

	LevelSettings::m_LevelLadderCrossPoints.insert(pos.x);


	return ladder;
}

std::shared_ptr<dae::GameObject> LevelGen::GenerateFloorDark(glm::ivec2 pos)
{
	auto floor = std::make_shared<dae::GameObject>();
	auto texture = std::make_shared<dae::TextureComponent>(floor.get(), "Burgertime/spritesheet.png", glm::vec4{ 202,141,32,3 });
	floor->AddComponent(texture);
	floor->SetSize(32 * LevelSettings::Scale, 3 * LevelSettings::Scale);
	floor->SetPosition(pos);

	auto block = std::make_shared<BlockComp>(floor.get(), (int)Direction::Down);
	floor->AddComponent(block);
	auto fallingBurgerColl = std::make_shared<BoxColliderComp>(floor.get(), "fallingBurger");
	floor->AddComponent(fallingBurgerColl);

	return floor;
}

std::shared_ptr<dae::GameObject> LevelGen::GenerateFloorLight(glm::ivec2 pos)
{
	auto floor = std::make_shared<dae::GameObject>();
	auto texture = std::make_shared<dae::TextureComponent>(floor.get(), "Burgertime/spritesheet.png", glm::vec4{ 202,147,16,3 });
	floor->AddComponent(texture);
	floor->SetSize(16 * LevelSettings::Scale, 3 * LevelSettings::Scale);
	floor->SetPosition(pos);
	return floor;
}

std::shared_ptr<dae::GameObject> LevelGen::GenerateBurgerPiece(glm::ivec2 pos, glm::ivec2 texCoord, dae::Scene& scene)
{
	auto burger = std::make_shared<dae::GameObject>();
	auto burgerComp = std::make_shared<BurgerPiece>(burger.get());
	burger->AddComponent(burgerComp);
	burger->SetPosition(pos);
	burger->SetSize(32 * LevelSettings::Scale, 8 * LevelSettings::Scale);
	burgerComp->GenerateShards(texCoord, scene);
	auto fallingBurgerColl = std::make_shared<BoxColliderComp>(burger.get(), "fallingBurger");
	burger->AddComponent(fallingBurgerColl);
	return burger;
}

std::shared_ptr<dae::GameObject> LevelGen::GenerateBurgerTray(glm::ivec2 pos, dae::Scene& scene, int partsNeeded)
{
	auto tray = std::make_shared<dae::GameObject>();
	tray->SetPosition(pos);
	tray->SetSize(38 * LevelSettings::Scale, 6 * LevelSettings::Scale);
	auto txtr = std::make_shared<dae::TextureComponent>(tray.get(), "Burgertime/spritesheet.png", glm::vec4{ 202,162,38,6 });
	tray->AddComponent(txtr);

	auto collGo = std::make_shared<dae::GameObject>();
	collGo->SetParent(tray.get());
	collGo->SetSize(38 * LevelSettings::Scale, 1);
	collGo->SetPosition({ 0,0 });
	auto trayComp = std::make_shared<BurgerTray>(collGo.get(), partsNeeded);
	collGo->AddComponent(trayComp);
	auto coll = std::make_shared<BoxColliderComp>(collGo.get(), "fallingBurger");
	collGo->AddComponent(coll);

	scene.Add(collGo);

	return tray;
}
