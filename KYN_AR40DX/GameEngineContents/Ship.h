#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineBase/GameEngineSound.h>
#include "LevelParent.h"

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : ������ ���Ϸ��忡�� ���丮�Ʒ� ���� �� ��
class Player;
class StageObject;
class Ship : public LevelParent
{
public:
	//����Ʈ ������
	Ship();
	//����Ʈ �Ҹ���
	~Ship();

	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======	
	//����Ʈ ���� ������
	Ship(const Ship& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	Ship(Ship&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	Ship& operator=(const Ship& _Other) = delete;
	Ship& operator=(Ship&& _Other) noexcept = delete;
	//====================================================

	void CameraRange();
	//void NextStage();
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
	bool BgmOn;
	float ShipTime;
};

