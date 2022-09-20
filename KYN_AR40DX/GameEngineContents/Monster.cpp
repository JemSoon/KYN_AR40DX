#include "Monster.h"

Monster::Monster()
	:MonsterAtt(1)
	,MonsterCurHP(1)
	,MonsterHPMax(1)
	,HPRenderer(nullptr)
	,HPbarRenderer(nullptr)
	,IsBuff(false)
	,DamageRender(nullptr)
{

}

Monster::~Monster()
{

}

void Monster::Start()
{
	CharacterObject::Start();

	HPRenderer = CreateComponent<GameEngineTextureRenderer>();
	HPRenderer->GetTransform().SetLocalScale({ 50, 10, 1 });
	HPRenderer->SetTexture("MonsterHP.png");
	HPRenderer->GetTransform().SetWorldPosition({ -25, 50,0 });
	HPRenderer->SetPivot(PIVOTMODE::LEFT);

	HPbarRenderer = CreateComponent<GameEngineTextureRenderer>();
	HPbarRenderer->GetTransform().SetLocalScale({ 50, 10, 1 });
	HPbarRenderer->SetTexture("MonsterHPbar.png");
	HPbarRenderer->GetTransform().SetWorldPosition({ -25, 50,0 });
	HPbarRenderer->SetPivot(PIVOTMODE::LEFT);
}

void Monster::Update(float _DeltaTime)
{
	if (PlayerInfo == nullptr)
	{
		PlayerInfo = Player::GetMainPlayer();
	}

	MonsterHPSetting();
}

void Monster::MonsterHPSetting()
{
	int HPbarSize = (HPRenderer->GetTransform().GetLocalScale().x * MonsterCurHP) / MonsterHPMax;
	HPbarRenderer->GetTransform().SetWorldScale({ (float)HPbarSize, 10, 0 });
}

