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
	const char *pszEffectFilePath = "../../../../engine/Shaders/DirectX/Terrain_Effect.hlsl";
	 m_pEffect = NX::EffectManager::Instance().GetEffect(pszEffectFilePath);

	 IDirect3DDevice9 *pDevice = glb_GetD3DDevice();
	 pDevice->CreateVertexBuffer(sizeof(NX::Particle::Vertex) * 4, D3DUSAGE_WRITEONLY, 0, D3DPOOL_DEFAULT, &m_pVertexBuffer, NULL);
	 pDevice->CreateIndexBuffer(sizeof(NXUInt16) * 6, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pIndexBuffer, NULL);

	 D3DVERTEXELEMENT9 VertexDesc[] = {
		 {0, CLS_MEM_OFFSET(NX::Particle::Vertex, x), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		 {0, CLS_MEM_OFFSET(NX::Particle::Vertex, u), D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0},
		 D3DDECL_END(),
	 };

	 pDevice->CreateVertexDeclaration(VertexDesc, &m_pVertexDesc);
}

NX::ParticleSystem::~ParticleSystem() {
	m_TextureSet.clear();
	for (int i = 0; i < m_Particles.size(); ++i) {
		delete m_Particles[i];
	}
	m_Particles.clear();
}

void NX::ParticleSystem::Render(struct RenderParameter &renderer) {
	m_pEffect->SetTechnique(m_pEffect->GetTechniqueByName("ParticleShader"));
	UINT uPasses = 0;
	for (int idx = 0; idx < m_Particles.size(); ++idx) {
		if (m_Particles[idx] && !m_Particles[idx]->IsDied()) {
			m_pEffect->Begin(&uPasses, 0);
			const std::vector<NX::Particle::Vertex> &rv = m_Particles[idx]->GetVertex();
			const std::vector<int> &ri = m_Particles[idx]->GetVertexIndex();
			void *pBase;

			{//vertex data
				pBase = NULL;
				m_pVertexBuffer->Lock(0, 0, &pBase, D3DLOCK_DISCARD);
				memcpy(pBase, &rv[0], rv.size() * sizeof(NX::Particle::Vertex));
				m_pVertexBuffer->Unlock();
			}

			{//index data
				pBase = NULL;
				NXUInt16 ib[] = {ri[0], ri[1], ri[2], ri[3], ri[4], ri[5]};
				m_pIndexBuffer->Lock(0, 0, &pBase, D3DLOCK_DISCARD);
				memcpy(pBase, ib, sizeof(ib));
				m_pIndexBuffer->Unlock();
			}

			{
				glb_GetD3DDevice()->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(NX::Particle::Vertex));
				glb_GetD3DDevice()->SetIndices(m_pIndexBuffer);
			}

			m_pEffect->SetMatrixTranspose(m_pEffect->GetParameterByName(NULL, "VPMatrix"), (D3DXMATRIX*)(&renderer.pProjectController->GetWatchMatrix()));
			m_pEffect->SetTexture(m_pEffect->GetParameterByName(NULL, "ParticleTexture"), NX::DX9TextureManager::Instance().GetTexture(m_TextureSet[m_Particles[idx]->GetTextureIndex()]));

			for (int i = 0; i < uPasses; ++i) {
				m_pEffect->BeginPass(i);
				glb_GetD3DDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 6, 0, 2);
			}
			m_pEffect->End();
		}
	}
}

NX::ENTITY_TYPE NX::ParticleSystem::GetEntityType() {
	return ENTITY_TYPE::ENTITY_TYPE_PARTICLE_SYSTEM;
}

void NX::ParticleSystem::OnTick(const float fDeleta) {
	for (int i = 0; i < m_Particles.size(); ++i) {
		if (m_Particles[i] && !m_Particles[i]->IsDied()) {
			m_Particles[i]->OnTick(fDeleta);
		}
	}

	for (int i = 0; i < m_Particles.size(); ++i) {
		if (m_Particles[i] && !m_Particles[i]->IsDied () && !InBoundBox(m_Particles[i]->GetPosition())) {
			m_Particles[i]->SetDied(true);
		}
	}
}

void NX::ParticleSystem::AddNewParticle(Particle *pParticle) {
	NXAssert(pParticle != NULL && "Particle shouldn't be null");
	if(pParticle){
		m_Particles.push_back(pParticle);
	}
}

bool NX::ParticleSystem::InBoundBox(const NX::float3 &_Position) {
	return _Position.x >= m_ParticleBoundBox[0][0] && _Position.x <= m_ParticleBoundBox[0][1]
		&& _Position.y >= m_ParticleBoundBox[1][0] && _Position.y <= m_ParticleBoundBox[1][1]
		&& _Position.z >= m_ParticleBoundBox[2][0] && _Position.z <= m_ParticleBoundBox[2][1];
}

void NX::ParticleSystem::RemoveParticle(const int iParticleIndex) {
	NXAssert(iParticleIndex >= 0 && iParticleIndex < m_Particles.size());
	m_Particles.erase(m_Particles.begin() + iParticleIndex);
}

const NX::float3X2& NX::ParticleSystem::GetBoundBox() const {
	return m_ParticleBoundBox;
}

const std::vector<std::string>& NX::ParticleSystem::GetTextureSet() const {
	return m_TextureSet;
}