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
		inline Transform&    GetTransform();
		inline Transform     GetTransform() const;
		inline bool          IsVisible() const;
		inline bool          IsTickedEachFrame() const;
		inline std::string&  GetObjName();
		inline std::string   GetObjName() const;
		inline IEntity&      SetVisible(const bool Visible);
		inline IEntity&      SetTransform(const Transform &trans);
		inline IEntity&      SetCanEverTick(const bool EverTick);
		inline IEntity&      SetObjectName(const std::string &ObjName);

	private:
		Transform			  m_Transform;	
		bool				  m_Visible;
		bool				  m_CanEverTick;
		std::string           m_strObjName;
	};
}