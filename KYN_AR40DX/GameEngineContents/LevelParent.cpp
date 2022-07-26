#include "LevelParent.h"

LevelParent::LevelParent() 
{
}

LevelParent::~LevelParent() 
{
}


void LevelParent::CreateStageObject(const std::string _BGName, const std::string _ColName)
{
	{
		LevelStageObject = CreateActor<StageObject>();


		{	//진짜 그림 맵
			LevelStageObject->GetMap()->GetTransform().SetLocalScale({ 2270, 1807, 100 });
			LevelStageObject->GetMap()->SetPivot(PIVOTMODE::LEFTTOP);
			// LevelStageObject->GetMap()->SetTexture("Stage1.png");
			LevelStageObject->GetMap()->SetTexture(_BGName);
		}


		{	//컬러충돌 맵
			LevelStageObject->GetMap_Col()->GetTransform().SetLocalScale({ 2270, 1807, 100 });
			LevelStageObject->GetMap_Col()->SetPivot(PIVOTMODE::LEFTTOP);
			// LevelStageObject->GetMap_Col()->SetTexture("Stage1_Col.png");
			LevelStageObject->GetMap_Col()->SetTexture(_ColName);

			//뒷배경	얘를 카메라이동 반응을 1초정도 느리게 쫓아오게 하고 싶다..
			LevelStageObject->GetBG()->GetTransform().SetLocalScale({ 4270, 1807, 100 });
			LevelStageObject->GetBG()->SetTexture("Stage1_BG.png");
		}

		{	//포탈 렌더러
			LevelStageObject->GetPortal()->GetTransform().SetLocalScale({ 90, 201, 100 });
			LevelStageObject->GetPortal()->SetTexture("Portal.png");

			LevelStageObject->GetPortal()->CreateFrameAnimation("Portal", FrameAnimation_DESC("Portal.png", 0, 3, 0.1f));
			LevelStageObject->GetPortal()->ChangeFrameAnimation("Portal");
			LevelStageObject->GetPortal()->GetTransform().SetLocalPosition({ 720.0f,-330.0f,0.0f });
		}
	}
}