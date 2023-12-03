struct PixelInput
{
	float4 pos : SV_POSITION;	
};

cbuffer ColorBuffer : register(b0)
{
	float4 color;
}

float4 PS(PixelInput input) : SV_TARGET
{
	return color;
}