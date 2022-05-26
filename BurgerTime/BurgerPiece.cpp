#include "BurgerPiece.h"

#include "BoxColliderComp.h"
#include "BurgerShardComp.h"
#include "GameObject.h"
#include "GlobalTime.h"

BurgerPiece::BurgerPiece(dae::GameObject* gameObject, int shardSize): BaseComponent(gameObject), m_ShardSize(shardSize)
{
}


void BurgerPiece::GenerateShards(glm::ivec2 texSrc, dae::Scene& sceneRef)
{
	for (int i = 0; i < 4; ++i)
	{
		glm::ivec4 srcRec = glm::ivec4{ texSrc.x + i * 8,texSrc.y , 8,8};
		auto shardGo = std::make_shared<dae::GameObject>();
		shardGo->SetParent(m_pGameObject);
		glm::vec3 offset = glm::vec3{ i * m_ShardSize, 0 , 0 };
		shardGo->SetPosition(m_pGameObject->GetPosition() + offset);
		shardGo->SetSize(m_ShardSize, m_ShardSize);
		auto pTexture = std::make_shared<dae::TextureComponent>(shardGo.get(), "Burgertime/spritesheet.png", srcRec);
		shardGo->AddComponent(pTexture);
		auto shard = std::make_shared<BurgerShardComp>(shardGo.get(), i, this);
		shardGo->AddComponent(shard);

		auto collision = std::make_shared<BoxColliderComp>(shardGo.get(), "burgerPiece");
		shardGo->AddComponent(collision);
		m_pShards.push_back(shard);
		sceneRef.Add(shardGo);
	}
}

void BurgerPiece::OnSteppedOn(int shardIdx)
{
	m_ShardsSteppedOn[shardIdx] = true;
	for (bool shard : m_ShardsSteppedOn)
	{
		if (!shard) return;
	}
	//If we get this far it means all shards are stepped on

}

void BurgerPiece::Start()
{

}

void BurgerPiece::Update()
{
	if(m_IsFalling)
	{
		auto newPos = m_pGameObject->GetPosition();
		newPos.y -= m_FallingSpeed * GlobalTime::GetInstance().GetElapsed();
		m_pGameObject->SetPosition(newPos);
	}
}

void BurgerPiece::Render() const
{
}

void BurgerPiece::FallDown()
{
	for (auto shard : m_pShards)
	{
		shard->m_SteppedOn = false;
	}
	m_IsFalling = true;
}
