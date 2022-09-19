#include "PreCompile.h"
#include "BossHPUI.h"
#include "BossMano.h"

BossHPUI::BossHPUI()
	:HPbar(nullptr)
	,HPback(nullptr)
	,CurHP(-1)
	,HPMax(-1)
{

}

BossHPUI::~BossHPUI()
{

}

void BossHPUI::Start()
{
	HPback = CreateComponent<GameEngineUIRenderer>();
	HPback->SetTexture("boss_hp_bg.png");
	HPback->GetTransform().SetWorldScale({ 801,37,1 });
	HPback->GetTransform().SetLocalPosition({ 0, 0,-100 });
	HPback->SetPivot(PIVOTMODE::LEFT);

	HPbar = CreateComponent<GameEngineUIRenderer>();
	HPbar->SetTexture("boss_hp_bar.png");
	HPbar->GetTransform().SetWorldScale({ 758,12,1 });
	HPbar->GetTransform().SetLocalPosition({ 39, -1,-100 });
	HPbar->SetPivot(PIVOTMODE::LEFT);
}

void BossHPUI::Update(float _DeltaTime)
{

}

void BossHPUI::SetBoss(Monster* _Boss)
{
	CurHP = _Boss->GetCurHP();
	HPMax = _Boss->GetMaxHP();

	//float HPbarSize = (HPbar->GetTransform().GetWorldScale().x * CurHP) / HPMax; //이걸로 하면 왜인지 HPbarSize가 꼬임
	float HPbarSize = (758 * CurHP) / HPMax;
	HPbar->GetTransform().SetWorldScale({ HPbarSize, 12, 0 });
}