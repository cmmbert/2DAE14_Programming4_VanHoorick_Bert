#include "BurgerPiece.h"

#include "BlockComp.h"
#include "BoxColliderComp.h"
#include "BurgerBlock.h"
#include "BurgerShardComp.h"
#include "BurgerTray.h"
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
		shardGo->SetPosition(offset);
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
	bool allPieces{true};
	for (auto shard : m_pShards)
	{
		if (!shard->m_SteppedOn)
			allPieces = false;
		else
			shard->IncrementNudge();
	}
	if (!allPieces) return;
	//If we get this far it means all shards are stepped on
	FallDown();
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
	if (m_IsFalling) return;
	auto pos = m_pGameObject->GetPosition();
	m_pGameObject->SetPosition(pos.x, pos.y - 20);
	m_LastHeight = m_pGameObject->GetPosition().y;
	std::cout << m_LastHeight << "\n";
	m_IsFalling = true;
	for (auto shard : m_pShards)
	{
		shard->Reset();
	}
}

void BurgerPiece::OnCollision(dae::GameObject* other)
{
	if(other->GetComponent<BurgerTray>())
	{
		m_IsFalling = false;
		return;
	}
	if(other->GetComponent<BurgerBlock>() && (m_LastHeight - m_pGameObject->GetPosition().y) > m_MinFallDistance)
	{
		if(m_IsFalling)
		{
			auto pos = m_pGameObject->GetPosition();
			auto otherPos = other->GetPosition();
			auto deviation = 1;
			auto distance = sqrt(pow(otherPos.x - pos.x, 2) + pow(otherPos.y - pos.y, 2));
			if(distance < deviation)
			{
				m_IsFalling = false;
				m_pGameObject->SetPosition(otherPos);
			}

		}
	}
	if(other->GetComponent<BurgerPiece>())
	{
		FallDown();
	}
}
