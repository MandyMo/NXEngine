/*
 *  File:    NXSky.h
 *
 *  author:  张雄(zhang xiong, 1025679612@qq.com)
 *  date:    2017_04_13
 *  purpose: define sky box & sky sphere
 */


#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#include <string.h>

#include "NXIEntity.h"

namespace NX {

	extern IDirect3DDevice9* glb_GetD3DDevice();

	class Sky : public IEntity{
	public:
		Sky(){}
		virtual ~Sky(){}

	public:
		virtual void Render(struct RenderParameter &renderer) = 0;
		virtual ENTITY_TYPE GetEntityType() = 0;
		virtual void OnTick(const float fDeleta) = 0;
	};

	class SkyBox : public Sky {
	public:
		struct Vertex;
	public:
		SkyBox(const std::vector<std::string> &_TextureSet, const float fLength = 20000.f);
		virtual ~SkyBox();

	public:
		virtual void Render(struct RenderParameter &renderer) override;
		virtual ENTITY_TYPE GetEntityType() override;
		virtual void OnTick(const float fDeleta) override;

	private:
		IDirect3DVertexBuffer9                *m_pVertexBuffer;
		IDirect3DIndexBuffer9                 *m_pIndexBuffer;
		ID3DXEffect                           *m_pEffect;
		float                                 m_fLength;
		std::vector<std::string>              m_TextureSet;
	};

	class SkySphere : public Sky {
	public:
		SkySphere();
		virtual ~SkySphere();

	public:
		virtual void Render(struct RenderParameter &renderer) override;
	};
}