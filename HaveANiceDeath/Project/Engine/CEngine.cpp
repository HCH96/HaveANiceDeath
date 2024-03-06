#include "pch.h"
#include "CEngine.h"


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


	// Manager 초기화


	return S_OK;
}

void CEngine::progress()
{

}
