#include <Windows.h>

#pragma comment(lib, "GameEngineBase.lib")

#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngineBase/GameEngineWindow.h>

void Init()
{

}

void Loop()
{

}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR		lpCmdLine,
	_In_ int		nCmdShow)
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

	//GameEngineSound::SoundPlayOneShot("BGM.mp3");

	GameEngineWindow::GetInst().CreateGameWindow(hInstance, "GameName");
														//Ÿ��Ʋ �̸�
	GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 0,0 }, { 1280,720 });
														//0,0��ġ�� 1280,720������
	GameEngineWindow::GetInst().ShowGameWindow();
	
	GameEngineWindow::GetInst().MessageLoop(Init, Loop);


	return 0;
}