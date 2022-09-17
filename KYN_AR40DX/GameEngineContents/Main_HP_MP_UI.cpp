#include "PreCompile.h"
#include "Main_HP_MP_UI.h"


Main_HP_MP_UI::Main_HP_MP_UI()
	:HP_MP(nullptr)
	,EXP(nullptr)
	,HPbarMaxSize(171)
	,MPbarMaxSize(171)
	,EXPbarSize(0)
	,Hit(0)
	,UseMana(-1)
	,Level(nullptr)
	,LevelNum(nullptr)
	,CurHPNumber(0)
	,MaxHPNumber(0)
{
}

Main_HP_MP_UI::~Main_HP_MP_UI()
{

}

void Main_HP_MP_UI::Start()
{
	// UI는 기본 텍스쳐 렌더러 위에 올라가니 텍스쳐랜더러 z값(1)보다 위에(작아야)있어야한다
	//-100으로 통일하자
	GameEngineUIRenderer* Renderer = CreateComponent<GameEngineUIRenderer>();
	GetTransform().SetLocalScale({ 1, 1, 1 });
	//Renderer->ChangeCamera(CAMERAORDER::MAINCAMERA);
	{
		HPbar = CreateComponent<GameEngineUIRenderer>();
		HPbar->SetTexture("HPbar.png");
		HPbar->GetTransform().SetWorldScale({ (float)HPbarMaxSize,13,-100 });
		HPbar->GetTransform().SetLocalPosition({ -75, 0,-100 });
		HPbar->SetPivot(PIVOTMODE::LEFT);

		MPbar = CreateComponent<GameEngineUIRenderer>();
		MPbar->SetTexture("MPbar.png");
		MPbar->GetTransform().SetWorldScale({ 171,13,0 });
		MPbar->GetTransform().SetWorldPosition({ -75,-15,-100 });
		MPbar->SetPivot(PIVOTMODE::LEFT);
	}

	{
		HPNumSlash = CreateComponent<GameEngineUIRenderer>();
		HPNumSlash->SetTexture("HPMPNum.png");
		HPNumSlash->GetTransform().SetWorldScale({ 7,9,-100 });
		HPNumSlash->GetTransform().SetLocalPosition({ 10, 1,-101 });
		HPNumSlash->SetPivot(PIVOTMODE::CENTER);

		//현재체력 숫자렌더러
		HPNumOne = CreateComponent<GameEngineUIRenderer>();
		HPNumOne->SetTexture("HPMPNum0.png");
		HPNumOne->GetTransform().SetWorldScale({ 7,9,-100 });
		HPNumOne->GetTransform().SetLocalPosition({ -8, 1,-101 });
		HPNumOne->SetPivot(PIVOTMODE::CENTER);

		HPNumTen = CreateComponent<GameEngineUIRenderer>();
		HPNumTen->SetTexture("HPMPNum0.png");
		HPNumTen->GetTransform().SetWorldScale({ 7,9,-100 });
		HPNumTen->GetTransform().SetLocalPosition({ -16, 1,-101 });
		HPNumTen->SetPivot(PIVOTMODE::CENTER);

		HPNumHun = CreateComponent<GameEngineUIRenderer>();
		HPNumHun->SetTexture("HPMPNum0.png");
		HPNumHun->GetTransform().SetWorldScale({ 7,9,-100 });
		HPNumHun->GetTransform().SetLocalPosition({ -24, 1,-101 });
		HPNumHun->SetPivot(PIVOTMODE::CENTER);

		HPNumTho = CreateComponent<GameEngineUIRenderer>();
		HPNumTho->SetTexture("HPMPNum0.png");
		HPNumTho->GetTransform().SetWorldScale({ 7,9,-100 });
		HPNumTho->GetTransform().SetLocalPosition({ -32, 1,-101 });
		HPNumTho->SetPivot(PIVOTMODE::CENTER);

		//최대체력 출력 렌더러
		HPMaxNumTho = CreateComponent<GameEngineUIRenderer>();
		HPMaxNumTho->SetTexture("HPMPNum0.png");
		HPMaxNumTho->GetTransform().SetWorldScale({ 7,9,-100 });
		HPMaxNumTho->GetTransform().SetLocalPosition({ 28, 1,-101 });
		HPMaxNumTho->SetPivot(PIVOTMODE::CENTER);

		HPMaxNumHun = CreateComponent<GameEngineUIRenderer>();
		HPMaxNumHun->SetTexture("HPMPNum0.png");
		HPMaxNumHun->GetTransform().SetWorldScale({ 7,9,-100 });
		HPMaxNumHun->GetTransform().SetLocalPosition({ 36, 1,-101 });
		HPMaxNumHun->SetPivot(PIVOTMODE::CENTER);

		HPMaxNumTen = CreateComponent<GameEngineUIRenderer>();
		HPMaxNumTen->SetTexture("HPMPNum0.png");
		HPMaxNumTen->GetTransform().SetWorldScale({ 7,9,-100 });
		HPMaxNumTen->GetTransform().SetLocalPosition({ 44, 1,-101 });
		HPMaxNumTen->SetPivot(PIVOTMODE::CENTER);

		HPMaxNumOne = CreateComponent<GameEngineUIRenderer>();
		HPMaxNumOne->SetTexture("HPMPNum0.png");
		HPMaxNumOne->GetTransform().SetWorldScale({ 7,9,-100 });
		HPMaxNumOne->GetTransform().SetLocalPosition({ 52, 1,-101 });
		HPMaxNumOne->SetPivot(PIVOTMODE::CENTER);

	}

	{
		HP_MP = CreateComponent<GameEngineUIRenderer>();
		HP_MP->GetTransform().SetWorldScale({ 204,70,-100 });
		HP_MP->GetTransform().SetWorldPosition({ 0,0,-100 });
		HP_MP->SetTexture("mainHP_MP_UI.png"); 
	}

	{
		EXP = CreateComponent<GameEngineUIRenderer>();
		EXP->GetTransform().SetWorldScale({ 1280, 10, -100 });
		EXP->GetTransform().SetWorldPosition({0,-35,-100});
		EXP->SetTexture("mainEXP_UI.png");
	}

	{
		EXPbar = CreateComponent<GameEngineUIRenderer>();
		EXPbar->GetTransform().SetWorldScale({ (float)EXPbarSize, 7, 0 });
		EXPbar->GetTransform().SetWorldPosition({ -626,-35,-100 });
		EXPbar->SetTexture("EXPbar.png");
		EXPbar->SetPivot(PIVOTMODE::LEFT);
	}

	{
		QuickSlot = CreateComponent<GameEngineUIRenderer>();
		QuickSlot->GetTransform().SetWorldScale({151, 80, 0});
		QuickSlot->GetTransform().SetWorldPosition({564, 8, -100});
		QuickSlot->SetTexture("QuickSlot.png");

		TESTUICollision= CreateComponent<GameEngineCollision>();
		TESTUICollision->SetDebugSetting(CollisionType::CT_OBB2D, float4{ 0.0f,0.0f,1.0f,0.3f });
		TESTUICollision->GetTransform().SetWorldScale({ 151, 80, 100.0f });
		TESTUICollision->GetTransform().SetWorldPosition({564.5f, 0, -200 });
		TESTUICollision->ChangeOrder(OBJECTORDER::UI);
		TESTUICollision->SetUIDebugCamera();
	}

	{
		Level= CreateComponent<GameEngineUIRenderer>();
		Level->GetTransform().SetWorldScale({ 15, 10, 0 });
		Level->GetTransform().SetWorldPosition({ -65, 23, -100 });
		Level->SetTexture("Level.png");

		LevelNum = CreateComponent<GameEngineUIRenderer>();
		LevelNum->GetTransform().SetWorldScale({ 7, 10, 0 });
		LevelNum->GetTransform().SetWorldPosition({ -35, 23, -100 });
		LevelNum->SetTexture("Level1.png");
	}

}

void Main_HP_MP_UI::Update(float _DeltaTime)
{
	if (PlayerInfo == nullptr)
	{
		PlayerInfo = Player::GetMainPlayer();
	}
	
	HPSetting();
	HPNumberSetting();

	MPSetting();

	EXPSetting();

	LevelSetting();
}

void Main_HP_MP_UI::HPSetting()
{
	{
		if (PlayerInfo->HitCheck == true)
		{
			//부딪혔을때 HP+Hit하지않으면 처음부터 HP+Hit하면 오버해버림
			//HPbarMaxSize = PlayerInfo->CurHP + Hit;//이게 원본인데 플레이어 체력비례로 만들기↓
			HPbarMaxSize = (171 * (PlayerInfo->CurHP + Hit)) / PlayerInfo->HPMax;
			Hit = Hit - GameEngineTime::GetDeltaTime();
			if (HPbarMaxSize <= 0)
			{
				HPbarMaxSize = 0;
				//HP바를 오버해서 깎지 않게끔
				Hit = 0;
			}
		}

		else
		{
			//else안해주면 레벨넘어갈대 체크안해서 풀피처럼 보임
			HPbarMaxSize = (171 * (PlayerInfo->CurHP)) / PlayerInfo->HPMax;

			if (HPbarMaxSize <= 0)
			{
				HPbarMaxSize = 0;
				//HP바를 오버해서 깎지 않게끔
				Hit = 0;
			}
		}
	}

	if (Hit <= 0)
	{
		//델타타임으로 다 줄어들면 0고정
		Hit = 0;
		PlayerInfo->HitCheck = false;
		Hit = PlayerInfo->HitDamage;
	}

	HPbar->GetTransform().SetWorldScale({ (float)HPbarMaxSize ,13,0 });//줄어든비율로 사이즈세팅

	if (HPbarMaxSize <= 0)
	{
		Hit = 0;
		HPbarMaxSize = 0;
	}

	if (true == PlayerInfo->IsLevelUp)
	{
		HPbarMaxSize = (171 * (PlayerInfo->CurHP)) / PlayerInfo->HPMax;
	}
}

void Main_HP_MP_UI::MPSetting()
{
	if (PlayerInfo->IsSuperJump == true)
	{
		if (UseMana == -1)
		{
			//델타타임으로 다 줄어들면 0고정
			UseMana = PlayerInfo->ManaDamage;
		}

		static_cast<float>(UseMana);
		UseMana = UseMana - GameEngineTime::GetDeltaTime();

		if (UseMana >= 0)
		{
			MPbarMaxSize = (171 * (PlayerInfo->CurMP + UseMana)) / PlayerInfo->MPMax;
		}

		if (MPbarMaxSize <= 0)
		{
			MPbarMaxSize = 0;
			//MP바를 오버해서 깎지 않게끔
			UseMana = 0;
		}
	}
	else
	{
		//else안해주면 레벨넘어갈대 체크안해서 풀피처럼 보임
		MPbarMaxSize = (171 * (PlayerInfo->CurMP)) / PlayerInfo->MPMax;

		if (MPbarMaxSize <= 0)
		{
			MPbarMaxSize = 0;
			//HP바를 오버해서 깎지 않게끔
			UseMana = 0;
		}
	}

	MPbar->GetTransform().SetWorldScale({ (float)MPbarMaxSize ,13,0 });//줄어든비율로 사이즈세팅

	if (UseMana <= 0)
	{
		PlayerInfo->IsSuperJump = false;
		UseMana = -1;
	}

	if (MPbarMaxSize <= 0)
	{
		UseMana = 0;
		MPbarMaxSize = 0;
	}

	if (true == PlayerInfo->IsLevelUp)
	{
		MPbarMaxSize = (171 * (PlayerInfo->CurMP)) / PlayerInfo->MPMax;
	}
}

void Main_HP_MP_UI::EXPSetting()
{
	//1264가 경험치바 최대치
	EXPbarSize = (1264 * PlayerInfo->CurEXP) / PlayerInfo->EXPMax;
	EXPbar->GetTransform().SetWorldScale({ (float)EXPbarSize, 7, 0 });
}

void Main_HP_MP_UI::LevelSetting()
{
	int A = PlayerInfo->PlayerLevel;
	switch (A)
	{
	case 1:
		LevelNum->SetTexture("Level1.png");
		break;
	case 2:
		LevelNum->SetTexture("Level2.png");
		break;
	default:
		LevelNum->SetTexture("Level0.png");
	}
}

void Main_HP_MP_UI::HPNumberSetting()
{
	CurHPNumber = PlayerInfo->CurHP;
	MaxHPNumber = PlayerInfo->HPMax;

	{
		CurTho = CurHPNumber / 1000;
		CurHun = CurHPNumber / 100;
		CurTen = CurHPNumber / 10;
		CurOne = CurHPNumber % 10;

		switch (CurTho)
		{
		case 0:
			HPNumTho->SetTexture("HPMPNum0.png");
			break;
		case 1:
			HPNumTho->SetTexture("HPMPNum1.png");
			break;
		case 2:
			HPNumTho->SetTexture("HPMPNum2.png");
			break;
		case 3:
			HPNumTho->SetTexture("HPMPNum3.png");
			break;
		case 4:
			HPNumTho->SetTexture("HPMPNum4.png");
			break;
		case 5:
			HPNumTho->SetTexture("HPMPNum5.png");
			break;
		case 6:
			HPNumTho->SetTexture("HPMPNum6.png");
			break;
		case 7:
			HPNumTho->SetTexture("HPMPNum7.png");
			break;
		case 8:
			HPNumTho->SetTexture("HPMPNum8.png");
			break;
		case 9:
			HPNumTho->SetTexture("HPMPNum9.png");
			break;
		default:
			HPNumTho->SetTexture("HPMPNum0.png");
			break;
		}

		switch (CurHun)
		{
		case 0:
			HPNumHun->SetTexture("HPMPNum0.png");
			break;
		case 1:
			HPNumHun->SetTexture("HPMPNum1.png");
			break;
		case 2:
			HPNumHun->SetTexture("HPMPNum2.png");
			break;
		case 3:
			HPNumHun->SetTexture("HPMPNum3.png");
			break;
		case 4:
			HPNumHun->SetTexture("HPMPNum4.png");
			break;
		case 5:
			HPNumHun->SetTexture("HPMPNum5.png");
			break;
		case 6:
			HPNumHun->SetTexture("HPMPNum6.png");
			break;
		case 7:
			HPNumHun->SetTexture("HPMPNum7.png");
			break;
		case 8:
			HPNumHun->SetTexture("HPMPNum8.png");
			break;
		case 9:
			HPNumHun->SetTexture("HPMPNum9.png");
			break;
		default:
			HPNumHun->SetTexture("HPMPNum0.png");
			break;
		}

		switch (CurTen)
		{
		case 0:
			HPNumTen->SetTexture("HPMPNum0.png");
			break;
		case 1:
			HPNumTen->SetTexture("HPMPNum1.png");
			break;
		case 2:
			HPNumTen->SetTexture("HPMPNum2.png");
			break;
		case 3:
			HPNumTen->SetTexture("HPMPNum3.png");
			break;
		case 4:
			HPNumTen->SetTexture("HPMPNum4.png");
			break;
		case 5:
			HPNumTen->SetTexture("HPMPNum5.png");
			break;
		case 6:
			HPNumTen->SetTexture("HPMPNum6.png");
			break;
		case 7:
			HPNumTen->SetTexture("HPMPNum7.png");
			break;
		case 8:
			HPNumTen->SetTexture("HPMPNum8.png");
			break;
		case 9:
			HPNumTen->SetTexture("HPMPNum9.png");
			break;
		default:
			HPNumTen->SetTexture("HPMPNum0.png");
			break;
		}

		switch (CurOne)
		{
		case 0:
			HPNumOne->SetTexture("HPMPNum0.png");
			break;
		case 1:
			HPNumOne->SetTexture("HPMPNum1.png");
			break;
		case 2:
			HPNumOne->SetTexture("HPMPNum2.png");
			break;
		case 3:
			HPNumOne->SetTexture("HPMPNum3.png");
			break;
		case 4:
			HPNumOne->SetTexture("HPMPNum4.png");
			break;
		case 5:
			HPNumOne->SetTexture("HPMPNum5.png");
			break;
		case 6:
			HPNumOne->SetTexture("HPMPNum6.png");
			break;
		case 7:
			HPNumOne->SetTexture("HPMPNum7.png");
			break;
		case 8:
			HPNumOne->SetTexture("HPMPNum8.png");
			break;
		case 9:
			HPNumOne->SetTexture("HPMPNum9.png");
			break;
		default:
			HPNumTen->SetTexture("HPMPNum0.png");
			break;
		}
	}
}

