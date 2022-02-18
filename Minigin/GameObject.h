#pragma once
#include "Transform.h"
#include "SceneObject.h"

namespace dae
{
	class BaseComponent;
	
	class GameObject final : public SceneObject
	{
	public:
		void Update(float elapsedSec) override;
		void Render() const override;

		void AddComponent(const std::shared_ptr<BaseComponent>& comp);
		

		void SetPosition(float x, float y);

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		Transform m_Transform;
		std::vector<std::shared_ptr<BaseComponent>> m_pComponents;
	};
}
