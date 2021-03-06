#pragma once
#include "MiniginPCH.h"
#include "Transform.h"
#include "SceneObject.h"

namespace dae
{
	class BaseComponent;
	
	class GameObject final : public SceneObject
	{
	public:
		void Update() override;
		void Render() const override;

		void AddComponent(const std::shared_ptr<BaseComponent>& comp);
		template <typename T> T* GetComponent() const;
		template <typename T> bool RemoveComponent();
		template <typename T> std::vector<std::shared_ptr<BaseComponent>>::const_iterator GetComponentIdx() const;

		bool RemoveComponent(std::shared_ptr<dae::BaseComponent> comp);



		void SetParent(GameObject* parent);
		GameObject* GetParent() { return m_Parent; }
		void AddToChildren(const std::shared_ptr<GameObject>& newChild);
		std::vector<std::shared_ptr<GameObject>> GetChildren() const { return m_Children; }

		glm::vec3 GetWorldPosition();
		void SetPosition(float x, float y);
		void SetPosition(int x, int y);
		void SetPosition(glm::vec2 vec);
		void SetPosition(glm::vec3 vec);
		glm::vec3 GetPosition() const { return m_Transform.GetPosition(); }
		const Transform& GetTransform() const { return m_Transform; }
		void SetSize(int w, int h);

		std::vector<std::shared_ptr<BaseComponent>> GetComponents() { return m_pComponents; }

		GameObject();
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		Transform m_Transform;
		std::vector<std::shared_ptr<BaseComponent>> m_pComponents;
		std::vector<std::shared_ptr<GameObject>> m_Children;
		GameObject* m_Parent;
	};


	template <typename T>
	T* GameObject::GetComponent() const
	{
		for (auto& component : m_pComponents)
		{
			T* rtrn = dynamic_cast<T*>(component.get());
			if (rtrn != nullptr) 
				return rtrn; //https://stackoverflow.com/questions/351845/finding-the-type-of-an-object-in-c
		}
		return nullptr;
	}

	template <typename T>
	std::vector<std::shared_ptr<BaseComponent>>::const_iterator GameObject::GetComponentIdx() const
	{
		return std::find_if(m_pComponents.begin(), m_pComponents.end(),
			[](std::shared_ptr<BaseComponent> component)
			{
				T* rtrn = dynamic_cast<T*>(component.get());
				if ((rtrn != nullptr)) return true;
				return false;
			});
	}

	template <typename T>
	bool GameObject::RemoveComponent()
	{
		std::vector<std::shared_ptr<BaseComponent>>::const_iterator compIdx = GetComponentIdx<T>();
		m_pComponents.erase(compIdx);
		//auto res = std::find_if(m_pComponents.begin(), m_pComponents.end(), 
			//[](std::shared_ptr<BaseComponent> c) {c.get() == compPtr; });
		//std::find(m_pComponents.begin(), m_pComponents.end(), item) != m_pComponents.end()
		//if (comp == nullptr) return false;
		//m_pComponents.erase(std::remove(m_pComponents.begin(), m_pComponents.end(), comp), m_pComponents.end());
		return true;
	}
	
	
}
