#pragma once
#include "GameEngineRenderer.h"
#include "GameEngineShaderResourcesHelper.h"

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : 
class GameEngineRenderingPipeLine;
class GameEngineDefaultRenderer : public GameEngineRenderer
{
	//������ ���������� �ϳ���
	//�ϳ��� �޽�, �ϳ��� ���׸���, �ϳ��� ����Ÿ�� ��Ʈ

public:
	GameEngineShaderResourcesHelper ShaderResources;

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

	void SetPipeLine(const std::string& _Name);

	GameEngineRenderingPipeLine* GetPipeLine();

protected:
	virtual void Start();
	virtual void Update(float _DeltaTime) {}
	virtual void End() {}

private:
	//�׸� �������� ����Ѵ� ���..
	// �������� �޸� �����ϴ� �޷θ����� ��� �ְ�
	GameEngineRenderingPipeLine* PipeLine;
};

