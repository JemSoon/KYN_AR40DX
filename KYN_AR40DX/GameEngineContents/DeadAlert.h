#pragma once
#include <GameEngineCore/CoreMinimal.h>
//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : �׾����� �ߴ� â
class GameEngineUIRenderer;
class DeadAlert : public GameEngineActor
{
public:
	//����Ʈ ������
	DeadAlert();
	//����Ʈ �Ҹ���
	~DeadAlert();

	
	
	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	DeadAlert(const DeadAlert& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	DeadAlert(DeadAlert&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	DeadAlert& operator=(const DeadAlert& _Other) = delete;
	DeadAlert& operator=(DeadAlert&& _Other) noexcept = delete;

	bool MouseHit(GameEngineCollision* _This, GameEngineCollision* _Other);
	bool IsRespawn;
protected:

private:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

	GameEngineUIRenderer* Dialogue;
	GameEngineCollision* Collision;

};

