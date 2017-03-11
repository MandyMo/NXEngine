
/**
 *  File:      NXChap2_1.h
 *
 *  Author:    张雄(zhangxiong 1025679612@qq.com)
 *  Date:	   2017_03_08
 *  Purpose:   DX9 X File test
 */

#pragma once

#include "..\..\NXDX9Window.h"
#include <vector>
#include <string>

namespace NX {
	class NXChap3_1 : public NX::DX9Window {
	public:
		NXChap3_1();
		virtual ~NXChap3_1();
	public:
		struct Vertex {
		public:
			Vertex(float _x, float _y, float _z, DWORD _dwColor): x(_x), y (_y), z(_z), dwColor(_dwColor){}
		public:
			float x, y, z;
			DWORD	dwColor;
		};
	public:
		class MeshLoader;
		class Bone;
		class Mesh;
	public:
		virtual void PostRender();
		virtual void PreRender();
		virtual void Render();

	private:
		virtual void OnInitDX3Succeed();
		virtual void OnTick(NXUInt32 uDelta);

	private:
		Mesh			*m_pMesh;
	};
}