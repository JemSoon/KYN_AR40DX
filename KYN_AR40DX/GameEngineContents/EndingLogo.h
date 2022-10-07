#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ���� :
class GameEngineTextureRenderer;
class EndingLogo : public GameEngineActor
{
public:
	//����Ʈ ������
	EndingLogo();
	//����Ʈ �Ҹ���
	~EndingLogo();

	
	
	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	EndingLogo(const EndingLogo& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	EndingLogo(EndingLogo&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	EndingLogo& operator=(const EndingLogo& _Other) = delete;
	EndingLogo& operator=(EndingLogo&& _Other) noexcept = delete;


protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	GameEngineTextureRenderer* Renderer;

	float TitleTime;
};

