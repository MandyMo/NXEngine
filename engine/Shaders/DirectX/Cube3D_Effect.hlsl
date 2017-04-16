/**
 *    File:      Cube3D_Effect.hlsl
 *  
 *    Date:      2017_04_10  
 *    Author:    ’≈–€(zhang xiong, 1025679612@qq.com)
 *    Purpose:   render Cube3D
 */

extern matrix MVP;
extern texture BaseColor;

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

sampler2D BaseColorSampler = sampler_state {
	texture		= <BaseColor>;
	MinFilter	= LINEAR;
	MagFilter	= LINEAR;
	MipFilter	= LINEAR;
};

VS_OUTPUT VSMain(VS_INPUT input) {
	VS_OUTPUT o = (VS_OUTPUT)0;
	o.position  = mul(input.position, MVP);
	o.texCoord  = input.texCoord;
	return o;
}

PS_OUTPUT PSMain(PS_INTPUT input) {
	PS_OUTPUT o      = (PS_OUTPUT)0;
	o.color.rgb          = tex2D(BaseColorSampler, input.texCoord).rgb;
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