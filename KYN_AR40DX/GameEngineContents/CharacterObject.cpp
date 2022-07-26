#include "PreCompile.h"
#include "CharacterObject.h"

CharacterObject::CharacterObject()
	:Renderer(nullptr)
	,Speed(100.0f)
	,AccSpeed(300.0f)
{

}

CharacterObject::~CharacterObject()
{

}

void CharacterObject::Start()
{
	GetTransform().SetLocalScale({ 1, 1, 1 });
}

void CharacterObject::Gravity()
{
	GameEngineTexture* MapTexture = GetLevel<LevelParent>()->GetMap_Col()->GetCurTexture();

	float4 Color = MapTexture->GetPixel(GetTransform().GetWorldPosition().ix(), -GetTransform().GetWorldPosition().iy());

	if (false == Color.CompareInt4D(float4(0.0f, 1.0f, 0.0f, 1.0f)) /*&&
		false == Color.CompareInt4D(float4(0.0f, 0.0f, 1.0f, 1.0f))*/)
	{	//초록이 아니라면 추락
		GetTransform().SetWorldMove(GetTransform().GetDownVector() * AccSpeed * GameEngineTime::GetDeltaTime());
	}
}