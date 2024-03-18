#include "pch.h"
#include "CAsset.h"

CAsset::CAsset(ASSET_TYPE _Type, bool _EngineAsset)
	: m_Type(_Type)
	, m_EngineAsset(_EngineAsset)
	, m_RefCount(0)
{
}

CAsset::CAsset(const CAsset& _Origin)
	: CEntity(_Origin)
	, m_Type(_Origin.m_Type)
	, m_EngineAsset(_Origin.m_EngineAsset)
	, m_RefCount(0)
{
}


CAsset::~CAsset()
{
}
