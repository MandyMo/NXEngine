/*
 *  File:    NXParticle.cpp
 *
 *  author:  张雄(zhang xiong, 1025679612@qq.com)
 *  date:    2017_04_12
 *  purpose: define a particle
 */

#include <vector>

#include "NXParticle.h"
#include "../math/NXAlgorithm.h"

NX::Particle::Particle(const int iTextureIndex, const NX::float3 &_Rotation, const NX::float3 &_Position, const NX::float3 &_Acceleration, const NX::float3 &_AngularAcceleration,
	const NX::float3 &_Velocity, const NX::float3 &_AngularVelocity, const float _LiveTime, const NX::float2 &_Size):
	m_iTextureIndex(iTextureIndex), m_Rotation(_Rotation), m_Position(_Position), m_Acceleration(_Acceleration), m_Angularcceleration(_AngularAcceleration),
	m_Velocity(_Velocity), m_AngularVelocity(_AngularVelocity), m_fLiveTime(_LiveTime), m_Size(_Size)
{
	m_fTimeElapsed = 0.f;
	m_bDied        = false;
}

NX::Particle::~Particle() {
	/**empty here*/
}

void NX::Particle::OnTick(const float fDelta) {
	if (m_bDied) {
		return;
	}
	m_Position            += m_Velocity * fDelta;
	m_Rotation            += m_AngularVelocity * fDelta;
	m_Velocity            += m_Acceleration * fDelta;
	m_AngularVelocity     += m_Angularcceleration * fDelta;
	m_fTimeElapsed        += fDelta;
	m_Rotation            =  m_Rotation % kf2Pi;

	if (m_fTimeElapsed >= m_fLiveTime) {
		m_bDied           = true;
	}
}

void NX::Particle::Reset(const int iTextureIndex, const float3 &_Rotation, const float3 &_Position, const float3 &_Acceleration, const float3 &_AngularAcceleration,
	const float3 &_Velocity, const float3 &_AngularVelocity, const float _LiveTime, const float2 &_Size) {
	m_iTextureIndex              =            iTextureIndex;
	m_Rotation                   =            _Rotation;
	m_Position                   =            _Position;
	m_Acceleration               =            _Acceleration;
	m_Angularcceleration         =            _AngularAcceleration;
	m_Velocity                   =            _Velocity;
	m_AngularVelocity            =            _AngularVelocity;
	m_fLiveTime                  =            _LiveTime;
	m_Size                       =            _Size;
	m_fTimeElapsed               =            0.f;
	m_bDied                      =            false;
}

std::vector<NX::Particle::Vertex>  NX::Particle::GetVertex() {
	std::vector<NX::Particle::Vertex> v(4);
	float lx = m_Size.x * .5f, ly = m_Size.y * .5f;
	v[0] = Vertex(-lx, ly,  0.f, 0.f, 0.f);
	v[1] = Vertex(lx,  ly,  0.f, 1.f, 0.f);
	v[2] = Vertex(lx,  -ly, 0.f, 1.f, 1.f);
	v[3] = Vertex(-lx, -ly, 0.f, 0.f, 1.f);

	NX::float3X3 RotationMatrix = NX::GetMatrixRotateByXYZ(m_Rotation);
	for (int i = 0; i < 4; ++i) {
		float3X1& rm = (*(float3X1*)(&v[i].x));
		float3 &rv   = (*(float3*)(&v[i].x));
		rm = RotationMatrix * rm;        //rotate
		rv += m_Position;                //position
	}

	return v;
}

std::vector<int>  NX::Particle::GetVertexIndex() {
	return std::vector<int>({0, 1, 2, 0, 2, 3});
}

NX::Particle& NX::Particle::SetTextureIndex(const int TextureIndex) {
	m_iTextureIndex = TextureIndex;
	return *this;
}

NX::Particle& NX::Particle::SetRotation(const float3 &_Rotation) {
	m_Rotation = _Rotation;
	return *this;
}

NX::Particle& NX::Particle::SetRotation(const float _rx, const float _ry, const float _rz) {
	return SetRotation(float3(_rx, _ry, _rz));
}

NX::Particle& NX::Particle::AddRotation(const float _arx, const float _ary, const float _arz) {
	return AddRotation(float3(_arx, _ary, _arz));
}

NX::Particle& NX::Particle::AddRotation(const float3 &_addRotation) {
	m_Rotation += _addRotation;
	return  *this;
}

NX::Particle& NX::Particle::SetPosition(const float3 &_Position) {
	m_Position = _Position;
	return *this;
}

NX::Particle& NX::Particle::SetPosition(const float _x, const float _y, const float _z) {
	return SetPosition(float3(_x, _y, _z));
}

NX::Particle& NX::Particle::AddPosition(const float _ax, const float _ay, const float _az) {
	return AddPosition(float3(_ax, _ay, _az));
}

NX::Particle& NX::Particle::AddPosition(const float3 &_addPosition) {
	m_Position += _addPosition;
	return *this;
}

NX::Particle& NX::Particle::SetAcceleration(const float3 &_Acceleration) {
	m_Acceleration = _Acceleration;
	return *this;
}

NX::Particle& NX::Particle::SetAcceleration(const float _acx, const float _acy, const float _acz) {
	return SetAcceleration(float3(_acx, _acy, _acz));
}

NX::Particle& NX::Particle::AddAcceleration(const float _aacx, const float _aacy, const float _aacz) {
	return AddAcceleration(float3(_aacx, _aacy, _aacz));
}

NX::Particle& NX::Particle::AddAcceleration(const float3 &_addAcceleration) {
	m_Acceleration += _addAcceleration;
	return *this;
}

NX::Particle& NX::Particle::SetAngularAcceleration(const float3 &_Acceleration) {
	m_Angularcceleration = _Acceleration;
	return *this;
}

NX::Particle& NX::Particle::SetAngularAcceleration(const float _acx, const float _acy, const float _acz) {
	return SetAngularAcceleration(float3(_acx, _acy, _acz));
}

NX::Particle& NX::Particle::AddAngularAcceleration(const float _aacx, const float _aacy, const float _aacz) {
	return AddAngularAcceleration(float3(_aacx, _aacy, _aacz));
}

NX::Particle& NX::Particle::AddAngularAcceleration(const float3 &_addAcceleration) {
	m_Angularcceleration += _addAcceleration;
	return *this;
}

NX::Particle& NX::Particle::SetVelocity(const float3 &_Velocity) {
	m_Velocity = _Velocity;
	return *this;
}

NX::Particle& NX::Particle::SetVelocity(const float _vx, const float _vy, const float _vz) {
	return SetVelocity(float3(_vx, _vy, _vz));
}

NX::Particle& NX::Particle::AddVelocity(const float _avx, const float _avy, const float _avz) {
	return AddVelocity(float3(_avx, _avy, _avz));
}

NX::Particle& NX::Particle::AddVelocity(const float3 &_addVelocity) {
	m_Velocity += _addVelocity;
	return *this;
}

NX::Particle& NX::Particle::SetAngularVelocity(const float3 &_Velocity) {
	m_AngularVelocity = _Velocity;
	return *this;
}

NX::Particle& NX::Particle::SetAngularVelocity(const float _vx, const float _vy, const float _vz) {
	return SetAngularVelocity(float3(_vx, _vy, _vz));
}

NX::Particle& NX::Particle::AddAngularVelocity(const float _avx, const float _avy, const float _avz) {
	return AddAngularVelocity(float3(_avx, _avy, _avz));
}

NX::Particle& NX::Particle::AddAngularVelocity(const float3 &_addVelocity) {
	m_AngularVelocity += _addVelocity;
	return *this;
}

NX::Particle& NX::Particle::SetLiveTime(const float _LiveTime) {
	m_fLiveTime = _LiveTime;
	return *this;
}

NX::Particle& NX::Particle::AddLiveTime(const float _addLiveTime) {
	m_fLiveTime += _addLiveTime;
	return *this;
}

NX::Particle& NX::Particle::SetSize(const float2 &_Size) {
	m_Size = _Size;
	return *this;
}

NX::Particle& NX::Particle::SetDied(const bool bDied) {
	m_bDied = bDied;
	return *this;
}

int NX::Particle::GetTextureIndex() const {
	return m_iTextureIndex;
}

const NX::float3& NX::Particle::GetRotation() const {
	return m_Rotation;
}

const NX::float3&   NX::Particle::GetPosition() const {
	return m_Position;
}

const NX::float3& NX::Particle::GetAcceleration() const {
	return m_Acceleration;
}

const NX::float3& NX::Particle::GetAngularAcceleration() const {
	return m_Angularcceleration;
}

const NX::float3& NX::Particle::GetVelocity() const {
	return m_Velocity;
}

const NX::float3& NX::Particle::GetAngularVelocity() const {
	return m_AngularVelocity;
}

float NX::Particle::GetLiveTime() const {
	return m_fLiveTime;
}

float NX::Particle::GetTimeElapsed() const {
	return m_fTimeElapsed;
}

const NX::float2& NX::Particle::GetSize() const {
	return m_Size;
}

bool NX::Particle::IsDied() const {
	return m_bDied;
}