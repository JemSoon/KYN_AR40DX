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

	// ĳ���� ũ�⸶�� �ٸ��� �ƴϿ���?
	// �������� üũ�ϴ� �κ��� 
	ColorDir[static_cast<unsigned int>(COLORCHECKDIR::LEFT)] = float4::LEFT * 15.0f + float4::UP * 5.0f;
	ColorDir[static_cast<unsigned int>(COLORCHECKDIR::LEFTTOP)] = float4::LEFT * 15.0f + float4::UP * 15.0f;
	ColorDir[static_cast<unsigned int>(COLORCHECKDIR::RIGHT)] = float4::RIGHT * 15.0f + float4::UP * 5.0f;
	ColorDir[static_cast<unsigned int>(COLORCHECKDIR::RIGHTTOP)] = float4::RIGHT * 15.0f + float4::UP * 15.0f;
	ColorDir[static_cast<unsigned int>(COLORCHECKDIR::UP)] = float4::UP * 35.0f;
	ColorDir[static_cast<unsigned int>(COLORCHECKDIR::DOWN)] = float4::ZERO;
	ColorDir[static_cast<unsigned int>(COLORCHECKDIR::DOWNL)] = float4::LEFT * 20.0f;
	ColorDir[static_cast<unsigned int>(COLORCHECKDIR::DOWNR)] = float4::RIGHT * 20.0f;
	ColorDir[static_cast<unsigned int>(COLORCHECKDIR::CENTER)] = float4::UP * 16.0f;

}

void CharacterObject::Gravity(float _DeltaTime)
{
	GameEngineTexture* MapTexture = GetLevel<LevelParent>()->GetMap_Col()->GetCurTexture();

	MovePower += float4::DOWN * _DeltaTime * 10.0f;//���ӵ�

	ColorCheckUpdateNext(MovePower);

	if (true == IsNextColor(COLORCHECKDIR::DOWN, float4::WHITE))
	{	//�߹ٴ��� ����̶�� �߶�
		GetTransform().SetWorldMove(MovePower);
	}
	
	else if (MovePower.y > 0|| true == IsNextColor(COLORCHECKDIR::DOWN, float4::BLUE))
	{
		//y���� ������ �״�� ���� �����Ѵ�
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
		MsgBoxAssert("�浹�� ���� �������� �ʽ��ϴ�");
	}

	for (size_t i = 0; i < static_cast<unsigned int>(COLORCHECKDIR::MAX); i++)
	{
		float4 CheckDir = GetTransform().GetWorldPosition() + ColorDir[i] + _Move;

		NextColorCheck[i] = MapTexture->GetPixelToFloat4(CheckDir.ix(), -CheckDir.iy());
		iNextColorCheck[i] = MapTexture->GetPixelToPixelColor(CheckDir.ix(), -CheckDir.iy());
		//�̰� ������ ���� IsNexColor�� ���� �ι�°�� PixelColor�� �����Ȱ� �ʿ�
	}

	return;

}

bool CharacterObject::IsNextColor(COLORCHECKDIR _Dir, float4 _Color)
{
	if (_Dir == COLORCHECKDIR::MAX)
	{
		MsgBoxAssert("���� ������ �Ѿ���ϴ�.");
	}

	unsigned int Index = static_cast<unsigned int>(_Dir);

	return NextColorCheck[Index].CompareInt3D(_Color);
}

void CharacterObject::ColorCheckUpdate()
{
	GameEngineTexture* MapTexture = GetLevel<LevelParent>()->GetMap_Col()->GetCurTexture();

	if (nullptr == MapTexture)
	{
		MsgBoxAssert("�浹�� ���� �������� �ʽ��ϴ�");
	}

	for (size_t i = 0; i < static_cast<unsigned int>(COLORCHECKDIR::MAX); i++)
	{
		float4 CheckDir = GetTransform().GetWorldPosition() + ColorDir[i];

		//ColorCheck[i] = MapTexture->GetPixelToFloat4(CheckDir.ix(), -CheckDir.iy());

		iColorCheck[i] = MapTexture->GetPixelToPixelColor(CheckDir.ix(), -CheckDir.iy());
	}

	return;
}