#include "PreCompile.h"
#include "CharacterObject.h"
#include "LevelParent.h"

CharacterObject::CharacterObject()
	:Renderer(nullptr)
	, Speed(100.0f)
	, AccSpeed(15.0f)
	, DownSpeed(0.0f)
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

	DownSpeed += AccSpeed * GameEngineTime::GetDeltaTime();//가속도

	if (DownSpeed > 300.0f)
	{
		DownSpeed = 300.0f;
	}

	if (false == Color.CompareInt4D(float4(0.0f, 1.0f, 0.0f, 1.0f)) /*&&
		false == Color.CompareInt4D(float4(0.0f, 0.0f, 1.0f, 1.0f))*/)
	{	//초록이 아니라면 추락
		//GetTransform().SetWorldMove(GetTransform().GetDownVector() * AccSpeed * GameEngineTime::GetDeltaTime());
		GetTransform().SetWorldMove(GetTransform().GetDownVector() * DownSpeed);
	}
	else
	{	//그외엔 초록에 닿았다는것
		GetTransform().SetWorldMove(GetTransform().GetDownVector() * 0);
		//다운스피드 값 초기화
		DownSpeed = 0;
	}

}

bool CharacterObject::GroundCheck()
{
	GameEngineTexture* MapTexture = GetLevel<LevelParent>()->GetMap_Col()->GetCurTexture();

	if (nullptr == MapTexture)
	{
		MsgBoxAssert("충돌용 맵이 존재하지 않습니다");
	}

	//컬러충돌용 체크 점
	FootColorCheck = MapTexture->GetPixel(GetTransform().GetWorldPosition().ix(), -GetTransform().GetWorldPosition().iy());

	if (false == FootColorCheck.CompareInt4D(float4(1.0f, 1.0f, 1.0f, 0.0f)))
	{	//BGRA
		//투명 배경색이 아니라면
		//빨간색 혹은 초록색 땅에 부딪혔다
		int a = 0;
	}

	// GetLevel()
	return true;
}