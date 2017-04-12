/*
*  File:    NXCube.h
*
*  author:  张雄(zhang xiong, 1025679612@qq.com)
*  date:    2017_04_12
*  purpose: define a cube
*/

#pragma once

#include "NXIEntity.h"
#include <d3d9.h>
#include <d3dx9.h>

namespace NX {
	class Cube : public IEntity {
	public:
		Cube(const Size3D &_size = float3(1.f, 1.f, 1.f));
		virtual ~Cube();

	public:
		virtual void Render() override;
		virtual ENTITY_TYPE GetEntityType() override;
		virtual void OnTick(const int dwMillSeconds) override;
	
	private:
		struct Vertex;

	private:
		Size3D				           m_Size;
		IDirect3DIndexBuffer9          *m_pIndexBuffer;
		IDirect3DVertexBuffer9         *m_pVertexBuffer;
		ID3DXEffect                    *m_pEffect;
		IDirect3DVertexDeclaration9    *m_pVertexDesc;
	};
}