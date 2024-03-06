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
	// MainWindow, Resolution ����
	m_MainWindow = _HWND;
	m_Resolution = _Resolution;

	// �ػ� 
	RECT rt = { 0,0,(int)m_Resolution.x, (int)m_Resolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(m_MainWindow, nullptr, 10, 10, rt.right - rt.left, rt.bottom - rt.top, 0);

	// Device �ʱ�ȭ


	// Manager �ʱ�ȭ


	return S_OK;
}

void CEngine::progress()
{

}
