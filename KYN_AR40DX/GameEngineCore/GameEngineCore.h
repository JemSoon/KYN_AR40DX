#pragma once
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineString.h>

// 설명 :
class GameEngineCore
{
public:
	template<typename CoreType>
	static void Start()
	{
		GameEngineDebug::LeakCheckOn();

		//여기서 만들어진 이 코어를 알아야 하는 것
		CoreType Core;
		WindowCreate(Core.GetWindowTitle(), &Core);
						//↑템플릿 형식이라 .다음 미리보기 안떠..
	}

protected:
	virtual std::string GetWindowTitle() { return "MainWindow"; }

	virtual void UserGameStart() = 0;
	virtual void UserGameUpdate() = 0;
	virtual void UserGameEnd() = 0;

	// constrcuter destructer
	GameEngineCore();
	~GameEngineCore();

	template<typename LevelType>
	void LevelCreate(const std::string& _Name)
	{
		std::string UpperName = GameEngineString::ToUpperReturn(_Name);
	}

private:
	static void WindowCreate(const std::string& _Name, GameEngineCore* _UserCore);//윈도우 창 생성
	static void CoreStart(GameEngineCore* _UserCore);//프로그램 시작
	static void CoreUpdate(GameEngineCore* _UserCore);//프로그램 업데이트(계속 실행되는)
	static void CoreEnd(GameEngineCore* _UserCore);//프로그램 종료

	// delete Function
	GameEngineCore(const GameEngineCore& _Other) = delete;
	GameEngineCore(GameEngineCore&& _Other) noexcept = delete;
	GameEngineCore& operator=(const GameEngineCore& _Other) = delete;
	GameEngineCore& operator=(GameEngineCore&& _Other) noexcept = delete;

};

