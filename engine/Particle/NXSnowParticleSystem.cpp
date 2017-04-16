/*
 *  File:    NXSnowParticleSystem.h
 *
 *  author:  张雄(zhang xiong, 1025679612@qq.com)
 *  date:    2017_04_15
 *  purpose: define snow particle system
 */

#include "NXSnowParticleSystem.h"
#include "NXParticle.h"

NX::SnowParticleSystem::SnowParticleSystem(const int _ParticleCount, const std::vector<std::string> &_TextureFileSet, const float3x2 &_ParticleBound) :ParticleSystem(_TextureFileSet, _ParticleBound) {
	for (int i = 0; i < _ParticleCount; ++i) {
		AddNewParticle();
	}
}

NX::SnowParticleSystem::~SnowParticleSystem() {
	/**empty*/
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
	if (!pParticle) {
		return *this;
	}

	int _TextureIndex = RandIntInRange(0, GetTextureSet().size() - 1);
	float3 _Rotation  = float3(RandFloatInRange(-kfPi, kfPi), RandFloatInRange(-kfPi, kfPi), RandFloatInRange(-kfPi, kfPi));
	const float3X2& _BoundBox = GetBoundBox();
	float3 _Position = float3(RandFloatInRange(_BoundBox[0][0], _BoundBox[0][1]), RandFloatInRange(_BoundBox[1][0], _BoundBox[1][1]), RandFloatInRange(_BoundBox[2][0], _BoundBox[2][1]));
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

void NX::SnowParticleSystem::OnTick(const float fDeleta) {
	const std::vector<Particle*>& rv = GetParticles();
	for (int i = 0; i < rv.size(); ++i) {
		if (rv[i] && rv[i]->IsDied()) {
			ResetParticle(rv[i]);
		}
	}

	ParticleSystem::OnTick(fDeleta);
}