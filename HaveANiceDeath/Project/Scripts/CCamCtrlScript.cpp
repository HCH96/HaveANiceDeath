#include "pch.h"
#include "CCamCtrlScript.h"

#include <Engine/CTimeMgr.h>
#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CLayer.h>
#include <Engine/CGameObject.h>


CCamCtrlScript::CCamCtrlScript()
	: CScript(CAMCTRLSCRIPT)
	, m_Speed(0.f)
	, m_SpeedScale(1500.f)
	, m_Target(nullptr)
	, m_Transition(nullptr)
	, m_IsTracking(false)
{
	AddScriptParam(SCRIPT_PARAM::FLOAT, "Speed", &m_SpeedScale);
	AddScriptParam(SCRIPT_PARAM::VEC3, "Target Offset", &m_CamOffset);
}

CCamCtrlScript::CCamCtrlScript(const CCamCtrlScript& _Origin)
	: CScript(CAMCTRLSCRIPT)
	, m_Speed(_Origin.m_Speed)
	, m_SpeedScale(_Origin.m_SpeedScale)
	, m_Target(nullptr)
	, m_Transition(nullptr)
{
	AddScriptParam(SCRIPT_PARAM::FLOAT, "Speed", &m_SpeedScale);
	AddScriptParam(SCRIPT_PARAM::VEC3, "Target Offset", &m_CamOffset);
}

CCamCtrlScript::~CCamCtrlScript()
{
}

void CCamCtrlScript::begin()
{
	CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	if (pLevel)
	{
		CLayer* CurLayer = pLevel->GetLayer(L"Player");
		m_Target = CurLayer->GetObjectByName(L"LD");

		//m_Transition = GetOwner()->GetChildByName(L"Transition");
		//if (m_Transition)
		//	m_Transition->Deactivate();
	}
}

#define CENTER		150.f
#define MAXWIDTH	(1600.f / 2.f)
#define MAXHEIGHT	(900.f / 2.f)
#define MAXDIFF		(MAXWIDTH - CENTER)

void CCamCtrlScript::tick()
{
	m_Move = Vec3();

	// track target
	if (m_Target)
	{
		Vec3 vTargetPos = m_Target->Transform()->GetWorldPos() + m_CamOffset;
		Vec3 vCamPos = GetOwner()->Transform()->GetWorldPos();
		vTargetPos.z = vCamPos.z;
		float vDist = (vTargetPos - vCamPos).Length();

		// case: in tracking distance
		if (vDist > CENTER)
		{
			m_IsTracking = true;
		}

		if (m_IsTracking)
		{
			if (vDist > MAXDIFF)
				vDist = MAXDIFF;
			vDist = vDist / MAXDIFF;

			m_Speed = m_SpeedScale * sinf(vDist * XM_PI / 2);
			Vec3 vDir = (vTargetPos - vCamPos).Normalize();
			Vec3 vUpdatePos = vCamPos + vDir * m_Speed * DT;

			// case: out of screen
			if (fabs(vUpdatePos.x - vTargetPos.x) > (MAXWIDTH - CENTER))
				vUpdatePos.x = vTargetPos.x - vDir.x * (MAXWIDTH - CENTER);
			if (fabs(vUpdatePos.y - vTargetPos.y) > (MAXHEIGHT))
				vUpdatePos.y = vTargetPos.y - vDir.y * (MAXHEIGHT);
			m_Move = vUpdatePos - vCamPos;

			// case: exceed target
			if (m_Move.Length() > (vTargetPos - vCamPos).Length())
				vUpdatePos = vTargetPos;

			// case: ���� �� �°��
			if ((vTargetPos - vCamPos).Length() < 1.f)
			{
				vUpdatePos = vTargetPos;
				m_IsTracking = false;
			}


			// update camera position
			//vUpdatePos = CheckCamArea(vUpdatePos);
			Transform()->SetRelativePos(Vec3(vUpdatePos.x, vUpdatePos.y, vCamPos.z));
			m_Move = vUpdatePos - vCamPos;
		}

	}

	// play effect
	if (!m_Effect.empty())
	{
		FCamEffect& CurEffect = m_Effect.front();
		CurEffect.fAccTime += DT;

		switch (CurEffect.Type)
		{
		case CAMEFFECT_TYPE::SHAKE:
		{
			float Strength = CurEffect.fVar;

			Vec3 vCurDelta;
			vCurDelta.x = sin(CurEffect.fAccTime * 30.f) * Strength;
			vCurDelta.y = cos(CurEffect.fAccTime * 10.f) * Strength;

			Vec3 vPrevDelta;
			float vPrevTime = CurEffect.fAccTime - DT;
			vPrevDelta.x = sin(vPrevTime * 30.f) * Strength;
			vPrevDelta.y = cos(vPrevTime * 10.f) * Strength;

			Vec3 Pos = Transform()->GetRelativePos() + vCurDelta - vPrevDelta;
			Transform()->SetRelativePos(Pos);

			m_Move = Vec3();
		}
		break;

		case CAMEFFECT_TYPE::TRANSITION_ON:
		{
			if (!m_Transition)
				break;

			//GamePlayStatic::Play2DSound(L"sound\\title\\Menu_Main_Whsh_Play_01.wav", 1, 0.3f);
			//m_Transition->Activate();
			//m_Transition->Animator2D()->Play(L"Transition", false, true);
			//m_Transition->Transform()->SetRelativeScale(Vec3(1600, 900, 0));
		}
		break;

		case CAMEFFECT_TYPE::TRANSITION_OFF:
		{
			if (!m_Transition)
				break;

			//m_Transition->Activate();
			//m_Transition->Animator2D()->Play(L"Transition", false);
			//m_Transition->Transform()->SetRelativeScale(Vec3(1600, 900, 0));
		}
		break;
		}

		if (CurEffect.fAccTime > CurEffect.fPlayTime)
			m_Effect.pop_front();
	}

	//if (m_Transition && m_Transition->IsActivate() && !m_Transition->Animator2D()->IsPlaying())
	//	m_Transition->Deactivate();
}


void CCamCtrlScript::SaveToFile(FILE* _File)
{
	fwrite(&m_Speed, 1, sizeof(float), _File);
	fwrite(&m_CamOffset, 1, sizeof(Vec3), _File);
}

void CCamCtrlScript::LoadFromFile(FILE* _File)
{
	fread(&m_Speed, 1, sizeof(float), _File);
	fread(&m_CamOffset, 1, sizeof(Vec3), _File);
}

void CCamCtrlScript::PushEffect(FCamEffect _Effect)
{
	m_Effect.push_back(_Effect);
}

void CCamCtrlScript::PushTransition(bool _Start)
{
	//FCamEffect Transition = {};
	//Transition.Type = _Start ? CAMEFFECT_TYPE::TRANSITION_ON : CAMEFFECT_TYPE::TRANSITION_OFF;
	//m_Effect.push_back(Transition);
}

Vec3 CCamCtrlScript::CheckCamArea(Vec3 _Pos)
{
	Vec3 ret = _Pos;

	//if (_Pos.x < -7200.f)
	//	ret.x = -7200.f;

	//if (_Pos.x > 7120.f)
	//	ret.x = 7120.f;

	return ret;
}