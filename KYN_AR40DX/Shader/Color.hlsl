
//SV_POSITION �ø�ƽ �ȼ� �������� �� ���⼭ �������� �����Ͷ������ �Ѿ
//�׷���ī�忡�� �̳༮�� �̷� �η��ϱ� �ϰ� �ڵ����� ó���ϴ� �༮�� ������ �ض�

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
	//���̴��� ��쿡�� ��κ��� ��Ȳ���� ����ȯ�� �����ϴ�
	//0
	Output NewOutput = (Output)0;
	NewOutPut.Pos = _Input.Pos;
	NewOutPut.Color = _Input.Color;

	return NewOutPut;
}

