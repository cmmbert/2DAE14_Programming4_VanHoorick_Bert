#include "BurgerPiece.h"

#include "BoxColliderComp.h"
#include "BurgerShardComp.h"
#include "GameObject.h"

BurgerPiece::BurgerPiece(int shardSize): m_ShardSize(shardSize)
{
}


void BurgerPiece::GenerateShards(glm::ivec2 texSrc, dae::Scene& sceneRef)
{
	for (int i = 0; i < 4; ++i)
	{
		glm::ivec4 srcRec = glm::ivec4{ texSrc.x + i * 8,texSrc.y , 8,8};
		auto shardGo = std::make_shared<dae::GameObject>();
		glm::vec3 offset = glm::vec3{ i * m_ShardSize, 0 , 0 };
		shardGo->SetPosition(m_pGameObject->GetPosition() + offset);
		shardGo->SetSize(m_ShardSize, m_ShardSize);
		//auto coll = std::make_shared<BoxColliderComp>("burgerPiece");
		//shardGo->AddComponent(coll);
		auto pTexture = std::make_shared<dae::TextureComponent>("Burgertime/spritesheet.png", srcRec);
		shardGo->AddComponent(pTexture);
		auto shard = std::make_shared<BurgerShardComp>(i);
		shardGo->AddComponent(shard);

		auto collision = std::make_shared<BoxColliderComp>("burgerPiece");
		shardGo->AddComponent(collision);
		m_pShards.push_back(shardGo);
		sceneRef.Add(shardGo);
	}
}

void BurgerPiece::Start()
{

}

void BurgerPiece::Update()
{
}

void BurgerPiece::Render() const
{
}
