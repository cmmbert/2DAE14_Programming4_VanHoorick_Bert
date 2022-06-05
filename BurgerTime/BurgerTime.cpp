#include "MiniginPCH.h"

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif


#include "CoopButton.h"
#include "SelectModeCommand.h"
#include "GameObject.h"
#include "InputManager.h"
#include "LevelGen.h"
#include "LevelSettings.h"
#include "Minigin.h"
#include "Renderer.h"
#include "Scene.h"
#include "SoloButton.h"
#include "SwapModeCommand.h"
#include "LevelSettings.h"
#include "VersusButton.h"


int main(int, char* []) {
	auto& input = dae::InputManager::GetInstance();

	dae::Minigin engine;
	engine.Initialize();
	auto& menuScene = dae::SceneManager::GetInstance().CreateScene("Menu");
	ServiceLocator::GetAudioService()->PlaySound(1, 0.5f);

	std::vector<ModeButton*> buttons{};

	
	auto buttonSolo = std::make_shared<dae::GameObject>();
	auto size = glm::ivec2{ 51 * LevelSettings::Scale, 20 * LevelSettings::Scale };
	buttonSolo->SetSize(size.x, size.y);
	buttonSolo->SetPosition({ dae::Renderer::GetInstance().ScreenSize().x / 2 - size.x/2 , (dae::Renderer::GetInstance().ScreenSize().y / 2) + 30*LevelSettings::Scale });
	auto texture = std::make_shared<dae::TextureComponent>(buttonSolo.get(), "Burgertime/menu.png", glm::vec4{ 0,0,51,25 });
	buttonSolo->AddComponent(texture);
	auto solo = std::make_shared<SoloButton>(buttonSolo.get(), texture.get());
	buttonSolo->AddComponent(solo);
	menuScene.Add(buttonSolo);
	buttons.push_back(solo.get());

	auto buttonCoop = std::make_shared<dae::GameObject>();
	size = glm::ivec2{ 74 * LevelSettings::Scale, 25 * LevelSettings::Scale };
	buttonCoop->SetSize(size.x, size.y);
	buttonCoop->SetPosition({ dae::Renderer::GetInstance().ScreenSize().x / 2 - size.x/2, dae::Renderer::GetInstance().ScreenSize().y / 2 });
	texture = std::make_shared<dae::TextureComponent>(buttonCoop.get(), "Burgertime/menu.png", glm::vec4{ 62,0,74,25 });
	buttonCoop->AddComponent(texture);
	auto coop = std::make_shared<CoopButton>(buttonCoop.get(), texture.get());
	buttonCoop->AddComponent(coop);
	menuScene.Add(buttonCoop);
	buttons.push_back(coop.get());

	auto buttonVersus = std::make_shared<dae::GameObject>();
	size = glm::ivec2{ 74 * LevelSettings::Scale, 25 * LevelSettings::Scale };
	buttonVersus->SetSize(size.x, size.y);
	buttonVersus->SetPosition({ dae::Renderer::GetInstance().ScreenSize().x / 2 - size.x/2, dae::Renderer::GetInstance().ScreenSize().y / 2 - 30 * LevelSettings::Scale });
	texture = std::make_shared<dae::TextureComponent>(buttonVersus.get(), "Burgertime/menu.png", glm::vec4{ 141,0,84,25 });
	buttonVersus->AddComponent(texture);
	auto versus = std::make_shared<VersusButton>(buttonVersus.get(), texture.get());
	buttonVersus->AddComponent(versus);
	menuScene.Add(buttonVersus);
	buttons.push_back(versus.get());



	auto menu = std::make_shared<dae::GameObject>();
	auto select = std::make_shared<SelectModeComp>(menu.get(), buttons);
	menu->AddComponent(select);
	input.AddOrChangeCommand(eControllerButton::ButtonA, std::make_shared<SelectModeCommand>(select.get()));
	input.AddOrChangeCommand(eControllerButton::DpadDown, std::make_shared<SwapModeCommand>(select.get(), 1));
	input.AddOrChangeCommand(eControllerButton::DpadUp, std::make_shared<SwapModeCommand>(select.get(), -1));
	input.AddOrChangeCommand(eKeyboardButton::Enter , std::make_shared<SelectModeCommand>(select.get()));
	input.AddOrChangeCommand(eKeyboardButton::S , std::make_shared<SwapModeCommand>(select.get(), 1));
	input.AddOrChangeCommand(eKeyboardButton::W  ,std::make_shared<SwapModeCommand>(select.get(), -1));
	input.AddOrChangeCommand(eKeyboardButton::Z  ,std::make_shared<SwapModeCommand>(select.get(), -1));
	input.AddOrChangeCommand(eKeyboardButton::Down, std::make_shared<SwapModeCommand>(select.get(), 1));
	input.AddOrChangeCommand(eKeyboardButton::Up, std::make_shared<SwapModeCommand>(select.get(), -1));

	auto& scene = dae::SceneManager::GetInstance().CreateScene("Level" + std::to_string(LevelSettings::CurrentLevel));
	scene.m_IsActive = false;
	auto left = LevelGen::GenerateBlockingField(Direction::Left);
	left->SetPosition(0, 0);
	left->SetSize(1, 1000);
	scene.Add(left);
	auto right = LevelGen::GenerateBlockingField(Direction::Right);
	right->SetPosition(dae::Renderer::GetInstance().ScreenSize().x, 0);
	right->SetSize(1, 1000);
	scene.Add(right);
	


	dae::SceneManager::GetInstance().SetActiveScene("Level" + std::to_string(LevelSettings::CurrentLevel));

	engine.Run();
	return 0;
}
