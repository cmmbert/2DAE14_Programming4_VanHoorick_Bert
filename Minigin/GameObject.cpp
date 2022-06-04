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

bool GameObject::RemoveComponent(std::shared_ptr<dae::BaseComponent> comp)
{
	m_pComponents.erase(std::remove(m_pComponents.begin(), m_pComponents.end(), comp), m_pComponents.end());
	return true;
}

void GameObject::SetParent(GameObject* parent)
{
	m_Parent = parent;
}

void GameObject::AddToChildren(const std::shared_ptr<GameObject>& newChild)
{
	newChild->SetParent(this);
	m_Children.push_back(newChild);
}

glm::vec3 GameObject::GetWorldPosition()
{
	if(m_Parent != nullptr)
	{
		return m_Parent->GetWorldPosition() + m_Transform.GetPosition();
	}
	return m_Transform.GetPosition();
}

void dae::GameObject::SetPosition(float x, float y)
{
	SetPosition({ x,y,m_Transform.GetPosition().z });
}

void GameObject::SetPosition(int x, int y)
{
	SetPosition(static_cast<float>(x), static_cast<float>(y));

}

void GameObject::SetPosition(glm::vec2 vec)
{
	SetPosition(vec.x, vec.y);
	
}

void GameObject::SetPosition(glm::vec3 vec)
{
	m_Transform.SetPosition(vec.x, vec.y, vec.z);
}

void GameObject::SetSize(int w, int h)
{
	m_Transform.SetSize(w, h);
}

GameObject::GameObject(): m_Parent(nullptr)
{
	auto sSize = Renderer::GetInstance().ScreenSize();
	m_Transform.SetPosition(0, (float)(-sSize.y), 0);
	for (auto& comp : m_pComponents)
	{
		comp->Start();
	}
}
