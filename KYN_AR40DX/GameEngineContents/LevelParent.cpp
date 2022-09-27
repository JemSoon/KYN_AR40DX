#include "LevelParent.h"
#include "GlobalContentsValue.h"
#include "Main_HP_MP_UI.h"
#include "Mouse.h"
#include "Inventory.h"

LevelParent::LevelParent() 
	:BlackOutTime(0.0f)
	,BlackInTime(0.0f)
	,LevelIn(false)
{
}

LevelParent::~LevelParent() 
{
}

void LevelParent::CreateStageObject(const std::string _BG, const std::string _ColName, const std::string _MapName)
{
	{
		LevelStageObject = CreateActor<StageObject>(OBJECTORDER::Map);
		{
			//뒷배경	얘를 카메라이동 반응을 1초정도 느리게 쫓아오게 하고 싶다..
			LevelStageObject->GetBG()->SetTexture(_BG);
			LevelStageObject->GetBG()->ScaleToTexture();
			//LevelStageObject->GetBG()->GetTransform().SetLocalScale({ 4270, 1807, 100 });
			LevelStageObject->GetBG()->SetPivot(PIVOTMODE::MIDDLETOP);

		}
		{
			//컬러충돌 맵
			LevelStageObject->GetMap_Col()->SetTexture(_ColName);
			LevelStageObject->GetMap_Col()->ScaleToTexture();
			//LevelStageObject->GetMap_Col()->GetTransform().SetLocalScale({ 2270, 1807, 100 });
			LevelStageObject->GetMap_Col()->SetPivot(PIVOTMODE::LEFTTOP);
			// LevelStageObject->GetMap_Col()->SetTexture("Stage1_Col.png");

		}

		{	//진짜 그림 맵
			LevelStageObject->GetMap()->SetTexture(_MapName);
			LevelStageObject->GetMap()->ScaleToTexture();
			//LevelStageObject->GetMap()->GetTransform().SetLocalScale({ 2270, 1807, 100 });
			LevelStageObject->GetMap()->SetPivot(PIVOTMODE::LEFTTOP);
			// LevelStageObject->GetMap()->SetTexture("Stage1.png");
		}

		{
			MainUI = CreateActor<Main_HP_MP_UI>(OBJECTORDER::UI);
			MainUI->GetTransform().SetWorldPosition({ 0.0f,-320.0f,-100.0f });

			Item = CreateActor<Inventory>(OBJECTORDER::UI);
			Item->GetTransform().SetWorldPosition({ 300.0f,0.0f,-100.0f });
		}

		{
			Cursor = CreateActor<Mouse>(OBJECTORDER::UI);
		}
		
		{
			B = CreateActor<Black>(OBJECTORDER::Black);
			B->GetTransform().SetWorldPosition({ 0,0,-500 });
		}
	}
}

void LevelParent::BlackTimeOut()
{
	BlackOutTime += GameEngineTime::GetDeltaTime();

	if ((B->GetRenderer()->GetPixelData().MulColor.a >= 0.0f)&&LevelIn==true)
	{
		B->GetRenderer()->GetPixelData().MulColor.a -= BlackOutTime * 0.1f;
	}

	if (B->GetRenderer()->GetPixelData().MulColor.a <= 0.0f)
	{
		LevelIn = false;
		BlackOutTime = 0.0f;
		B->GetRenderer()->GetPixelData().MulColor.a == 0.0f;
	}
}