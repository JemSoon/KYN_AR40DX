#include "PreCompile.h"
#include "CharacterObject.h"
#include "LevelParent.h"

CharacterObject::CharacterObject()
	:Renderer(nullptr)
	, Speed(100.0f)
	, MovePower(0.0f)
{

}

CharacterObject::~CharacterObject()
{

}

void CharacterObject::Start()
{
	GetTransform().SetLocalScale({ 1, 1, 1 });

	// 캐릭터 크기마다 다를거 아니에요?
	// 예나양이 체크하는 부분을 
	ColorDir[static_cast<unsigned int>(COLORCHECKDIR::LEFT)] = float4::LEFT * 20.0f + float4::UP * 20.0f;
	ColorDir[static_cast<unsigned int>(COLORCHECKDIR::RIGHT)] = float4::RIGHT * 20.0f + float4::UP * 20.0f;
	ColorDir[static_cast<unsigned int>(COLORCHECKDIR::UP)] = float4::UP * 100.0f;
	ColorDir[static_cast<unsigned int>(COLORCHECKDIR::DOWN)] = float4::ZERO;
	ColorDir[static_cast<unsigned int>(COLORCHECKDIR::DOWNL)] = float4::LEFT * 20.0f;
	ColorDir[static_cast<unsigned int>(COLORCHECKDIR::DOWNR)] = float4::RIGHT * 20.0f;

}

void CharacterObject::Gravity(float _DeltaTime)
{
	GameEngineTexture* MapTexture = GetLevel<LevelParent>()->GetMap_Col()->GetCurTexture();

	MovePower += float4::DOWN * _DeltaTime * 7.0f;//가속도

	ColorCheckUpdateNext(MovePower);

	if (true == IsNextColor(COLORCHECKDIR::DOWN, float4::WHITE))
	{	//발바닥이 흰색이라면 추락
		GetTransform().SetWorldMove(MovePower);
	}
	else
	{	
		MovePower = float4::ZERO;
	}

}

void CharacterObject::ColorCheckUpdateNext(float4 _Move)
{
	GameEngineTexture* MapTexture = GetLevel<LevelParent>()->GetMap_Col()->GetCurTexture();

	if (nullptr == MapTexture)
	{
		MsgBoxAssert("충돌용 맵이 존재하지 않습니다");
	}

	for (size_t i = 0; i < static_cast<unsigned int>(COLORCHECKDIR::MAX); i++)
	{
		float4 CheckDir = GetTransform().GetWorldPosition() + ColorDir[i] + _Move;

		NextColorCheck[i] = MapTexture->GetPixel(CheckDir.ix(), -CheckDir.iy());
	}

	return;

}

bool CharacterObject::IsNextColor(COLORCHECKDIR _Dir, float4 _Color)
{
	if (_Dir == COLORCHECKDIR::MAX)
	{
		MsgBoxAssert("방향 범위를 넘어갔습니다.");
	}

	unsigned int Index = static_cast<unsigned int>(_Dir);

	return NextColorCheck[Index].CompareInt3D(_Color);
}

void CharacterObject::ColorCheckUpdate()
{
	GameEngineTexture* MapTexture = GetLevel<LevelParent>()->GetMap_Col()->GetCurTexture();

	if (nullptr == MapTexture)
	{
		MsgBoxAssert("충돌용 맵이 존재하지 않습니다");
	}

	for (size_t i = 0; i < static_cast<unsigned int>(COLORCHECKDIR::MAX); i++)
	{
		float4 CheckDir = GetTransform().GetWorldPosition() + ColorDir[i];

		ColorCheck[i] = MapTexture->GetPixel(CheckDir.ix(), -CheckDir.iy());
	}

	return;
}