/*
 *  File:    NXTerrain.h
 *
 *  author:  张雄(zhang xiong, 1025679612@qq.com)
 *  date:    2017_04_09
 *  purpose: define Terrain, A terrain is the surface that the player can walk on
 */

#pragma once

#include "NXIEntity.h"
#include <d3d9.h>

namespace NX {
	class Terrain : public IEntity {
	public:
		struct Vertex;

	public:
		Terrain(const int Row, const int Col, const float dx, const float dz, const std::string &strTextureFilePath);
		virtual ~Terrain();

	public:
		float GetHeight(const float x, const float z) const;
		Vertex&	GetVertex(const int r, const int c);

	public:
		virtual void Render() override;
		virtual ENTITY_TYPE GetEntityType() override;
		virtual void OnTick(const int dwMillSeconds) override;

	private:
		void CreateVertexs();
		float GetHeight(float3 &pA, float3 &pB, float3 &pC, const float x, const float z) const;

	private:
		int						                 m_RowCount;
		int						                 m_ColCount;
		float					                 m_Width;
		float					                 m_Height;
		float					                 m_dx;
		float					                 m_dz;
		Vertex					                 **m_pVertexData;
		std::string				                 m_strTextureFilePath;
	};

	struct Terrain::Vertex {
		Vertex(const float3 _pos, const float2 _uv, const float3 _normal) : Position(_pos), TexCoord(_uv), Normal(_normal) {}
		Vertex(const float _x, const float _y, const float _z, const float _u, const float _v, const float _nx, const float _ny, const float _nz) {
			x = _x, y = _y, z = _z;
			u = _u, v = _v;
			nx = _nx, ny = _ny, nz = _nz;
		}

		Vertex() {
			/**trival*/
		}

		union {// position
			float3 Position;
			struct {
				float x;
				float y;
				float z;
			};
		};

		union {// texture uv
			float2 TexCoord;
			struct {
				float u;
				float v;
			};
		};

		union {// normal
			float3 Normal;
			struct {
				float nx;
				float ny;
				float nz;
			};
		};
	};
}