#include "StageObject.h"
#include "Player.h"

StageObject::StageObject()
	: BG(nullptr)
	, Map(nullptr)
	, Portal(nullptr)
	, Map_Col(nullptr)
	, Speed(10.0f)
{

}

StageObject::~StageObject()
{

}

void StageObject::Start()
{
	if (false == GameEngineInput::GetInst()->IsKey("BGLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("BGLeft", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("BGRight", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("BGUp", VK_UP);
		GameEngineInput::GetInst()->CreateKey("BGDown", VK_DOWN);
	}

	GetTransform().SetLocalScale({ 1, 1, 1 });

	Map_Col = CreateComponent<GameEngineTextureRenderer>();
	BG = CreateComponent<GameEngineTextureRenderer>();
	Map = CreateComponent<GameEngineTextureRenderer>();
	Portal = CreateComponent<GameEngineTextureRenderer>();
}

void StageObject::Update(float _DeltaTime)
{
	if (MainPlayer == nullptr)
	{
		MainPlayer = Player::GetMainPlayer();
	}

	{	
		if (true == GameEngineInput::GetInst()->IsPress("BGLeft")&&
			MainPlayer->stop==false)
		{
			BG->GetTransform().SetWorldMove(GetTransform().GetLeftVector() * (-Speed) * _DeltaTime);
		}

		if (true == GameEngineInput::GetInst()->IsPress("BGRight")&&
			MainPlayer->stop == false)
		{
			BG->GetTransform().SetWorldMove(GetTransform().GetLeftVector() * (Speed)*_DeltaTime);
		}
	}
}

