
//SV_POSITION 시맨틱 픽셀 건져내는 애 여기서 건져져야 래스터라이즈로 넘어감
//그래픽카드에게 이녀석은 이런 부류니까 니가 자동으로 처리하는 녀석이 있으면 해라

struct Input
{
	float4 Pos	 : POSITION;
	float4 Color : COLOR;
};

struct Output
{
	float4 Pos	 : SV_POSITION;
	float4 Color : COLOR;
};

Output VS_Color(Input _Input)
{
	//쉐이더의 경우에는 대부분의 상황에서 형변환이 가능하다
	//0
	Output NewOutput = (Output)0;
	NewOutPut.Pos = _Input.Pos;
	NewOutPut.Color = _Input.Color;

	return NewOutPut;
}

