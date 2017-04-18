/**
 *    File:      SkyBox_Effect.hlsl
 *  
 *    Date:      2017_04_13  
 *    Author:    ’≈–€(zhang xiong, 1025679612@qq.com)
 *    Purpose:   Sky Box Shader
 */

extern texture SkyColorTexture;
extern matrix VPMatrix;

struct VS_INPUT {
    vector Position: POSITION;
	float2 TexCoord: TEXCOORD;
};

struct VS_OUTPUT {
	vector Position : POSITION;
    float2 TexCoord : TEXCOORD;
};


struct PS_INTPUT {
	vector Position : POSITION;
    float2 TexCoord : TEXCOORD;
};

struct PS_OUTPUT {
	vector	color	: COLOR0;
};

sampler2D SkyColorSampler = sampler_state {
	texture		= <SkyColorTexture>;
	MinFilter	= LINEAR;
	MagFilter	= LINEAR;
	MipFilter	= LINEAR;
	AddressU    = Mirror; 
    AddressV    = Mirror; 
};

VS_OUTPUT VSMain(VS_INPUT input) {
	VS_OUTPUT o = (VS_OUTPUT)0;
	o.TexCoord  = input.TexCoord;
	o.Position  = mul(input.Position, VPMatrix);
	return o;
}

PS_OUTPUT PSMain(PS_INTPUT input) {
	PS_OUTPUT o      = (PS_OUTPUT)0;
	o.color          = tex2D(SkyColorSampler, input.TexCoord);
	return o;
}

Technique SkyBoxShader{
	Pass BasePass {
		LIGHTING           = false;
		CULLMODE           = none;
		ALPHABLENDENABLE   = false;
		VertexShader       = compile vs_3_0 VSMain();
		PixelShader        = compile ps_3_0 PSMain();
	}
}