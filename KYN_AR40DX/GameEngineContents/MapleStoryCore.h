#pragma once
#include <GameEngineCore/GameEngineCore.h>

// ���� : ������ ���۵� �ھ�
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
	void UserStart() override;

	// �� ���α׷��� ��� ��Ȳ������ ��� Update�ϸ鼭 üũ������ �ִٸ� ���⼭ �Ѵ�.
	// ������ ���� ������ �׷����� ����. ������ ���� �����̰� ���� ����Ű�� ������ �����Ѵ�.
	// Ÿ��Ʋ�� �ѱ�ų� �̷�
	void UserUpdate(float _DeltaTime) override;

	void UserEnd() override;

private:
	 
};

