#pragma once
#include "GameEngineRes.h"

// �������ٽ� �����̶�
// �������ٽ� �ؽ�ó��



// ���� : ���� �ȼ����̴��� ��°���� ����Ÿ�ٿ� ����Ҷ� ���� ���̰� ���� �������� ���� ó��
//		  ���� ���ٽ� ����
class GameEngineDepthStencil : public GameEngineRes<GameEngineDepthStencil>
{
	//public:
	//	static GameEngineDepthStencil* Create(const float4 _Scale);

public:
	// constrcuter destructer
	GameEngineDepthStencil();
	~GameEngineDepthStencil();

	// delete Function
	GameEngineDepthStencil(const GameEngineDepthStencil& _Other) = delete;
	GameEngineDepthStencil(GameEngineDepthStencil&& _Other) noexcept = delete;
	GameEngineDepthStencil& operator=(const GameEngineDepthStencil& _Other) = delete;
	GameEngineDepthStencil& operator=(GameEngineDepthStencil&& _Other) noexcept = delete;

protected:

private:

};

