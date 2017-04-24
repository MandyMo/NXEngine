/**
 *    File:      Basic_Lighting.hlsl
 *  
 *    Date:      2017_04_10  
 *    Author:    ÕÅÐÛ(zhang xiong, 1025679612@qq.com)
 *    Purpose:   render terrain
 */

 #if defined(ENABLE_BASIC_LIGHTING)

 extern matrix   RModelMatrix;   // the reverse of Model -> View space transform matrix
 extern float3   EyePotion;      // the position of camera
 extern float4   LightPosition;  // the position of light, if LightPosition.w is 1, then it's point light, else it's directional light
 extern float3   AmbientColor;   // the ambient color
 extern float3   LightColor;     // the light's color

float3 GetSpecularColor(float3 Normal, float3 Position){
	float3 P2E         = EyePotion - Position;
	float3 WorldNormal = mul(float4(Normal, 0.f), RModelMatrix);
	float3 P2L;
	if( LightPosition.w > 0.f ) {
		P2L = LightPosition.xyz - Position;
	} else {
		P2L = LightPosition;
	}

	float3 HalfNormal = normalize(P2L + P2E);
	
	return saturate(dot(HalfNormal, WorldNormal)) * LightColor;
}

 #endif