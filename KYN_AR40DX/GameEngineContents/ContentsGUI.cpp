#include "ContentsGUI.h"
#include "Player.h"

ContentsGUI::ContentsGUI()
{

}

ContentsGUI::~ContentsGUI()
{

}


void ContentsGUI::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	ImGui::NewLine();

	ImGui::Text("EXP Get");
	{
		if (true == ImGui::Button("EXP"))
		{
			if (PlayerInfo == nullptr)
			{
				PlayerInfo = Player::GetMainPlayer();
			}

			PlayerInfo->CurEXP += 20;
		}
	}
}



