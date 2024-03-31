#include "pch.h"
#include "CStateMgr.h"

#include "CIdleState.h"
#include "CLDIdle.h"
#include "CLDIdleUTurn.h"

void CStateMgr::GetStateInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"CIdleState");
	_vec.push_back(L"CLDIdle");
	_vec.push_back(L"CLDIdleUTurn");
}

CState* CStateMgr::GetState(const wstring& _strStateName)
{
	if (L"CIdleState" == _strStateName)
		return new CIdleState;
	if (L"CLDIdle" == _strStateName)
		return new CLDIdle;
	if (L"CLDIdleUTurn" == _strStateName)
		return new CLDIdleUTurn;
	return nullptr;
}

CState* CStateMgr::GetState(UINT _iStateType)
{
	switch (_iStateType)
	{
	case (UINT)STATE_TYPE::IDLESTATE:
		return new CIdleState;
		break;
	case (UINT)STATE_TYPE::LDIDLE:
		return new CLDIdle;
		break;
	case (UINT)STATE_TYPE::LDIDLEUTURN:
		return new CLDIdleUTurn;
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

	case STATE_TYPE::LDIDLE:
		return L"CLDIdle";
		break;

	case STATE_TYPE::LDIDLEUTURN:
		return L"CLDIdleUTurn";
		break;

	}
	return nullptr;
}