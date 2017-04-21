/*
 *  File:    NXIEntity.h
 *
 *  author:  张雄
 *  date:    2017_04_09
 *  purpose: define IEntity, A entity is a object which can be placed in game world
 */


#pragma once

#include "NXTransform.h"

namespace NX {
	enum ENTITY_TYPE{
		ENTITY_TYPE_TERRAIN,             // terrain
		ENTITY_TYPE_SPHERE,              // sphere
		ENTITY_TYPE_SKY_BOX,             // sky box
		ENTITY_TYPE_SKY_SPHERE,          // sky sphere
		ENTITY_TYPE_CUBE3D,              // cube
		ENTITY_TYPE_PARTICLE_SYSTEM,     // particle system
	};

	class IEntity {
	public:
		IEntity();

		virtual ~IEntity();

	public:
		virtual void Render(struct RenderParameter &renderer) = 0;

		virtual ENTITY_TYPE GetEntityType() = 0;

		virtual void OnTick(const float fDeleta) = 0;

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