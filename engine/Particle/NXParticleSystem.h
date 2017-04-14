/*
 *  File:    NXParticleSystem.h
 *
 *  author:  张雄(zhang xiong, 1025679612@qq.com)
 *  date:    2017_04_15
 *  purpose: define a particle system
 */

#pragma once

#include <vector>

#include "../entity/NXIEntity.h"

namespace NX {
	class ParticleSystem : public IEntity{
	public:
		ParticleSystem();
		virtual ~ParticleSystem();
	
	public:
		virtual void Render(struct RenderParameter &renderer) = 0;
		virtual ENTITY_TYPE GetEntityType() = 0;
		virtual void OnTick(const float fDeleta) = 0;

	private:
		std::vector<class Particle*>         m_Particles;
	};
}