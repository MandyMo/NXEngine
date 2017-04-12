/*
 *  File:    NXTransform.h
 *
 *  author:  张雄(zhang xiong 1025679612@qq.com)
 *  date:    2017_04_09
 *  purpose: define transform class
 */

#pragma once

#include "../math/NXMatrix.h"
#include "../math/NXEulerAngle.h"

namespace NX {
	class Transform {
	public:
		Transform();
		Transform(const Transform &rhs){
			*this = rhs;
		}
		~Transform();

	public:

		const float4x4&	GetTransformMatrix();
		const float3&   GetRotation()         const;
		const float3&   GetScale()            const;
		const float3&   GetTranslation()      const;
		Transform& SetRotation(const float3 &_rotation);
		Transform& SetRotation(const float rx, const float ry, const float rz);
		Transform& SetScale(const float3 &_scale);
		Transform& SetScale(const float sx, const float sy, const float sz);
		Transform& SetTranslation(const float3 &_translation);
		Transform& SetTranslation(const float dx, const float dy, const float dz);
		Transform& SetTransform(const Transform& trans);

	public:
		friend bool operator == (const Transform &l, const Transform &r);
		Transform& operator = (const Transform &r);

	private:
		void ReCaculateLocalTransform();

	private:
		float4X4	m_LocalTransform;

		union {//rotation angles
			float3      m_Rotation;
			struct {
				float m_RX;
				float m_RY;
				float m_RZ;
			};
		};

		union {
			float3      m_Scale;
			struct {
				float m_SX;
				float m_SY;
				float m_SZ;
			};
		};

		union {
			float3      m_Translation;
			struct {
				float m_TX;
				float m_TY;
				float m_TZ;
			};
		};
	};
}