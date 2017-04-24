/*
 *  File:    NXSphere.h
 *
 *  author:  张雄(zhang xiong, 1025679612@qq.com)
 *  date:    2017_04_22
 *  purpose: define a sphere
 */

#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include "NXIEntity.h"

namespace NX {
	IDirect3DDevice9* glb_GetD3DDevice();

	class Sphere : public IEntity {
	public:
		Sphere(const std::string &_TextureFilePath, const int _iStacks, const int _iSlices, const float _radius, const bool bUseLighting = false);
		virtual ~Sphere();

	public:
		virtual void Render(struct RenderParameter &renderer) override;
		virtual ENTITY_TYPE GetEntityType() override;
		virtual void OnTick(const float fDeleta) override;

	public:
		const std::string& GetTextureFilePath() const;
		std::string& GetTextureFilePath();
		Sphere& SetTextureFilePath(const std::string &_TextureFilePath);

	public:
		struct Vertex {
		public:
			Vertex(const float _x, const float _y, const float _z, const float _u, const float _v, const float _nx, const float _ny, const float _nz) {
				x = _x, y = _y, z = _z;
				u = _u, v = _v;
				nx = _nx, ny = _ny, nz = _nz;
			}
			Vertex() = default;

		public:
			float x, y, z;
			float u, v;
			float nx, ny, nz;
		};

	private:
		void CreateTriangles();
		void SetupLightingInfo(struct RenderParameter &renderer);

	private:
		int                                 m_iStacks;
		int                                 m_iSlices;
		IDirect3DVertexBuffer9              *m_pVertexBuffer;
		IDirect3DVertexDeclaration9         *m_pVertexDesc;
		IDirect3DIndexBuffer9               *m_pIndexBuffer;
		ID3DXEffect                         *m_pEffect;
		Vertex                              *m_pVertexs;
		float                               m_fRadius;
		std::string                         m_TextureFilePath;
	};
}