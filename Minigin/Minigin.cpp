#include "MiniginPCH.h"
#include "Minigin.h"

#include <steam_api_common.h>
#include <thread>

#include "Achievements.h"
#include "EnemyComp.h"
#include "Font.h"
#include "FpsCounterComp.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "GameObject.h"
#include "ImGuiPlotComponent.h"
#include "LivesLeftComp.h"
#include "PeterPepperComp.h"
#include "PointsComp.h"
#include "Scene.h"
#include "ServiceLocator.h"
#include "SoundComponent.h"
#include "TextureComponent.h"
#include "Time.h"

using namespace std;

void PrintSDLVersion()
{
	SDL_version compiled{};
	SDL_version linked{};

	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);
	printf("We compiled against SDL version %d.%d.%d ...\n",
		compiled.major, compiled.minor, compiled.patch);
	printf("We are linking against SDL version %d.%d.%d.\n",
		linked.major, linked.minor, linked.patch);
}

void dae::Minigin::Initialize()
{
	PrintSDLVersion();
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
	ServiceLocator::RegisterAudioService(nullptr);
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<GameObject>();
	auto tc = std::make_shared<TextureComponent>("Burgertime/spritesheet.png", glm::ivec2(50,50), 16, 16, glm::ivec4(16,16, 16,16));
	go->AddComponent(tc);
	scene.Add(go);

	go = std::make_shared<GameObject>();
	tc = std::make_shared<TextureComponent>("logo.png", glm::ivec2(216, 180));
	go->AddComponent(tc);
	scene.Add(go);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go = std::make_shared<GameObject>();
	auto textc = std::make_shared<TextComponent>("Programming 4 Assignment", font);
	textc->SetPosition(80, 20);
	go->AddComponent(textc);
	scene.Add(go);

	go = std::make_shared<GameObject>();
	font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);
	auto fpsComp = std::make_shared<FpsCounterComp>("FPS: ", font);
	fpsComp->SetPosition(10, 10);
	go->AddComponent(fpsComp);

	auto sound = std::make_shared<SoundComponent>(1);
	go->AddComponent(sound);
	scene.Add(go);
	sound->Play();
	//DemoScene1(scene);
	DemoScene2(scene);
}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::Minigin::FixedUpdate(float fixedTimeStep)
{

}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		bool doContinue = true;
		auto lastTime = chrono::high_resolution_clock::now();
		float lag = 0.0f;
		while (doContinue)
		{
			const auto currentTime = chrono::high_resolution_clock::now();
			float deltaTime = chrono::duration<float>(currentTime - lastTime).count();
			lastTime = currentTime;
			lag += deltaTime;
			doContinue = input.Update();

			SteamAPI_RunCallbacks();

			while (lag >= m_FixedTimeStep)
			{
				FixedUpdate(m_FixedTimeStep);
				lag -= m_FixedTimeStep;
			}
			Time::GetInstance().Update(deltaTime);

			if (dae::InputManager::GetInstance().IsPressed(dae::ControllerButton::ButtonY)) 
				Achievements::GetInstance().SetWinGameAch();

			sceneManager.Update();
			renderer.Render();
			auto sleepTime = std::chrono::duration_cast<std::chrono::duration<float>>(currentTime + std::chrono::milliseconds(MsPerFrame) - std::chrono::high_resolution_clock::now());
			this_thread::sleep_for(sleepTime);
		}
	}

	Cleanup();
}

void dae::Minigin::DemoScene1(Scene& scene) const
{
	auto go = std::make_shared<GameObject>();

	go = std::make_shared<GameObject>();
	std::map<std::string, std::vector<float>> map{};
	map.insert(pair<std::string, std::vector<float>>("int array", { 2025.4f, 407, 339.8f, 260.6f, 233.4f, 170.8f, 107.4f, 59.f, 24.2f, 11.f, 4.6f }));
	auto plotComp = std::make_shared<ImGuiPlotComponent>(map);
	go->AddComponent(plotComp);

	std::map<std::string, std::vector<float>> map2{};
	map2.insert(pair<std::string, std::vector<float>>("gameobject array", { 7269.4f, 5228.8f,2853.6f,1520.6f,774.4f,577.2f,149.4f,81.6f,34.6f,25.2f, 11.8f }));
	plotComp = std::make_shared<ImGuiPlotComponent>(map2);
	go->AddComponent(plotComp);



	std::map<std::string, std::vector<float>> map3{};
	map3.insert(pair<std::string, std::vector<float>>("gameobjectalt array", { 1533.0f, 1971.0f,1616.4f,1030.4f,673.4f,562.0f,313.4f,148.2f,53.0f,26.2f,13.0f }));
	plotComp = std::make_shared<ImGuiPlotComponent>(map3);
	go->AddComponent(plotComp);

	map.insert(map2.begin(), map2.end());
	plotComp = std::make_shared<ImGuiPlotComponent>(map);
	go->AddComponent(plotComp);
	scene.Add(go);
}

void dae::Minigin::DemoScene2(Scene& scene) const
{
	auto peppergo = std::make_shared<GameObject>();

	auto peterPepper = std::make_shared<PeterPepperComp>();
	peppergo->AddComponent(peterPepper);

	scene.Add(peppergo);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);

	auto go = std::make_shared<GameObject>();
	auto livesLeftComp = std::make_shared<LivesLeftComp>("Lives left: ", font);
	go->AddComponent(livesLeftComp);
	livesLeftComp->SetPosition(10, 100);

	peterPepper->AddObserver(livesLeftComp.get());
	scene.Add(go);

	livesLeftComp->OnNotify(*peppergo, eEvent::PepperDied);


	go = std::make_shared<GameObject>();
	auto enemyComp = make_shared<EnemyComp>();
	go->AddComponent(enemyComp);
	scene.Add(go);

	go = make_shared<GameObject>();
	auto textComp = make_shared<TextComponent>("Punten: 0",font);
	go->AddComponent(textComp);
	textComp->SetPosition(10, 120);

	auto pointsComp = make_shared<PointsComp>("Punten: ");
	go->AddComponent(pointsComp);

	enemyComp->AddObserver(pointsComp.get());
	scene.Add(go);

}
