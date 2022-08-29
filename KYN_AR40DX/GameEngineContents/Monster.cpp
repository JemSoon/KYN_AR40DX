#include "PreCompile.h"
#include "Monster.h"

#include <GameEngineBase/GameEngineRandom.h>

Monster::Monster()
	:Damage(15)
	,PatternTime(0)
	,Random(0)
	,RandomDir(0)
{
	Speed = 75;
}

Monster::~Monster()
{
}

void Monster::Start()
{
	//상속에 써둠
	//GetTransform().SetLocalScale({ 1, 1, 1 });
	CharacterObject::Start();
	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->GetTransform().SetLocalScale({ 64, 64, 1 });
		Renderer->SetTexture("snail_stand.png");
		//Renderer->ScaleToTexture();//나는 쓰면 늘어난다

		std::vector<unsigned int> Five = { 0, 1, 2 ,3, 4, 3, 2, 1};
		std::vector<unsigned int> Three = { 0, 1, 2 };
		std::vector<unsigned int> Two = { 0, 1 };
		std::vector<unsigned int> One = { 0 };

		Renderer->CreateFrameAnimationCutTexture("Idle", FrameAnimation_DESC("snail_stand.png", One, 0.2f, false));
		Renderer->CreateFrameAnimationCutTexture("Move", FrameAnimation_DESC("snail_move.png", Five, 0.2f));

		Renderer->ChangeFrameAnimation("Idle");
		Renderer->SetPivot(PIVOTMODE::BOT);
	}

	{
		Collision = CreateComponent<GameEngineCollision>();
		Collision->SetDebugSetting(CollisionType::CT_OBB2D, float4{ 1.0f,0.0f,0.0f,0.3f });
		Collision->GetTransform().SetLocalScale({ 32.0f, 24.0f, 100.0f });
		Collision->GetTransform().SetLocalPosition({ 0.0f, 13.0f, 0.0f });
		Collision->ChangeOrder(OBJECTORDER::Monster);
	}

	{
		StateManager.CreateStateMember("Idle"
			, std::bind(&Monster::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
			, std::bind(&Monster::IdleStart, this, std::placeholders::_1));

		StateManager.CreateStateMember("Move"
			, std::bind(&Monster::MoveUpdate, this, std::placeholders::_1, std::placeholders::_2)
			, std::bind(&Monster::MoveStart, this, std::placeholders::_1));

		StateManager.ChangeState("Idle");
	}
}

void Monster::IdleStart(const StateInfo& _Info)
{
	Random = GameEngineRandom::MainRandom.RandomInt(1, 2);
	Renderer->ChangeFrameAnimation("Idle");
	Speed = 75.0f;
}

void Monster::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	PatternTime += GameEngineTime::GetDeltaTime();
	if (Random == 1)
	{
		if (PatternTime >= 1.0f)
		{
			StateManager.ChangeState("Move");
			PatternTime = 0;
		}
	}

	if (Random == 2)
	{
		if (PatternTime >= 2.0f)
		{
			StateManager.ChangeState("Move");
			PatternTime = 0;
		}
	}
}

void Monster::MoveStart(const StateInfo& _Info)
{
	Renderer->ChangeFrameAnimation("Move");
	Random = GameEngineRandom::MainRandom.RandomInt(1, 2);
	RandomDir = Random = GameEngineRandom::MainRandom.RandomInt(1, 2);
}

void Monster::MoveUpdate(float _DeltaTime, const StateInfo& _Info)
{
	PatternTime += GameEngineTime::GetDeltaTime();
	//Random = GameEngineRandom::MainRandom.RandomInt(1, 4);
	if (Random == 1)
	{
		if (PatternTime >= 1.0f)
		{
			StateManager.ChangeState("Idle");
			PatternTime = 0;
		}
	}

	if (Random == 2)
	{
		if (PatternTime >= 2.0f)
		{
			StateManager.ChangeState("Idle");
			PatternTime = 0;
		}
	}

	if (RandomDir == 1)
	{
		MovePower = GetTransform().GetLeftVector() * Speed * _DeltaTime;
		Renderer->GetTransform().PixLocalPositiveX();
	}

	if (RandomDir == 2)
	{
		MovePower = GetTransform().GetRightVector() * Speed * _DeltaTime;
		Renderer->GetTransform().PixLocalNegativeX();
	}

	if (((iNextColorCheck[static_cast<unsigned int>(COLORCHECKDIR::DOWN)].g >= 200 && iNextColorCheck[static_cast<unsigned int>(COLORCHECKDIR::DOWN)].r == 0 && iNextColorCheck[static_cast<unsigned int>(COLORCHECKDIR::DOWN)].b == 0) &&//다운이 그린
		iNextColorCheck[static_cast<unsigned int>(COLORCHECKDIR::LEFT)].g >= 200 && iNextColorCheck[static_cast<unsigned int>(COLORCHECKDIR::LEFT)].r == 0 && iNextColorCheck[static_cast<unsigned int>(COLORCHECKDIR::LEFT)].b == 0) &&//왼이 그린
		iNextColorCheck[static_cast<unsigned int>(COLORCHECKDIR::LEFTTOP)].g == 255 && iNextColorCheck[static_cast<unsigned int>(COLORCHECKDIR::LEFTTOP)].r == 255 && iNextColorCheck[static_cast<unsigned int>(COLORCHECKDIR::LEFTTOP)].b == 255)//왼탑이 화이트
	{	//언덕길은 위로 올리는힘이 추가
		MovePower += (GetTransform().GetUpVector() * Speed * _DeltaTime);
	}

	ColorCheckUpdateNext(MovePower);

	if (((iNextColorCheck[static_cast<unsigned int>(COLORCHECKDIR::LEFT)].g < 200) || (iNextColorCheck[static_cast<unsigned int>(COLORCHECKDIR::LEFT)].g == 255 && (iNextColorCheck[static_cast<unsigned int>(COLORCHECKDIR::LEFT)].r == 255))) &&
		((iNextColorCheck[static_cast<unsigned int>(COLORCHECKDIR::RIGHT)].g < 200) || (iNextColorCheck[static_cast<unsigned int>(COLORCHECKDIR::RIGHT)].g == 255 && (iNextColorCheck[static_cast<unsigned int>(COLORCHECKDIR::RIGHT)].r == 255))))
	{
		//양옆이 벽이 아니라면 움직인다
		GetTransform().SetWorldMove(MovePower);
	}
}
//====================================================================================//
//====================================================================================//
//====================================================================================//
//====================================================================================//
//====================================================================================//

void Monster::Update(float _DeltaTime)
{
	StateManager.Update(_DeltaTime);
	Gravity(_DeltaTime);
}
