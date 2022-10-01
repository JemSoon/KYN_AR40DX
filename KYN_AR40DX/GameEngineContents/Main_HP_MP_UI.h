#pragma once
#include <GameEngineCore/GameEngineActor.h>

//���� : �ΰ��� ȭ�� �ϴ� �߾ӿ� ������ ü�� ���� ui
class GameEngineTextureRenderer;
class Player;
class ItemIcon;
class Main_HP_MP_UI : public GameEngineActor
{

	static Main_HP_MP_UI* MainUI;
public:
	//����Ʈ ������
	Main_HP_MP_UI();
	//����Ʈ �Ҹ���
	~Main_HP_MP_UI();

	Main_HP_MP_UI* GetUI()
	{
		return MainUI;
	}
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	Main_HP_MP_UI(const Main_HP_MP_UI& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	Main_HP_MP_UI(Main_HP_MP_UI&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	Main_HP_MP_UI& operator=(const Main_HP_MP_UI& _Other) = delete;
	Main_HP_MP_UI& operator=(Main_HP_MP_UI&& _Other) noexcept = delete;

	inline GameEngineTextureRenderer* GetHP_MP_Renderer() const
	{
		return HP_MP;
	}


	inline GameEngineTextureRenderer* GetEXPRenderer() const
	{
		return EXP;
	}
	void CreateQuickSlot(int X, int Y, float4 Size, int CollisionOrder);
	void HPSetting();
	void EXPSetting();
	void MPSetting();
	void HPNumberSetting();
	void MPNumberSetting();
	void EXPNumberSetting();
	void LevelNumberSetting();
	void LevelRenderSetting(int _Value, GameEngineTextureRenderer* _Render);
	void HPMPNumRendererSetting(int _Value, GameEngineTextureRenderer* _Render);

	GameEngineTextureRenderer* HPbar;
protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

	GameEngineTextureRenderer* HP_MP;
	GameEngineTextureRenderer* EXP;
	GameEngineTextureRenderer* MPbar;
	GameEngineTextureRenderer* EXPbar;
	GameEngineTextureRenderer* QuickSlot;
	GameEngineTextureRenderer* Level;
	std::vector<std::vector<ItemIcon*>> ItemSlots;
private:
	GameEngineCameraActor* Camera;
	GameEngineCollision* TESTUICollision;
	Player* PlayerInfo;
	int HPbarMaxSize;
	int MPbarMaxSize;
	int EXPbarSize;
	
	int Hit;
	int UseMana;

	int CurHPNumber;
	int MaxHPNumber;

	int CurMPNumber;
	int MaxMPNumber;

	int HPCurOne;
	int HPCurTen;
	int HPCurHun;
	int HPCurTho;

	int HPMaxOne;
	int HPMaxTen;
	int HPMaxHun;
	int HPMaxTho;

	int MPCurOne;
	int MPCurTen;
	int MPCurHun;
	int MPCurTho;

	int MPMaxOne;
	int MPMaxTen;
	int MPMaxHun;
	int MPMaxTho;

	int LevelNumOne;
	int LevelNumTen;
	int LevelNumHun;

	int EXPCurOne;
	int EXPCurTen;
	int EXPCurHun;
	int EXPCurTho;
		
	int EXPMaxOne;
	int EXPMaxTen;
	int EXPMaxHun;
	int EXPMaxTho;

	GameEngineTextureRenderer* HPNumOne;
	GameEngineTextureRenderer* HPNumTen;
	GameEngineTextureRenderer* HPNumHun;
	GameEngineTextureRenderer* HPNumTho;
	GameEngineTextureRenderer* HPNumSlash;
	GameEngineTextureRenderer* HPMaxNumOne;
	GameEngineTextureRenderer* HPMaxNumTen;
	GameEngineTextureRenderer* HPMaxNumHun;
	GameEngineTextureRenderer* HPMaxNumTho;

	GameEngineTextureRenderer* MPNumOne;
	GameEngineTextureRenderer* MPNumTen;
	GameEngineTextureRenderer* MPNumHun;
	GameEngineTextureRenderer* MPNumTho;
	GameEngineTextureRenderer* MPNumSlash;
	GameEngineTextureRenderer* MPMaxNumOne;
	GameEngineTextureRenderer* MPMaxNumTen;
	GameEngineTextureRenderer* MPMaxNumHun;
	GameEngineTextureRenderer* MPMaxNumTho;

	GameEngineTextureRenderer* LevelOne;
	GameEngineTextureRenderer* LevelTen;
	GameEngineTextureRenderer* LevelHun;

	GameEngineTextureRenderer* EXPNumOne;
	GameEngineTextureRenderer* EXPNumTen;
	GameEngineTextureRenderer* EXPNumHun;
	GameEngineTextureRenderer* EXPNumTho;
	GameEngineTextureRenderer* EXPNumSlash;
	GameEngineTextureRenderer* EXPMaxNumOne;
	GameEngineTextureRenderer* EXPMaxNumTen;
	GameEngineTextureRenderer* EXPMaxNumHun;
	GameEngineTextureRenderer* EXPMaxNumTho;
};

