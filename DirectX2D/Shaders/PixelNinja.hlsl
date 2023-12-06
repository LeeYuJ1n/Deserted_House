struct PixelInput
{
	float4 pos : SV_POSITION;
	float2 uv : UV;
};

Texture2D map : register(t0);
Texture2D secondMap : register(t1);

SamplerState samp : register(s0);

cbuffer IndexBuffer : register(b1)
{
	int weight;
	int scale;
}

cbuffer SizeBuffer : register(b2)
{
	float2 imageSize;
}

float4 PS(PixelInput input) : SV_TARGET
{	
	float4 color = map.Sample(samp, input.uv);
	
	float count = 0;
	
	for (int y = -1; y <= 1; y++)
	{
		for (int x = -1; x <= 1; x++)
		{
			float2 offset = (float2(x, y) / imageSize) * weight;
			count += map.Sample(samp, input.uv + offset).a;
		}
	}
	
	if (count > scale && count < (9 - scale))
		return secondMap.Sample(samp, input.uv);
	
	return color;
}