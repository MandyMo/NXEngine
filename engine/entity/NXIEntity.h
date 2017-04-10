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
		IEntity();

		virtual ~IEntity();

	public:
		virtual void Render() = 0;

		virtual ENTITY_TYPE GetEntityType() = 0;

		virtual void OnTick(const int dwMillSeconds) = 0;

	public:
		Transform&    GetTransform();
		Transform     GetTransform() const;
		bool          IsVisible() const;
		bool          IsTickedEachFrame() const;
		std::string&  GetObjName();
		std::string   GetObjName() const;
		IEntity&      SetVisible(const bool Visible);
		IEntity&      SetTransform(const Transform &trans);
		IEntity&      SetCanEverTick(const bool EverTick);
		IEntity&      SetObjectName(const std::string &ObjName);

	private:
		Transform			  m_Transform;	
		bool				  m_Visible;
		bool				  m_CanEverTick;
		std::string           m_strObjName;
	};
}