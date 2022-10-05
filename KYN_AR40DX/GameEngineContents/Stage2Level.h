#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "LevelParent.h"

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : ������ ���
class Player;
class StageObject;
class BossMano;
class Snail;
class Stage2Level : public LevelParent
{
public:
	//����Ʈ ������
	Stage2Level();
	//����Ʈ �Ҹ���
	~Stage2Level();

	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	Stage2Level(const Stage2Level& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	Stage2Level(Stage2Level&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	Stage2Level& operator=(const Stage2Level& _Other) = delete;
	Stage2Level& operator=(Stage2Level&& _Other) noexcept = delete;

	void CameraChase(float _Delta);
	void NextStage();
	void CameraRange();
	void LevelMove();
	void MonsterRespawnPosition(Monster* _Mob, float4 _Position);
protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;
	void LevelStartEvent() override;

private:
	GameEngineCameraActor* Camera;
	Player* NewPlayer;

	BossMano* Mano;
	Snail* Snail1;
	Snail* Snail2;
};

