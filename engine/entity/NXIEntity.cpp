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

inline NX::Transform& NX::IEntity::GetTransform() {
	return m_Transform;
}

inline NX::Transform NX::IEntity::GetTransform() const {
	return m_Transform;
}

inline NX::IEntity& NX::IEntity::SetVisible(const bool Visible) {
	m_Visible = Visible;
	return *this;
}

inline bool NX::IEntity::IsVisible() const {
	return m_Visible;
}

inline NX::IEntity& NX::IEntity::SetCanEverTick(const bool EverTick) {
	m_CanEverTick = EverTick;
	return *this;
}

inline bool NX::IEntity::IsTickedEachFrame() const {
	return m_CanEverTick;
}

inline NX::IEntity& NX::IEntity::SetObjectName(const std::string &ObjName) {
	m_strObjName = ObjName;
	return *this;
}

inline std::string NX::IEntity::GetObjName() const {
	return m_strObjName;
}

inline std::string& NX::IEntity::GetObjName() {
	return m_strObjName;
}