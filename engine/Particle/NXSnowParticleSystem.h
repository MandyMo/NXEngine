/*
 *  File:    NXSnowParticleSystem.h
 *
 *  author:  张雄(zhang xiong, 1025679612@qq.com)
 *  date:    2017_04_15
 *  purpose: define snow particle system
 */

#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#include <string>

#include "NXParticleSystem.h"

namespace NX {
	IDirect3DDevice9 * glb_GetD3DDevice();
	class MVMatrixController;

	class SnowParticleSystem : public ParticleSystem {
	public:
		SnowParticleSystem(const MVMatrixController *pMoveController, const float _fRadius, const float _fIgnoreRadius, const int _ParticleCount, const std::vector<std::string> &_TextureFileSet);
		virtual ~SnowParticleSystem();

	public:
		virtual void Render(struct RenderParameter &renderer) override;
		virtual void OnTick(const float fDeleta) override;
		virtual ENTITY_TYPE GetEntityType() override;

	public:
		virtual SnowParticleSystem& EmitParticle() override;
		virtual SnowParticleSystem& AddParticle(Particle *pParticle) override;
		virtual SnowParticleSystem& ResetParticle(Particle *pParticle) override;
		virtual SnowParticleSystem& RemoveParticle(const int iParticleIndex);

	public:
		virtual int GetParticleCount() const override;
		virtual Particle* GetParticle(const int index) override;
		virtual const Particle* GetParticle(const int index) const override;

	private:
		bool InShpere(const Particle *pParticle);
		void ResizeBuffer();

	private:
		float                          m_fRadius;
		float                          m_fRadiusSquare;
		float                          m_fIgnoreRadius;
		class MVMatrixController*      m_MoveController;
		std::vector<class Particle*>   m_Particles;
		IDirect3DIndexBuffer9          *m_pIndexBuffer;
		IDirect3DVertexBuffer9         *m_pVertexBuffer;
		ID3DXEffect                    *m_pEffect;
		std::vector<std::string>       m_TextureSet;
		int                            m_BufferSize;
		IDirect3DVertexDeclaration9    *m_pVertexDesc;
	};
};