#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update()
{
	for(auto& scene : m_Scenes)
	{
		if(scene->m_IsActive)
			scene->Update();
	}
}

void dae::SceneManager::Render()
{
	for (const auto& scene : m_Scenes)
	{
		if (scene->m_IsActive)
			scene->Render();
	}
}

dae::Scene& dae::SceneManager::GetCurrentScene()
{
	return *m_Scenes[0].get();
}

void dae::SceneManager::SetActiveScene(const std::string& name, bool newState)
{
	auto it = std::find_if(m_Scenes.begin(), m_Scenes.end(), [&name](const std::shared_ptr<Scene>& scene) { return scene->GetName() == name; });
	if(it != m_Scenes.end())
	{
		__int64 idx = std::distance(m_Scenes.begin(), it);
		m_Scenes[idx]->m_IsActive = newState;
	}
}

dae::Scene& dae::SceneManager::GetScene(const std::string& name)
{
	auto it = std::find_if(m_Scenes.begin(), m_Scenes.end(), [&name](const std::shared_ptr<Scene>& scene) { return scene->GetName() == name; });
	if (it != m_Scenes.end())
	{
		__int64 idx = std::distance(m_Scenes.begin(), it);
		return *m_Scenes[idx];
	}
	return GetInstance().CreateScene(name);
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	return *scene;
}
