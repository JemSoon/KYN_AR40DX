#include "PreCompile.h"
#include "NPC.h"
#include "Dialogue.h"

NPC::NPC()
{

}

NPC::~NPC()
{

}

void NPC::Start()
{
	CharacterObject::Start();

	{
		Chat = GetLevel()->CreateActor<Dialogue>();
		Level = GetLevel()->GetNameCopy();
		Chat->GetTransform().SetWorldPosition({ 0.0f,0.0f,-200.0f });
		Chat->Off();
	}
}

void NPC::Update(float _DeltaTime)
{
	ColorCheckUpdate();

	if (PlayerInfo == nullptr)
	{
		PlayerInfo = Player::GetMainPlayer();
	}

	if (true == IsColor(COLORCHECKDIR::DOWN, CharacterObject::WHITE))
	{
		//조건문 안해주면 계속 중력받아서 오차땜에 부들부들 떰
		Gravity(_DeltaTime);
	}

	MovePower.x = static_cast<int>(MovePower.x);
	MovePower.y = static_cast<int>(MovePower.y);

	GetTransform().SetWorldMove(MovePower * _DeltaTime);

	NoGravity();
}

void NPC::ChatOn()
{
	Chat->On();
}