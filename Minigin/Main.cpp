#include "MiniginPCH.h"

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include <steam_api.h>

#include "Achievements.h"

int main(int, char*[]) {
	if (!SteamAPI_Init())
	{
		Achievements::GetInstance().IsSteamInitiated = false;
		std::cerr << "Fatal Error - SteamAPI_Init() failed." << std::endl;
	}
	else
	{
		Achievements::GetInstance().IsSteamInitiated = true;
		std::cout << "Successfully initialized steam." << std::endl;
	}

	dae::Minigin engine;
	engine.Run();

	SteamAPI_Shutdown();
    return 0;
}
