//Global variables


cbuffer CB0
{
	matrix WVPMatrix;				//	64 bytes
	float4 directional_light_vector;//  16 bytes
	float4 directional_light_colour;//  16 bytes
	float4 ambient_light_colour;	//  16 bytes
};	// TOTAL SIZE = 112 bytes

Texture2D	 texture0;
SamplerState sampler0;

struct VOut
{
	float4 position : SV_POSITION;
	float4 color	: COLOR;//Note the spelling of this and all instances below
	float2 texcoord : TEXCOORD;
	float3 normal	: NORMAL;
	float3 tangent	: TANGENT;
	float3 binormal : BINORMAL;
};

VOut ModelVS(float4 position : POSITION, float2 texcoord : TEXCOORD, float3 normal : NORMAL)
{
	
	VOut output;  
	
	//input.position.w = 1.0f;

	float4 default_color	= { 1.0f,1.0f,1.0f,1.0f };
	output.position			= mul(WVPMatrix, position);

	float diffuse_amount = dot(directional_light_vector, normal);

	diffuse_amount = saturate(diffuse_amount);

	output.color = ambient_light_colour + (directional_light_colour * diffuse_amount);

	output.texcoord			= texcoord;
	
	//output.normal = mul(output.normal, WVPMatrix);
	//output.normal = normalize(output.normal);

	//output.tangent = mul(output.tangent, WVPMatrix);
	//output.tangent = normalize(output.tangent);

	//// Calculate the binormal vector against the world matrix only and then normalize the final value.
	//output.binormal = mul(output.binormal, WVPMatrix);
	//output.binormal = normalize(output.binormal);

	return output;
}

float4 ModelPS(float4 position : SV_POSITION, float4 color : COLOR, float2 texcoord : TEXCOORDS) : SV_TARGET
{
	return texture0.Sample(sampler0,texcoord) * color;
}
