

cbuffer		cbRarelyChanged
{
	float4x4		gView_Projection;		//�� �۲�ռ� �� ��βü��ռ�		���ֱܷ���Ӱ�죩
};

cbuffer		cbPerObject
{
	float4x4		gLocal_World;				//�� ���ؿռ� �� ����ռ�				��������״̬Ӱ�죩
};

Texture2D	gSpriteMap;

cbuffer		cbPerFrame
{
	float4x4		gWorld_View;				//�� ����ռ� �� �۲�ռ�				���������״̬Ӱ�죩
};

SamplerState	sAnisotropic
{
	Filter						= ANISOTROPIC;
	MaxAnisotropy		= 4;
	AddressU					= Wrap;
	AddressV					= Wrap;
};

struct VertexIn
{
	float2 localPosition			: POSITION;
	float2 textureCoord			: TEXCOORD;
};

struct VertexOut
{
	float4 projPosition			: SV_POSITION;
	float2 textureCoord			: TEXCOORD;
};

VertexOut VS(VertexIn vin)
{
	VertexOut vout;

	vout.projPosition = mul(float4(vin.localPosition, 0.0f, 1.0f), gLocal_World);
	vout.projPosition = mul(vout.projPosition, gWorld_View);
	vout.projPosition = mul(vout.projPosition, gView_Projection);

	vout.textureCoord = vin.textureCoord;

	return vout;
}

float4 PS(VertexOut pin) : SV_TARGET
{
	return gSpriteMap.Sample(sAnisotropic, pin.textureCoord);
}

technique11 LookDown2DSprite
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_5_0, PS()));
	}
};