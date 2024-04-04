#include "pch.h"
#include "CCombine.h"

CCombine::CCombine()
	: CComputeShader(32, 32, 1)
{
	Create(L"shader\\combind.fx", "CS_Combind");
}

CCombine::~CCombine()
{
}


int CCombine::UpdateData()
{
	if (nullptr == m_RenderTargetCopyTex || nullptr == m_BloomTex || nullptr == m_RenderTarget)
		return E_FAIL;


	// �ؽ��� t0 �� ���ε�
	if (FAILED(m_RenderTargetCopyTex->UpdateData_CS_SRV(0)))
	{
		return E_FAIL;
	}

	if (FAILED(m_BloomTex->UpdateData_CS_SRV(1)))
	{
		return E_FAIL;
	}

	if (FAILED(m_RenderTarget->UpdateData_CS_UAV(0)))
	{
		return E_FAIL;
	}


	return S_OK;
}

void CCombine::UpdateGroupCount()
{
	// ������ �׷� �� üũ
	UINT width = m_RenderTarget->GetWidth();
	UINT height = m_RenderTarget->GetHeight();

	SetGroupX(1 + width / m_ThreadX);
	SetGroupY(1 + height / m_ThreadY);
	SetGroupZ(1);
}

void CCombine::Clear()
{
	m_RenderTargetCopyTex->Clear_CS_SRV();
	m_BloomTex->Clear_CS_SRV();
	m_RenderTarget->Clear_CS_UAV();
}

