#pragma once
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineString.h>
#include <map>

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

	virtual void UserStart() = 0;
	// �������� �����ϴ� �ð��� �ְ� �̰� ����
	virtual void UserUpdate(float _DeltaTime) = 0;
	virtual void UserEnd() = 0;

	// constrcuter destructer
	GameEngineCore();
	~GameEngineCore();

	class GameEngineLevel* FindLevel(const std::string& _Name);

	template<typename LevelType>
	GameEngineLevel* CreateLevel(const std::string& _Name)
	{
		std::string UpperName = GameEngineString::ToUpperReturn(_Name);
		GameEngineLevel* NewLevel = new LevelType();
		InitializeLevel(NewLevel, UpperName);
		return NewLevel;
	}

	bool ChangeLevel(const std::string& _Name);

private:
	static std::map<std::string, class GameEngineLevel*> AllLevels;
	static GameEngineLevel* CurrentLevel;
	static GameEngineLevel* NextLevel;

	static void WindowCreate(const std::string& _Name, GameEngineCore* _UserCore);//������ â ����
	static void CoreStart(GameEngineCore* _UserCore);//���α׷� ����
	static void CoreUpdate(GameEngineCore* _UserCore);//���α׷� ������Ʈ(��� ����Ǵ�)
	static void CoreEnd(GameEngineCore* _UserCore);//���α׷� ����

	// ��� �߰��ϱ� �Ⱦ �ʱ�ȭ�� CPP���� �ϱ� ���� �Լ�.
	void InitializeLevel(GameEngineLevel* _Level, const std::string _Name);

	// delete Function
	GameEngineCore(const GameEngineCore& _Other) = delete;
	GameEngineCore(GameEngineCore&& _Other) noexcept = delete;
	GameEngineCore& operator=(const GameEngineCore& _Other) = delete;
	GameEngineCore& operator=(GameEngineCore&& _Other) noexcept = delete;

};

