#pragma once
#include <GameEngineCore/CoreMinimal.h>

class Player;
//���� : �������� ���� ���� Ŭ����
class StageObject : public GameEngineActor
{
public:
	//����Ʈ ������
	StageObject();
	//����Ʈ �Ҹ���
	~StageObject();

	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	StageObject(const StageObject& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	StageObject(StageObject&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	StageObject& operator=(const StageObject& _Other) = delete;
	StageObject& operator=(StageObject&& _Other) noexcept = delete;
	

	inline GameEngineTextureRenderer* GetBG() const
	{
		return BG;
	}

	inline GameEngineTextureRenderer* GetMap() const
	{
		return Map;
	}

	inline GameEngineTextureRenderer* GetMap_Col() const
	{
		return Map_Col;
	}

	inline GameEngineTextureRenderer* GetPortal() const
	{
		return Portal;
	}

protected:
	virtual void Start() override;
	virtual void Update(float _DeltaTime);
	virtual void End() {}

	GameEngineTextureRenderer* BG;
	GameEngineTextureRenderer* Map;
	GameEngineTextureRenderer* Map_Col;
	GameEngineTextureRenderer* Portal;

	float Speed;
private:
	Player* MainPlayer;

};

