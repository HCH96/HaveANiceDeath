#include "pch.h"
#include "CRenderMgr.h"

#include "CDevice.h"
#include "CAssetMgr.h"

#include "CGameObject.h"
#include "CTransform.h"
#include "CMeshRender.h"

#include "CStructuredBuffer.h"



void CRenderMgr::init()
{
	// 광원효과를 위한 Structured Buffer 생성
	m_Light2DBuffer = new CStructuredBuffer;
	m_Light2DBuffer->Create(sizeof(tLightInfo), 10, SB_TYPE::READ_ONLY, true);

	// Debug 오브젝트 생성
	m_pDebugObj = new CGameObject;
	m_pDebugObj->AddComponent(new CTransform);
	m_pDebugObj->AddComponent(new CMeshRender);

	// PostProcessTex 생성
	Vec2 vRenderResolution = CDevice::GetInst()->GetRenderResolution();
	m_PostProcessTex = CAssetMgr::GetInst()->CreateTexture(L"PostProcessTex", (UINT)vRenderResolution.x, (UINT)vRenderResolution.y, DXGI_FORMAT_R8G8B8A8_UNORM, D3D11_BIND_SHADER_RESOURCE);

	// Bloom Texture 생성
	CreateBloomTex();

	// Noise Texture Load
	m_vecNoiseTex.push_back(CAssetMgr::GetInst()->Load<CTexture>(L"texture\\noise\\noise_01.png", L"texture\\noise\\noise_01.png"));
	m_vecNoiseTex.push_back(CAssetMgr::GetInst()->Load<CTexture>(L"texture\\noise\\noise_02.png", L"texture\\noise\\noise_02.png"));
	m_vecNoiseTex.push_back(CAssetMgr::GetInst()->Load<CTexture>(L"texture\\noise\\noise_03.jpg", L"texture\\noise\\noise_03.jpg"));

	// Noise Texture 바인딩
	m_vecNoiseTex[2]->UpdateData(14);
	m_vecNoiseTex[2]->UpdateData_CS_SRV(14);

	g_global.g_NoiseTexResolution = Vec2(m_vecNoiseTex[2]->GetWidth(), m_vecNoiseTex[2]->GetHeight());

	// RenderTarget Copy Texture
	m_RTCopyTex = CAssetMgr::GetInst()->CreateTexture(L"RTCopyTex", (UINT)vRenderResolution.x, (UINT)vRenderResolution.y, DXGI_FORMAT_R8G8B8A8_UNORM, D3D11_BIND_SHADER_RESOURCE, D3D11_USAGE_DEFAULT);
}

void CRenderMgr::CopyRenderTargetToPostProcessTarget()
{
	Ptr<CTexture> pRTTex = CAssetMgr::GetInst()->FindAsset<CTexture>(L"RenderTargetTex");
	CONTEXT->CopyResource(m_PostProcessTex->GetTex2D().Get(), pRTTex->GetTex2D().Get());
}

void CRenderMgr::CopyRTTexture()
{
	Ptr<CTexture> pRTTex = CAssetMgr::GetInst()->FindAsset<CTexture>(L"RenderTargetTex");

	CONTEXT->CopyResource(m_RTCopyTex->GetTex2D().Get(), pRTTex->GetTex2D().Get());
}

void CRenderMgr::CreateBloomTex()
{
	Vec2 Resolution = CDevice::GetInst()->GetRenderResolution();

	m_RTGlow = CAssetMgr::GetInst()->CreateTexture(L"GlowTexture", Resolution.x, Resolution.y, DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM, D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS, D3D11_USAGE_DEFAULT);


	for (int i = 1; i < m_BloomLevel; ++i)
	{
		int div = pow(2, i);

		// Bloom Down Texture
		Ptr<CTexture> pBloomFirstTex = CAssetMgr::GetInst()->CreateTexture(L"Bloom First " + std::to_wstring(i), Resolution.x/div, Resolution.y/div, DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM, D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET | D3D11_BIND_UNORDERED_ACCESS, D3D11_USAGE_DEFAULT);
		Ptr<CTexture> pBloomSecondTex = CAssetMgr::GetInst()->CreateTexture(L"Bloom Second " + std::to_wstring(i), Resolution.x/div, Resolution.y/div, DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM, D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET | D3D11_BIND_UNORDERED_ACCESS, D3D11_USAGE_DEFAULT);


		m_BloomFirst.push_back(pBloomFirstTex);
		m_BloomSecond.push_back(pBloomSecondTex);

	}


}