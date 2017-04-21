/*
 *  File:    NXCube.h
 *
 *  author:  张雄(zhang xiong, 1025679612@qq.com)
 *  date:    2017_04_12
 *  purpose: define a cube
 */

#pragma once

#include <string>
#include <d3d9.h>
#include <d3dx9.h>

#include "NXIEntity.h"

namespace NX {
	class Cube : public IEntity {
	public:
		Cube(const std::string &_TextureFilePath = "EngineResouces/Road/dirt01.jpg", const Size3D &_size = float3(1.f, 1.f, 1.f));
		virtual ~Cube();

	public:
		virtual void Render(struct RenderParameter &renderer) override;
		virtual ENTITY_TYPE GetEntityType() override;
		virtual void OnTick(const float dwMillSeconds) override;
	
	public:
		const std::string& GetTextureFilePath() const;
		std::string& GetTextureFilePath();
		Cube& SetTextureFilePath(const std::string &_TextureFilePath);

	private:
		struct Vertex;

	private:
		Size3D				           m_Size;
		IDirect3DVertexBuffer9         *m_pVertexBuffer;
		IDirect3DVertexDeclaration9    *m_pVertexDesc;
		ID3DXEffect                    *m_pEffect;
		std::string                    m_TextureFilePath;
	};
}