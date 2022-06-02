#include "MiniginPCH.h"
#include "Minigin.h"

#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Scene.h"
#include "SDLMixerAudioService.h"
#include "ServiceLocator.h"
#include "GlobalTime.h"
#include "CollisionManager.h"

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
	
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		624,
		624,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);



	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");


	auto SdlAudio = std::make_shared<SDLMixerAudioService>();
	ServiceLocator::RegisterAudioService(SdlAudio);
}

/**
 * Code constructing the scene world starts here
 */
dae::Scene& dae::Minigin::LoadGame() const
{
	auto& input = InputManager::GetInstance();

	auto& scene = SceneManager::GetInstance().CreateScene("Demo");


	return scene;
	//auto go = std::make_shared<GameObject>();
	//go->SetPosition(glm::vec2(50, -50));
	//auto tc = std::make_shared<TextureComponent>("Burgertime/spritesheet.png", 160, 160, glm::ivec4(16,16, 16,16));
	//go->AddComponent(tc);
	////scene.Add(go);
	//input.AddOrChangeCommand(eControllerButton::DpadUp, make_shared<ClimbCommand>(go));

	//go = std::make_shared<GameObject>();
	//go->SetPosition(glm::ivec2(216, -180));
	//tc = std::make_shared<TextureComponent>("logo.png");
	////go->AddComponent(tc);
	//scene.Add(go);

	//auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	//go = std::make_shared<GameObject>();
	//auto textc = std::make_shared<TextComponent>("Programming 4 Assignment", font);
	//textc->SetPosition(80, 20);
	////go->AddComponent(textc);
	//scene.Add(go);

	//go = std::make_shared<GameObject>();
	//font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);
	//auto fpsComp = std::make_shared<FpsCounterComp>("FPS: ", font);
	//fpsComp->SetPosition(10, 10);
	//go->AddComponent(fpsComp);

	//go = std::make_shared<GameObject>();
	//auto sound = std::make_shared<SoundComponent>(1);
	//go->AddComponent(sound);
	//auto sound2 = std::make_shared<SoundComponent>(2);
	//go->AddComponent(sound2);
	//auto sound3 = std::make_shared<SoundComponent>(3);
	//go->AddComponent(sound3);
	//scene.Add(go);
	////sound3->Play();
	//sound->Play(0.1f);
	////sound2->Play();
	////DemoScene1(scene);

	//auto anim = std::make_shared<AnimationComponent>();
	//go->AddComponent(anim);

	//Level1(scene);
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
			

			while (lag >= m_FixedTimeStep)
			{
				FixedUpdate(m_FixedTimeStep);
				lag -= m_FixedTimeStep;
			}
			GlobalTime::GetInstance().Update(deltaTime);

			sceneManager.Update();
			CollisionManager::GetInstance().Update();
			renderer.Render();
			auto sleepTime = std::chrono::duration_cast<std::chrono::duration<float>>(currentTime + std::chrono::milliseconds(MsPerFrame) - std::chrono::high_resolution_clock::now());
			this_thread::sleep_for(sleepTime);
		}
	}

	Cleanup();
}

void dae::Minigin::DemoScene1(Scene& scene) const
{
	
}

void dae::Minigin::DemoScene2(Scene& scene) const
{
	/*auto peppergo = std::make_shared<GameObject>();

	auto peterPepper = std::make_shared<PeterPepperComp>(peppergo.get());
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
	scene.Add(go);*/

}

void dae::Minigin::Level1(Scene& scene) const
{
	auto burgerGo = std::make_shared<GameObject>();
	burgerGo->SetPosition(50, -70);
	/*int burgerSize = 80;

	auto texLeft = std::make_shared<TextureComponent>("Burgertime/spritesheet.png", burgerSize, burgerSize, glm::vec4{ 112,49,8,8 });
	auto texMidL = std::make_shared<TextureComponent>("Burgertime/spritesheet.png", burgerSize, burgerSize, glm::vec4{ 120,49,8,8 }, glm::ivec2{burgerSize, 0});
	auto texMidR = std::make_shared<TextureComponent>("Burgertime/spritesheet.png", burgerSize, burgerSize, glm::vec4{ 128,49,8,8 }, glm::ivec2{ burgerSize*2, 0 });
	auto texRight = std::make_shared<TextureComponent>("Burgertime/spritesheet.png", burgerSize, burgerSize, glm::vec4{ 136,49,8,8 }, glm::ivec2{ burgerSize*3, 0 });
	burgerGo->AddComponent(texLeft);
	burgerGo->AddComponent(texMidL);
	burgerGo->AddComponent(texMidR);
	burgerGo->AddComponent(texRight);*/
	scene.Add(burgerGo);
}
