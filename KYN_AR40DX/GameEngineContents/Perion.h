#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineBase/GameEngineSound.h>
#include "LevelParent.h"

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : �丮�� �����ϴ� ��
class Perion : public LevelParent
{
public:
	//����Ʈ ������
	Perion();
	//����Ʈ �Ҹ���
	~Perion();

	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	Perion(const Perion& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	Perion(Perion&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	Perion& operator=(const Perion& _Other) = delete;
	Perion& operator=(Perion&& _Other) noexcept = delete;

	void CameraRange();

	void CameraChase(float _Delta);

	void LevelMove();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;
	void LevelStartEvent() override;

private:
	GameEngineCameraActor* Camera;
	Player* NewPlayer;
	GameEngineSoundPlayer BgmPlayer;
	GameEngineCollision* Collision;
	bool BgmOn;
	float ShipTime;
};

