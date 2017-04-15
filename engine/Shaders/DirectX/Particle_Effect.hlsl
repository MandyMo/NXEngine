/**
 *    File:      Particle_Effect.hlsl
 *  
 *    Date:      2017_04_15
 *    Author:    ’≈–€(zhang xiong, 1025679612@qq.com)
 *    Purpose:   render particle
 */

extern matrix   VPMatrix;
extern texture  ParticleTexture;

struct VS_INPUT {
    vector position : POSITION;
    float2 texCoord	: TEXCOORD0;
};

struct VS_OUTPUT {
    vector position : POSITION;
    float2 texCoord	: TEXCOORD0;
};


struct PS_INTPUT {
    vector position : POSITION;
    float2 texCoord	: TEXCOORD0;
};

struct PS_OUTPUT {
	vector	color	: COLOR0;
};

sampler2D ParticleSampler = sampler_state {
	texture		= <ParticleTexture>;
	MinFilter	= LINEAR;
	MagFilter	= LINEAR;
	MipFilter	= LINEAR;
};

VS_OUTPUT VSMain(VS_INPUT input) {
	VS_OUTPUT o = (VS_OUTPUT)0;
	o.position  = mul(input.position, VPMatrix);
	o.texCoord  = input.texCoord;
	return o;
}

PS_OUTPUT PSMain(PS_INTPUT input) {
	PS_OUTPUT o      = (PS_OUTPUT)0;
	o.color          = tex2D(ParticleSampler, input.texCoord);
	return o;
}

Technique ParticleShader{
	Pass BasePass {
		LIGHTING         = false;
		CULLMODE         = none;
		ALPHABLENDENABLE = true;
		SRCBLENDALPHA    = SRCALPHA;
		DESTBLENDALPHA   = INVSRCALPHA;
		VertexShader  = compile vs_3_0 VSMain();
		PixelShader   = compile ps_3_0 PSMain();
	}
}