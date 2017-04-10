/*
*  File:    NXTerrain.cpp
*
*  author:  张雄(zhang xiong, 1025679612@qq.com)
*  date:    2017_04_09
*  purpose: define Terrain, A terrain is the surface that the player can walk on
*/


#include "NXTerrain.h"
#include "../math/NXAlgorithm.h"

namespace NX {
	extern IDirect3DDevice9 * glb_GetD3DDevice();
}

NX::Terrain::Terrain(const int Row, const int Col, const float dx, const float dz, const std::string &strTextureFilePath) {
	m_RowCount                  =     Row;
	m_ColCount                  =     Col;
	m_dx                        =     dx;
	m_dz                        =     dz;
	m_Width                     =     m_dx * (m_RowCount - 1);
	m_Height                    =     m_dz * (m_ColCount - 1);
	m_strTextureFilePath        =     strTextureFilePath;
	m_pVertexData               =     NULL;
	CreateVertexs();
}

NX::Terrain::~Terrain() {
	if (m_pVertexData) {
		for (int r = 0; r < m_RowCount; ++r) {
			NX::NXSafeDeleteArray(m_pVertexData[r]);
		}
	}
	NX::NXSafeDeleteArray(m_pVertexData);
}

float NX::Terrain::GetHeight(const float x, const float y) const {
	NXAssert(x >= 0 && x <= m_Width && y >=0 && y <= m_Height);
	int r = x / m_dx, c = y / m_dz;
	float dr = x - r * m_dx, dc = y - c * m_dz;
	if (dr / m_dx + dc / m_dz >= 1.0f) {
		return GetHeight(m_pVertexData[r + 1][c].Position, m_pVertexData[r + 1][c + 1].Position, m_pVertexData[r][c + 1].Position, x, y);
	} else {
		return GetHeight(m_pVertexData[r + 1][c].Position, m_pVertexData[r][c].Position, m_pVertexData[r][c + 1].Position, x, y);
	}
}

float NX::Terrain::GetHeight(float3 &pA, float3 &pB, float3 &pC, const float x, const float z) const{
	Matrix<float, 2, 2> M;
	float2 V;
	{
		M[0][0] = pA.x - pC.x, M[0][1] = pB.x - pC.x;
		M[1][0] = pA.z - pC.z, M[1][1] = pB.z - pC.z;
		V[0] = x - pC.x, V[1] = z - pC.z;
		auto result = SolveEquation(M, V);
		auto cof = result.second;
		return cof[0] * pA.y + cof[1] * pB.y + (1.f - cof[0] - cof[1]) * pC.y;
	}
}

void NX::Terrain::Render() {
	IDirect3DVertexDeclaration9 *pVertexDesc = NULL;
	{//create vertex description
		D3DVERTEXELEMENT9 VertexDescs[] = {
			{ 0, 0,                                D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_POSITION, 0 },
			{ 0, CLS_MEM_OFFSET(Vertex, TexCoord), D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_TEXCOORD, 1 },
			{ 0, CLS_MEM_OFFSET(Vertex, Normal),   D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_NORMAL,   2 },
			D3DDECL_END(),
		};
		glb_GetD3DDevice()->CreateVertexDeclaration(VertexDescs, &pVertexDesc);
		glb_GetD3DDevice()->SetVertexDeclaration(pVertexDesc);
	}

	{//commit vertex data

	}

	{//clear
		NX::NXSafeRelease(pVertexDesc);
	}
}

NX::Terrain::Vertex&	NX::Terrain::GetVertex(const int r, const int c) {
	NXAssert(r >= 0 && r < m_RowCount && c >= 0 && c< m_ColCount);
	return m_pVertexData[r][c];
}

void NX::Terrain::CreateVertexs() {
	NXAssert(m_RowCount > 0 && m_ColCount > 0);

	{//create vertex data
		m_pVertexData = new Vertex*[m_RowCount];
		for (int r = 0; r < m_RowCount; ++r) {
			m_pVertexData[r] = new Vertex[m_ColCount];
			for (int c = 0; c < m_ColCount; ++c) {
				m_pVertexData[r][c] = Vertex(r * m_dx, 0, c * m_dz, r & 1, c & 1, .0f, 0.f, .0f);
			}
		}
	}

	{//set height
		for (int r = 0; r < m_RowCount; ++r) {
			for (int c = 0; c < m_ColCount; ++c) {
				GetVertex(r, c).y = rand() % 10000 - 10000;
			}
		}
	}

	{//calculate normals
		for (int r = 0; r < m_RowCount; ++r) {
			for (int c = 0; c < m_ColCount; ++c) {
				GetVertex(r, c).Normal = GetNormalized(GetVertex(r, c).Position);
			}
		}
	}
}


NX::ENTITY_TYPE NX::Terrain::GetEntityType() {
	return ENTITY_TYPE::ENTITY_TYPE_TERRAIN;
}

void NX::Terrain::OnTick(const int dwMillSeconds) {

}