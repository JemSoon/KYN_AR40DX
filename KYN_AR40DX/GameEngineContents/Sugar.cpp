#include "PreCompile.h"
#include "Sugar.h"
#include "Dialogue.h"

Sugar::Sugar()
{

}

Sugar::~Sugar()
{

}

void Sugar::Start()
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
		Renderer->GetTransform().SetLocalScale({ 48, 75, 1 });
		Renderer->GetTransform().PixLocalNegativeX();
		Renderer->SetTexture("sugar.png");
		Renderer->SetPivot(PIVOTMODE::BOT);
		//Renderer->ScaleToTexture();//나는 쓰면 늘어난다

		Collision = CreateComponent<GameEngineCollision>();
		Collision->SetDebugSetting(CollisionType::CT_OBB2D, float4{ 1.0f,0.0f,0.0f,0.3f });
		Collision->GetTransform().SetLocalScale({ 40.0f,64.0f,100.0f });
		Collision->ChangeOrder(OBJECTORDER::NPC);
		Collision->GetTransform().SetWorldPosition({0,35.0f});
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

void Sugar::Update(float _DeltaTime)
{
	//ColorCheckUpdate();

	//if (PlayerInfo == nullptr)
	//{
	//	PlayerInfo = Player::GetMainPlayer();
	//}

	//if (true == IsColor(COLORCHECKDIR::DOWN, CharacterObject::WHITE))
	//{	
	//	//조건문 안해주면 계속 중력받아서 오차땜에 부들부들 떰
	//	Gravity(_DeltaTime);
	//}

	//MovePower.x = static_cast<int>(MovePower.x);
	//MovePower.y = static_cast<int>(MovePower.y);

	//GetTransform().SetWorldMove(MovePower * _DeltaTime);

	//NoGravity();

	NPC::Update(_DeltaTime);

	if (Chat->IsUpdate() == true)
	{
		Level = GetLevel()->GetNameCopy();

		if (Level == "STAGE1")
		{
			Font->SetText("안녕", "돋움");
		}
		else if (Level == "STAGE2"&&PlayerInfo->PlayerLevel>=10)
		{
			Font->SetText("레벨이 10이 되었으면\n오른쪽 포탈을 타고 페리온으로 가봐", "돋움");
		}
		else if (Level == "STAGE2")
		{
			Font->SetText("달팽이가 많네", "돋움");
		}
		Font->SetColor({0.0f, 0.0f, 0.0f });
		Font->SetScreenPostion({ 540.0f, 270.0f ,-350.0f});
	}
}

void Sugar::ChatOn()
{
	Chat->On();
	Chat->SetNPCTexture("sugar.png");
}