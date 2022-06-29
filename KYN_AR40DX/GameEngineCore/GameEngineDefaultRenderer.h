#pragma once
#include "GameEngineRenderer.h"

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : 
class GameEngineDefaultRenderer : public GameEngineRenderer
{
	//������ ���������� �ϳ���
	//�ϳ��� �޽�, �ϳ��� ���׸���, �ϳ��� ����Ÿ�� ��Ʈ

public:
	//����Ʈ ������
	GameEngineDefaultRenderer();
	//����Ʈ �Ҹ���
	~GameEngineDefaultRenderer();
	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	GameEngineDefaultRenderer(const GameEngineDefaultRenderer& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	GameEngineDefaultRenderer(GameEngineDefaultRenderer&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	GameEngineDefaultRenderer& operator=(const GameEngineDefaultRenderer& _Other) = delete;
	GameEngineDefaultRenderer& operator=(GameEngineDefaultRenderer&& _Other) noexcept = delete;

	virtual void Render(float _DeltaTime);//GameEngineRenderer�� ���������Լ��� �ΰ� �������� ���빰�� ����Ʈ������(����)

protected:
	virtual void Start();
	virtual void Update(float _DeltaTime) {}
	virtual void End() {}

private:
	//�׸� �������� ����Ѵ� ���..
	GameEngineRenderingPipeLine* PipeLine;
};

