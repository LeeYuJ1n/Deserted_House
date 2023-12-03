struct PixelInput
{
	float4 pos : SV_POSITION;
	float2 uv : UV;
};

Texture2D map : register(t0);
SamplerState samp : register(s0);

cbuffer ColorBuffer : register(b0)
{
	float4 color;
}

cbuffer IndexBuffer : register(b1)
{
	int weight;
	int scale;
}

cbuffer SizeBuffer : register(b2)
{
	float2 imageSize;
}

cbuffer OutlineColorBuffer : register(b3)
{
	float4 outlineColor;
}

float4 PS(PixelInput input) : SV_TARGET
{
	float4 albedo = map.Sample(samp, input.uv);
	
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
		return outlineColor;
	
	return albedo * color;
}