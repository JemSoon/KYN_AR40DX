#include "PreCompile.h"
#include "Player.h"

#include <GameEngineContents/GlobalContentsValue.h>
#include <iostream>
#include "LevelParent.h"
#include <GameEngineBase/GameEngineRandom.h>

Player* Player::MainPlayer = nullptr;

Player::Player()
	:stop(false)
	,PortalOn(false)
{
	MainPlayer = this;
	Speed = 150.0f;
}

Player::~Player()
{
}

void Player::Start()
{
	CharacterObject::Start();

	if (false == GameEngineInput::GetInst()->IsKey("PlayerLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("PlayerLeft", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("PlayerRight", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("PlayerUp", VK_UP);
		GameEngineInput::GetInst()->CreateKey("PlayerDown", VK_DOWN);
		GameEngineInput::GetInst()->CreateKey("PlayerJump", 'C');
		GameEngineInput::GetInst()->CreateKey("PlayerAttack", 'Z');
	}

	GetTransform().SetLocalScale({ 1, 1, 1 });

	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->GetTransform().SetLocalScale({ 256, 256, 1 });
		Renderer->SetTexture("idle.png");
		//Renderer->ScaleToTexture();//아직 생성전이라 그런지 쓰면 터짐

		std::vector<unsigned int> Idle = { 0, 1, 2, 1 };//프레임 골라 실행 테스트
		std::vector<unsigned int> Three = { 0, 1, 2};
		std::vector<unsigned int> Two = { 0, 1 };
		std::vector<unsigned int> One = { 0 };

		Renderer->CreateFrameAnimationCutTexture("Idle", FrameAnimation_DESC("idle.png", Idle, 0.3f));
		Renderer->CreateFrameAnimationCutTexture("Move", FrameAnimation_DESC("walk.png", Three, 0.1f));
		Renderer->CreateFrameAnimationCutTexture("Sadari", FrameAnimation_DESC("sadari.png", Two, 0.3f));
		Renderer->CreateFrameAnimationCutTexture("Jump", FrameAnimation_DESC("jump.png", One, 0.0f, false));
		Renderer->CreateFrameAnimationCutTexture("Prone", FrameAnimation_DESC("prone.png", One, 0.0f, false));
		Renderer->CreateFrameAnimationCutTexture("Attack1", FrameAnimation_DESC("attack1.png", Three, 0.2f));
		Renderer->CreateFrameAnimationCutTexture("Attack2", FrameAnimation_DESC("attack2.png", Three, 0.2f));
		Renderer->CreateFrameAnimationCutTexture("Attack3", FrameAnimation_DESC("attack3.png", Three, 0.2f));
		Renderer->CreateFrameAnimationCutTexture("Attack4", FrameAnimation_DESC("attack4.png", Two, 0.23f));

		Renderer->ChangeFrameAnimation("Idle");
		Renderer->SetPivot(PIVOTMODE::CUSTOM);
	}
	
	{
		Renderer->AnimationBindEnd("Attack1", std::bind(&Player::AttackEnd, this));
		Renderer->AnimationBindEnd("Attack2", std::bind(&Player::AttackEnd, this));
		Renderer->AnimationBindEnd("Attack3", std::bind(&Player::AttackEnd, this));
		Renderer->AnimationBindEnd("Attack4", std::bind(&Player::AttackEnd, this));
	}

	{
		Collision = CreateComponent<GameEngineCollision>();
		Collision->SetDebugSetting(CollisionType::CT_OBB2D, float4{1.0f,0.0f,0.0f,0.3f});
		Collision->GetTransform().SetLocalScale({ 64.0f, 64.0f, 100.0f });
		Collision->ChangeOrder(OBJECTORDER::Player);
		Collision->GetTransform().SetWorldPosition({ 0.0f,35.0f });
	}
	{
		AttackCollision = CreateComponent<GameEngineCollision>();
		AttackCollision->SetDebugSetting(CollisionType::CT_OBB2D, float4{ 1.0f,0.0f,0.0f,0.3f });
		AttackCollision->GetTransform().SetLocalScale({ 84.0f, 64.0f, 100.0f });
		AttackCollision->ChangeOrder(OBJECTORDER::Player);
		AttackCollision->GetTransform().SetWorldPosition({ -35.0f,35.0f });
		AttackCollision->Off();
	}

	GameEngineFontRenderer* Font = CreateComponent<GameEngineFontRenderer>();
	Font->SetText("테스트", "궁서");
	Font->SetColor({ 1.0f, 0.0f, 0.0f });
	Font->SetScreenPostion({ 100.0f, 100.0f });

	StateManager.CreateStateMember("Idle"
		, std::bind(&Player::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::IdleStart, this, std::placeholders::_1));

	int MyValue = 10;//이 밖에있는걸

	StateManager.CreateStateMember("Move"
		, std::bind(&Player::MoveUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, [/*&*/=](const StateInfo& _Info)
		{
			// static const int MyValue = 바깥 MyValue;

			int Test = MyValue;//저장해서 가져와 쓸수있다
			// = 지역변수도 쓸수있다.
			// MyValue가 하나더 생기는 방식으로 컴파일러가 해석한다.
			// ????????
			// & 외부의 있는 값의 참조형을 받아오는 것이기 때문에
			// 지역변수를 쓰면 결과를 장담할수가 없다. = 참조는 안된다
			Renderer->ChangeFrameAnimation("Move");
		});

	StateManager.CreateStateMember("Sadari"
		, std::bind(&Player::SadariUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::SadariStart, this, std::placeholders::_1));
	StateManager.CreateStateMember("Jump"
		, std::bind(&Player::JumpUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::JumpStart, this, std::placeholders::_1));
	StateManager.CreateStateMember("Fall"
		, std::bind(&Player::FallUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::FallStart, this, std::placeholders::_1));
	StateManager.CreateStateMember("Prone"
		, std::bind(&Player::ProneUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::ProneStart, this, std::placeholders::_1));
	StateManager.CreateStateMember("Attack"
		, std::bind(&Player::AttackUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::AttackStart, this, std::placeholders::_1));
	StateManager.CreateStateMember("DownJump"
		, std::bind(&Player::DownJumpUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::DownJumpStart, this, std::placeholders::_1));

	StateManager.ChangeState("Idle");

}

void Player::IdleStart(const StateInfo& _Info)
{
	Speed = 150.0f;
	Renderer->ChangeFrameAnimation("Idle");
}
void Player::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{

	if (true == GameEngineInput::GetInst()->IsPress("PlayerLeft") ||
		true == GameEngineInput::GetInst()->IsPress("PlayerRight"))
	{
		StateManager.ChangeState("Move");
	}

	if (true == GameEngineInput::GetInst()->IsPress("PlayerUp") &&
		true == IsNextColor(COLORCHECKDIR::DOWN, float4::BLUE))
	{
		StateManager.ChangeState("Sadari");
	}

	if (true == GameEngineInput::GetInst()->IsPress("PlayerDown") &&
		true == IsNextColor(COLORCHECKDIR::DOWN, float4::RED))
	{
		StateManager.ChangeState("Sadari");
	}

	if (true == GameEngineInput::GetInst()->IsPress("PlayerJump"))
	{
		StateManager.ChangeState("Jump");
	}

	if (true == GameEngineInput::GetInst()->IsPress("PlayerDown")&&
		false == IsNextColor(COLORCHECKDIR::DOWN, float4::RED))
	{
		StateManager.ChangeState("Prone");
	}

	if (true == GameEngineInput::GetInst()->IsPress("PlayerAttack"))
	{
		StateManager.ChangeState("Attack");
	}

	if (true == IsNextColor(COLORCHECKDIR::DOWN, float4::BLUE))
	{
		return;
	}
	Gravity(_DeltaTime);
}

void Player::AttackStart(const StateInfo& _Info)
{
	AttackCollision->On();

	int RandomNumber = GameEngineRandom::MainRandom.RandomInt(1, 4);

	if (RandomNumber == 1)
	{
		Renderer->ChangeFrameAnimation("Attack1");
	}
	else if (RandomNumber == 2)
	{
		Renderer->ChangeFrameAnimation("Attack2");
	}
	else if (RandomNumber == 3)
	{
		Renderer->ChangeFrameAnimation("Attack3");
	}
	else
	{
		Renderer->ChangeFrameAnimation("Attack4");
	}


	Speed = 150.0f;//어택할때 왠지모르게 스피드가 -75로 변경됨;;
}

void Player::AttackUpdate(float _DeltaTime, const StateInfo& _Info)
{
	Gravity(_DeltaTime);
	GetTransform().SetWorldMove(MovePower);
	stop = true;
}

void Player::AttackEnd()
{

	if (true == GameEngineInput::GetInst()->IsFree("PlayerAttack"))
	{
		AttackCollision->Off();
		StateManager.ChangeState("Fall");
	}

	else if (true == GameEngineInput::GetInst()->IsPress("PlayerAttack"))
	{
		AttackCollision->On();
		int RandomNumber = GameEngineRandom::MainRandom.RandomInt(1, 4);

		if (RandomNumber == 1)
		{
			Renderer->ChangeFrameAnimation("Attack1");
		}
		else if (RandomNumber == 2)
		{
			Renderer->ChangeFrameAnimation("Attack2");
		}
		else if (RandomNumber == 3)
		{
			Renderer->ChangeFrameAnimation("Attack3");
		}
		else
		{
			Renderer->ChangeFrameAnimation("Attack4");
		}

		Speed = 150.0f;//어택할때 왠지모르게 스피드가 -75로 변경됨;;
	}
}

void Player::ProneStart(const StateInfo& _Info)
{
	MovePower.y = 0.0f;//가끔 팍 튀는현상 막기용
	Renderer->ChangeFrameAnimation("Prone");
}

void Player::ProneUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsUp("PlayerDown"))
	{
		StateManager.ChangeState("Idle");
	}

	if (true == GameEngineInput::GetInst()->IsPress("PlayerDown")&&
		true == GameEngineInput::GetInst()->IsDown("PlayerJump")&&
		(iNextColorCheck[5].g>245 && iNextColorCheck[5].r <= 0))
	{
		//그린245가 최종 밑바닥 여기서 더 내려가지 몬한다
		StateManager.ChangeState("DownJump");
	}
}

//void Player::MoveStart(const StateInfo& _Info)
//{
//	Renderer->ChangeFrameAnimation("Move");
//}

void Player::MoveUpdate(float _DeltaTime, const StateInfo& _Info)
{
	//GameEngineDebug::DrawBox();

	// GameEngineDebug::DebugSphereRender();

	if (false == GameEngineInput::GetInst()->IsPress("PlayerLeft") &&
		false == GameEngineInput::GetInst()->IsPress("PlayerRight") &&
		false == GameEngineInput::GetInst()->IsPress("PlayerUp") &&
		false == GameEngineInput::GetInst()->IsPress("PlayerDown"))
	{	//아무것도 안누르고 있고 바닥에있으면 Idle상태로 변경
		StateManager.ChangeState("Idle");
		return;
	}

	if (true == GameEngineInput::GetInst()->IsPress("PlayerJump"))
	{
		StateManager.ChangeState("Jump");
	}

	if (true == GameEngineInput::GetInst()->IsPress("PlayerAttack"))
	{
		StateManager.ChangeState("Attack");
	}

	if (true == GameEngineInput::GetInst()->IsPress("PlayerUp") &&
		true == IsNextColor(COLORCHECKDIR::UP, float4::BLUE))
	{
		StateManager.ChangeState("Sadari");
	}

	if (true == GameEngineInput::GetInst()->IsPress("PlayerDown") &&
		true == IsNextColor(COLORCHECKDIR::DOWN, float4::RED))
	{
		StateManager.ChangeState("Sadari");
	}

	if (true == GameEngineInput::GetInst()->IsPress("PlayerLeft"))
	{
		MovePower = GetTransform().GetLeftVector() * Speed * _DeltaTime;

		if 	((true==(iNextColorCheck[5].g>200 && iNextColorCheck[5].r <= 0 && iNextColorCheck[5].b <= 0))&&
			 (true==(iNextColorCheck[0].g>200 && iNextColorCheck[0].r <= 0 && iNextColorCheck[0].b <= 0))&&
			 (true==(iNextColorCheck[1].g!=0 && iNextColorCheck[1].r!=0 && iNextColorCheck[1].b != 0)))
		{	//언덕길은 위로 올리는힘이 추가
			MovePower += (GetTransform().GetUpVector() * Speed * 0.7f * _DeltaTime);
			stop = false;
		}

		/*if (true == IsNextColor(COLORCHECKDIR::DOWN, float4::WHITE)&&
			true == IsNextColor(COLORCHECKDIR::DOWNR, float4::WHITE)&&
			false == IsNextColor(COLORCHECKDIR::LEFT, float4::GREEN))*/
			
		if	(true == IsNextColor(COLORCHECKDIR::DOWN, float4::WHITE) &&
			true == IsNextColor(COLORCHECKDIR::DOWNR, float4::WHITE) &&
			(true == (iNextColorCheck[0].g != 245||250||255)))
		{	
			StateManager.ChangeState("Fall");
		}
		Renderer->GetTransform().PixLocalPositiveX();
		AttackCollision->GetTransform().SetLocalPosition({ -35.0f,35.0f });
	}

	if (true == GameEngineInput::GetInst()->IsPress("PlayerRight"))
	{
		//Renderer->GetColorData().MulColor.a -= _DeltaTime;
		//(누르면 점점 알파값 사라짐 MulColor는 기본 흰색 a는 알파값 곱하기레이어에 흰색은 투명색)
		MovePower = GetTransform().GetRightVector() * Speed * _DeltaTime;

		if ((iNextColorCheck[5].g > 200 && iNextColorCheck[5].r <= 0 && iNextColorCheck[5].b <= 0) &&
			(iNextColorCheck[2].g > 200 && iNextColorCheck[2].r <= 0 && iNextColorCheck[2].b <= 0) &&
			(iNextColorCheck[1].g != 0 && iNextColorCheck[3].r != 0 && iNextColorCheck[3].b != 0))
			
		{	//언덕길은 위로 올리는힘이 추가
			MovePower += (GetTransform().GetUpVector() * Speed * _DeltaTime);
			stop = false;
		}

		if (true == IsNextColor(COLORCHECKDIR::DOWN, float4::WHITE)&&
			true == IsNextColor(COLORCHECKDIR::DOWNL, float4::WHITE)&&
			false == IsNextColor(COLORCHECKDIR::RIGHT, float4::GREEN))
		{	
			StateManager.ChangeState("Fall");
		}

		Renderer->GetTransform().PixLocalNegativeX();
		AttackCollision->GetTransform().SetLocalPosition({ 35.0f,35.0f});
	}


	ColorCheckUpdateNext(MovePower);

	/*if (false == IsNextColor(COLORCHECKDIR::LEFT, float4::GREEN) 
		&& false == IsNextColor(COLORCHECKDIR::RIGHT, float4::GREEN))*/
	if((false == (iNextColorCheck[static_cast<unsigned int>(COLORCHECKDIR::LEFT)].g >200 && iNextColorCheck[0].r==0 && iNextColorCheck[0].b == 0))&&
		(false == (iNextColorCheck[static_cast<unsigned int>(COLORCHECKDIR::RIGHT)].g > 200 && iNextColorCheck[2].r == 0 && iNextColorCheck[2].b == 0)))
	{
		//양옆이 벽이 아니라면 움직인다
		GetTransform().SetWorldMove(MovePower);
		stop = false;
	}
	else if ((true == GameEngineInput::GetInst()->IsPress("PlayerRight") &&
			(true == IsNextColor(COLORCHECKDIR::DOWN, float4::GREEN) &&
			true == IsNextColor(COLORCHECKDIR::RIGHT, float4::GREEN) &&
			false == IsNextColor(COLORCHECKDIR::RIGHTTOP, float4::GREEN)))
										||
			(true == GameEngineInput::GetInst()->IsPress("PlayerLeft")&&
			(true == IsNextColor(COLORCHECKDIR::DOWN, float4::GREEN) &&
			true == IsNextColor(COLORCHECKDIR::LEFT, float4::GREEN) &&
			false == IsNextColor(COLORCHECKDIR::LEFTTOP, float4::GREEN))))
	{
		//언덕길 오르막길도 stop=false
		stop = false;
	}
	else 
	{	
		//그 외엔 벽에 부딪힌거니 BG는 멈추기 위해 stop=true
		stop = true;
	}

	if (true == GameEngineInput::GetInst()->IsDown("PlayerJump"))
	{
		StateManager.ChangeState("Jump");
	}
	
	if (true == IsNextColor(COLORCHECKDIR::DOWN, float4::BLUE))
	{	//바닥이 파랑일땐 중력 안받는다
		return;
	}
	
	Gravity(_DeltaTime);
}

void Player::SadariStart(const StateInfo& _Info)
{
	Renderer->ChangeFrameAnimation("Sadari");
}

void Player::SadariUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsPress("PlayerUp"))
	{	
		MovePower = GetTransform().GetUpVector() * Speed * _DeltaTime;
		GetTransform().SetWorldMove(MovePower);
		
		ColorCheckUpdateNext(MovePower);

		if (true == IsNextColor(COLORCHECKDIR::DOWN, float4::WHITE))
		{
			MovePower.y = 0.0f;
			StateManager.ChangeState("Idle");
		}
	}

	if (true == GameEngineInput::GetInst()->IsPress("PlayerDown"))
	{
		MovePower = GetTransform().GetDownVector() * Speed * _DeltaTime;
		GetTransform().SetWorldMove(MovePower);

		ColorCheckUpdateNext(MovePower);

		if (true == IsNextColor(COLORCHECKDIR::DOWN, float4::GREEN))
		{
			StateManager.ChangeState("Idle");
		}
	}

}

void Player::JumpStart(const StateInfo& _Info)
{
	Dir = float4::ZERO;
	{
		Renderer->ChangeFrameAnimation("Jump");
		Speed *= 0.5f;
		//Speed += -75.0f;
		MovePower += float4::UP * 4.0f;
	}
}

void Player::JumpUpdate(float _DeltaTime, const StateInfo& _Info)
{	
	Gravity(_DeltaTime);
	{
		if (true == GameEngineInput::GetInst()->IsPress("PlayerAttack"))
		{
			StateManager.ChangeState("Attack");
		}

		if (true == GameEngineInput::GetInst()->IsPress("PlayerRight"))
		{	//점프중 오른쪽 이동키 누를시
			MovePower += (float4::RIGHT * _DeltaTime);
			Renderer->GetTransform().PixLocalNegativeX();
			
		}

		if (true == GameEngineInput::GetInst()->IsPress("PlayerLeft"))
		{	//점프중 왼쪽 이동키 누를시
			MovePower += (float4::LEFT * _DeltaTime);
			Renderer->GetTransform().PixLocalPositiveX();
		}

		if (true == GameEngineInput::GetInst()->IsPress("PlayerUp") &&
			true == IsNextColor(COLORCHECKDIR::UP, float4::BLUE))
		{	
			Speed = 150.0f;
			StateManager.ChangeState("Sadari");
		}
	}

	GetTransform().SetWorldMove(MovePower);

	if (((true == IsNextColor(COLORCHECKDIR::DOWN, float4::GREEN) && MovePower.y<=0) ||
		(true == IsNextColor(COLORCHECKDIR::DOWN, float4::RED) && MovePower.y <= 0))
		||
		(iNextColorCheck[5].g > 100 && iNextColorCheck[5].r <= 0))
	{	//y속도가 마이너스 && 초록 바닥에 닿는다면 = 착지 = idle
		StateManager.ChangeState("Idle");
		Speed = 150.0f;
	}

}

void Player::FallStart(const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsPress("PlayerLeft"))
	{
		MovePower.x = -1.0f;
	}
	else if (true == GameEngineInput::GetInst()->IsPress("PlayerRight"))
	{
		MovePower.x = 1.0f;
	}
	Renderer->ChangeFrameAnimation("Jump");
}

void Player::FallUpdate(float _DeltaTime, const StateInfo& _Info)
{
	Gravity(_DeltaTime);
	if ((true == GameEngineInput::GetInst()->IsPress("PlayerLeft") ||
		true == GameEngineInput::GetInst()->IsPress("PlayerRight"))&&
		(true==(iNextColorCheck[5].g>100 && iNextColorCheck[5].r <= 0 && iNextColorCheck[5].b <= 0)))
	{	//착지했는데 방향키 누르고있으면 Move
		StateManager.ChangeState("Move");
		Speed = 150.0f;
	}
	else if ((false == GameEngineInput::GetInst()->IsPress("PlayerLeft") ||
			  false == GameEngineInput::GetInst()->IsPress("PlayerRight")) &&
			 (true == (iNextColorCheck[5].g > 100 && iNextColorCheck[5].r <= 0 && iNextColorCheck[5].b <= 0)))
	{	//착지했는데 방향키 안누르면 Idle
		StateManager.ChangeState("Idle");
		Speed = 150.0f;
	}
	GetTransform().SetWorldMove(MovePower);
}

void Player::DownJumpStart(const StateInfo& _Info)
{
	PrevColor = iNextColorCheck[static_cast<unsigned int>(COLORCHECKDIR::DOWN)];
	Dir = float4::ZERO;
	{
		Renderer->ChangeFrameAnimation("Jump");
		Speed *= 0.5f;
		//Speed += -75.0f;
		MovePower += float4::UP * 1.0f;
	}
}
void Player::DownJumpUpdate(float _DeltaTime, const StateInfo& _Info)
{
	Gravity(_DeltaTime);
}

void Player::Update(float _DeltaTime)
{
	//GameEngineDebug::DrawSphere(Collision->GetTransform(), { 1.0f, 0.0f,0.0f, 0.5f });

	if (true == GetLevel()->GetMainCameraActor()->IsFreeCameraMode())
	{	//프리카메라 모드일땐 카메라가 플레이어 안움직이게 여기서 리턴
		return;
	}

	// 색깔 체크하고
	ColorCheckUpdate();
	StateManager.Update(_DeltaTime);

	{
		float4 Test1 = GetLevel()->GetMainCamera()->GetMouseScreenPosition();

		float4 Test2 = GetLevel()->GetMainCamera()->GetMouseWorldPosition(); 
	}

	//카메라가 플레이어 중심으로 쫓아다닌다
	//GetLevel()->GetMainCameraActorTransform().SetLocalPosition({ GetTransform().GetLocalPosition()});
	
	{
		// std::placeholders::_1, std::placeholders::_2 니들이 넣어줘야 한다는것을 명시키는것.
		AttackCollision->IsCollision(CollisionType::CT_OBB2D, OBJECTORDER::Monster, CollisionType::CT_OBB2D,
			std::bind(&Player::MonsterCollision, this, std::placeholders::_1, std::placeholders::_2));

		//Collision->IsCollision(CollisionType::CT_OBB, OBJECTORDER::Monster, CollisionType::CT_OBB,
		//	std::bind(&Player::MonsterCollision, this)
		//);
	}
	{
		Collision->IsCollision(CollisionType::CT_OBB2D, OBJECTORDER::Portal, CollisionType::CT_OBB2D,
			std::bind(&Player::PortalCollision, this, std::placeholders::_1, std::placeholders::_2));
	}
}

bool Player::MonsterCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{	
	//플레이어와 몬스터가 충돌하면 해당 몬스터를 죽이고 true 를 리턴

	_Other->GetActor()->Death();
	
	return true;
}

bool Player::PortalCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	if (true == GameEngineInput::GetInst()->IsPress("PlayerUp"))
	{
		PortalOn = true;
		return true;
	}
}

void Player::Gravity(float _DeltaTime)
{
	GameEngineTexture* MapTexture = GetLevel<LevelParent>()->GetMap_Col()->GetCurTexture();

	MovePower += float4::DOWN * _DeltaTime * 10.0f;//가속도

	ColorCheckUpdateNext(MovePower);

	if (true == IsNextColor(COLORCHECKDIR::DOWN, float4::WHITE))
	{	//발바닥이 흰색이라면 추락
		GetTransform().SetWorldMove(MovePower);
	}

	else if (MovePower.y > 0 || true == IsNextColor(COLORCHECKDIR::DOWN, float4::BLUE))
	{
		//y힘이 양수라면 그대로 힘을 유지한다
		GetTransform().SetWorldMove(MovePower);
	}

	else if ("DownJump"== StateManager.GetCurStateStateName()&&
			 iNextColorCheck[5].g >= PrevColor.g)
	{
		GetTransform().SetWorldMove(MovePower);
	}

	else if ("DownJump" == StateManager.GetCurStateStateName() &&
		iNextColorCheck[5].g < PrevColor.g)
	{
		MovePower = float4::ZERO;
		StateManager.ChangeState("Idle");
	}

	else
	{
		MovePower = float4::ZERO;
	}

}