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
		void SetParent(GameObject* parent);
		GameObject* GetParent() { return m_Parent; }
		void AddToChildren(const std::shared_ptr<GameObject>& newChild);
		std::vector<std::shared_ptr<GameObject>> GetChildren() const { return m_Children; }

		glm::vec3 GetWorldPosition();
		void SetPosition(float x, float y);
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

	//TODO How to do this??
	template <typename T>
	T* GameObject::GetComponent() const
	{
		for (auto& component : m_pComponents)
		{
			auto rtrn = dynamic_cast<T*>(component.get());
			if (rtrn != nullptr) 
				return rtrn; //https://stackoverflow.com/questions/351845/finding-the-type-of-an-object-in-c
		}
		return nullptr;
	}
}
