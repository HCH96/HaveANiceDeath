#include "pch.h"
#include "CEngine.h"

#include "CDevice.h"

#include "CPathMgr.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CAssetMgr.h"
#include "CLevelMgr.h"
#include "CTaskMgr.h"
#include "CFontMgr.h"
#include "CRenderMgr.h"
#include "CGC.h"
#include "CCollisionMgr.h"

#include "CSound.h"

CEngine::CEngine()
	: m_MainWindow(nullptr)
	, m_Resolution()
{
}

CEngine::~CEngine()
{
	if (nullptr != CSound::g_pFMOD)
	{
		CSound::g_pFMOD->release();
		CSound::g_pFMOD = nullptr;
	}
}

int CEngine::init(HWND _HWND, Vec2 _Resolution)
{
	// MainWindow, Resolution 저장
	m_MainWindow = _HWND;
	m_Resolution = _Resolution;

	// Device 초기화
	if (FAILED(CDevice::GetInst()->init(m_MainWindow, m_Resolution)))
	{
		MessageBox(nullptr, L"Device 초기화 실패", L"초기화 실패", MB_OK);
		return E_FAIL;
	}

	// Manager 초기화
	CPathMgr::init();
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CAssetMgr::GetInst()->init();
	CRenderMgr::GetInst()->init();
	CLevelMgr::GetInst()->init();
	CFontMgr::GetInst()->init();
	CCollisionMgr::GetInst()->init();

	return S_OK;
}



void CEngine::progress()
{

	// Manager Update
	CTimeMgr::GetInst()->tick();
	CKeyMgr::GetInst()->tick();

	// FMOD Update
	CSound::g_pFMOD->update();

	// Level Update	
	CLevelMgr::GetInst()->tick();

	// Render
	CRenderMgr::GetInst()->tick();

	CRenderMgr::GetInst()->CopyRTTexture();

	// GC
	CGC::GetInst()->tick();

	// Task
	CTaskMgr::GetInst()->tick();
}