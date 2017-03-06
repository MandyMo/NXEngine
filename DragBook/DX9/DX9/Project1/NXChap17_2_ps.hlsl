/**
 *   File:      NXChap17_2_ps.hlsl
 *   
 *   Author:    ’≈–€(1025679612@qq.com)
 *   Date:      2017_03_06
 *   Purpose:   DX9 ps
 */

sampler2D	BaseColor;
sampler2D	GlossColor;


struct PS_INTPUT {
	vector position : POSITION;
	float2 t1		: TEXCOORD0;
	float2 t2		: TEXCOORD1;
};


struct PS_OUTPUT {
	vector	color	: COLOR0;
};

PS_OUTPUT Main(PS_INTPUT input) {
	PS_OUTPUT o = (PS_OUTPUT)0;
	o.color = tex2D(BaseColor, input.t1) * 0.3 + tex2D(GlossColor, input.t2) * 0.7 ;
	return o;
}