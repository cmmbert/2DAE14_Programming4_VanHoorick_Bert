#pragma once
#pragma warning(disable:4100)
namespace dae
{
	class GameObject;

	class BaseComponent
	{
	public:
		virtual void Start(){};
		virtual void Update(){};
		virtual void Render() const {};
		virtual void OnCollision(GameObject* other){};


		BaseComponent() = delete;
		BaseComponent(GameObject* gameObject);
		virtual ~BaseComponent() = default;
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;

		void SetGameObject(GameObject* go) { m_pGameObject = go; }
		GameObject* GetGameObject() const { return m_pGameObject; }
	protected:
		GameObject* m_pGameObject{};
	};
}

