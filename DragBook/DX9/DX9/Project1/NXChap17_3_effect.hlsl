/**
 *   File:      NXChap17_3_effect.hlsl
 *   
 *   Author:    ’≈–€(1025679612@qq.com)
 *   Date:      2017_03_08
 *   Purpose:   DX9 effect file
 */

extern matrix ViewProjMatrix;

struct VS_INPUT {
    vector position : POSITION;
    float2  t1		: TEXCOORD0;
	float2  t2		: TEXCOORD1;
};

struct VS_OUTPUT {
	vector position : POSITION;
	float2 t1		: TEXCOORD0;
	float2 t2		: TEXCOORD1;
};

VS_OUTPUT VSMainA(VS_INPUT input) {
	VS_OUTPUT o = (VS_OUTPUT)0;
	o.position	= mul(input.position, ViewProjMatrix);
	o.t1		= input.t1;
	o.t2		= input.t2;
	o.position.xy -= 0.5;
	return o;
}

VS_OUTPUT VSMainB(VS_INPUT input) {
	VS_OUTPUT o = (VS_OUTPUT)0;
	o.position	= mul(input.position, ViewProjMatrix);
	o.t1		= input.t1;
	o.t2		= input.t2;

	o.position.xy += 0.5;

	return o;
}

texture BaseColor;
texture GlossColor;

sampler2D BaseColorSampler = sampler_state {
	texture		= <BaseColor>;
	MinFilter	= LINEAR;
	MagFilter	= LINEAR;
	MipFilter	= LINEAR;
};

sampler2D GlossColorSampler = sampler_state {
	texture		= <GlossColor>;
	MinFilter	= LINEAR;
	MagFilter	= LINEAR;
	MipFilter	= LINEAR;
};


struct PS_INTPUT {
	vector position : POSITION;
	float2 t1		: TEXCOORD0;
	float2 t2		: TEXCOORD1;
};


struct PS_OUTPUT {
	vector	color	: COLOR0;
};

PS_OUTPUT PSMain(PS_INTPUT input) {
	PS_OUTPUT o = (PS_OUTPUT)0;
	o.color = tex2D(BaseColorSampler, input.t1) * 0.3 + tex2D(GlossColorSampler, input.t2) * 0.7 ;
	return o;
}

Technique T {
	Pass P {
	   VertexShader  = compile vs_2_0 VSMainA();
	   PixelShader   = compile ps_2_0 PSMain();
	}

	Pass Q {
	   VertexShader  = compile vs_2_0 VSMainB();
	   PixelShader	 = compile ps_2_0 PSMain();		
	}
}