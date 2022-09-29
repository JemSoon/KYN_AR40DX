#include "PreCompile.h"
#include "Rock.h"
#include "Dialogue.h"

Rock::Rock()
{

}

Rock::~Rock()
{

}

void Rock::Start()
{
	NPC::Start();
	//{
	//	Chat = GetLevel()->CreateActor<Dialogue>();
	//	//Level = GetLevel()->GetNameCopy();
	//	Chat->GetTransform().SetWorldPosition({ 0.0f,0.0f,-200.0f });
	//	Chat->Off();
	//}
	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->GetTransform().SetLocalScale({ 81, 88, 1 });
		Renderer->GetTransform().PixLocalNegativeX();
		Renderer->SetTexture("Rock.png");
		Renderer->SetPivot(PIVOTMODE::BOT);
		//Renderer->ScaleToTexture();//나는 쓰면 늘어난다

		Collision = CreateComponent<GameEngineCollision>();
		Collision->SetDebugSetting(CollisionType::CT_OBB2D, float4{ 1.0f,0.0f,0.0f,0.3f });
		Collision->GetTransform().SetLocalScale({ 70.0f,70.0f,100.0f });
		Collision->ChangeOrder(OBJECTORDER::NPC);
		Collision->GetTransform().SetWorldPosition({ 0,35.0f });
	}

	{
		Font = CreateComponent<GameEngineFontRenderer>();
		Font->SetRenderingOrder(1001);
		Font->ChangeCamera(CAMERAORDER::UICAMERA);
		Font->SetParent(Chat);
		Font->SetSize(15.0f);
		Font->SetColor({ 0.0f, 0.0f, 0.0f });
		Font->SetScreenPostion({ 540.0f, 270.0f ,-350.0f });
	}
}

void Rock::Update(float _DeltaTime)
{
	NPC::Update(_DeltaTime);

	if (Chat->IsUpdate() == true)
	{
		Level = GetLevel()->GetNameCopy();


		if (PlayerInfo->PlayerLevel < 10)
		{
			Font->SetText("전사가 되고싶으면 \n좀 더 수련을 하고 오십시오", "돋움");
		}
		else if (Chat->IsYes == false && PlayerInfo->PlayerLevel >= 10)
		{
			Font->SetText("전사로 전직하겠습니까?", "돋움");
			Chat->YesOn();
		}
	}


	if (Chat->IsYes == true)
	{
		PlayerInfo->MyJob = JOB::WARRIOR;
		PlayerInfo->IsJobChange = true;
		Chat->IsYes = false;
		Collision->Off();
	}
}

void Rock::ChatOn()
{
	Chat->On();
	Chat->SetNPCTexture("Rock.png");
}