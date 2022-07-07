#pragma once
#include "GameEngineRes.h"

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : 
class GameEngineRasterizer : public GameEngineRes<GameEngineRasterizer>
{
public:
	static GameEngineRasterizer* Create(const std::string& _Name, const D3D11_RASTERIZER_DESC& _Desc);

public:
	//����Ʈ ������
	GameEngineRasterizer();
	//����Ʈ �Ҹ���
	~GameEngineRasterizer();
	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	GameEngineRasterizer(const GameEngineRasterizer& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	GameEngineRasterizer(GameEngineRasterizer&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	GameEngineRasterizer& operator=(const GameEngineRasterizer& _Other) = delete;
	GameEngineRasterizer& operator=(GameEngineRasterizer&& _Other) noexcept = delete;


	void Setting();

protected:

private:
	D3D11_RASTERIZER_DESC Desc;
	ID3D11RasterizerState* State;
	// D3D11_RASTERIZER_DESC WireDesc_;

	void Create(const D3D11_RASTERIZER_DESC& _Desc);
};

