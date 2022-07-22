#pragma once
#include <GameEngineCore/CoreMinimal.h>

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : 
class Stage2 : public GameEngineActor
{
public:
	//����Ʈ ������
	Stage2();
	//����Ʈ �Ҹ���
	~Stage2();


	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	Stage2(const Stage2& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	Stage2(Stage2&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	Stage2& operator=(const Stage2& _Other) = delete;
	Stage2& operator=(Stage2&& _Other) noexcept = delete;

	inline GameEngineTextureRenderer* GetPortal() const
	{
		return Portal;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

	GameEngineTextureRenderer* BG;
	GameEngineTextureRenderer* Map;
	GameEngineTextureRenderer* Map_Col;
	GameEngineTextureRenderer* Portal;

private:
	float Speed;
};

