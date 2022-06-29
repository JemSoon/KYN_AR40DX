#pragma once
#include "GameEngineRes.h"

//���� : Res�� ��ӹ޾Ƽ� ���� �������� �� ����ִ� ����������

class GameEngineInputLayOut;
class GameEngineVertexBuffer;
class GameEngineVertexShader;
class GameEngineIndexBuffer;
class GameEngineRasterizer;
class GameEnginePixelShader;
class GameEngineDepthStencil;
class GameEngineBlend;
class GameEngineRenderingPipeLine :public GameEngineRes<GameEngineRenderingPipeLine>
{
public:
	//����Ʈ ������
	GameEngineRenderingPipeLine();
	//����Ʈ �Ҹ���
	~GameEngineRenderingPipeLine();

	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	GameEngineRenderingPipeLine(const GameEngineRenderingPipeLine& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	GameEngineRenderingPipeLine(GameEngineRenderingPipeLine&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	GameEngineRenderingPipeLine& operator=(const GameEngineRenderingPipeLine& _Other) = delete;
	GameEngineRenderingPipeLine& operator=(GameEngineRenderingPipeLine&& _Other) noexcept = delete;

	void Draw();

protected:
	GameEngineInputLayOut* InputLayOut; //��ǲ����� 1 ����
	
	GameEngineVertexBuffer* VertexBuffer; //��ǲ�����1 ����

	GameEngineVertexShader* VertexShader; //�����Ͷ����� ����

	GameEngineIndexBuffer* IndexBuffer; //��ǲ�����2 ����

	GameEngineRasterizer* Rasterizer; //�����Ͷ����� ����

	GameEnginePixelShader* PixelShader; //�ȼ����̴� ����

	GameEngineDepthStencil* DepthStencil; //�ƿ�ǲ���� ���� ������ ����

	GameEngineBlend* Blend; //�ƿ�ǲ ���� �������� ����

	//�ƿ�ǲ ���� �� ����Ÿ�� ������ �̹� �س���
	//����̽��� ����۸� ����ؼ� ���� ����Ÿ���� �Ź� ���õǰ� �ִ�
	//�ű⿡ �׷���

private:
	void SetInputAssembler1InputLayOutSetting(const std::string& _Name);
	
	void SetInputAssembler1VertexBufferSetting(const std::string& _Name);

	void SetVertexShader(const std::string& _Name);

	void SetInputAssembler2IndexBufferSetting(const std::string& _Name);

	void SetRasterizer(const std::string& _Nmae);

	void SetPixelShader(const std::string& _Name);

	void SetOutputMergerBlend(const std::string& _Name);

	void SetOutputMergerDepthStencilSetting(const std::string& _Name);

};

