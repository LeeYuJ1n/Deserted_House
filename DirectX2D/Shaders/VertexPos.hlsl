cbuffer WorldBuffer : register(b0)
{
	matrix world;
}

cbuffer ViewBuffer : register(b1)
{
	matrix view;
}

cbuffer ProjectionBuffer : register(b2)
{
	matrix projection;
}

struct VertexInput
{
	float4 pos : POSITION;	
};

struct VertexOutput
{
	float4 pos : SV_POSITION;	
};

VertexOutput VS(VertexInput input)
{
	VertexOutput output;
	output.pos = mul(input.pos, world);
	output.pos = mul(output.pos, view);
	output.pos = mul(output.pos, projection);	
	
	return output;
}