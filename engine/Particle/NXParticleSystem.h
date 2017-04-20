/*
 *  File:    NXParticleSystem.h
 *
 *  author:  张雄(zhang xiong, 1025679612@qq.com)
 *  date:    2017_04_15
 *  purpose: define a particle system
 */

#pragma once

#include "../entity/NXIEntity.h"

namespace NX {
	class Particle;

	class ParticleSystem : public IEntity{
	public:
		ParticleSystem() {}
		virtual ~ParticleSystem() {}
	
	public:
		virtual void Render(struct RenderParameter &renderer) = 0;
		virtual ENTITY_TYPE GetEntityType() = 0;
		virtual void OnTick(const float fDeleta) = 0;

	public:
		virtual ParticleSystem&  EmitParticle() = 0;
		virtual ParticleSystem&  AddParticle(Particle *pParticle) = 0;
		virtual ParticleSystem&  ResetParticle(Particle *pParticle) = 0;
		virtual ParticleSystem&  RemoveParticle(const int iParticleIndex) = 0;

	public:
		virtual int GetParticleCount() const = 0;
		virtual Particle* GetParticle(const int index) = 0;
		virtual const Particle* GetParticle(const int index) const = 0;
	};
}