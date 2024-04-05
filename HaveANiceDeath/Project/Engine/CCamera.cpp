#include "pch.h"
#include "CCamera.h"

#include "CDevice.h"
#include "CLevelMgr.h"
#include "CRenderMgr.h"

#include "CLevel.h"
#include "CLayer.h"

#include "CGameObject.h"

#include "CTransform.h"
#include "CRenderComponent.h"

CCamera::CCamera()
	: CComponent(COMPONENT_TYPE::CAMERA)
	, m_ProjType(PROJ_TYPE::ORTHOGRAPHIC)
	, m_FOV(XM_PI / 2.f)
	, m_Width(0.f)
	, m_Scale(1.f)
	, m_AspectRatio(1.f)
	, m_Far(10000.f)
	, m_LayerCheck(0)
	, m_CameraPriority(-1)
{
	// 종횡비 설정
	Vec2 vResol = CDevice::GetInst()->GetRenderResolution();
	m_AspectRatio = vResol.x / vResol.y;
}

CCamera::~CCamera()
{
}

bool CCamera::IsLayerCheck(UINT _LayerIdx)
{
	return m_LayerCheck & (1 << _LayerIdx);
}

bool CCamera::IsLayerCheck(const wstring& _strLayerName)
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	CLayer* pLayer = pCurLevel->GetLayer(_strLayerName);

	if (nullptr == pLayer)
	{
		MessageBoxA(nullptr, "레이어가 없습니다.", "IsLayerCheck Failed!", MB_OK);
		return false;
	}

	int idx = pLayer->GetLayerIdx();
	
	return IsLayerCheck(idx);
}

void CCamera::LayerCheck(UINT _LayerIdx, bool _bCheck)
{
	if (_bCheck)
	{
		m_LayerCheck |= (1 << _LayerIdx);
	}
	else
	{
		m_LayerCheck &= ~(1 << _LayerIdx);
	}
}

void CCamera::LayerCheck(const wstring& _strLayerName, bool _bCheck)
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	CLayer* pLayer = pCurLevel->GetLayer(_strLayerName);

	if (nullptr == pLayer)
		return;

	int idx = pLayer->GetLayerIdx();
	LayerCheck(idx, _bCheck);
}

Vec2 CCamera::GetWorldPosInWindow(Vec2 _Diff)
{
	Vec3 Center = Transform()->GetWorldPos();
	
	Vec2 vResol = CDevice::GetInst()->GetRenderResolution();
	Vec2 vWinSize = Vec2(vResol.x * m_Scale, (vResol.x / m_AspectRatio) * m_Scale);

	Vec2 MouseWorldPos = Vec2(Center.x + _Diff.x * m_Scale, Center.y + _Diff.y * m_Scale);

	return MouseWorldPos;
}

void CCamera::begin()
{
	// 카메라를 우선순위값에 맞게 RenderMgr 에 등록시킴
	CRenderMgr::GetInst()->RegisterCamera(this, m_CameraPriority);
}

void CCamera::finaltick()
{
	// 뷰 행렬을 계산한다.
	// 카메라를 원점으로 이동시키는 이동 행렬
	Vec3 vCamPos = Transform()->GetRelativePos();
	Matrix matTrans = XMMatrixTranslation(-vCamPos.x, -vCamPos.y, -vCamPos.z);

	// 카메라의 각 우, 상, 전 방 방향을 기저축이랑 일치시키도록 회전하는 회전행렬
	Vec3 vRight = Transform()->GetWorldDir(DIR_TYPE::RIGHT);
	Vec3 vUp = Transform()->GetWorldDir(DIR_TYPE::UP);
	Vec3 vFront = Transform()->GetWorldDir(DIR_TYPE::FRONT);

	Matrix matRotate = XMMatrixIdentity();
	matRotate._11 = vRight.x; matRotate._12 = vUp.x; matRotate._13 = vFront.x;
	matRotate._21 = vRight.y; matRotate._22 = vUp.y; matRotate._23 = vFront.y;
	matRotate._31 = vRight.z; matRotate._32 = vUp.z; matRotate._33 = vFront.z;

	// 이동 x 회전 = view 행렬
	m_matView = matTrans * matRotate;

	// 투영 방식에 따른 투영 행렬을 계산한다.
	m_matProj = XMMatrixIdentity();

	if (PROJ_TYPE::ORTHOGRAPHIC == m_ProjType)
	{
		// 직교투영
		Vec2 vResol = CDevice::GetInst()->GetRenderResolution();
		m_matProj = XMMatrixOrthographicLH(vResol.x * m_Scale, (vResol.x / m_AspectRatio) * m_Scale, 1.f, m_Far);
	}
	else
	{
		// 원근투영
		m_matProj = XMMatrixPerspectiveFovLH(m_FOV, m_AspectRatio, 1.f, m_Far);
	}
}

void CCamera::SortObject()
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();

	for (int i = 0; i < LAYER_MAX; ++i)
	{
		// 카메라가 찍도록 설정된 Layer 가 아니면 무시
		if (false == (m_LayerCheck & (1 << i)))
			continue;

		CLayer* pLayer = pCurLevel->GetLayer(i);
		const vector<CGameObject*>& vecObjects = pLayer->GetLayerObjects();
		for (size_t j = 0; j < vecObjects.size(); ++j)
		{
			// 메쉬, 재질, 쉐이더 확인
			if (!(vecObjects[j]->GetRenderComponent()
				&& vecObjects[j]->GetRenderComponent()->GetMesh().Get()
				&& vecObjects[j]->GetRenderComponent()->GetMaterial().Get()
				&& vecObjects[j]->GetRenderComponent()->GetMaterial()->GetShader().Get()))
			{
				continue;
			}

			SHADER_DOMAIN domain = vecObjects[j]->GetRenderComponent()->GetMaterial()->GetShader()->GetDomain();

			switch (domain)
			{
			case SHADER_DOMAIN::DOMAIN_OPAQUE:
				m_vecOpaque.push_back(vecObjects[j]);
				break;
			case SHADER_DOMAIN::DOMAIN_MASKED:
				m_vecMasked.push_back(vecObjects[j]);
				break;
			case SHADER_DOMAIN::DOMAIN_TRANSPARENT:
				m_vecTransparent.push_back(vecObjects[j]);
				break;
			case SHADER_DOMAIN::DOMAIN_POSTPROCESS:
				m_vecPostProcess.push_back(vecObjects[j]);
				break;
			case SHADER_DOMAIN::DOMAIN_DEBUG:
				break;
			}
		}
	}
}

void CCamera::render()
{
	// 계산한 view 행렬과 proj 행렬을 전역변수에 담아둔다.
	g_Transform.matView = m_matView;
	g_Transform.matProj = m_matProj;

	// Domain 순서대로 렌더링
	render(m_vecOpaque);
	render(m_vecMasked);
	render(m_vecTransparent);

	// 후처리 작업
	render_postprocess();

	// Bloom postprocess
	render_Bloom();
}

void CCamera::render(vector<CGameObject*>& _vecObj)
{
	for (size_t i = 0; i < _vecObj.size(); ++i)
	{
		_vecObj[i]->render();
	}
	_vecObj.clear();
}

void CCamera::render_postprocess()
{
	for (size_t i = 0; i < m_vecPostProcess.size(); ++i)
	{
		// 최종 렌더링 이미지를 후처리 타겟에 복사
		CRenderMgr::GetInst()->CopyRenderTargetToPostProcessTarget();

		// 복사받은 후처리 텍스쳐를 t13 레지스터에 바인딩
		Ptr<CTexture> pPostProcessTex = CRenderMgr::GetInst()->GetPostProcessTex();
		pPostProcessTex->UpdateData(13);

		// 후처리 오브젝트 렌더링
		m_vecPostProcess[i]->render();
	}

	m_vecPostProcess.clear();
}

#include "CBlurX.h"
#include "CBlurY.h"
#include "CCombine.h"
#include "CUpsampling.h"
#include "CDownSampling.h"

void CCamera::render_Bloom()
{
	CDevice::GetInst()->ClearRenderTarget();

	// 랜더타겟 텍스쳐
	Ptr<CTexture> mainRTTex = CAssetMgr::GetInst()->FindAsset<CTexture>(L"RenderTargetTex");

	// 렌더타겟 복사
	CRenderMgr::GetInst()->CopyRTTexture();

	// 랜더타겟 복사본
	Ptr<CTexture> RTCopy = CRenderMgr::GetInst()->GetRTCopyTex();

	// Glow Tex
	Ptr<CTexture> GlowTex = CRenderMgr::GetInst()->GetRTGlow();

	// Bloom Tex
	vector<Ptr<CTexture>> BloomFirst = CRenderMgr::GetInst()->GetBloomFirst();
	vector<Ptr<CTexture>> BloomSecond =  CRenderMgr::GetInst()->GetBloomSecond();

	// Bloom Level
	int BloomLevel = CRenderMgr::GetInst()->GetBloomLevel();

	// Compute Shader
	Ptr<CBlurX> BlurXShader = (CBlurX*)CAssetMgr::GetInst()->FindAsset<CComputeShader>(L"BlurXShader").Get();
	Ptr<CBlurY> BlurYShader = (CBlurY*)CAssetMgr::GetInst()->FindAsset<CComputeShader>(L"BlurYShader").Get();
	Ptr<CDownSampling> DownScalingShader = (CDownSampling*)CAssetMgr::GetInst()->FindAsset<CComputeShader>(L"DownSamplingShader").Get();
	Ptr<CUpsampling> UpScalingShader = (CUpsampling*)CAssetMgr::GetInst()->FindAsset<CComputeShader>(L"UpSamplingShader").Get();
	Ptr<CCombine> CombineShader = (CCombine*)CAssetMgr::GetInst()->FindAsset<CComputeShader>(L"CombineShader").Get();

	// Down Sampling
	for (int i = 0; i < BloomLevel-1; ++i)
	{
		if (i == 0)
		{
			DownScalingShader->SetResourceTex(GlowTex);
		}
		else
		{
			DownScalingShader->SetResourceTex(BloomFirst[i-1]);
		}

		DownScalingShader->SetTargetTexture(BloomFirst[i]);
		DownScalingShader->Execute();
	}

	// BlurXY, Up Scaling
	for (int i = BloomLevel-2 ; i >= 0; --i)
	{
		// Blur X
		BlurXShader->SetResourceTex(BloomFirst[i]);          
		BlurXShader->SetTargetTexture(BloomSecond[i]);       
		BlurXShader->Execute();

		// Blur Y
		BlurYShader->SetResourceTex(BloomSecond[i]);
		BlurYShader->SetTargetTexture(BloomFirst[i]);
		BlurYShader->Execute();

		// Up Scaling
		UpScalingShader->SetResourceTex(BloomFirst[i]);

		if (i == 0)
		{
			UpScalingShader->SetTargetTexture(GlowTex);
		}
		else
		{
			UpScalingShader->SetTargetTexture(BloomFirst[i - 1]);
		}
		UpScalingShader->Execute();
	}

	// Combine
	CombineShader->SetRenderTargetCopyTex(RTCopy);
	CombineShader->SetBloomTex(GlowTex);
	CombineShader->SetRenderTargetTex(mainRTTex);
	CombineShader->Execute();

	CDevice::GetInst()->SetRenderTarget();
}

void CCamera::SaveToFile(FILE* _File)
{
	fwrite(&m_ProjType, sizeof(PROJ_TYPE), 1, _File);
	fwrite(&m_FOV, sizeof(float), 1, _File);
	fwrite(&m_Width, sizeof(float), 1, _File);
	fwrite(&m_Scale, sizeof(float), 1, _File);
	//fwrite(&m_AspectRatio, sizeof(float), 1, _File);
	fwrite(&m_Far, sizeof(float), 1, _File);
	fwrite(&m_LayerCheck, sizeof(UINT), 1, _File);
	fwrite(&m_CameraPriority, sizeof(int), 1, _File);
}

void CCamera::LoadFromFile(FILE* _File)
{
	fread(&m_ProjType, sizeof(PROJ_TYPE), 1, _File);
	fread(&m_FOV, sizeof(float), 1, _File);
	fread(&m_Width, sizeof(float), 1, _File);
	fread(&m_Scale, sizeof(float), 1, _File);
	//fread(&m_AspectRatio, sizeof(float), 1, _File);
	fread(&m_Far, sizeof(float), 1, _File);
	fread(&m_LayerCheck, sizeof(UINT), 1, _File);
	fread(&m_CameraPriority, sizeof(int), 1, _File);
}
