#pragma once
#include "LevelParent.h"

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : 
class EndingLogo;
class Ending : public LevelParent
{
public:
	//����Ʈ ������
	Ending();
	//����Ʈ �Ҹ���
	~Ending();

	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	Ending(const Ending& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	Ending(Ending&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	Ending& operator=(const Ending& _Other) = delete;
	Ending& operator=(Ending&& _Other) noexcept = delete;
protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	void LevelStartEvent() override;
	EndingLogo* EndingActor;

};

