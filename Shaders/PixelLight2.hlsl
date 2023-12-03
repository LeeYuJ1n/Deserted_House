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
}

cbuffer PosBuffer : register(b3)
{
	float2 lightPos1;
	float2 lightPos2;
}

float4 Light(float2 uv, float2 lightPos)
{
	float4 albedo = map.Sample(samp, uv);

	float2 pixelCoord = uv * imageSize;
	
	float dist = distance(lightPos, pixelCoord);

	if (dist < range)
		return albedo;

	return float4(albedo.rgb * 0.1f, albedo.a);
}

float LightIntensity(float2 uv, float2 lightPos)
{
	float4 albedo = map.Sample(samp, uv);

	uv.y = 1.0f - uv.y;
	
	float2 pixelCoord = uv * imageSize;
	
	float dist = distance(lightPos, pixelCoord);

	return saturate(range / dist);
}

float4 PS(PixelInput input) : SV_TARGET
{
	float dist1 = LightIntensity(input.uv, lightPos1);
	float dist2 = LightIntensity(input.uv, lightPos2);
	
	float dist = saturate(dist1 + dist2);

	float4 albedo = map.Sample(samp, input.uv);
	
	return float4(albedo.rgb * dist, albedo.a);

}