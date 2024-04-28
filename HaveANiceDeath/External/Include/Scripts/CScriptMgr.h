#pragma once

#include <vector>
#include <string>

enum SCRIPT_TYPE
{
	BACKGROUNDSCRIPT,
	CAMCTRLSCRIPT,
	CAMERAMOVESCRIPT,
	CORNERTRIGGERSCRIPT,
	DROWNEDSCRIPT,
	LDHITBOX,
	LDSCRIPT,
	MISSILESCRIPT,
	MONSTERHITBOXSCRIPT,
	MONSTERSCRIPT,
	PARALLELSCRIPT,
	PLATFORMSCRIPT,
	PLAYERMGRSCRIPT,
	PLAYERSCRIPT,
	SCRIPTTEMPLATE,
	STORMBGSCRIPT,
	UNITSCRIPT,
	END,
};

using namespace std;

class CScript;

class CScriptMgr
{
public:
	static void GetScriptInfo(vector<wstring>& _vec);
	static CScript * GetScript(const wstring& _strScriptName);
	static CScript * GetScript(UINT _iScriptType);
	static const wchar_t * GetScriptName(CScript * _pScript);
};
