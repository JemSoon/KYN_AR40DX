#include "PreCompile.h"
#include "GameEngineRenderingPipeLine.h"

#include "GameEngineInputLayOut.h"
#include "GameEngineVertexBuffer.h"
#include "GameEngineVertexShader.h"
#include "GameEngineIndexBuffer.h"
#include "GameEngineRasterizer.h"
#include "GameEnginePixelShader.h"
#include "GameEngineDepthStencil.h"
#include "GameEngineBlend.h"

GameEngineRenderingPipeLine::GameEngineRenderingPipeLine()
	: InputLayOut(nullptr)
	, VertexBuffer(nullptr)
	, VertexShader(nullptr)
	, IndexBuffer(nullptr)
	, Rasterizer(nullptr)
	, PixelShader(nullptr)
	, DepthStencil(nullptr)
	, Blend(nullptr)
{

}

GameEngineRenderingPipeLine::~GameEngineRenderingPipeLine()
{

}

void GameEngineRenderingPipeLine::Draw()
{

}

void GameEngineRenderingPipeLine::SetInputAssembler1InputLayOutSetting(const std::string& _Name)
{
	InputLayOut = GameEngineInputLayOut::Find(_Name);
	
	if (nullptr == InputLayOut)
	{
		MsgBoxAssert("존재하지 않는 인풋 레이아웃을 세팅하려고 했습니다.");
		return;
	}
}