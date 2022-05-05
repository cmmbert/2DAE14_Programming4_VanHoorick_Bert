#include "MiniginPCH.h"
#include "GameObject.h"

#include "BaseComponent.h"
using namespace dae;

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update()
{
	for (auto &comp : m_pComponents)
	{
		comp.get()->Update();
	}
}

void dae::GameObject::Render() const
{
	for (auto &comp : m_pComponents)
	{
		comp.get()->Render();
	}
}

void GameObject::AddComponent(const std::shared_ptr<BaseComponent>& comp)
{
	m_pComponents.push_back(comp);
	comp->SetGameObject(this);
}

void GameObject::SetParent(const std::shared_ptr<GameObject>& parent)
{
	m_Parent = parent;
}

void GameObject::AddToChildren(const std::shared_ptr<GameObject>& newChild)
{
	m_Children.push_back(newChild);
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}

GameObject::GameObject()
{
	for (auto comp : m_pComponents)
	{
		comp->Start();
	}
}
