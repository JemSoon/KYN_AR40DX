#pragma once
#include <GameEngineCore/CoreMinimal.h>

//설명 : 게임내 마우스
class GameEngineTextureRenderer;
class Mouse : public GameEngineActor
{
public:
	//디폴트 생성자
	Mouse();
	//디폴트 소멸자
	~Mouse();

	//======아래것들은 명시적으로 안쓰겠습니다(delete)======
	
	//디폴트 복사 생성자
	Mouse(const Mouse& _Other) = delete;
	//RValue Reference 생성자 (나중에 배울것)
	Mouse(Mouse&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
	Mouse& operator=(const Mouse& _Other) = delete;
	Mouse& operator=(Mouse&& _Other) noexcept = delete;

	GameEngineTextureRenderer* GetMouse()
	{
		return MouseImage;
	}

	float4 GetCursorPos1()
	{
		return CursorPos1;
	}

	float4 GetCursorPos2()
	{
		return CursorPos2;
	}

	GameEngineCollision* GetMouseActorCol()
	{
		return ActorCollision;
	}

	GameEngineCollision* GetMouseUICol()
	{
		return UICollision;
	}

	bool MouseHit(GameEngineCollision* _This, GameEngineCollision* _Other);
	bool UITestHit(GameEngineCollision* _This, GameEngineCollision* _Other);

protected:

private:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

	GameEngineTextureRenderer* MouseImage;
	GameEngineCameraActor* Camera;
	float4 CursorPos1;
	float4 CursorPos2;
	GameEngineCollision* ActorCollision;
	GameEngineCollision* UICollision;

};

