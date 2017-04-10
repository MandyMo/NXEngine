/**
 *    File:      Terrain_Effect.hlsl
 *  
 *    Date:      2017_04_10  
 *    Author:    ÕÅÐÛ(zhang xiong, 1025679612@qq.com)
 *    Purpose:   render terrain
 */

extern Matrix ModelMatrix;      // Model => World
extern Matrix ViewmMatrix;      // World => View
extern Matrix ProjectMatrix;    // View  => Project plane
extern texture BaseColor;       // grass color
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
	Matrix MV   = ModelMatrix * ViewmMatrix;
	Matrix MVP  = ModelMatrix * ViewmMatrix * ProjectMatrix;
	o.position  = mul(input.position, MVP);
	return o;
}

PS_OUTPUT PSMain(PS_INTPUT input) {
	PS_OUTPUT o = (PS_OUTPUT)0;
	o.color     = tex2D(BaseColorSampler, input.texCoord);
	return o;
}

Technique TerrainShader{
	Pass BasePass {
		FILLMODE      = WIREFRAME;
		LIGHTING      = false;
		VertexShader  = compile vs_3_0 VSMain();
		PixelShader   = compile ps_3_0 PSMain();
	}
}