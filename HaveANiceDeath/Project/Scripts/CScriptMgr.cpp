#include "pch.h"
#include "CScriptMgr.h"

#include "CBackgroundScript.h"
#include "CCamCtrlScript.h"
#include "CCameraMoveScript.h"
#include "CCornerTriggerScript.h"
#include "CDrownedScript.h"
#include "CLDHitBox.h"
#include "CLDScript.h"
#include "CMissileScript.h"
#include "CMonsterHitBoxScript.h"
#include "CMonsterScript.h"
#include "CParallelScript.h"
#include "CPlatformScript.h"
#include "CPlayerMgrScript.h"
#include "CPlayerScript.h"
#include "CScriptTemplate.h"
#include "CStormBGScript.h"
#include "CUnitScript.h"

void CScriptMgr::GetScriptInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"CBackgroundScript");
	_vec.push_back(L"CCamCtrlScript");
	_vec.push_back(L"CCameraMoveScript");
	_vec.push_back(L"CCornerTriggerScript");
	_vec.push_back(L"CDrownedScript");
	_vec.push_back(L"CLDHitBox");
	_vec.push_back(L"CLDScript");
	_vec.push_back(L"CMissileScript");
	_vec.push_back(L"CMonsterHitBoxScript");
	_vec.push_back(L"CMonsterScript");
	_vec.push_back(L"CParallelScript");
	_vec.push_back(L"CPlatformScript");
	_vec.push_back(L"CPlayerMgrScript");
	_vec.push_back(L"CPlayerScript");
	_vec.push_back(L"CScriptTemplate");
	_vec.push_back(L"CStormBGScript");
	_vec.push_back(L"CUnitScript");
}

CScript * CScriptMgr::GetScript(const wstring& _strScriptName)
{
	if (L"CBackgroundScript" == _strScriptName)
		return new CBackgroundScript;
	if (L"CCamCtrlScript" == _strScriptName)
		return new CCamCtrlScript;
	if (L"CCameraMoveScript" == _strScriptName)
		return new CCameraMoveScript;
	if (L"CCornerTriggerScript" == _strScriptName)
		return new CCornerTriggerScript;
	if (L"CDrownedScript" == _strScriptName)
		return new CDrownedScript;
	if (L"CLDHitBox" == _strScriptName)
		return new CLDHitBox;
	if (L"CLDScript" == _strScriptName)
		return new CLDScript;
	if (L"CMissileScript" == _strScriptName)
		return new CMissileScript;
	if (L"CMonsterHitBoxScript" == _strScriptName)
		return new CMonsterHitBoxScript;
	if (L"CMonsterScript" == _strScriptName)
		return new CMonsterScript;
	if (L"CParallelScript" == _strScriptName)
		return new CParallelScript;
	if (L"CPlatformScript" == _strScriptName)
		return new CPlatformScript;
	if (L"CPlayerMgrScript" == _strScriptName)
		return new CPlayerMgrScript;
	if (L"CPlayerScript" == _strScriptName)
		return new CPlayerScript;
	if (L"CScriptTemplate" == _strScriptName)
		return new CScriptTemplate;
	if (L"CStormBGScript" == _strScriptName)
		return new CStormBGScript;
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
	case (UINT)SCRIPT_TYPE::CAMCTRLSCRIPT:
		return new CCamCtrlScript;
		break;
	case (UINT)SCRIPT_TYPE::CAMERAMOVESCRIPT:
		return new CCameraMoveScript;
		break;
	case (UINT)SCRIPT_TYPE::CORNERTRIGGERSCRIPT:
		return new CCornerTriggerScript;
		break;
	case (UINT)SCRIPT_TYPE::DROWNEDSCRIPT:
		return new CDrownedScript;
		break;
	case (UINT)SCRIPT_TYPE::LDHITBOX:
		return new CLDHitBox;
		break;
	case (UINT)SCRIPT_TYPE::LDSCRIPT:
		return new CLDScript;
		break;
	case (UINT)SCRIPT_TYPE::MISSILESCRIPT:
		return new CMissileScript;
		break;
	case (UINT)SCRIPT_TYPE::MONSTERHITBOXSCRIPT:
		return new CMonsterHitBoxScript;
		break;
	case (UINT)SCRIPT_TYPE::MONSTERSCRIPT:
		return new CMonsterScript;
		break;
	case (UINT)SCRIPT_TYPE::PARALLELSCRIPT:
		return new CParallelScript;
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
	case (UINT)SCRIPT_TYPE::STORMBGSCRIPT:
		return new CStormBGScript;
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

	case SCRIPT_TYPE::CAMCTRLSCRIPT:
		return L"CCamCtrlScript";
		break;

	case SCRIPT_TYPE::CAMERAMOVESCRIPT:
		return L"CCameraMoveScript";
		break;

	case SCRIPT_TYPE::CORNERTRIGGERSCRIPT:
		return L"CCornerTriggerScript";
		break;

	case SCRIPT_TYPE::DROWNEDSCRIPT:
		return L"CDrownedScript";
		break;

	case SCRIPT_TYPE::LDHITBOX:
		return L"CLDHitBox";
		break;

	case SCRIPT_TYPE::LDSCRIPT:
		return L"CLDScript";
		break;

	case SCRIPT_TYPE::MISSILESCRIPT:
		return L"CMissileScript";
		break;

	case SCRIPT_TYPE::MONSTERHITBOXSCRIPT:
		return L"CMonsterHitBoxScript";
		break;

	case SCRIPT_TYPE::MONSTERSCRIPT:
		return L"CMonsterScript";
		break;

	case SCRIPT_TYPE::PARALLELSCRIPT:
		return L"CParallelScript";
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

	case SCRIPT_TYPE::STORMBGSCRIPT:
		return L"CStormBGScript";
		break;

	case SCRIPT_TYPE::UNITSCRIPT:
		return L"CUnitScript";
		break;

	}
	return nullptr;
}