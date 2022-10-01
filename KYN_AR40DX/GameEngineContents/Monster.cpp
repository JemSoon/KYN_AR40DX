#include "Monster.h"

Monster::Monster()
	:MonsterAtt(1)
	,MonsterCurHP(1)
	,MonsterHPMax(1)
	,HPRenderer(nullptr)
	,HPbarRenderer(nullptr)
	,IsBuff(false)
	,DamageRender(nullptr)
	,MonsterHit(false)
	,DeathCheck(false)

{

}

Monster::~Monster()
{

}

void Monster::Start()
{
	CharacterObject::Start();

	std::vector<unsigned int> Six = { 0, 1, 2, 3, 4, 5 };

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

	SlashBlastHit = CreateComponent<GameEngineTextureRenderer>();
	SlashBlastHit->GetTransform().SetLocalScale({ 256, 256, 1 });
	SlashBlastHit->SetTexture("slashblasthit.png");
	SlashBlastHit->CreateFrameAnimationCutTexture("SlashBlastHit", FrameAnimation_DESC("slashblasthit.png", Six, 0.1f, false));
	SlashBlastHit->GetTransform().SetWorldPosition({ 0, 0,-1 });
	SlashBlastHit->SetPivot(PIVOTMODE::CENTER);
	SlashBlastHit->ChangeFrameAnimation("SlashBlastHit");
	SlashBlastHit->Off();

	SlashBlastHit->AnimationBindEnd("SlashBlastHit", std::bind(&Monster::SlashBlastHitEnd, this));
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

void Monster::SlashBlastHitEnd()
{
	SlashBlastHit->Off();
}