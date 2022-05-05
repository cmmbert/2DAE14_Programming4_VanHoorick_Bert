#pragma once
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
		void SetParent(const std::shared_ptr<GameObject>& parent);
		void AddToChildren(const std::shared_ptr<GameObject>& newChild);

		void SetPosition(float x, float y);

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
		std::shared_ptr<GameObject> m_Parent;
	};

	//TODO How to do this??
	template <typename T>
	T* GameObject::GetComponent() const
	{
		for (auto& component : m_pComponents)
		{
			//std::cout << "Comparing " << typeid(component).name << "to type " << typeid(T).name();
			auto rtrn = dynamic_cast<T*>(component.get());
			if (rtrn != nullptr) 
				return rtrn; //https://stackoverflow.com/questions/351845/finding-the-type-of-an-object-in-c
		}
		return nullptr;
	}
}
