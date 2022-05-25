#include "MiniginPCH.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"
#include "3rdParty/imgui-1.87/imgui_impl_opengl2.h"
#include "3rdParty/imgui-1.87/imgui_impl_sdl.h"
#include "3rdParty/imgui-1.87/imgui.h"

int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void dae::Renderer::Init(SDL_Window * window)
{
	m_Window = window;
	m_Renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_Renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	/*IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL2_Init();*/
}

void dae::Renderer::Render() const
{
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_Renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_Renderer);

	//ImGui_ImplOpenGL2_NewFrame(); //Have to do this before the render of objects to allow components to use ImGui
	//ImGui_ImplSDL2_NewFrame(m_Window);
	//ImGui::NewFrame();

	SceneManager::GetInstance().Render();

	
	//ImGui::ShowDemoWindow();
	/*ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());*/


	SDL_RenderPresent(m_Renderer);
}

void dae::Renderer::Destroy()
{
	//ImGui_ImplOpenGL2_Shutdown();
	//ImGui_ImplSDL2_Shutdown();
	//ImGui::DestroyContext();

	if (m_Renderer != nullptr)
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
	}
}

void dae::Renderer::RenderTexture(
	const Texture2D& texture, const int x, const int y, const int width, const int height,
	glm::ivec4 srcRect
) const
{
	SDL_Rect dst{};
	dst.x = x;
	dst.y = GetInstance().ScreenSize().y - y - height;
	dst.w = width;
	dst.h = height;

	if(dst.w <= 0 || dst.h <= 0)
		SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);

	if(srcRect.w <= 0 || srcRect.z <= 0)
	{
		SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
	}
	else
	{
		SDL_Rect src{};
		src.x = srcRect.x;
		src.y = srcRect.y;
		src.w = srcRect.w;
		src.h = srcRect.z;

		SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), &src, &dst);
	}

}

glm::ivec2 dae::Renderer::ScreenSize()
{
	glm::ivec2 size{};
	SDL_GetWindowSize(m_Window, &size.x, &size.y);
	return size;
}
