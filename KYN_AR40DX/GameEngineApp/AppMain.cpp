#include <Windows.h>

#pragma comment(lib, "GameEngineBase.lib")

#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngineBase/GameEngineSound.h>


int main()
{
	GameEngineDirectory Dir;

	if (false == Dir.MoveParentToExitsChildDirectory("Resources"))
	{
		MsgBoxAssert("��θ� ã�� ���߽��ϴ�.");
		return 0;
	}

	Dir.Move("Resources");
	Dir.Move("Sound");

	std::vector<GameEngineFile> Files = Dir.GetAllFile();

	// Range for
	// Files Ư���� ���۷����Ͱ� �Ǿ������� 
	for (GameEngineFile& File : Files)
	{
		GameEngineSound::LoadRessource(File);
		// GameEngineSound::LoadRessource("BGM.MP3");
	}

	GameEngineSound::SoundPlayOneShot("BGM.mp3");

	while (true)
	{
		GameEngineSound::Update();
	}

	return 0;
}