#pragma once
#include <GameEngineCore/GameEngineActor.h>

//���� : ���� ü�� ui�� Ŭ����
class GameEngineUIRenderer;
class Monster;
class BossHPUI : public GameEngineActor
{
public:
	//����Ʈ ������
	BossHPUI();
	//����Ʈ �Ҹ���
	~BossHPUI();

	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	BossHPUI(const BossHPUI& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	BossHPUI(BossHPUI&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	BossHPUI& operator=(const BossHPUI& _Other) = delete;
	BossHPUI& operator=(BossHPUI&& _Other) noexcept = delete;
	
	void SetBoss(Monster* _Boss);

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

	GameEngineUIRenderer* HPbar;
	GameEngineUIRenderer* HPback;
private:
	int HPbarMaxSize;
	int HPbackMaxSize;

	int CurHP;
	int HPMax;
};

