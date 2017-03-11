/**
 *   File:      NXChap2_1_effect.hlsl
 *   
 *   Author:    ’≈–€(1025679612@qq.com)
 *   Date:      2017_03_08
 *   Purpose:   DX9 effect file
 */

extern matrix	WorldMatrix;
extern matrix	ViewProjectMatrix;
extern float3	LightPosition;
extern texture	BaseColor;


sampler BaseColorSampler = sampler_state {
	texture			= <BaseColor>;
	MinFilter		= LINEAR;
	MagFilter		= LINEAR;
	MipFilter		= LINEAR;
	AddressU		= WRAP;     
	AddressV		= WRAP;    
	AddressW		= WRAP;
	MaxAnisotropy	= 16;
};

struct VS_INPUT {
	float4	Position	:	POSITION;
	float3	Normal		:	NORMAL;	
	float2	TexCord		:	TEXCOORD;
};

struct VS_OUTPUT {
	float4	Position	:	POSITION;
	float2	TexCord		:	TEXCOORD0;
	float	Shadow		:	TEXCOORD1;
};

struct PS_INPUT {
	float4	Position	:	POSITION;
	float2	TexCord		:	TEXCOORD;
	float	Shadow		:	TEXCOORD1;
};

struct PS_OUTPUT {
	vector	ShadedColor	:	COLOR;	
};

VS_OUTPUT VSMain(VS_INPUT input) {
	VS_OUTPUT o = (VS_OUTPUT)0;
	float4	WorldPosition	= mul(input.Position, WorldMatrix);
	float4	WorldNormal		= normalize(mul(input.Normal, WorldMatrix));
	o.Position				= mul(WorldPosition, ViewProjectMatrix);
	o.Shadow				= max(dot(WorldNormal, normalize(LightPosition - WorldPosition)), 0.2);
	o.TexCord				= input.TexCord;
	return o;
}

PS_OUTPUT PSMainLight(PS_INPUT input) {
	PS_OUTPUT	o	=	(PS_OUTPUT)0;
	o.ShadedColor	=	tex2D(BaseColorSampler, input.TexCord) * input.Shadow;
	return o;
}

PS_OUTPUT PSMainShadow(PS_INPUT input){
	PS_OUTPUT o		=	(PS_OUTPUT)0;
	o.ShadedColor	=	input.Shadow;
	return o;
}

Technique Lighting {
	pass P0 {
		Lighting = false;
		VertexShader	= compile vs_2_0 VSMain();
		PixelShader		= compile ps_2_0 PSMainLight();
	}
}

Technique Shadow {
	pass P0 {
	   Lighting			=	false;
	   VertexShader		=	compile vs_2_0 VSMain();
	   PixelShader		=	compile ps_2_0 PSMainShadow();
	}
}