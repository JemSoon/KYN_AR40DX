#pragma once
#include <GameEngineCore/CoreMinimal.h>

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : 
class GameEngineTextureRenderer;
class DamageNumber : public GameEngineActor
{
public:
	//����Ʈ ������
	DamageNumber();
	//����Ʈ �Ҹ���
	~DamageNumber();

	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	DamageNumber(const DamageNumber& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	DamageNumber(DamageNumber&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	DamageNumber& operator=(const DamageNumber& _Other) = delete;
	DamageNumber& operator=(DamageNumber&& _Other) noexcept = delete;

	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

	void DamageRender();
	GameEngineTextureRenderer* GetRenderer()
	{
		return Renderer;
	}

	void SetParentMonster(Monster* _Parent)
	{
		Mob = _Parent;
	}

protected:

private:
	GameEngineTextureRenderer* Renderer;
	Monster* Mob;
	int nDamageFont;
};

