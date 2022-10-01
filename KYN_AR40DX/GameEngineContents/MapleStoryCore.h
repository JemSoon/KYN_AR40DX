#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include <GameEngineCore/GameEngineCore.h>

// ���� : ���α׷� ��ü�� �����ϰ� �Ѵ�.
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

	// �� ���α׷��� ��� ��Ȳ������ ��� Update�ϸ鼭 üũ������ �ִٸ� ���⼭ �Ѵ�.
	// ������ ���� ������ �׷����� ����. ������ ���� �����̰� ���� ����Ű�� ������ �����Ѵ�.
	// Ÿ��Ʋ�� �ѱ�ų� �̷�
	void Update(float _DeltaTime) override;

	void End() override;

private:
	//Main_HP_MP_UI* MainUI;
};

