#pragma once
#include <GameEngineCore/CoreMinimal.h>

class Player;
//설명 : 스테이지 액터 공용 클래스
class StageObject : public GameEngineActor
{
public:
	//디폴트 생성자
	StageObject();
	//디폴트 소멸자
	~StageObject();

	//======아래것들은 명시적으로 안쓰겠습니다(delete)======
	
	//디폴트 복사 생성자
	StageObject(const StageObject& _Other) = delete;
	//RValue Reference 생성자 (나중에 배울것)
	StageObject(StageObject&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
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

