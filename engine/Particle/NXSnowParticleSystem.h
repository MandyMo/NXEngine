/*
 *  File:    NXSnowParticleSystem.h
 *
 *  author:  张雄(zhang xiong, 1025679612@qq.com)
 *  date:    2017_04_15
 *  purpose: define snow particle system
 */

#pragma once

#include "NXParticleSystem.h"

namespace NX {
	class SnowParticleSystem : public ParticleSystem {
	public:
		SnowParticleSystem(const int _ParticleCount, const std::vector<std::string> &_TextureFileSet, const float3x2 &_ParticleBound);
		virtual ~SnowParticleSystem();

	public:
		virtual SnowParticleSystem& AddNewParticle() override;
		virtual SnowParticleSystem& AddNewParticle(Particle *pParticle) override;
		virtual void OnTick(const float fDeleta) override;
		virtual SnowParticleSystem& ResetParticle(Particle *pParticle) override;
	};
};