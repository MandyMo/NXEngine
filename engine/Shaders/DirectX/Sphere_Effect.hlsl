/**
 *    File:      BasevertexShading.hlsl
 *  
 *    Date:      2017_04_22
 *    Author:    ’≈–€(zhang xiong, 1025679612@qq.com)
 *    Purpose:   Render base vertex
 */

 #include "Basic_Lighting.hlsl"

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
#if defined(ENABLE_BASIC_LIGHTING)
	float3  Normal   : NORMAL;
#endif
};

struct VS_OUTPUT {
	float4  Position         : POSITION;
	float2  TexCoord         : TEXCOORD;
#if defined(ENABLE_BASIC_LIGHTING)
	float3  SpecularColor    : COLOR;
#endif
};

struct PS_INPUT {
	float4  Position         : POSITION;
	float2  TexCoord         : TEXCOORD;
#if defined(ENABLE_BASIC_LIGHTING)
	float3  SpecularColor    : COLOR;
#endif
};


struct PS_OUTPUT {
	float4 Color : COLOR;
};

VS_OUTPUT VSMain(VS_INPUT input) {
	VS_OUTPUT o   = (VS_OUTPUT)0;
	o.TexCoord    = input.TexCoord;
	o.Position    = mul(PVMMatrix, input.Position);
#if defined(ENABLE_BASIC_LIGHTING)
	o.SpecularColor = GetSpecularColor(input.Normal, input.Position);
#endif
	return o;
}

PS_OUTPUT PSMain(PS_INPUT input) {
	PS_OUTPUT o      = (PS_OUTPUT)0;
	o.Color          = tex2D(SphereColorSampler, input.TexCoord);
#if defined(ENABLE_BASIC_LIGHTING)
	o.Color.xyz      = o.Color.xyz * AmbientColor + input.SpecularColor;
#endif
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