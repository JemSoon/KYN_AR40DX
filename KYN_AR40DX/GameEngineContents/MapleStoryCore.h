#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include <GameEngineCore/GameEngineCore.h>

// ���� : ���α׷� ��ü�� �����ϰ� �Ѵ�.
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
	void Start() override;

	// �� ���α׷��� ��� ��Ȳ������ ��� Update�ϸ鼭 üũ������ �ִٸ� ���⼭ �Ѵ�.
	// ������ ���� ������ �׷����� ����. ������ ���� �����̰� ���� ����Ű�� ������ �����Ѵ�.
	// Ÿ��Ʋ�� �ѱ�ų� �̷�
	void Update(float _DeltaTime) override;

	void End() override;

private:

};

