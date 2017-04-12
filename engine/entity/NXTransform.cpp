/*
*  File:    NXTransform.cpp
*
*  author:  张雄(zhang xiong 1025679612@qq.com)
*  date:    2017_04_09
*  purpose: define transform class
*/


#include "NXTransform.h"
#include "../math/NXAlgorithm.h"


NX::Transform::Transform(): m_LocalTransform(NX::GetIdentityMatrix<float, 4>()), m_Rotation(0.f), m_Translation(0.f), m_Scale(1.f) {
	/**empty here*/
}

NX::Transform::~Transform() {
	m_LocalTransform = NX::GetIdentityMatrix<float, 4>();
}

NX::Transform& NX::Transform::SetTransform(const Transform& trans) {
	return *this = trans;
}

const NX::float4x4&	NX::Transform::GetTransformMatrix(){
	return m_LocalTransform;
}

bool NX::operator == (const NX::Transform &l, const NX::Transform &r) {
	return l.m_LocalTransform == r.m_LocalTransform && l.m_Rotation == r.m_Rotation && l.m_Scale == r.m_Scale && l.m_Translation == r.m_Translation;
}

NX::Transform& NX::Transform::operator = (const Transform &r) {
	m_LocalTransform = r.m_LocalTransform;
	m_Rotation       = r.m_Rotation;
	m_Scale          = r.m_Scale;
	m_Translation    = r.m_Translation;
	return *this;
}

void NX::Transform::ReCaculateLocalTransform() {
	NX::float4X4 ScaleMatrix         =    NX::GetScaleMatrix(m_Scale);
	NX::float4X4 TranslationMatrix   =    NX::GetTranslated(m_Translation);
	NX::float4X4 RotationMatrix      =    NX::GetMatrixRotateByXYZ(m_Rotation);
	m_LocalTransform                 =    TranslationMatrix * RotationMatrix * ScaleMatrix;
}

const NX::float3& NX::Transform::GetRotation() const {
	return m_Rotation;
}

const NX::float3& NX::Transform::GetScale() const {
	return m_Scale;
}

const NX::float3&   NX::Transform::GetTranslation() const {
	return m_Translation;
}

NX::Transform& NX::Transform::SetRotation(const float3 &_rotation) {
	m_Rotation = _rotation;
	ReCaculateLocalTransform();
	return *this;
}

NX::Transform& NX::Transform::SetRotation(const float rx, const float ry, const float rz) {
	return SetRotation(float3(rx, ry, rz));
}

NX::Transform& NX::Transform::SetScale(const float3 &_scale) {
	m_Scale = _scale;
	ReCaculateLocalTransform();
	return *this;
}

NX::Transform& NX::Transform::SetScale(const float sx, const float sy, const float sz) {
	return SetScale(float3(sx, sy, sz));
}

NX::Transform& NX::Transform::SetTranslation(const float3 &_translation) {
	m_Translation = _translation;
	ReCaculateLocalTransform();
	return *this;
}

NX::Transform& NX::Transform::SetTranslation(const float dx, const float dy, const float dz) {
	return SetTranslation(float3(dx, dy, dz));
}