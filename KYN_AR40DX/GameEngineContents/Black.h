#pragma once
#include <GameEngineCore/CoreMinimal.h>
//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : 
class Black : public GameEngineActor
{
public:
	//����Ʈ ������
	Black();
	//����Ʈ �Ҹ���
	~Black();

	
	
	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	Black(const Black& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	Black(Black&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	Black& operator=(const Black& _Other) = delete;
	Black& operator=(Black&& _Other) noexcept = delete;

	GameEngineTextureRenderer* GetRenderer()
	{
		return Renderer;
	}
	
protected:
	virtual void Start() override;
	virtual void Update(float _DeltaTime);
	virtual void End() {}

private:
	GameEngineUIRenderer* Renderer;
};

