﻿/*
 *  File:    NXSphere.cpp
 *
 *  author:  张雄(zhang xiong, 1025679612@qq.com)
 *  date:    2017_04_22
 *  purpose: define a sphere
 */

#include "NXSphere.h"
#include "../render/NXEngine.h"

NX::Sphere::Sphere(const std::string &_TextureFilePath, const int _iStacks, const int _iSlices, const float _fRadius):m_TextureFilePath(_TextureFilePath){
	m_iSlices         = _iSlices;
	m_iStacks         = _iStacks;
	m_fRadius         = 1.f; //_fRadius;
	m_pVertexs        = nullptr;
	m_pVertexDesc     = nullptr;
	CreateTriangles();
}

NX::Sphere::~Sphere() {
	NX::NXSafeRelease(m_pVertexBuffer);
	NX::NXSafeRelease(m_pIndexBuffer);
	NX::NXSafeRelease(m_pVertexDesc);
	NX::NXSafeRelease(m_pEffect);
	NX::NXSafeDeleteArray(m_pVertexs);
}

void NX::Sphere::CreateTriangles() {
	int nV = (m_iStacks - 1) * (m_iSlices + 1) + 2, r, c;
	int nI = (m_iStacks - 2) * (m_iSlices + 1) * 2 + (m_iSlices + 2) * 2;
	float rr = kfPiOver2, rc, dr = kfPi / m_iStacks, dc = kf2Pi / m_iSlices;
	float sr, cr, sc, cc;
	IDirect3DDevice9 *pDevice = glb_GetD3DDevice();
	m_pVertexs = new Vertex[nV];
	{//calculate vertex data 
		Vertex *pVertex = m_pVertexs;
		*pVertex++ = { 0.f, m_fRadius, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f };
		for (r = 1; r < m_iStacks; ++r) {
			rr -= dr;
			rc = 0.f;
			cr = std::cosf(rr), sr = std::sinf(rr);
			for (c = 0; c <= m_iSlices; ++c) {
				sc = std::sinf(rc);
				cc = std::cosf(rc);
				*pVertex++ = { m_fRadius * cr * cc, m_fRadius * sr, m_fRadius * cr * sc, c * 1.f / m_iSlices, r * 1.f / m_iStacks,  cr * cc, sr, cr * sc };
				rc += dc;
			}
		}
		*pVertex = { 0.f, -m_fRadius, 0.f, 0.f, 1.f, 0.f, -1.f, 0.f };
		pDevice->CreateVertexBuffer(sizeof(Vertex) * nV, D3DUSAGE_WRITEONLY, 0, D3DPOOL_DEFAULT, &m_pVertexBuffer, nullptr);
	}


	{//vertex desc
		D3DVERTEXELEMENT9 VertexDesc[] = {
			{ 0, CLS_MEM_OFFSET(Vertex, x), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
			{ 0, CLS_MEM_OFFSET(Vertex, u), D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
			{ 0, CLS_MEM_OFFSET(Vertex,nx), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0 },
			D3DDECL_END(),
		};
		pDevice->CreateVertexDeclaration(VertexDesc, &m_pVertexDesc);
	}

	{//calculate index data
		pDevice->CreateIndexBuffer(nI * sizeof(int), D3DUSAGE_WRITEONLY, D3DFMT_INDEX32, D3DPOOL_DEFAULT, &m_pIndexBuffer, nullptr);
		int *pBase = nullptr;
		m_pIndexBuffer->Lock(0, 0, (void**)&pBase, D3DLOCK_DISCARD);
		for (int i = 0; i <= m_iSlices + 1; ++i) {//first stack, triangle_fan
			*pBase++ = i;
		}
		int a = 1;
		for (int i = 1; i < m_iStacks - 1; ++i) {//inner stacks, triangle_list
			for (int j = 0; j <= m_iSlices; ++j) {
				*pBase++ = a;
				*pBase++ = a + m_iSlices + 1;
				++a;
			}
		}

		*pBase++ = m_iStacks * (m_iSlices + 1) + 1;
		for (int i = 0; i <= m_iSlices; ++i) {
			*pBase++ = (m_iStacks - 1) * (m_iSlices + 1) + 1 + i;
		}

		m_pIndexBuffer->Unlock();
	}
}


const std::string& NX::Sphere::GetTextureFilePath() const{
	return m_TextureFilePath;
}

std::string& NX::Sphere::GetTextureFilePath() {
	return m_TextureFilePath;
}

NX::Sphere& NX::Sphere::SetTextureFilePath(const std::string &_TextureFilePath) {
	m_TextureFilePath = _TextureFilePath;
	return *this;
}

void NX::Sphere::Render(struct RenderParameter &renderer) {
	if (!m_pVertexs) {
		return;
	}

	int nV = (m_iStacks - 1) * (m_iSlices + 1) + 2;

//	float3X3 M = GetTransform().GetTransformMatrix();
	float3 T = GetTransform().GetTranslation();

	for (int i = 0; i < nV; ++i) {
// 		float3X1& rm = (*(float3X1*)(&m_pVertexs[i].x)) ;
// 		rm = M * rm;
		(*(float3*)(&m_pVertexs[i].x)) += T;
	}
	
	void *pBase = nullptr;
	m_pVertexBuffer->Lock(0, 0, &pBase, D3DLOCK_DISCARD);
	memcpy(pBase, m_pVertexs, sizeof(Vertex) * nV);
	m_pVertexBuffer->Unlock();

	IDirect3DDevice9 *pDevice = renderer.pDXDevice;
}

NX::ENTITY_TYPE NX::Sphere::GetEntityType() {
	return ENTITY_TYPE::ENTITY_TYPE_SPHERE;
}

void NX::Sphere::OnTick(const float fDeleta) {

}