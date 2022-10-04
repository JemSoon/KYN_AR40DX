#include "ContentsGUI.h"
#include "Player.h"
#include "LevelParent.h"

ContentsGUI::ContentsGUI()
{

}

ContentsGUI::~ContentsGUI()
{

}


void ContentsGUI::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	PlayerInfo = Player::GetMainPlayer();

	ImGui::NewLine();

	ImGui::Text("EXP Get");
	{
		if (true == ImGui::Button("EXP"))
		{
			PlayerInfo->CurEXP += 20;
		}
	}

	ImGui::Text("ColMapOnOff");
	{
		if (true == ImGui::Button("ColMap"))
		{
			static_cast<LevelParent*>(PlayerInfo->GetLevel())->GetMap()->OnOffSwitch();
			static_cast<LevelParent*>(PlayerInfo->GetLevel())->GetBG()->OnOffSwitch();
		}
	}
}



