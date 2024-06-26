#include "pch.h"
#include "CRenderMgr.h"

#include "CDevice.h"
#include "CConstBuffer.h"
#include "CStructuredBuffer.h"

#include "CTimeMgr.h"
#include "CAssetMgr.h"
#include "CLevelMgr.h"
#include "CLevel.h"

#include "components.h"

CRenderMgr::CRenderMgr()
	: m_Light2DBuffer(nullptr)
	, m_pDebugObj(nullptr)
	, m_DebugPosition(true)
	, m_EditorCam(nullptr)
	, m_RenderFunc(nullptr)
	, m_RTGlow(nullptr)
	, m_BloomLevel(5)
{
	m_RenderFunc = &CRenderMgr::render_play;

#ifndef _RELEASE_GAME
	m_isEditorMode = true;
#else
	m_isEditorMode = false;
#endif

}

CRenderMgr::~CRenderMgr()
{
	if (nullptr != m_pDebugObj)
		delete m_pDebugObj;

	if (nullptr != m_Light2DBuffer)
		delete m_Light2DBuffer;
}

void CRenderMgr::tick()
{
	// Output Merge State�� ����Ÿ�ٰ� �X�����ٽ� �ؽ��ĸ� ���
	CDevice::GetInst()->SetRenderTarget();

	// Clear
	Vec4 vClearColor = Vec4(0.f, 0.f, 0.f, 1.f);
	CDevice::GetInst()->ClearRenderTarget(vClearColor);

	UpdateData();

	(this->*m_RenderFunc)();
	render_debug();

	Clear();
}

void CRenderMgr::ActiveEditorMode(bool _bActive)
{
	if (_bActive)
	{
		m_RenderFunc = &CRenderMgr::render_editor;
		m_isEditorMode = true;
	}
	else
	{
		m_RenderFunc = &CRenderMgr::render_play;
		m_isEditorMode = false;
	}
}



void CRenderMgr::render_play()
{
	// ViewPort ����
	CDevice::GetInst()->SetViewPort(CDevice::GetInst()->GetRenderResolution());

	for (size_t i = 0; i < m_vecCam.size(); ++i)
	{
		m_vecCam[i]->SortObject();
		m_vecCam[i]->DepthSort();
		m_vecCam[i]->render();
	}
}

void CRenderMgr::render_editor()
{
	// ViewPort ����
	CDevice::GetInst()->SetViewPort(CDevice::GetInst()->GetRenderResolution());

	if (nullptr == m_EditorCam)
		return;

	m_EditorCam->SortObject();
	m_EditorCam->DepthSort();
	m_EditorCam->render();
}

void CRenderMgr::render_debug()
{
	// ViewPort ����
	CDevice::GetInst()->SetViewPort(CDevice::GetInst()->GetRenderResolution());

	// ī�޶� ���ٸ� return
	if (m_vecCam.empty() && m_EditorCam == nullptr)
	{
		return;
	}

	// ������ ����� ���� ������ ī�޶� ���
	if (m_isEditorMode)
	{
		g_Transform.matView = m_EditorCam->GetViewMat();
		g_Transform.matProj = m_EditorCam->GetProjMat();
	}
	else
	{
		g_Transform.matView = m_vecCam[0]->GetViewMat();
		g_Transform.matProj = m_vecCam[0]->GetProjMat();
	}

	list<tDebugShapeInfo>::iterator iter = m_DbgShapeInfo.begin();
	for (; iter != m_DbgShapeInfo.end(); )
	{
		// Mesh ����
		switch ((*iter).eShape)
		{
		case DEBUG_SHAPE::RECT:
			m_pDebugObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh_Debug"));
			break;
		case DEBUG_SHAPE::CIRCLE:
			m_pDebugObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"CircleMesh_Debug"));
			break;
		case DEBUG_SHAPE::CROSS:
			m_pDebugObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"CrossMesh"));
			break;
		case DEBUG_SHAPE::CUBE:
			m_pDebugObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"CubeMesh"));
			break;
		case DEBUG_SHAPE::SPHERE:
			m_pDebugObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"SphereMesh"));
			break;
		default:
			break;
		}

		// Mtrl, Color ����
		m_pDebugObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"DebugShapeMtrl"));
		m_pDebugObj->MeshRender()->GetMaterial()->SetScalarParam(SCALAR_PARAM::VEC4_0, (*iter).vColor);


		D3D11_PRIMITIVE_TOPOLOGY PrevTopology = m_pDebugObj->MeshRender()->GetMaterial()->GetShader()->GetTopology();
		if (DEBUG_SHAPE::CROSS == (*iter).eShape)
		{
			m_pDebugObj->MeshRender()->GetMaterial()->GetShader()->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_LINELIST);
		}

		m_pDebugObj->Transform()->SetWorldMat((*iter).matWorld);
		m_pDebugObj->render();

		m_pDebugObj->MeshRender()->GetMaterial()->GetShader()->SetTopology(PrevTopology);

		(*iter).fLifeTime += DT;
		if ((*iter).fDuration <= (*iter).fLifeTime)
		{
			iter = m_DbgShapeInfo.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void CRenderMgr::UpdateData()
{
	g_global.g_Light2DCount = (int)m_vecLight2D.size();

	// ���� ������ ������Ʈ
	static CConstBuffer* pCB = CDevice::GetInst()->GetConstBuffer(CB_TYPE::GLOBAL_DATA);
	pCB->SetData(&g_global);

	pCB->UpdateData();
	pCB->UpdateData_CS();

	// 2D �������� ������Ʈ
	static vector<tLightInfo> vecLight2DInfo;

	for (size_t i = 0; i < m_vecLight2D.size(); ++i)
	{
		const tLightInfo& info = m_vecLight2D[i]->GetLightInfo();
		vecLight2DInfo.push_back(info);
	}

	if (!vecLight2DInfo.empty())
	{
		m_Light2DBuffer->SetData(vecLight2DInfo.data(), (UINT)vecLight2DInfo.size());
	}
	m_Light2DBuffer->UpdateData(11);

	vecLight2DInfo.clear();
}

void CRenderMgr::Clear()
{
	m_vecLight2D.clear();
}


void CRenderMgr::RegisterCamera(CCamera* _Cam, int _Idx)
{
	if (m_vecCam.size() <= _Idx + 1)
	{
		m_vecCam.resize(_Idx + 1);
	}

	// ������ �켱������ ī�޶� �̹� �����ϸ� assert
	assert(nullptr == m_vecCam[_Idx]);

	m_vecCam[_Idx] = _Cam;
}