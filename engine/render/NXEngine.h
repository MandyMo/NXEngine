/*
*  File:    NXEngine.h
*
*  author:  张雄(zhang xiong, 1025679612@qq.com)
*  date:    2017_04_10
*  purpose: define engine class
*/


#pragma once

#include "../math/NXVector.h"

namespace NX {
	class Engine {

	};

	struct RenderParameter {
		class MVMatrixController  *pMVController;
		class ProjectController   *pProjectController;
		class IDirect3DDevice9    *pDXDevice;
		class IDirect3D9          *pDirectX;
		float4                    LightPosition;
		float3                    AmbientColor;
		float3                    LightColor;
	};
}