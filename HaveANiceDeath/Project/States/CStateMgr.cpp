#include "pch.h"
#include "CStateMgr.h"

#include "CComboMove01.h"
#include "CComboMove02.h"
#include "CComboMove03.h"
#include "CComboMove04.h"
#include "CComboStand01.h"
#include "CComboStand02.h"
#include "CComboStand03.h"
#include "CComboUp.h"
#include "CCrush.h"
#include "CCrushDown.h"
#include "CDrownedAppear.h"
#include "CDrownedAttack01.h"
#include "CDrownedDeath.h"
#include "CDrownedHit.h"
#include "CDrownedIdle.h"
#include "CDrownedRun.h"
#include "CDrownedStunEnd.h"
#include "CDrownedStunLoop.h"
#include "CDrownedStunStart.h"
#include "CDrownedSurprised.h"
#include "CDrownedUTurn.h"
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
	_vec.push_back(L"CComboMove01");
	_vec.push_back(L"CComboMove02");
	_vec.push_back(L"CComboMove03");
	_vec.push_back(L"CComboMove04");
	_vec.push_back(L"CComboStand01");
	_vec.push_back(L"CComboStand02");
	_vec.push_back(L"CComboStand03");
	_vec.push_back(L"CComboUp");
	_vec.push_back(L"CCrush");
	_vec.push_back(L"CCrushDown");
	_vec.push_back(L"CDrownedAppear");
	_vec.push_back(L"CDrownedAttack01");
	_vec.push_back(L"CDrownedDeath");
	_vec.push_back(L"CDrownedHit");
	_vec.push_back(L"CDrownedIdle");
	_vec.push_back(L"CDrownedRun");
	_vec.push_back(L"CDrownedStunEnd");
	_vec.push_back(L"CDrownedStunLoop");
	_vec.push_back(L"CDrownedStunStart");
	_vec.push_back(L"CDrownedSurprised");
	_vec.push_back(L"CDrownedUTurn");
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
	if (L"CComboMove01" == _strStateName)
		return new CComboMove01;
	if (L"CComboMove02" == _strStateName)
		return new CComboMove02;
	if (L"CComboMove03" == _strStateName)
		return new CComboMove03;
	if (L"CComboMove04" == _strStateName)
		return new CComboMove04;
	if (L"CComboStand01" == _strStateName)
		return new CComboStand01;
	if (L"CComboStand02" == _strStateName)
		return new CComboStand02;
	if (L"CComboStand03" == _strStateName)
		return new CComboStand03;
	if (L"CComboUp" == _strStateName)
		return new CComboUp;
	if (L"CCrush" == _strStateName)
		return new CCrush;
	if (L"CCrushDown" == _strStateName)
		return new CCrushDown;
	if (L"CDrownedAppear" == _strStateName)
		return new CDrownedAppear;
	if (L"CDrownedAttack01" == _strStateName)
		return new CDrownedAttack01;
	if (L"CDrownedDeath" == _strStateName)
		return new CDrownedDeath;
	if (L"CDrownedHit" == _strStateName)
		return new CDrownedHit;
	if (L"CDrownedIdle" == _strStateName)
		return new CDrownedIdle;
	if (L"CDrownedRun" == _strStateName)
		return new CDrownedRun;
	if (L"CDrownedStunEnd" == _strStateName)
		return new CDrownedStunEnd;
	if (L"CDrownedStunLoop" == _strStateName)
		return new CDrownedStunLoop;
	if (L"CDrownedStunStart" == _strStateName)
		return new CDrownedStunStart;
	if (L"CDrownedSurprised" == _strStateName)
		return new CDrownedSurprised;
	if (L"CDrownedUTurn" == _strStateName)
		return new CDrownedUTurn;
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
	case (UINT)STATE_TYPE::COMBOMOVE01:
		return new CComboMove01;
		break;
	case (UINT)STATE_TYPE::COMBOMOVE02:
		return new CComboMove02;
		break;
	case (UINT)STATE_TYPE::COMBOMOVE03:
		return new CComboMove03;
		break;
	case (UINT)STATE_TYPE::COMBOMOVE04:
		return new CComboMove04;
		break;
	case (UINT)STATE_TYPE::COMBOSTAND01:
		return new CComboStand01;
		break;
	case (UINT)STATE_TYPE::COMBOSTAND02:
		return new CComboStand02;
		break;
	case (UINT)STATE_TYPE::COMBOSTAND03:
		return new CComboStand03;
		break;
	case (UINT)STATE_TYPE::COMBOUP:
		return new CComboUp;
		break;
	case (UINT)STATE_TYPE::CRUSH:
		return new CCrush;
		break;
	case (UINT)STATE_TYPE::CRUSHDOWN:
		return new CCrushDown;
		break;
	case (UINT)STATE_TYPE::DROWNEDAPPEAR:
		return new CDrownedAppear;
		break;
	case (UINT)STATE_TYPE::DROWNEDATTACK01:
		return new CDrownedAttack01;
		break;
	case (UINT)STATE_TYPE::DROWNEDDEATH:
		return new CDrownedDeath;
		break;
	case (UINT)STATE_TYPE::DROWNEDHIT:
		return new CDrownedHit;
		break;
	case (UINT)STATE_TYPE::DROWNEDIDLE:
		return new CDrownedIdle;
		break;
	case (UINT)STATE_TYPE::DROWNEDRUN:
		return new CDrownedRun;
		break;
	case (UINT)STATE_TYPE::DROWNEDSTUNEND:
		return new CDrownedStunEnd;
		break;
	case (UINT)STATE_TYPE::DROWNEDSTUNLOOP:
		return new CDrownedStunLoop;
		break;
	case (UINT)STATE_TYPE::DROWNEDSTUNSTART:
		return new CDrownedStunStart;
		break;
	case (UINT)STATE_TYPE::DROWNEDSURPRISED:
		return new CDrownedSurprised;
		break;
	case (UINT)STATE_TYPE::DROWNEDUTURN:
		return new CDrownedUTurn;
		break;
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
	case STATE_TYPE::COMBOMOVE01:
		return L"CComboMove01";
		break;

	case STATE_TYPE::COMBOMOVE02:
		return L"CComboMove02";
		break;

	case STATE_TYPE::COMBOMOVE03:
		return L"CComboMove03";
		break;

	case STATE_TYPE::COMBOMOVE04:
		return L"CComboMove04";
		break;

	case STATE_TYPE::COMBOSTAND01:
		return L"CComboStand01";
		break;

	case STATE_TYPE::COMBOSTAND02:
		return L"CComboStand02";
		break;

	case STATE_TYPE::COMBOSTAND03:
		return L"CComboStand03";
		break;

	case STATE_TYPE::COMBOUP:
		return L"CComboUp";
		break;

	case STATE_TYPE::CRUSH:
		return L"CCrush";
		break;

	case STATE_TYPE::CRUSHDOWN:
		return L"CCrushDown";
		break;

	case STATE_TYPE::DROWNEDAPPEAR:
		return L"CDrownedAppear";
		break;

	case STATE_TYPE::DROWNEDATTACK01:
		return L"CDrownedAttack01";
		break;

	case STATE_TYPE::DROWNEDDEATH:
		return L"CDrownedDeath";
		break;

	case STATE_TYPE::DROWNEDHIT:
		return L"CDrownedHit";
		break;

	case STATE_TYPE::DROWNEDIDLE:
		return L"CDrownedIdle";
		break;

	case STATE_TYPE::DROWNEDRUN:
		return L"CDrownedRun";
		break;

	case STATE_TYPE::DROWNEDSTUNEND:
		return L"CDrownedStunEnd";
		break;

	case STATE_TYPE::DROWNEDSTUNLOOP:
		return L"CDrownedStunLoop";
		break;

	case STATE_TYPE::DROWNEDSTUNSTART:
		return L"CDrownedStunStart";
		break;

	case STATE_TYPE::DROWNEDSURPRISED:
		return L"CDrownedSurprised";
		break;

	case STATE_TYPE::DROWNEDUTURN:
		return L"CDrownedUTurn";
		break;

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