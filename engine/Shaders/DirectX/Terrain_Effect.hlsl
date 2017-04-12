/**
 *    File:      Terrain_Effect.hlsl
 *  
 *    Date:      2017_04_10  
 *    Author:    ÕÅÐÛ(zhang xiong, 1025679612@qq.com)
 *    Purpose:   render terrain
 */

extern Matrix ModelMatrix;      // Model => World
extern Matrix ViewMatrix;       // World => View
extern Matrix ProjectMatrix;    // View  => Project plane
extern texture RoadTexture;     // road color
extern texture GrassTexture;    // grass color
extern texture NormalMap;       // normal map

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

sampler2D RoadColorSampler = sampler_state {
	texture		= <RoadTexture>;
	MinFilter	= LINEAR;
	MagFilter	= LINEAR;
	MipFilter	= LINEAR;
};

sampler2D GrassColorSampler = sampler_state {
	texture		= <GrassTexture>;
	MinFilter	= LINEAR;
	MagFilter	= LINEAR;
	MipFilter	= LINEAR;
};

VS_OUTPUT VSMain(VS_INPUT input) {
	VS_OUTPUT o = (VS_OUTPUT)0;
	Matrix MV   = mul(ModelMatrix , ViewMatrix);
	Matrix MVP  = mul(MV, ProjectMatrix);
	o.position  = mul(input.position, MVP);
	o.texCoord  = input.texCoord;
	return o;
}

PS_OUTPUT PSMain(PS_INTPUT input) {
	PS_OUTPUT o      = (PS_OUTPUT)0;
	float3 RoadColor = tex2D(RoadColorSampler, input.texCoord);

	float3 GrassColor= tex2D(GrassColorSampler, input.texCoord);

	o.color.xyz      = RoadColor *0.9 + GrassColor * 0.1;
	return o;
}

Technique TerrainShader{
	Pass BasePass {
		LIGHTING      = false;
		CULLMODE      = none;
		VertexShader  = compile vs_3_0 VSMain();
		PixelShader   = compile ps_3_0 PSMain();
	}
}