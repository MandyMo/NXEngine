/*
 *  File:    NXSnowParticleSystem.h
 *
 *  author:  张雄(zhang xiong, 1025679612@qq.com)
 *  date:    2017_04_15
 *  purpose: define snow particle system
 */

#include "NXSnowParticleSystem.h"
#include "NXParticle.h"
#include "../render/NXCamera.h"
#include "../render/NXEffectManager.h"
#include "../render/NXDX9TextureManager.h"
#include "../math/NXAlgorithm.h"
#include "../render/NXEngine.h"


/*
NX::SnowParticleSystem::SnowParticleSystem(const float _fRadius, const float _fIgnoreRadius, const int _ParticleCount, const std::vector<std::string> &_TextureFileSet, const float3x2 &_ParticleBound) :ParticleSystem(_TextureFileSet, _ParticleBound) {
	m_fRadius         = _fRadius;
	m_MoveController  = nullptr;
	m_fIgnoreRadius   = _fIgnoreRadius;
	for (int i = 0; i < _ParticleCount; ++i) {
		AddNewParticle();
	}
}

NX::SnowParticleSystem::~SnowParticleSystem() {

}

NX::SnowParticleSystem& NX::SnowParticleSystem::AddNewParticle() {
	NX::Particle *pParticle = new NX::Particle();
	ResetParticle(pParticle);
	AddNewParticle(pParticle);
	return *this;
}

NX::SnowParticleSystem& NX::SnowParticleSystem::AddNewParticle(Particle *pParticle) {
	ParticleSystem::AddNewParticle(pParticle);
	return *this;
}

NX::SnowParticleSystem& NX::SnowParticleSystem::ResetParticle(Particle *pParticle) {

}

void NX::SnowParticleSystem::OnTick(const float fDeleta) {
	const std::vector<Particle*>& rv = GetParticles();
	for (int i = 0; i < rv.size(); ++i) {
		if (rv[i] && rv[i]->IsDied()) {
			ResetParticle(rv[i]);
		}
	}

	ParticleSystem::OnTick(fDeleta);
}

*/

NX::SnowParticleSystem::SnowParticleSystem(const MVMatrixController *pMoveController, const float _fRadius, const float _fIgnoreRadius, const int _ParticleCount, const std::vector<std::string> &_TextureFileSet): m_TextureSet(_TextureFileSet) {
	m_MoveController      =    const_cast<MVMatrixController*>(pMoveController);
	m_fRadius             =    _fRadius;
	m_fRadiusSquare       =    m_fRadius * m_fRadius;
	m_fIgnoreRadius       =    _fIgnoreRadius;
	m_BufferSize          =    0;
	m_Particles.clear();

	m_pIndexBuffer        = nullptr;
	m_pVertexBuffer       = nullptr;
	m_pEffect             = nullptr;
	m_pVertexDesc         = nullptr;

	const char *pszEffectFilePath = "../../../../engine/Shaders/DirectX/Particle_Effect.hlsl";
	m_pEffect = NX::EffectManager::Instance().GetEffect(pszEffectFilePath);

	IDirect3DDevice9 *pDevice = glb_GetD3DDevice();

	D3DVERTEXELEMENT9 VertexDesc[] = {
		{ 0, CLS_MEM_OFFSET(NX::Particle::Vertex, x), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, CLS_MEM_OFFSET(NX::Particle::Vertex, u), D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
		D3DDECL_END(),
	};

	pDevice->CreateVertexDeclaration(VertexDesc, &m_pVertexDesc);

	NX::Particle *pParticle = nullptr;
	for (int i = 0; i < _ParticleCount; ++i) {
		pParticle = new Particle();
		ResetParticle(pParticle);
		AddParticle(pParticle);
	}
}

NX::SnowParticleSystem::~SnowParticleSystem() {
	NX::NXSafeRelease(m_pVertexDesc);
	NX::NXSafeRelease(m_pVertexBuffer);
	NX::NXSafeRelease(m_pIndexBuffer);
	NX::NXSafeRelease(m_pEffect);

	for (int i = 0; i < m_Particles.size(); ++i) {
		delete m_Particles[i];
	}
	m_Particles.clear();
}


void NX::SnowParticleSystem::Render(struct RenderParameter &renderer) {
	UINT uPasses = 0;
	Particle *pParticle = nullptr;
	char *pVB = nullptr;
	char *pIB = nullptr;
	UINT32 CC = 0;
	std::vector<int> ri;
	int LiveParticleCount = 0;
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
		++LiveParticleCount;
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
		renderer.pDXDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, LiveParticleCount * 6, 0, LiveParticleCount * 2);
		m_pEffect->EndPass();
	}
	m_pEffect->End();
}

void NX::SnowParticleSystem::OnTick(const float fDeleta) {
	Particle *pParticle = nullptr;
	for (int i = 0; i < m_Particles.size(); ++i) {
		pParticle = m_Particles[i];
		if (!pParticle) {
			continue;
		} else if (pParticle->IsDied() || !InShpere(pParticle)) {
			ResetParticle(pParticle);
		} else {
			pParticle->OnTick(fDeleta);
		}
	}

	if (!m_MoveController) {
		return;
	}

	float3 Dif = GetTransform().GetTranslation() - m_MoveController->GetEyePosition();
	if (NX::LengthSquare(Dif) <= m_fIgnoreRadius *m_fIgnoreRadius || NX::Dot(Dif, m_MoveController->GetFrontAxis()) >= 0.f) {
		return;
	}

	const float3 &n = m_MoveController->GetFrontAxis();
	const float4X4 &RM = NX::GetReflectionMatrix(n[0], n[1], n[2], NX::Dot(n, m_MoveController->GetEyePosition()));

	for (int i = 0; i < m_Particles.size(); ++i) {
		pParticle = m_Particles[i];
		if (!pParticle) {
			return;
		} else {
			Dif = pParticle->GetPosition() - m_MoveController->GetEyePosition();
			if (NX::Dot(n, Dif) < 0.f && LengthSquare(Dif) > m_fIgnoreRadius * m_fIgnoreRadius) {
				pParticle->SetPosition(RM * pParticle->GetPosition());
			}
		}
	}

	GetTransform().SetTranslation(RM * GetTransform().GetTranslation());
}

NX::ENTITY_TYPE  NX::SnowParticleSystem::GetEntityType() {
	return ENTITY_TYPE::ENTITY_TYPE_PARTICLE_SYSTEM;
}


NX::SnowParticleSystem& NX::SnowParticleSystem::EmitParticle() {
	Particle * pParticle = new NX::Particle();
	ResetParticle(pParticle);
	return AddParticle(pParticle);
}

NX::SnowParticleSystem& NX::SnowParticleSystem::AddParticle(Particle *pParticle) {
	NXAssert(pParticle);
	if (pParticle) {
		m_Particles.push_back(pParticle);
		ResizeBuffer();
	}
	return *this;
}

NX::SnowParticleSystem& NX::SnowParticleSystem::ResetParticle(Particle *pParticle) {
	if (!pParticle) {
		return *this;
	}

	int _TextureIndex = RandIntInRange(0, m_TextureSet.size() - 1);
	float3 _Rotation = float3(RandFloatInRange(-kfPi, kfPi), RandFloatInRange(-kfPi, kfPi), RandFloatInRange(-kfPi, kfPi));
	float3 _Position;
	{
		float u = NX::RandFloatInRange(0, kfPi);
		float v = NX::RandFloatInRange(0, kf2Pi);
		float r = NX::RandFloatInRange(0, m_fRadius);
		_Position.y = std::cosf(u);
		_Position.x = std::sinf(u) * std::cosf(v);
		_Position.z = std::sinf(u) * std::sinf(v);
		_Position *= r;
		_Position += GetTransform().GetTranslation();
	}
	float3 _Acceleration = float3(0.f, 0.f, 0.f);
	float3 _AngularAcceleration = float3(0.f, 0.f, 0.f);
	float3 _Velocity = float3(RandFloatInRange(-0.3f, 0.3f), -RandFloatInRange(0.2f, 0.4f), RandFloatInRange(-0.3f, 0.3f));
	float3 _AngularVelocity = float3(RandFloatInRange(-1.f, 1.f), RandFloatInRange(-1.f, 1.f), RandFloatInRange(-1.f, 1.f));
	float _LiveTime = RandFloatInRange(0.f, 100000.f);
	float _Size = RandFloatInRange(0.01, 0.05);

	pParticle->SetTextureIndex(_TextureIndex).SetRotation(_Rotation).SetPosition(_Position).SetAcceleration(_Acceleration).
		SetAngularAcceleration(_AngularAcceleration).SetVelocity(_Velocity).SetAngularVelocity(_AngularVelocity).
		SetLiveTime(_LiveTime).SetSize(float2(_Size, _Size)).SetDied(false);

	return *this;
}

NX::SnowParticleSystem& NX::SnowParticleSystem::RemoveParticle(const int iParticleIndex) {
	if (iParticleIndex >= 0 && iParticleIndex < m_Particles.size()) {
		delete m_Particles[iParticleIndex];
		m_Particles.erase(m_Particles.begin() + iParticleIndex);
	}
	return *this;
}

int NX::SnowParticleSystem::GetParticleCount()const {
	return m_Particles.size();
}

NX::Particle* NX::SnowParticleSystem::GetParticle(const int index) {
	NXAssert(index < m_Particles.size() &&index >= 0);
	if (index < m_Particles.size() && index >= 0) {
		return m_Particles[index];
	}
	return index < m_Particles.size() && index >= 0 ? m_Particles[index] : nullptr;
}

const NX::Particle* NX::SnowParticleSystem::GetParticle(const int index) const {
	NXAssert(index < m_Particles.size() && index >= 0);
	if (index < m_Particles.size() && index >= 0) {
		return m_Particles[index];
	}
	return index < m_Particles.size() && index >= 0 ? m_Particles[index] : nullptr;
}

bool NX::SnowParticleSystem::InShpere(const Particle *pParticle) {
	NXAssert(pParticle);
	if (!pParticle) {
		return true;
	}

	return NX::LengthSquare(pParticle->GetPosition() - GetTransform().GetTranslation()) <= m_fRadiusSquare;
}

void NX::SnowParticleSystem::ResizeBuffer() {
	if (m_BufferSize < m_Particles.size() || m_BufferSize > 2 * m_Particles.size() + 1) {
		NX::NXSafeRelease(m_pVertexBuffer);
		NX::NXSafeRelease(m_pIndexBuffer);
		m_BufferSize = 2 * m_Particles.size() + 1;
		IDirect3DDevice9 *pDevice = glb_GetD3DDevice();
		pDevice->CreateIndexBuffer(m_BufferSize * sizeof(int) * 6,                   D3DUSAGE_WRITEONLY, D3DFMT_INDEX32, D3DPOOL_MANAGED, &m_pIndexBuffer,  NULL);
		pDevice->CreateVertexBuffer(m_BufferSize * sizeof(NX::Particle::Vertex) * 4, D3DUSAGE_WRITEONLY, 0,              D3DPOOL_MANAGED, &m_pVertexBuffer, NULL);
	}
}