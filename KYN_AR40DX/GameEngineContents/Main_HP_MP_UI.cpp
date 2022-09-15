#include "PreCompile.h"
#include "Main_HP_MP_UI.h"


Main_HP_MP_UI::Main_HP_MP_UI()
	:HP_MP(nullptr)
	,EXP(nullptr)
	,HPbarMaxSize(171)
	,MPbarMaxSize(171)
	,EXPbarSize(0)
	,Hit(0)
	,UseMana(0)
	,Level(nullptr)
	,LevelNum(nullptr)
{
}

Main_HP_MP_UI::~Main_HP_MP_UI()
{

}

void Main_HP_MP_UI::Start()
{
	// UI�� �⺻ �ؽ��� ������ ���� �ö󰡴� �ؽ��ķ����� z��(1)���� ����(�۾ƾ�)�־���Ѵ�
	//-100���� ��������
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

	MPSetting();

	EXPSetting();

	LevelSetting();
}

void Main_HP_MP_UI::HPSetting()
{
	{
		if (PlayerInfo->HitCheck == true)
		{
			//�ε������� HP+Hit���������� ó������ HP+Hit�ϸ� �����ع���
			//HPbarMaxSize = PlayerInfo->CurHP + Hit;//�̰� �����ε� �÷��̾� ü�º�ʷ� ������
			HPbarMaxSize = (171 * (PlayerInfo->CurHP + Hit)) / PlayerInfo->HPMax;
			Hit = Hit - GameEngineTime::GetDeltaTime();
			if (HPbarMaxSize <= 0)
			{
				HPbarMaxSize = 0;
				//HP�ٸ� �����ؼ� ���� �ʰԲ�
				Hit = 0;
			}
		}

		else
		{
			//else�����ָ� �����Ѿ�� üũ���ؼ� Ǯ��ó�� ����
			HPbarMaxSize = (171 * (PlayerInfo->CurHP)) / PlayerInfo->HPMax;

			if (HPbarMaxSize <= 0)
			{
				HPbarMaxSize = 0;
				//HP�ٸ� �����ؼ� ���� �ʰԲ�
				Hit = 0;
			}
		}
	}

	if (Hit <= 0)
	{
		//��ŸŸ������ �� �پ��� 0����
		Hit = 0;
		PlayerInfo->HitCheck = false;
		Hit = PlayerInfo->HitDamage;
	}

	HPbar->GetTransform().SetWorldScale({ (float)HPbarMaxSize ,13,0 });//�پ������� �������

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
		UseMana = UseMana - GameEngineTime::GetDeltaTime();
		MPbarMaxSize = (171 * (PlayerInfo->CurMP + UseMana)) / PlayerInfo->MPMax;
		if (HPbarMaxSize <= 0)
		{
			HPbarMaxSize = 0;
			//MP�ٸ� �����ؼ� ���� �ʰԲ�
			UseMana = 0;
		}
		if (UseMana <= 0)
		{
			//��ŸŸ������ �� �پ��� 0����
			UseMana = 0;
			PlayerInfo->IsSuperJump = false;
			UseMana = PlayerInfo->ManaDamage;
		}

	}
	else
	{
		//else�����ָ� �����Ѿ�� üũ���ؼ� Ǯ��ó�� ����
		MPbarMaxSize = (171 * (PlayerInfo->CurMP)) / PlayerInfo->MPMax;

		if (MPbarMaxSize <= 0)
		{
			MPbarMaxSize = 0;
			//HP�ٸ� �����ؼ� ���� �ʰԲ�
			UseMana = 0;
		}
	}

	MPbar->GetTransform().SetWorldScale({ (float)MPbarMaxSize ,13,0 });//�پ������� �������

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
	//1264�� ����ġ�� �ִ�ġ
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