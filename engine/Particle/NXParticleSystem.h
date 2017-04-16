/*
 *  File:    NXParticleSystem.h
 *
 *  author:  张雄(zhang xiong, 1025679612@qq.com)
 *  date:    2017_04_15
 *  purpose: define a particle system
 */

#pragma once

#include <vector>
#include <string>

#include "../entity/NXIEntity.h"
#include <d3d9.h>
#include <d3dx9.h>

namespace NX {
	extern IDirect3DDevice9* glb_GetD3DDevice();

	class Particle;

	class ParticleSystem : public IEntity{
	public:
		ParticleSystem(const std::vector<std::string> &_TextureFileSet, const float3x2 &_ParticleBound);
		virtual ~ParticleSystem();
	
	public:
		virtual void Render(struct RenderParameter &renderer) override;
		virtual ENTITY_TYPE GetEntityType() override;
		virtual void OnTick(const float fDeleta) override;

	public:
		virtual ParticleSystem& AddNewParticle() = 0;
		virtual ParticleSystem& AddNewParticle(Particle *pParticle);
		virtual ParticleSystem& ResetParticle(Particle *pParticle) = 0;

	public:
		ParticleSystem&  RemoveParticle(const int iParticleIndex);
		const Particle* GetParticle(const int iParticleIndex) const;
		const float3X2& GetBoundBox() const;
		const std::vector<std::string>& GetTextureSet() const;
		const std::vector<Particle*>&   GetParticles() const;
		int             GetParticleCount() const;

	private:
		bool             InBoundBox(const float3 &_Position);

	private:
		std::vector<Particle*>               m_Particles;
		std::vector<std::string>             m_TextureSet;
		float3X2                             m_ParticleBoundBox;
		IDirect3DVertexBuffer9               *m_pVertexBuffer;
		IDirect3DIndexBuffer9                *m_pIndexBuffer;
		ID3DXEffect                          *m_pEffect;
		IDirect3DVertexDeclaration9          *m_pVertexDesc;
		int                                  m_LiveParticleCount;
		int                                  m_BufferAllocedCount;
	};
}