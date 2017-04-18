/*
*  File:    NXSky.h
*
*  author:  张雄(zhang xiong, 1025679612@qq.com)
*  date:    2017_04_13
*  purpose: define sky box & sky sphere
*/

#include "NXSky.h"
#include "../render/NXEffectManager.h"
#include "../render/NXDX9TextureManager.h"
#include "../render/NXEngine.h"
#include "../render/NXCamera.h"

struct NX::SkyBox::Vertex {
	Vertex(float _x, float _y, float _z, float _u, float _v) {
		x = _x, y = _y, z = _z;
		u = _u, v = _v;
	}
	Vertex(const float3 &_v, const float2 &_TexCoord): position(_v), TexCoord(_TexCoord){}
	Vertex() = default;
	union {
		struct {
			float x, y, z;
		};
		float3  position;
	};
	
	union{
		struct {
			float u, v;
		};
		float2 TexCoord;
	};
};

NX::SkyBox::SkyBox(const std::vector<std::string> &_TextureSet, const float fLength /* = 20000.f */):m_TextureSet(_TextureSet){
	m_fLength = fLength;
	Vertex v[] ={
		//front
		{ -m_fLength / 2, -m_fLength / 2,    m_fLength / 2, 0.0f, 1.0f, },
		{ -m_fLength / 2, m_fLength / 2,   m_fLength / 2, 0.0f, 0.0f, },
		{ m_fLength / 2, -m_fLength / 2,    m_fLength / 2, 1.0f, 1.0f, },
		{ m_fLength / 2, m_fLength / 2,   m_fLength / 2, 1.0f, 0.0f, },

		//back
		{ m_fLength / 2, -m_fLength / 2,   -m_fLength / 2, 0.0f, 1.0f, },
		{ m_fLength / 2, m_fLength / 2,  -m_fLength / 2, 0.0f, 0.0f, },
		{ -m_fLength / 2, -m_fLength / 2,   -m_fLength / 2, 1.0f, 1.0f, },
		{ -m_fLength / 2, m_fLength / 2,  -m_fLength / 2, 1.0f, 0.0f, },

		//left
		{ -m_fLength / 2, -m_fLength / 2,   -m_fLength / 2, 0.0f, 1.0f, },
		{ -m_fLength / 2, m_fLength / 2,  -m_fLength / 2, 0.0f, 0.0f, },
		{ -m_fLength / 2, -m_fLength / 2,    m_fLength / 2, 1.0f, 1.0f, },
		{ -m_fLength / 2, m_fLength / 2,   m_fLength / 2, 1.0f, 0.0f, },

		//right  
		{ m_fLength / 2, -m_fLength / 2,   m_fLength / 2, 0.0f, 1.0f, },
		{ m_fLength / 2, m_fLength / 2,  m_fLength / 2, 0.0f, 0.0f, },
		{ m_fLength / 2, -m_fLength / 2,  -m_fLength / 2, 1.0f, 1.0f, },
		{ m_fLength / 2, m_fLength / 2, -m_fLength / 2, 1.0f, 0.0f, },

		//up
		{ m_fLength / 2, m_fLength / 2, -m_fLength / 2, 1.0f, 0.0f, },
		{ m_fLength / 2, m_fLength / 2,  m_fLength / 2, 1.0f, 1.0f, },
		{ -m_fLength / 2, m_fLength / 2, -m_fLength / 2, 0.0f, 0.0f, },
		{ -m_fLength / 2, m_fLength / 2,  m_fLength / 2, 0.0f, 1.0f, },
	};

	IDirect3DDevice9 *pDevice = glb_GetD3DDevice();

	m_pVertexBuffer = nullptr;
	m_pIndexBuffer  = nullptr;
	pDevice->CreateVertexBuffer(sizeof(v),  D3DUSAGE_WRITEONLY, D3DFVF_XYZ | D3DFVF_TEX0,     D3DPOOL_MANAGED, &m_pVertexBuffer, nullptr);
	void *pBase = nullptr;
	m_pVertexBuffer->Lock(0, 0, &pBase, D3DLOCK_DISCARD);
	memcpy(pBase, v,   sizeof(v));
	m_pVertexBuffer->Unlock();

	const char *pszEffectFilePath = "../../../../engine/Shaders/DirectX/SkyBox_Effect.hlsl";
	m_pEffect = NX::EffectManager::Instance().GetEffect(pszEffectFilePath);
}


NX::SkyBox::~SkyBox() {
	NX::NXSafeRelease(m_pVertexBuffer);
	NX::NXSafeRelease(m_pIndexBuffer);
	m_pEffect   = nullptr;
}

void NX::SkyBox::Render(struct RenderParameter &renderer) {	
	UINT uPasses = 0;
	renderer.pDXDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(Vertex));
	m_pEffect->Begin(&uPasses, 0);
	for (int i = 0; i < uPasses; ++i) {
		m_pEffect->BeginPass(i);
		for(int j = 0; j < 5; ++j){
			m_pEffect->SetMatrixTranspose(m_pEffect->GetParameterByName(NULL, "VPMatrix"), (D3DXMATRIX*)&renderer.pProjectController->GetWatchMatrix());
			m_pEffect->SetTechnique(m_pEffect->GetTechniqueByName("SkyBoxShader"));
			renderer.pDXDevice->SetTexture(0, DX9TextureManager::Instance().GetTexture(m_TextureSet[j]));
			//m_pEffect->SetTexture(m_pEffect->GetParameterByName(NULL, "SkyColorTexture"), DX9TextureManager::Instance().GetTexture(m_TextureSet[j]));
			renderer.pDXDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, j * 4, 2);
		}
		m_pEffect->EndPass();
	}
	m_pEffect->End();
}

NX::ENTITY_TYPE NX::SkyBox::GetEntityType() {
	return ENTITY_TYPE::ENTITY_TYPE_SKY_BOX;
}

void NX::SkyBox::OnTick(const float fDeleta) {

}