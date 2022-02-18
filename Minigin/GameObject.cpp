#include "MiniginPCH.h"
#include "GameObject.h"

#include "BaseComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
using namespace dae;

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update()
{
	for (auto comp : m_pComponents)
	{
		comp.get()->Update();
	}
}

void dae::GameObject::Render() const
{
	for (auto comp : m_pComponents)
	{
		comp.get()->Render();
	}
}

void GameObject::AddComponent(const std::shared_ptr<BaseComponent>& comp)
{
	m_pComponents.push_back(comp);
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}
