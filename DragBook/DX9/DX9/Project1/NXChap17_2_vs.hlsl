/**
 *   File:      NXChap17_2_vs.hlsl
 *   
 *   Author:    ’≈–€(1025679612@qq.com)
 *   Date:      2017_03_06
 *   Purpose:   DX9 vs
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

VS_OUTPUT Main(VS_INPUT input) {
	VS_OUTPUT o = (VS_OUTPUT)0;
	o.position	= mul(input.position, ViewProjMatrix);
	o.t1		= input.t1;
	o.t2		= input.t2;
	return o;
}