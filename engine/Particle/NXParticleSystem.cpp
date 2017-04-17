/*
 *  File:    NXParticleSystem.cpp
 *
 *  author:  张雄(zhang xiong, 1025679612@qq.com)
 *  date:    2017_04_15
 *  purpose: define a particle system
 */

#include "NXParticleSystem.h"
#include "NXParticle.h"
#include "../render/NXEngine.h"
#include "../render/NXEffectManager.h"
#include "../render/NXCamera.h"
#include "../render/NXDX9TextureManager.h"

NX::ParticleSystem::ParticleSystem(const std::vector<std::string> &_TextureFileSet, const float3x2 &_ParticleBound) :
	m_TextureSet(_TextureFileSet), m_ParticleBoundBox(_ParticleBound) {
	 m_pIndexBuffer = nullptr;
	 m_pVertexDesc  = nullptr;
	 const char *pszEffectFilePath = "../../../../engine/Shaders/DirectX/Particle_Effect.hlsl";
	 m_pEffect = NX::EffectManager::Instance().GetEffect(pszEffectFilePath);

	 IDirect3DDevice9 *pDevice = glb_GetD3DDevice();

	 D3DVERTEXELEMENT9 VertexDesc[] = {
		 { 0, CLS_MEM_OFFSET(NX::Particle::Vertex, x), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		 { 0, CLS_MEM_OFFSET(NX::Particle::Vertex, u), D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
		 D3DDECL_END(),
	 };

	 pDevice->CreateVertexDeclaration(VertexDesc, &m_pVertexDesc);

	 m_BufferAllocedCount = 0;
}

NX::ParticleSystem::~ParticleSystem() {
	m_TextureSet.clear();
	for (int i = 0; i < m_Particles.size(); ++i) {
		delete m_Particles[i];
	}
	m_Particles.clear();

	m_BufferAllocedCount = 0;
	NX::NXSafeRelease(m_pVertexBuffer);
	NX::NXSafeRelease(m_pIndexBuffer);
}

void NX::ParticleSystem::Render(struct RenderParameter &renderer) {
	if (!m_LiveParticleCount) {
		return;
	}

	UINT uPasses = 0;
	Particle *pParticle = nullptr;
	char *pVB = nullptr;
	char *pIB = nullptr;
	UINT32 CC = 0;
	std::vector<int> ri;

	m_pVertexBuffer->Lock(0, 0, (void**)&pVB, D3DLOCK_DISCARD);
	m_pIndexBuffer->Lock(0, 0, (void**)&pIB, D3DLOCK_DISCARD);

	for (int idx = 0; idx < m_Particles.size(); ++idx) {
		pParticle = m_Particles[idx];
		if (!pParticle || pParticle->IsDied()) {
			continue;
		}
		const std::vector<NX::Particle::Vertex> &rv = m_Particles[idx]->GetVertex();
		ri = m_Particles[idx]->GetVertexIndex();
		memcpy(pVB, &rv[0], sizeof(Particle::Vertex) * 4);
		for (int i = 0; i < 6; ++i) {
			ri[i] += CC;
		}
		memcpy(pIB, &ri[0], sizeof(int) * 6);
		CC += 4;
		pVB += sizeof(Particle::Vertex) * 4;
		pIB += sizeof(int) * 6;
	}

	m_pVertexBuffer->Unlock();
	m_pIndexBuffer->Unlock();

	m_pEffect->SetMatrixTranspose(m_pEffect->GetParameterByName(NULL, "VPMatrix"), (D3DXMATRIX*)(&renderer.pProjectController->GetWatchMatrix()));
	m_pEffect->SetTexture(m_pEffect->GetParameterByName(NULL, "ParticleTexture"), NX::DX9TextureManager::Instance().GetTexture(m_TextureSet[m_Particles[0]->GetTextureIndex()]));

	m_pEffect->SetTechnique(m_pEffect->GetTechniqueByName("ParticleShader"));
	m_pEffect->Begin(&uPasses, 0);

	for (int i = 0; i < uPasses; ++i) {
		m_pEffect->BeginPass(i);
		glb_GetD3DDevice()->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(NX::Particle::Vertex));
		glb_GetD3DDevice()->SetIndices(m_pIndexBuffer);
		renderer.pDXDevice->SetVertexDeclaration(m_pVertexDesc);
		renderer.pDXDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_LiveParticleCount * 6, 0, m_LiveParticleCount * 2);
		m_pEffect->EndPass();
	}
	m_pEffect->End();
}

NX::ENTITY_TYPE NX::ParticleSystem::GetEntityType() {
	return ENTITY_TYPE::ENTITY_TYPE_PARTICLE_SYSTEM;
}

void NX::ParticleSystem::OnTick(const float fDeleta) {
	m_LiveParticleCount = 0;
	NX::Particle *pParticle = nullptr;
	for (int i = 0; i < m_Particles.size(); ++i) {
		pParticle = m_Particles[i];
		if (pParticle && !pParticle->IsDied()) {
			pParticle->OnTick(fDeleta);
			if (!InBoundBox(pParticle->GetPosition())) {
				pParticle->SetDied(true);
			} else {
				++m_LiveParticleCount;
			}
		}
	}
}

NX::ParticleSystem& NX::ParticleSystem::AddNewParticle(Particle *pParticle) {
	NXAssert(pParticle != NULL && "Particle shouldn't be null");
	if(pParticle){
		m_Particles.push_back(pParticle);
	}

	ShrinkBuffer();
	return *this;
}

bool NX::ParticleSystem::InBoundBox(const NX::float3 &_Position) {
	return _Position.x >= m_ParticleBoundBox[0][0] && _Position.x <= m_ParticleBoundBox[0][1]
		&& _Position.y >= m_ParticleBoundBox[1][0] && _Position.y <= m_ParticleBoundBox[1][1]
		&& _Position.z >= m_ParticleBoundBox[2][0] && _Position.z <= m_ParticleBoundBox[2][1];
}

NX::ParticleSystem& NX::ParticleSystem::RemoveParticle(const int iParticleIndex) {
	NXAssert(iParticleIndex >= 0 && iParticleIndex < m_Particles.size());
	m_Particles.erase(m_Particles.begin() + iParticleIndex);
	ShrinkBuffer();
	return *this;
}

const NX::float3X2& NX::ParticleSystem::GetBoundBox() const {
	return m_ParticleBoundBox;
}

const std::vector<std::string>& NX::ParticleSystem::GetTextureSet() const {
	return m_TextureSet;
}

const std::vector<NX::Particle*>&  NX::ParticleSystem::GetParticles() const {
	return m_Particles;
}

int NX::ParticleSystem::GetParticleCount() const {
	return m_Particles.size();
}

void NX::ParticleSystem::ShrinkBuffer() {
	if (m_BufferAllocedCount < m_Particles.size() || m_BufferAllocedCount >= m_Particles.size() * 4) {//expand or shrink buffer
		NX::NXSafeRelease(m_pIndexBuffer);
		NX::NXSafeRelease(m_pVertexBuffer);
		m_BufferAllocedCount = m_BufferAllocedCount * 2 + 1;
		IDirect3DDevice9 *pDevice = glb_GetD3DDevice();
		pDevice->CreateIndexBuffer(m_BufferAllocedCount * sizeof(int) * 6, D3DUSAGE_WRITEONLY, D3DFMT_INDEX32, D3DPOOL_MANAGED, &m_pIndexBuffer, NULL);
		pDevice->CreateVertexBuffer(m_BufferAllocedCount * sizeof(NX::Particle::Vertex) * 4, D3DUSAGE_WRITEONLY, 0, D3DPOOL_MANAGED, &m_pVertexBuffer, NULL);
	}
}