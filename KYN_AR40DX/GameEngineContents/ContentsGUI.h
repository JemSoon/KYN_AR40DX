#pragma once
#include <GameEngineCore/GameEngineStatusWindow.h>

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : 
class Player;
class LevelParent;
class ContentsGUI : public GameEngineStatusWindow
{
public:
	//����Ʈ ������
	ContentsGUI();
	//����Ʈ �Ҹ���
	~ContentsGUI();

	
	
	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	ContentsGUI(const ContentsGUI& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	ContentsGUI(ContentsGUI&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	ContentsGUI& operator=(const ContentsGUI& _Other) = delete;
	ContentsGUI& operator=(ContentsGUI&& _Other) noexcept = delete;


protected:
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;
private:
	Player* PlayerInfo;
};

