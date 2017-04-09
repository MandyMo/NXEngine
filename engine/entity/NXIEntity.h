/*
 *  File:    NXIEntity.h
 *
 *  author:  张雄
 *  date:    2017_04_09
 *  purpose: define IEntity, A entity is a object which can be placed in game world
 */

#include "NXTransform.h"

namespace NX {
	enum ENTITY_TYPE{
		ENTITY_TYPE_TERRAIN,           // 地形
		ENTITY_TYPE_SKY_BOX,           // 天空盒
		ENTITY_TYPE_SKY_SPHERE,        // 天空球
	};

	class IEntity {
	public:
		NX::IEntity::IEntity() {
			/**empty here*/
		}

		NX::IEntity::~IEntity() {
			/**empty here*/
		}

	public:
		virtual void Render() = 0;

		virtual ENTITY_TYPE GetEntityType() = 0;

	public:
		void SetTransform(const Transform &trans) {
			m_Transform = trans;
		}

		Transform& GetTransform() {
			return m_Transform;
		}
	private:
		Transform			m_Transform;
	};


}