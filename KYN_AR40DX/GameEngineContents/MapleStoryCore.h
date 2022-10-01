#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include <GameEngineCore/GameEngineCore.h>

// 설명 : 프로그램 자체를 시작하게 한다.
//class Main_HP_MP_UI;
class MapleStoryCore : public GameEngineCore
{
public:
	// constrcuter destructer
	MapleStoryCore();
	~MapleStoryCore();

	// delete Function
	MapleStoryCore(const MapleStoryCore& _Other) = delete;
	MapleStoryCore(MapleStoryCore&& _Other) noexcept = delete;
	MapleStoryCore& operator=(const MapleStoryCore& _Other) = delete;
	MapleStoryCore& operator=(MapleStoryCore&& _Other) noexcept = delete;

	// float4 StartWindowSize() override { return { 800.0f, 600.0f }; } ;
	// float4 StartWindowPosition() override { return { -2000,0 }; };

	std::string GetWindowTitle() override
	{
		return "Maple Story";
	}

protected:
	void Start() override;

	// 이 프로그램이 어느 상황에서건 계속 Update하면서 체크할일이 있다면 여기서 한다.
	// 서버가 붙지 않으면 그럴일은 없다. 게임이 무슨 레벨이건 뭐건 무슨키를 누르면 종료한다.
	// 타이틀을 넘기거나 이런
	void Update(float _DeltaTime) override;

	void End() override;

private:
	//Main_HP_MP_UI* MainUI;
};

