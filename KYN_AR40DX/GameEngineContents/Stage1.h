#pragma once
#include <GameEngineCore/CoreMinimal.h>

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : 
class Stage1 : public GameEngineActor
{
public:
	//����Ʈ ������
	Stage1();
	//����Ʈ �Ҹ���
	~Stage1();

	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	Stage1(const Stage1& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	Stage1(Stage1&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	Stage1& operator=(const Stage1& _Other) = delete;
	Stage1& operator=(Stage1&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) {}
	void End() {}

	GameEngineTextureRenderer* BG;
	GameEngineTextureRenderer* Map;

private:

};

