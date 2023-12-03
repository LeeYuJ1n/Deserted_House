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
	int index;
	int scale;
	int radialScale1;
	int radialScale2;
}

cbuffer SizeBuffer : register(b2)
{
	float2 imageSize;
}

float4 Grayscale(float4 albedo)
{
	//float scale = (albedo.r + albedo.g + albedo.b) / 3;
	
	//float3 grayColor;
	//grayColor.r = albedo.r * 0.3f;
	//grayColor.g = albedo.g * 0.59f;
	//grayColor.b = albedo.b * 0.11f;
	//
	//float scale = grayColor.r + grayColor.g + grayColor.b;
	
	float scale = dot(albedo.rgb, float3(0.3f, 0.59f, 0.11f));
	
	return float4(scale.xxx, albedo.a);
}

float4 Sepia(float4 albedo)
{
	float4 sepia;
	
	sepia.a = albedo.a;
	
	sepia.r = dot(albedo.rgb, float3(0.393f, 0.769f, 0.189f));
	sepia.g = dot(albedo.rgb, float3(0.349f, 0.646f, 0.168f));
	sepia.b = dot(albedo.rgb, float3(0.272f, 0.534f, 0.131f));

	return sepia;
}

float4 Mosaic(float2 uv)
{
	float2 temp = floor(uv * scale) / scale;
	
	return map.Sample(samp, temp);
}

float4 Blur(float2 uv)
{
	float4 result = 0;
	
	for (int i = 0; i < scale; i++)
	{
		float2 div = (1 + i) / imageSize;
		
		result += map.Sample(samp, float2(uv.x + div.x, uv.y)); //R
		result += map.Sample(samp, float2(uv.x - div.x, uv.y)); //L
		result += map.Sample(samp, float2(uv.x, uv.y + div.y)); //D
		result += map.Sample(samp, float2(uv.x, uv.y - div.y)); //U
	}
	
	result /= scale * 4;
	
	return result;
}

static const float2 edges[8] =
{
	float2(-1, -1), float2(0, -1), float2(1, -1),
	float2(-1, 0), float2(1, 0),
	float2(-1, 1), float2(0, 1), float2(1, 1)
};

float4 Blur2(float2 uv)
{
	float4 result = 0;
	
	//[unroll(4)]
	for (int i = 0; i < scale; i++)
	{
		float2 div = (1 + i) / imageSize;
		
		for (int j = 0; j < 8; j++)
		{
			float2 xy = edges[j] * div + uv;
			
			result += map.Sample(samp, xy);
		}
	}
	
	result /= scale * 8;
	
	return result;
}

static const float weights[13] =
{
	0.0561f, 0.1353f, 0.2730f, 0.4868f, 0.7261f, 0.9231f,
	1.0f,
	0.9231f, 0.7261f, 0.4868f, 0.2730f, 0.1353f, 0.0561f
};

float4 GaussianBlur(float2 uv)
{
	float2 div = 1.0f / imageSize;
	
	float sum = 0.0f;
	float4 result = 0;
	
	for (int i = -6; i <= 6; i++)
	{
		float2 temp = uv + float2(div.x * i, 0);
		result += weights[6 + i] * map.Sample(samp, temp);
		
		temp = uv + float2(0, div.y * i);
		result += weights[6 + i] * map.Sample(samp, temp);

		sum += weights[6 + i] * 2.0f;
	}
	
	result /= sum;
	
	return result;
}

float4 RadialBlur(float2 uv)
{
	float2 radiusUV = uv - float2(0.5f, 0.5f);
	float r = length(radiusUV);
	radiusUV /= r;
	
	r = saturate(r / radialScale1);
	
	float2 delta = -radiusUV * r * r * radialScale2 / scale;
	
	float4 result = 0;
	
	for (int i = 0; i < scale; i++)
	{
		result += map.Sample(samp, uv);
		uv += delta;
	}
	
	result /= scale;
	
	return result;
}

float4 PS(PixelInput input) : SV_TARGET
{
	float4 tex = map.Sample(samp, input.uv);
	
	if (index == 1)
		return Grayscale(tex) * color;
	else if (index == 2)
		return Sepia(tex) * color;
	else if (index == 3)
		return Mosaic(input.uv) * color;
	else if (index == 4)
		return Blur(input.uv) * color;
	else if (index == 5)
		return Blur2(input.uv) * color;
	else if (index == 6)
		return GaussianBlur(input.uv) * color;
	else if (index == 7)
		return RadialBlur(input.uv) * color;
	
	return tex * color;
}