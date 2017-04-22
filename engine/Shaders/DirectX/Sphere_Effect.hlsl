/**
 *    File:      BasevertexShading.hlsl
 *  
 *    Date:      2017_04_22
 *    Author:    ’≈–€(zhang xiong, 1025679612@qq.com)
 *    Purpose:   Render base vertex
 */

extern matrix  ModelMatrix;
extern matrix  ViewMatrix;
extern matrix  ProjectMatrix;
extern matrix  PVMMatrix;
extern texture BaseColor;

sampler2D SphereColorSampler = sampler_state{
	texture     = <BaseColor>;
	MinFilter	= LINEAR;
	MagFilter	= LINEAR;
	MipFilter	= LINEAR;
	AddressU    = Mirror; 
    AddressV    = Mirror; 
};

struct VS_INPUT {
	float4  Position : POSITION;
	float2  TexCoord : TEXCOORD;
	float3  Normal   : NORMAL;
};

struct VS_OUTPUT {
	float4  Position : POSITION;
	float2  TexCoord : TEXCOORD;
	float3  Normal   : NORMAL;
};

struct PS_INPUT {
	float4  Position : POSITION;
	float2  TexCoord : TEXCOORD;
	float3  Normal   : NORMAL;
};


struct PS_OUTPUT {
	float4 Color : COLOR;
};

VS_OUTPUT VSMain(VS_INPUT input) {
	VS_OUTPUT o   = (VS_OUTPUT)0;
	o.TexCoord    = input.TexCoord;
	o.Position    = mul(PVMMatrix, input.Position);
	o.Normal      = input.Normal;
	return o;
}

PS_OUTPUT PSMain(PS_INPUT input) {
	PS_OUTPUT o      = (PS_OUTPUT)0;
	o.Color          = tex2D(SphereColorSampler, input.TexCoord);
	return o;
}

Technique Cube3DShader{
	Pass BasePass {
		LIGHTING           = false;
		CULLMODE           = none;
		ALPHABLENDENABLE   = false;
		VertexShader       = compile vs_3_0 VSMain();
		PixelShader        = compile ps_3_0 PSMain();
	}
}