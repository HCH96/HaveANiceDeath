#pragma once

#include <vector>
#include <string>

enum STATE_TYPE
{
	COMBOMOVE01,
	COMBOMOVE02,
	COMBOMOVE03,
	COMBOMOVE04,
	COMBOSTAND01,
	COMBOSTAND02,
	COMBOSTAND03,
	COMBOUP,
	IDLESTATE,
	LDCORNERTRIGGER,
	LDDASH,
	LDIDLE,
	LDIDLETORUN,
	LDIDLEUTURN,
	LDJUMPFALL,
	LDJUMPLANDING,
	LDJUMPSTART,
	LDRUN,
	LDRUNTOIDLE,
	LDRUNUTURN,
	STATE_END,
};

using namespace std;

class CState;

class CStateMgr
{
public:
	static void GetStateInfo(vector<wstring>& _vec);
	static CState * GetState(const wstring& _strStateName);
	static CState * GetState(UINT _iStateType);
	static const wchar_t * GetStateName(CState * _pState);
};
