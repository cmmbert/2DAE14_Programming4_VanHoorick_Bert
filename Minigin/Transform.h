#pragma once
namespace dae
{
	class Transform final
	{
	public:
		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(float x, float y, float z);
		void SetSize(int w, int h);
		const glm::ivec2 GetSize() const { return m_Size; }
	private:
		glm::vec3 m_Position;
		glm::ivec2 m_Size;
	};
}
