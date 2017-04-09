/**
 *    File:      Terrain_Effect.hlsl
 *  
 *    Date:      2017_04_10  
 *    Author:    ’≈–€(zhang xiong, 1025679612@qq.com)
 *    Purpose:   render terrain
 */


struct VS_INPUT {
    vector position : POSITION;
    float2 texCoord	: TEXCOORD0;
	float3 Normal   : NORMAL;
};

struct VS_OUTPUT {
    vector position : POSITION;
    float2 texCoord	: TEXCOORD0;
	float3 Normal   : NORMAL;
};


struct PS_INTPUT {
    vector position : POSITION;
    float2 texCoord	: TEXCOORD0;
	float3 Normal   : NORMAL;
};

struct PS_OUTPUT {
	vector	color	: COLOR0;
};

texture BaseColor;

sampler2D BaseColorSampler = sampler_state {
	texture		= <BaseColor>;
	MinFilter	= LINEAR;
	MagFilter	= LINEAR;
	MipFilter	= LINEAR;
};

VS_OUTPUT VSMain(VS_INPUT input) {
	VS_OUTPUT o = (VS_OUTPUT)0;
	return o;
}

PS_OUTPUT PSMain(PS_INTPUT input) {
	PS_OUTPUT o = (PS_OUTPUT)0;
	return o;
}

Technique TerrainShader{
	Pass BasePass {
	   VertexShader  = compile vs_2_0 VSMain();
	   PixelShader   = compile ps_2_0 PSMain();
	}
}