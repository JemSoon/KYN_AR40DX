#pragma once
#include <GameEngineCore/GameEngineCore.h>

// 설명 : 게임이 시작될 코어
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

	std::string GetWindowTitle() override
	{
		return "Maple Story";
	}

protected:
	void UserGameStart() override;
	void UserGameUpdate() override;
	// 이 프로그램이 어느 상황에서건 계속 Update하면서 체크할일이 있다면 여기서 한다.
	// 서버가 붙지 않으면 그럴일은 없다. 게임이 무슨 레벨이건 뭐건 무슨키를 누르면 종료한다.
	// 타이틀을 넘기거나 이런

	void UserGameEnd() override;

private:
	 
};

