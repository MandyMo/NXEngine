/*
 *  File:    NXTransform.h
 *
 *  author:  张雄(zhang xiong 1025679612@qq.com)
 *  date:    2017_04_09
 *  purpose: define transform class
 */

#pragma once

#include "../math/NXMatrix.h"

namespace NX {
	class Transform {
	public:
		Transform();
		~Transform();

	public:
		Transform& SetTranslation(const float dx, const float dy, const float dz);
		Transform& SetTransform(const Transform& trans);

	public:
		friend bool operator == (const Transform &l, const Transform &r);
		Transform& operator = (const Transform &r);

	public:
		float4x4&	GetTransformMatrix();

	private:
		float4X4	m_LocalTransform;
	};
}