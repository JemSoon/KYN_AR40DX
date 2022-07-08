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
	static GameEngineRenderingPipeLine* Create(const std::string& _Name);

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

	// void SetInputAssembler1InputLayOutSetting(const std::string& _Name);

	void SetInputAssembler1VertexBuffer(const std::string& _Name);

	void SetVertexShader(const std::string& _Name);

	void SetInputAssembler2IndexBuffer(const std::string& _Name);

	void SetRasterizer(const std::string& _Name);

	void SetPixelShader(const std::string& _Name);

	void SetOutputMergerBlend(const std::string& _Name);

	void SetOutputMergerDepthStencil(const std::string& _Name);

	void Rendering();

	inline GameEngineVertexShader* GetVertexShader()
	{
		return VertexShader;
	}

protected:

private:
	GameEngineInputLayOut* InputLayOut; //��ǲ����� 1 ����
	
	GameEngineVertexBuffer* VertexBuffer; //��ǲ�����1 ����

	// HLSL�̶�� �ٸ� �� ����ϴ� �ܰ迡��.
	// HLSL�� �׷���ī�忡 Ư�� �����Ϳ� ���� ó�� �ܰ踦 �츮�� ���� �ۼ��ؼ�
	// �׷���ī�忡 �÷��ټ� �ִ� �̴ϴ�.

	//������ �̷��� ó����
	GameEngineVertexShader* VertexShader; //�����Ͷ����� ����

	GameEngineIndexBuffer* IndexBuffer; //��ǲ�����2 ����

	D3D11_PRIMITIVE_TOPOLOGY Topology;// ��ǲ�����2 ����

	GameEngineRasterizer* Rasterizer; //�����Ͷ����� ����

	//�ȼ��� �̷��� ó����
	GameEnginePixelShader* PixelShader; //�ȼ����̴� ����

	GameEngineDepthStencil* DepthStencil; //�ƿ�ǲ���� ���� ������ ����

	GameEngineBlend* Blend; //�ƿ�ǲ ���� �������� ����


	//�ƿ�ǲ ���� �� ����Ÿ�� ������ �̹� �س���
	//����̽��� ����۸� ����ؼ� ���� ����Ÿ���� �Ź� ���õǰ� �ִ�
	//�ű⿡ �׷���
	
	// ���� �������ش�.

	// �Ʒ��� �Լ����� ����
	void InputAssembler1VertexBufferSetting();

	void VertexShaderSetting();

	void InputAssembler2IndexBufferSetting();

	void RasterizerSetting();

	void PixelShaderSetting();

	void OutputMergerBlendSetting();

	void OutputMergerDepthStencilSetting();

	void Draw();
};

