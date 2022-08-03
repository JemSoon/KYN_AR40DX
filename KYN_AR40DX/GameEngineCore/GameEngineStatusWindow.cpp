#include "PreCompile.h"
#include "GameEngineStatusWindow.h"
#include "GameEngineRenderTarget.h"

void GameEngineImageShotWindow::RenderTextureSetting(ImTextureID _RenderTexture, ImVec2 _Size)
{
	RenderTexture = _RenderTexture;
	Size = _Size;
}

void GameEngineImageShotWindow::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	if (true == ImGui::ImageButton(RenderTexture, { Size.x, Size.y }))
	{
		Off();
	}

}

GameEngineStatusWindow::GameEngineStatusWindow()
{
}

GameEngineStatusWindow::~GameEngineStatusWindow()
{
}


void GameEngineStatusWindow::Initialize(class GameEngineLevel* _Level)
{

}

void GameEngineStatusWindow::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	int FPS = static_cast<int>(1.0f / _DeltaTime);
	// printf 형식인데 안씀.

	std::string Name = "FPS : " + std::to_string(FPS);
	ImGui::Text(std::to_string(FPS).c_str());
}