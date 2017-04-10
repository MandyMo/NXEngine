/*
*  File:    NXIEntity.cpp
*
*  author:  张雄
*  date:    2017_04_09
*  purpose: define IEntity, A entity is a object which can be placed in game world
*/

#include "NXIEntity.h"

NX::IEntity::IEntity() {
	m_CanEverTick = false;
	m_Visible = true;
}

NX::IEntity::~IEntity() {
	/**empty here*/
}

NX::IEntity& NX::IEntity::SetTransform(const Transform &trans) {
	m_Transform = trans;
	return *this;
}

NX::Transform& NX::IEntity::GetTransform() {
	return m_Transform;
}

NX::Transform NX::IEntity::GetTransform() const {
	return m_Transform;
}

NX::IEntity& NX::IEntity::SetVisible(const bool Visible) {
	m_Visible = Visible;
	return *this;
}

bool NX::IEntity::IsVisible() const {
	return m_Visible;
}

NX::IEntity& NX::IEntity::SetCanEverTick(const bool EverTick) {
	m_CanEverTick = EverTick;
	return *this;
}

bool NX::IEntity::IsTickedEachFrame() const {
	return m_CanEverTick;
}

NX::IEntity& NX::IEntity::SetObjectName(const std::string &ObjName) {
	m_strObjName = ObjName;
	return *this;
}

std::string NX::IEntity::GetObjName() const {
	return m_strObjName;
}

std::string& NX::IEntity::GetObjName() {
	return m_strObjName;
}