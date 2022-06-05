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


