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

	DownSpeed += AccSpeed * GameEngineTime::GetDeltaTime();//���ӵ�

	if (DownSpeed > 300.0f)
	{
		DownSpeed = 300.0f;
	}

	if (false == Color.CompareInt4D(float4(0.0f, 1.0f, 0.0f, 1.0f)) /*&&
		false == Color.CompareInt4D(float4(0.0f, 0.0f, 1.0f, 1.0f))*/)
	{	//�ʷ��� �ƴ϶�� �߶�
		//GetTransform().SetWorldMove(GetTransform().GetDownVector() * AccSpeed * GameEngineTime::GetDeltaTime());
		GetTransform().SetWorldMove(GetTransform().GetDownVector() * DownSpeed);
	}
	else
	{	//�׿ܿ� �ʷϿ� ��Ҵٴ°�
		GetTransform().SetWorldMove(GetTransform().GetDownVector() * 0);
		//�ٿ�ǵ� �� �ʱ�ȭ
		DownSpeed = 0;
	}

}

bool CharacterObject::GroundCheck()
{
	GameEngineTexture* MapTexture = GetLevel<LevelParent>()->GetMap_Col()->GetCurTexture();

	if (nullptr == MapTexture)
	{
		MsgBoxAssert("�浹�� ���� �������� �ʽ��ϴ�");
	}

	//�÷��浹�� üũ ��
	FootColorCheck = MapTexture->GetPixel(GetTransform().GetWorldPosition().ix(), -GetTransform().GetWorldPosition().iy());

	if (false == FootColorCheck.CompareInt4D(float4(1.0f, 1.0f, 1.0f, 0.0f)))
	{	//BGRA
		//���� ������ �ƴ϶��
		//������ Ȥ�� �ʷϻ� ���� �ε�����
		int a = 0;
	}

	// GetLevel()
	return true;
}