#pragma once
namespace dae
{
	class BaseComponent
	{
	public:
		virtual void Update() = 0;
		virtual void Render()  const = 0;

		BaseComponent() = default;
		virtual ~BaseComponent() = default;
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;
	};
}

