#pragma once
struct SDL_Window;
namespace dae
{
	class Scene;

	class Minigin
	{
	public:
		void Initialize();
		void Cleanup();
		void FixedUpdate(float fixedTimeStep);
		void Run();
	private:
		static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* m_Window{};
		float m_FixedTimeStep = 0.02f;

		void DemoScene1(Scene& scene) const;
		void DemoScene2(Scene& scene) const;
		void Level1(Scene& scene) const;
	};
}