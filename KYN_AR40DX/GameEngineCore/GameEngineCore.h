#pragma once
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineString.h>
#include <map>

// 설명 :
class GameEngineCore
{
	friend class GEngine;

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

	virtual void Start() = 0;
	// 엔진에서 제공하는 시간을 주고 이걸 쓴다
	virtual void Update(float _DeltaTime) = 0;
	virtual void End() = 0;

	// constrcuter destructer
	GameEngineCore();
	~GameEngineCore();

	static class GameEngineLevel* FindLevel(const std::string& _Name);

	template<typename LevelType>
	static GameEngineLevel* CreateLevel(const std::string& _Name)
	{
		std::string UpperName = GameEngineString::ToUpperReturn(_Name);
		GameEngineLevel* NewLevel = new LevelType();
		InitializeLevel(NewLevel, UpperName);
		return NewLevel;
	}

	static bool ChangeLevel(const std::string& _Name);

private:
	static std::map<std::string, class GameEngineLevel*> AllLevels;
	static GameEngineLevel* CurrentLevel;
	static GameEngineLevel* NextLevel;

	static void WindowCreate(const std::string& _Name, GameEngineCore* _UserCore);//윈도우 창 생성
	static void CoreStart(GameEngineCore* _UserCore);//프로그램 시작
	static void CoreUpdate(GameEngineCore* _UserCore);//프로그램 업데이트(계속 실행되는)
	static void CoreEnd(GameEngineCore* _UserCore);//프로그램 종료

	// 헤더 추가하기 싫어서 초기화를 CPP에서 하기 위한 함수.
	static void InitializeLevel(GameEngineLevel* _Level, const std::string _Name);

	// delete Function
	GameEngineCore(const GameEngineCore& _Other) = delete;
	GameEngineCore(GameEngineCore&& _Other) noexcept = delete;
	GameEngineCore& operator=(const GameEngineCore& _Other) = delete;
	GameEngineCore& operator=(GameEngineCore&& _Other) noexcept = delete;

};

