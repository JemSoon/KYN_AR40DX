#pragma once
#include <GameEngineCore/CoreMinimal.h>

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : ����Ʈ ��ȭâ
class GameEngineUIRenderer;
class Dialogue : public GameEngineActor
{
public:
	//����Ʈ ������
	Dialogue();
	//����Ʈ �Ҹ���
	~Dialogue();

	
	
	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	Dialogue(const Dialogue& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	Dialogue(Dialogue&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	Dialogue& operator=(const Dialogue& _Other) = delete;
	Dialogue& operator=(Dialogue&& _Other) noexcept = delete;

	bool MouseHit(GameEngineCollision* _This, GameEngineCollision* _Other);
protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

	GameEngineUIRenderer* Chat;
	GameEngineUIRenderer* Exit;
	GameEngineCollision* ExitCollision;
private:

};

