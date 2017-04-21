
/**
*  File:      NXChap17_3.h
*
*  Author:    张雄(zhangxiong 1025679612@qq.com)
*  Date:	   2017_03_08
*  Purpose:   DX9 Effect test
*/

#pragma once

#include "../../../../engine/Window/NXDX9Window.h"
#include "../../../../engine/render/NXCamera.h"
namespace NX {
	class NXChap17_3 : public NX::DX9Window {
	public:
		NXChap17_3();
		virtual ~NXChap17_3();

	public:
		virtual void PostRender();
		virtual void PreRender();
		virtual void Render();

	private:
		virtual void OnInitDX3Succeed();
		virtual void OnTick(NXUInt32 uDelta);

	public:
		struct Vertex {
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

	private:
		D3DXHANDLE						WorldMatrixHandle;
		D3DXHANDLE						ViewMatrixHandle;
		D3DXHANDLE                      ProjMatrixHandle;
		D3DXHANDLE						TexAHandle;
		D3DXHANDLE						TexBHandle;
		Vertex							m_v[4];
		IDirect3DVertexBuffer9			*m_pVB;
		IDirect3DIndexBuffer9			*m_pIB;
		IDirect3DVertexDeclaration9		*m_pVertexDesc;
		ID3DXEffect						*m_pEffect;

		IDirect3DTexture9				*m_pTexA;
		IDirect3DTexture9				*m_pTexB;
		D3DXHANDLE						TechHandle;
		float Angle;
		NX::PerspectCamera              *m_pCamera;
	};
}