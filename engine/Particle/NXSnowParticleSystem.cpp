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

void NX::SnowParticleSystem::AddNewParticle() {
// 	int _TextureIndex            = RandIntInRange(0, GetTextureSet().size() - 1);
// 	float3 _Rotation             = float3(RandFloatInRange(-kfPi, kfPi), RandFloatInRange(-kfPi, kfPi), RandFloatInRange(-kfPi, kfPi));
// 	const float3X2& _BoundBox    = GetBoundBox();
// 	float3 _Position             = float3(RandFloatInRange(_BoundBox[0][0], _BoundBox[0][1]), RandFloatInRange(_BoundBox[1][0], _BoundBox[1][1]), RandFloatInRange(_BoundBox[2][0], _BoundBox[2][1]));
// 	float3 _Acceleration         = float3(0.f, 0.f, 0.f);
// 	float3 _AngularAcceleration  = float3(0.f, 0.f, 0.f);
// 	float3 _Velocity             = float3(RandFloatInRange(-0.3f, 0.3f), -RandFloatInRange(0.2f, 0.4f), RandFloatInRange(-0.3f, 0.3f));
// 	float3 _AngularVelocity      = float3(RandFloatInRange(-0.1f, 0.1f), RandFloatInRange(-0.1f, 0.1f), RandFloatInRange(-0.1f, 0.1f));
// 	float _LiveTime              = RandFloatInRange(0.f, 100000.f);
// 	float _Size                  = RandFloatInRange(0.005, 0.01);

	int _TextureIndex = RandIntInRange(0, GetTextureSet().size() - 1);
	float3 _Rotation = float3(RandFloatInRange(-kfPi, kfPi), RandFloatInRange(-kfPi, kfPi), RandFloatInRange(-kfPi, kfPi));
	const float3X2& _BoundBox = GetBoundBox();
	float3 _Position = float3(0.f, 1.f, 0.f);
	float3 _Acceleration = float3(0.f, 0.f, 0.f);
	float3 _AngularAcceleration = float3(0.f, 0.f, 0.f);
	float3 _Velocity = float3();
	float3 _AngularVelocity = float3();
	float _LiveTime = 100000000.f;
	float _Size = 0.02f;
	NX::Particle *pParticle = new NX::Particle(_TextureIndex, _Rotation, _Position, _Acceleration, _AngularAcceleration, _Velocity, _AngularVelocity, _LiveTime, float2(_Size, _Size));
	AddNewParticle(pParticle);
}

void NX::SnowParticleSystem::AddNewParticle(Particle *pParticle) {
	ParticleSystem::AddNewParticle(pParticle);
}