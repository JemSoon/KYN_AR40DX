#pragma once
#include <GameEngineCore/GameEngineActor.h>

//설명 : 인게임 화면 하단 중앙에 나오는 체력 엠피 ui
class GameEngineTextureRenderer;
class Player;
class Main_HP_MP_UI : public GameEngineActor
{
public:
	//디폴트 생성자
	Main_HP_MP_UI();
	//디폴트 소멸자
	~Main_HP_MP_UI();

	
	//======아래것들은 명시적으로 안쓰겠습니다(delete)======
	
	//디폴트 복사 생성자
	Main_HP_MP_UI(const Main_HP_MP_UI& _Other) = delete;
	//RValue Reference 생성자 (나중에 배울것)
	Main_HP_MP_UI(Main_HP_MP_UI&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
	Main_HP_MP_UI& operator=(const Main_HP_MP_UI& _Other) = delete;
	Main_HP_MP_UI& operator=(Main_HP_MP_UI&& _Other) noexcept = delete;

	inline GameEngineTextureRenderer* GetHP_MP_Renderer() const
	{
		return HP_MP;
	}


	inline GameEngineTextureRenderer* GetEXPRenderer() const
	{
		return EXP;
	}

	void HPSetting();
	void EXPSetting();

	GameEngineTextureRenderer* HPbar;
protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

	GameEngineTextureRenderer* HP_MP;
	GameEngineTextureRenderer* EXP;
	GameEngineTextureRenderer* MPbar;
	GameEngineTextureRenderer* EXPbar;
	GameEngineTextureRenderer* QuickSlot;

private:
	GameEngineCameraActor* Camera;
	GameEngineCollision* TESTUICollision;
	Player* PlayerInfo;
	int HPbarMaxSize;
	int EXPbarSize;
	int Hit;
};

