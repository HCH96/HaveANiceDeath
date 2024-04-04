#include "pch.h"
#include "CBlurX.h"

CBlurX::CBlurX()
	: CComputeShader(32, 32, 1)
{
	Create(L"shader\\blurx.fx", "CS_BlurX");
}

CBlurX::~CBlurX()
{

}


int CBlurX::UpdateData()
{
	if (nullptr == m_TargetTex || nullptr == m_ResourceTex)
		return E_FAIL;


	// �ؽ��� U0 �� ���ε�
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

void CBlurX::UpdateGroupCount()
{
	// ������ �׷� �� üũ
	UINT width = m_TargetTex->GetWidth();
	UINT height = m_TargetTex->GetHeight();

	SetGroupX(1 + width / m_ThreadX);
	SetGroupY(1 + height / m_ThreadY);
	SetGroupZ(1);
}

void CBlurX::Clear()
{
	m_ResourceTex->Clear_CS_SRV();
	m_TargetTex->Clear_CS_UAV();
}
