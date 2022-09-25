#include "PreCompile.h"
#include "CharacterObject.h"
#include "LevelParent.h"

const PixelColor CharacterObject::WHITE = {255, 255, 255, 255};
const PixelColor CharacterObject::BLUE = { 0, 0, 255, 255 };
const PixelColor CharacterObject::RED = { 255, 0, 0, 255 };



CharacterObject::CharacterObject()
	:Renderer(nullptr)
	, Speed(100.0f)
	, MovePower(0.0f)
	, GravitySpeed(1500.0f)
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
	ColorDir[static_cast<unsigned int>(COLORCHECKDIR::LEFT)] = float4::LEFT * 15.0f + float4::UP * 3.0f;
	ColorDir[static_cast<unsigned int>(COLORCHECKDIR::LEFTTOP)] = float4::LEFT * 15.0f + float4::UP * 15.0f;
	ColorDir[static_cast<unsigned int>(COLORCHECKDIR::RIGHT)] = float4::RIGHT * 15.0f + float4::UP * 3.0f;
	ColorDir[static_cast<unsigned int>(COLORCHECKDIR::RIGHTTOP)] = float4::RIGHT * 15.0f + float4::UP * 15.0f;
	ColorDir[static_cast<unsigned int>(COLORCHECKDIR::UP)] = float4::UP * 35.0f;
	ColorDir[static_cast<unsigned int>(COLORCHECKDIR::DOWN)] = float4::ZERO;
	ColorDir[static_cast<unsigned int>(COLORCHECKDIR::DOWNL)] = float4::LEFT * 20.0f;
	ColorDir[static_cast<unsigned int>(COLORCHECKDIR::DOWNR)] = float4::RIGHT * 20.0f;
	ColorDir[static_cast<unsigned int>(COLORCHECKDIR::CENTER)] = float4::UP * 2.0f;

}

void CharacterObject::Gravity(float _DeltaTime)
{
	GameEngineTexture* MapTexture = GetLevel<LevelParent>()->GetMap_Col()->GetCurTexture();

	MovePower += float4::DOWN * _DeltaTime * GravitySpeed;//���ӵ�

	// ColorCheckUpdateNext(MovePower);
}

void CharacterObject::NoGravity()
{
	if (false == IsColor(COLORCHECKDIR::DOWN, CharacterObject::WHITE) &&
		false == IsColor(COLORCHECKDIR::DOWN, CharacterObject::BLUE)&&
		MovePower.y<=0.0f)
	{
		//�߹ٴ��� ���,�Ķ����� �ƴ϶��
		MovePower.y = 0.0f;
		//y��(�߷�)�� 0�̵ȴ�
		while (false == IsColor(COLORCHECKDIR::DOWN, CharacterObject::WHITE) &&
			false == IsColor(COLORCHECKDIR::DOWN, CharacterObject::BLUE))
		{
			//�߹ٴ��� ȭ��Ʈ,��簡 �ƴѵ��� �ٴڿ��� �ø��� ���� ��������
			GetTransform().SetWorldMove(float4::UP);
			//�ø��� �ٽ� �߹ٴ�üũ�� ������Ʈ�� Ȯ���Ѵ�
			ColorCheckUpdate();
		}
		GetTransform().SetWorldMove(float4::DOWN);
		ColorCheckUpdate();
		ColorCheckUpdateNext(MovePower);
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

		NextColorCheck[i] = MapTexture->GetPixelToPixelColor(CheckDir.ix(), -CheckDir.iy());
		//�̰� ������ ���� IsNexColor�� ���� �ι�°�� PixelColor�� �����Ȱ� �ʿ�
	}

	return;

}

bool CharacterObject::IsNextColor(COLORCHECKDIR _Dir, PixelColor _Color)
{
	if (_Dir == COLORCHECKDIR::MAX)
	{
		MsgBoxAssert("���� ������ �Ѿ���ϴ�.");
	}

	unsigned int Index = static_cast<unsigned int>(_Dir);

	return NextColorCheck[Index] == _Color;
}

bool CharacterObject::IsColor(COLORCHECKDIR _Dir, PixelColor _Color)
{
	if (_Dir == COLORCHECKDIR::MAX)
	{
		MsgBoxAssert("���� ������ �Ѿ���ϴ�.");
	}

	unsigned int Index = static_cast<unsigned int>(_Dir);

	return ColorCheck[Index] == _Color;
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

		ColorCheck[i] = MapTexture->GetPixelToPixelColor(CheckDir.ix(), -CheckDir.iy());
	}

	return;
}