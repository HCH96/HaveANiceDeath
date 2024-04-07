#include "pch.h"
#include "CStateMgr.h"

#include "CIdleState.h"
#include "CLDCornerTrigger.h"
#include "CLDDash.h"
#include "CLDIdle.h"
#include "CLDIdleToRun.h"
#include "CLDIdleUTurn.h"
#include "CLDJumpFall.h"
#include "CLDJumpLanding.h"
#include "CLDJumpStart.h"
#include "CLDRun.h"
#include "CLDRunToIdle.h"
#include "CLDRunUTurn.h"

void CStateMgr::GetStateInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"CIdleState");
	_vec.push_back(L"CLDCornerTrigger");
	_vec.push_back(L"CLDDash");
	_vec.push_back(L"CLDIdle");
	_vec.push_back(L"CLDIdleToRun");
	_vec.push_back(L"CLDIdleUTurn");
	_vec.push_back(L"CLDJumpFall");
	_vec.push_back(L"CLDJumpLanding");
	_vec.push_back(L"CLDJumpStart");
	_vec.push_back(L"CLDRun");
	_vec.push_back(L"CLDRunToIdle");
	_vec.push_back(L"CLDRunUTurn");
}

CState* CStateMgr::GetState(const wstring& _strStateName)
{
	if (L"CIdleState" == _strStateName)
		return new CIdleState;
	if (L"CLDCornerTrigger" == _strStateName)
		return new CLDCornerTrigger;
	if (L"CLDDash" == _strStateName)
		return new CLDDash;
	if (L"CLDIdle" == _strStateName)
		return new CLDIdle;
	if (L"CLDIdleToRun" == _strStateName)
		return new CLDIdleToRun;
	if (L"CLDIdleUTurn" == _strStateName)
		return new CLDIdleUTurn;
	if (L"CLDJumpFall" == _strStateName)
		return new CLDJumpFall;
	if (L"CLDJumpLanding" == _strStateName)
		return new CLDJumpLanding;
	if (L"CLDJumpStart" == _strStateName)
		return new CLDJumpStart;
	if (L"CLDRun" == _strStateName)
		return new CLDRun;
	if (L"CLDRunToIdle" == _strStateName)
		return new CLDRunToIdle;
	if (L"CLDRunUTurn" == _strStateName)
		return new CLDRunUTurn;
	return nullptr;
}

CState* CStateMgr::GetState(UINT _iStateType)
{
	switch (_iStateType)
	{
	case (UINT)STATE_TYPE::IDLESTATE:
		return new CIdleState;
		break;
	case (UINT)STATE_TYPE::LDCORNERTRIGGER:
		return new CLDCornerTrigger;
		break;
	case (UINT)STATE_TYPE::LDDASH:
		return new CLDDash;
		break;
	case (UINT)STATE_TYPE::LDIDLE:
		return new CLDIdle;
		break;
	case (UINT)STATE_TYPE::LDIDLETORUN:
		return new CLDIdleToRun;
		break;
	case (UINT)STATE_TYPE::LDIDLEUTURN:
		return new CLDIdleUTurn;
		break;
	case (UINT)STATE_TYPE::LDJUMPFALL:
		return new CLDJumpFall;
		break;
	case (UINT)STATE_TYPE::LDJUMPLANDING:
		return new CLDJumpLanding;
		break;
	case (UINT)STATE_TYPE::LDJUMPSTART:
		return new CLDJumpStart;
		break;
	case (UINT)STATE_TYPE::LDRUN:
		return new CLDRun;
		break;
	case (UINT)STATE_TYPE::LDRUNTOIDLE:
		return new CLDRunToIdle;
		break;
	case (UINT)STATE_TYPE::LDRUNUTURN:
		return new CLDRunUTurn;
		break;
	}
	return nullptr;
}

const wchar_t * CStateMgr::GetStateName(CState * _pState)
{
	switch ((STATE_TYPE)_pState->GetStateType())
	{
	case STATE_TYPE::IDLESTATE:
		return L"CIdleState";
		break;

	case STATE_TYPE::LDCORNERTRIGGER:
		return L"CLDCornerTrigger";
		break;

	case STATE_TYPE::LDDASH:
		return L"CLDDash";
		break;

	case STATE_TYPE::LDIDLE:
		return L"CLDIdle";
		break;

	case STATE_TYPE::LDIDLETORUN:
		return L"CLDIdleToRun";
		break;

	case STATE_TYPE::LDIDLEUTURN:
		return L"CLDIdleUTurn";
		break;

	case STATE_TYPE::LDJUMPFALL:
		return L"CLDJumpFall";
		break;

	case STATE_TYPE::LDJUMPLANDING:
		return L"CLDJumpLanding";
		break;

	case STATE_TYPE::LDJUMPSTART:
		return L"CLDJumpStart";
		break;

	case STATE_TYPE::LDRUN:
		return L"CLDRun";
		break;

	case STATE_TYPE::LDRUNTOIDLE:
		return L"CLDRunToIdle";
		break;

	case STATE_TYPE::LDRUNUTURN:
		return L"CLDRunUTurn";
		break;

	}
	return nullptr;
}