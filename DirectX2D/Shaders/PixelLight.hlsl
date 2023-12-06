//PixelLight.hlsl

struct PixelInput
{
	float4 pos : SV_POSITION;
	float2 uv : UV;
};

Texture2D map : register(t0);
SamplerState samp : register(s0);

cbuffer IndexBuffer : register(b1)
{
	int index;
	int range;	
	int squared;
}

cbuffer SizeBuffer : register(b2)
{
	float2 imageSize;
	float2 lightPos;
}

float4 Light(float2 uv)
{
	float4 albedo = map.Sample(samp, uv);

	float2 pixelCoord = uv * imageSize;
	
	float dist = distance(lightPos, pixelCoord);

	if (dist < range)
		return albedo;

	return float4(albedo.rgb * 0.1f, albedo.a);
}

float4 LightIntensity(float2 uv)
{
	float4 albedo = map.Sample(samp, uv);

	float2 pixelCoord = uv * imageSize;
	
	float dist = distance(lightPos, pixelCoord);

	float value = saturate(dist / range);
	
	float3 color = albedo.rgb - pow(value, (float)squared / 10.0f);

	return float4(color, albedo.a);
}

float4 PS(PixelInput input) : SV_TARGET
{
	if (index == 1)
		return LightIntensity(input.uv);
		
	return Light(input.uv);
}