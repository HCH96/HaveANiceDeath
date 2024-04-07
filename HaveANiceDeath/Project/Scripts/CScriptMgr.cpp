#include "pch.h"
#include "CScriptMgr.h"

#include "CBackgroundScript.h"
#include "CCameraMoveScript.h"
#include "CCornerTriggerScript.h"
#include "CLDScript.h"
#include "CMissileScript.h"
#include "CMonsterScript.h"
#include "CPlatformScript.h"
#include "CPlayerMgrScript.h"
#include "CPlayerScript.h"
#include "CScriptTemplate.h"
#include "CUnitScript.h"

void CScriptMgr::GetScriptInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"CBackgroundScript");
	_vec.push_back(L"CCameraMoveScript");
	_vec.push_back(L"CCornerTriggerScript");
	_vec.push_back(L"CLDScript");
	_vec.push_back(L"CMissileScript");
	_vec.push_back(L"CMonsterScript");
	_vec.push_back(L"CPlatformScript");
	_vec.push_back(L"CPlayerMgrScript");
	_vec.push_back(L"CPlayerScript");
	_vec.push_back(L"CScriptTemplate");
	_vec.push_back(L"CUnitScript");
}

CScript * CScriptMgr::GetScript(const wstring& _strScriptName)
{
	if (L"CBackgroundScript" == _strScriptName)
		return new CBackgroundScript;
	if (L"CCameraMoveScript" == _strScriptName)
		return new CCameraMoveScript;
	if (L"CCornerTriggerScript" == _strScriptName)
		return new CCornerTriggerScript;
	if (L"CLDScript" == _strScriptName)
		return new CLDScript;
	if (L"CMissileScript" == _strScriptName)
		return new CMissileScript;
	if (L"CMonsterScript" == _strScriptName)
		return new CMonsterScript;
	if (L"CPlatformScript" == _strScriptName)
		return new CPlatformScript;
	if (L"CPlayerMgrScript" == _strScriptName)
		return new CPlayerMgrScript;
	if (L"CPlayerScript" == _strScriptName)
		return new CPlayerScript;
	if (L"CScriptTemplate" == _strScriptName)
		return new CScriptTemplate;
	if (L"CUnitScript" == _strScriptName)
		return new CUnitScript;
	return nullptr;
}

CScript * CScriptMgr::GetScript(UINT _iScriptType)
{
	switch (_iScriptType)
	{
	case (UINT)SCRIPT_TYPE::BACKGROUNDSCRIPT:
		return new CBackgroundScript;
		break;
	case (UINT)SCRIPT_TYPE::CAMERAMOVESCRIPT:
		return new CCameraMoveScript;
		break;
	case (UINT)SCRIPT_TYPE::CORNERTRIGGERSCRIPT:
		return new CCornerTriggerScript;
		break;
	case (UINT)SCRIPT_TYPE::LDSCRIPT:
		return new CLDScript;
		break;
	case (UINT)SCRIPT_TYPE::MISSILESCRIPT:
		return new CMissileScript;
		break;
	case (UINT)SCRIPT_TYPE::MONSTERSCRIPT:
		return new CMonsterScript;
		break;
	case (UINT)SCRIPT_TYPE::PLATFORMSCRIPT:
		return new CPlatformScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERMGRSCRIPT:
		return new CPlayerMgrScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERSCRIPT:
		return new CPlayerScript;
		break;
	case (UINT)SCRIPT_TYPE::SCRIPTTEMPLATE:
		return new CScriptTemplate;
		break;
	case (UINT)SCRIPT_TYPE::UNITSCRIPT:
		return new CUnitScript;
		break;
	}
	return nullptr;
}

const wchar_t * CScriptMgr::GetScriptName(CScript * _pScript)
{
	switch ((SCRIPT_TYPE)_pScript->GetScriptType())
	{
	case SCRIPT_TYPE::BACKGROUNDSCRIPT:
		return L"CBackgroundScript";
		break;

	case SCRIPT_TYPE::CAMERAMOVESCRIPT:
		return L"CCameraMoveScript";
		break;

	case SCRIPT_TYPE::CORNERTRIGGERSCRIPT:
		return L"CCornerTriggerScript";
		break;

	case SCRIPT_TYPE::LDSCRIPT:
		return L"CLDScript";
		break;

	case SCRIPT_TYPE::MISSILESCRIPT:
		return L"CMissileScript";
		break;

	case SCRIPT_TYPE::MONSTERSCRIPT:
		return L"CMonsterScript";
		break;

	case SCRIPT_TYPE::PLATFORMSCRIPT:
		return L"CPlatformScript";
		break;

	case SCRIPT_TYPE::PLAYERMGRSCRIPT:
		return L"CPlayerMgrScript";
		break;

	case SCRIPT_TYPE::PLAYERSCRIPT:
		return L"CPlayerScript";
		break;

	case SCRIPT_TYPE::SCRIPTTEMPLATE:
		return L"CScriptTemplate";
		break;

	case SCRIPT_TYPE::UNITSCRIPT:
		return L"CUnitScript";
		break;

	}
	return nullptr;
}