#include "MiniginPCH.h"
#include "GameObject.h"

#include "BaseComponent.h"
#include "Renderer.h"
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
	newChild->SetParent(std::shared_ptr<GameObject>(this));
	m_Children.push_back(newChild);
}

void dae::GameObject::SetPosition(float x, float y)
{
	SetPosition({ x,y,m_Transform.GetPosition().z });
}

void GameObject::SetPosition(glm::vec2 vec)
{
	SetPosition(vec.x, vec.y);
}

void GameObject::SetPosition(glm::vec3 vec)
{
	auto sSize = Renderer::GetInstance().ScreenSize();
	m_Transform.SetPosition(vec.x, vec.y, vec.z);
}

void GameObject::SetSize(int w, int h)
{
	m_Transform.SetSize(w, h);
}

GameObject::GameObject()
{
	auto sSize = Renderer::GetInstance().ScreenSize();
	m_Transform.SetPosition(0, (float)(-sSize.y), 0);
	for (auto comp: m_pComponents)
	{
		comp->Start();
	}
}
