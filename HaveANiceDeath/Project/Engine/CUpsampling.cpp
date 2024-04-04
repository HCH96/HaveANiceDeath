#include "pch.h"
#include "CUpsampling.h"

CUpsampling::CUpsampling()
	: CComputeShader(32, 32, 1)
{
	Create(L"shader\\upsampling.fx", "CS_UpSampling");
}

CUpsampling::~CUpsampling()
{
}


int CUpsampling::UpdateData()
{
	if (nullptr == m_TargetTex || nullptr == m_ResourceTex)
		return E_FAIL;


	// 텍스쳐 U0 에 바인딩
	if (FAILED(m_ResourceTex->UpdateData_CS_SRV(0)))
	{
		return E_FAIL;
	}

	if (FAILED(m_TargetTex->UpdateData_CS_UAV(0)))
	{
		return E_FAIL;
	}

	return S_OK;
}

void CUpsampling::UpdateGroupCount()
{
	// 스레드 그룹 수 체크
	UINT width = m_TargetTex->GetWidth();
	UINT height = m_TargetTex->GetHeight();

	SetGroupX(1 + width / m_ThreadX);
	SetGroupY(1 + height / m_ThreadY);
	SetGroupZ(1);
}

void CUpsampling::Clear()
{
	m_ResourceTex->Clear_CS_SRV();
	m_TargetTex->Clear_CS_UAV();
}

