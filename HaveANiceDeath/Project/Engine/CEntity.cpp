#include "pch.h"
#include "CEntity.h"

UINT CEntity::g_NextID = 0;

CEntity::CEntity()
	: m_ID(g_NextID++)
{
	int a = 0;

}

CEntity::CEntity(const CEntity& _Origin)
	: m_ID(g_NextID++)
	, m_Name(_Origin.m_Name)
{
}

CEntity::~CEntity()
{
}
