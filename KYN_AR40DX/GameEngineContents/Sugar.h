#pragma once
#include <GameEngineCore/CoreMinimal.h>

//�������� ������ �͵鵵 ���������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : �����Ҷ� Ʃ�丮�� �ϴ� NPC
class Sugar : public GameEngineActor
{
public:
	//����Ʈ ������
	Sugar();
	//����Ʈ �Ҹ���
	~Sugar();

	
	
	
	//======�Ʒ��͵��� ���������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	Sugar(const Sugar& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	Sugar(Sugar&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	Sugar& operator=(const Sugar& _Other) = delete;
	Sugar& operator=(Sugar&& _Other) noexcept = delete;


protected:
	void Start() override;
	void Update(float _DeltaTime) {}
	void End() {}

	GameEngineTextureRenderer* Renderer;


private:

};
