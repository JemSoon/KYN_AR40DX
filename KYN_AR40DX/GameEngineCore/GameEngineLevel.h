#pragma once
#include <GameEngineBase/GameEngineNameObject.h>
#include <GameEngineBase/GameEngineUpdateObject.h>
// ���� :
class GameEngineLevel :
	public GameEngineNameObject,
	public GameEngineUpdateObject
{
	friend class GameEngineCore;
	//������ ������� �󸶳� �����־����� �ð��� �� �� �ְ� �Ѵ�

public:
	// constrcuter destructer
	GameEngineLevel();
	virtual ~GameEngineLevel() = 0;

	// delete Function
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;

protected:
	virtual void UserGameStart() = 0;
	virtual void UserGameUpdate() = 0;
	virtual void UserGameEnd() = 0;

private:

};

