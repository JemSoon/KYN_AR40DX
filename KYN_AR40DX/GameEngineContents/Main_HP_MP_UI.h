#pragma once
#include <GameEngineCore/GameEngineActor.h>

//���� : �ΰ��� ȭ�� �ϴ� �߾ӿ� ������ ü�� ���� ui
class GameEngineTextureRenderer;
class Player;
class Main_HP_MP_UI : public GameEngineActor
{
public:
	//����Ʈ ������
	Main_HP_MP_UI();
	//����Ʈ �Ҹ���
	~Main_HP_MP_UI();

	
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

	void HPSetting();
	void EXPSetting();
	void LevelSetting();
	void MPSetting();
	void HPNumberSetting();
	void MPNumberSetting();
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
	GameEngineTextureRenderer* LevelNum;

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
};

