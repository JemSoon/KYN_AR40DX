#pragma once
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineString.h>

// ���� :
class GameEngineCore
{
public:
	template<typename CoreType>
	static void Start()
	{
		GameEngineDebug::LeakCheckOn();

		//���⼭ ������� �� �ھ �˾ƾ� �ϴ� ��
		CoreType Core;
		WindowCreate(Core.GetWindowTitle(), &Core);
						//�����ø� �����̶� .���� �̸����� �ȶ�..
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
	static void WindowCreate(const std::string& _Name, GameEngineCore* _UserCore);//������ â ����
	static void CoreStart(GameEngineCore* _UserCore);//���α׷� ����
	static void CoreUpdate(GameEngineCore* _UserCore);//���α׷� ������Ʈ(��� ����Ǵ�)
	static void CoreEnd(GameEngineCore* _UserCore);//���α׷� ����

	// delete Function
	GameEngineCore(const GameEngineCore& _Other) = delete;
	GameEngineCore(GameEngineCore&& _Other) noexcept = delete;
	GameEngineCore& operator=(const GameEngineCore& _Other) = delete;
	GameEngineCore& operator=(GameEngineCore&& _Other) noexcept = delete;

};

