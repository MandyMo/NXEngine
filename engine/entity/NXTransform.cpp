/*
*  File:    NXTransform.cpp
*
*  author:  张雄(zhang xiong 1025679612@qq.com)
*  date:    2017_04_09
*  purpose: define transform class
*/


#include "NXTransform.h"
#include "../math/NXAlgorithm.h"


NX::Transform::Transform() {
	m_LocalTransform = NX::GetIdentityMatrix<float, 4>();
}

NX::Transform::~Transform() {
	m_LocalTransform = NX::GetIdentityMatrix<float, 4>();
}

NX::Transform& NX::Transform::SetTranslation(const float dx, const float dy, const float dz) {
	m_LocalTransform[0][3] = dx;
	m_LocalTransform[1][3] = dy;
	m_LocalTransform[2][3] = dz;
	return *this;
}

NX::Transform& NX::Transform::SetTransform(const Transform& trans) {
	return *this = trans;
}

NX::float4x4&	NX::Transform::GetTransformMatrix() {
	return m_LocalTransform;
}

bool NX::operator == (const NX::Transform &l, const NX::Transform &r) {
	return l.m_LocalTransform == r.m_LocalTransform;
}

NX::Transform& NX::Transform::operator = (const Transform &r) {
	m_LocalTransform = r.m_LocalTransform;
	return *this;
}