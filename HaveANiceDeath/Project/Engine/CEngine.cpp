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

#include "CGC.h"

CEngine::CEngine()
	: m_MainWindow(nullptr)
	, m_Resolution()
{
}

CEngine::~CEngine()
{
}

int CEngine::init(HWND _HWND, Vec2 _Resolution)
{
	// MainWindow, Resolution 저장
	m_MainWindow = _HWND;
	m_Resolution = _Resolution;

	// 해상도 
	RECT rt = { 0,0,(int)m_Resolution.x, (int)m_Resolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(m_MainWindow, nullptr, 10, 10, rt.right - rt.left, rt.bottom - rt.top, 0);

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


	CFontMgr::GetInst()->init();



	return S_OK;
}



void CEngine::progress()
{
	float clearcolor[4] = { 0.3,0.3,0.3,1.f };
	CDevice::GetInst()->ClearRenderTarget(clearcolor);

	// Manager Update
	CTimeMgr::GetInst()->tick();
	CKeyMgr::GetInst()->tick();

	// Level Update	
	CLevelMgr::GetInst()->tick();

	// 충돌 처리
	//CCollisionMgr::GetInst()->tick();

	// Render
	//CRenderMgr::GetInst()->tick();

	// FPS render
	CTimeMgr::GetInst()->render();

	// GC
	CGC::GetInst()->tick();

	// Task
	CTaskMgr::GetInst()->tick();
}