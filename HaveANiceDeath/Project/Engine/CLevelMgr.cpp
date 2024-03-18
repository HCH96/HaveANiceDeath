#include "pch.h"
#include "CLevelMgr.h"

#include "CDevice.h"

#include "CAssetMgr.h"
#include "CTaskMgr.h"
#include "CCollisionMgr.h"

#include "CLevel.h"
#include "CLayer.h"

//====== 임시 ======
#include "CGameObject.h"
#include "components.h"
#include "CRenderMgr.h"
#include "CAnimator2D.h"
#include "CCollider2D.h"
#include "CParticleSystem.h"


CLevelMgr::CLevelMgr()
	: m_CurLevel(nullptr)
{

}

CLevelMgr::~CLevelMgr()
{
	if (nullptr != m_CurLevel)
		delete m_CurLevel;
}

void CLevelMgr::init()
{
	//CLevel* pTempLevel = new CLevel;

	//pTempLevel->GetLayer(0)->SetName(L"Default");
	//pTempLevel->GetLayer(1)->SetName(L"Background");
	//pTempLevel->GetLayer(2)->SetName(L"Tile");
	//pTempLevel->GetLayer(3)->SetName(L"Player");
	//pTempLevel->GetLayer(4)->SetName(L"Monster");
	//pTempLevel->GetLayer(5)->SetName(L"Light");
	//pTempLevel->GetLayer(6)->SetName(L"Tile");
	//pTempLevel->GetLayer(31)->SetName(L"UI");

	//// Main Camera Object 생성
	//CGameObject* pCamObj = new CGameObject;
	//pCamObj->SetName(L"MainCamera");
	//pCamObj->AddComponent(new CTransform);
	//pCamObj->AddComponent(new CCamera);

	//pCamObj->Transform()->SetRelativePos(Vec3(0.f, 0.f, 0.f));
	//pCamObj->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 0.f));

	//pCamObj->Camera()->SetProjType(PROJ_TYPE::PERSPECTIVE);
	//pCamObj->Camera()->SetCameraPriority(0);
	//pCamObj->Camera()->LayerCheckAll();
	//pCamObj->Camera()->LayerCheck(31, false);


	//pTempLevel->AddObject(pCamObj, 0);

	//// UI 카메라 생성
	//pCamObj = new CGameObject;
	//pCamObj->SetName(L"UICamera");
	//pCamObj->AddComponent(new CTransform);
	//pCamObj->AddComponent(new CCamera);

	//pCamObj->Transform()->SetRelativePos(Vec3(0.5f, 0.f, 0.f));
	//pCamObj->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 0.f));

	//pCamObj->Camera()->SetCameraPriority(1);
	//pCamObj->Camera()->LayerCheck(31, true);

	//pTempLevel->AddObject(pCamObj, 0);

	//// 전역 광원 추가
	//CGameObject* pLight = new CGameObject;
	//pLight->SetName(L"Directional Light");
	//pLight->AddComponent(new CTransform);
	//pLight->AddComponent(new CLight2D);

	//pLight->Light2D()->SetLightType(LIGHT_TYPE::DIRECTIONAL);
	//pLight->Light2D()->SetAmbient(Vec3(0.8f, 0.8f, 0.8f));
	//pTempLevel->AddObject(pLight, L"Light");

	//CGameObject* pObj = nullptr;

	//// Backgruond Object 생성
	//pObj = new CGameObject;
	//pObj->SetName(L"Background");

	//pObj->AddComponent(new CTransform);
	//pObj->AddComponent(new CMeshRender);

	//pObj->Transform()->SetRelativePos(Vec3(0.f, 0.f, 600.f));
	//pObj->Transform()->SetRelativeScale(Vec3(1600.f, 800.f, 1.f));

	//pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	//pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"BackgroundMtrl"));

	//Ptr<CTexture> pTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Background.jpg", L"texture\\Background.jpg");
	//pObj->MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, pTex);

	//pTempLevel->AddObject(pObj, L"Background", false);

	//// Player Object 생성
	//pObj = new CGameObject;
	//pObj->SetName(L"Player");

	//pObj->AddComponent(new CTransform);
	//pObj->AddComponent(new CCollider2D);
	//pObj->AddComponent(new CAnimator2D);
	//pObj->AddComponent(new CMeshRender);

	//pObj->Transform()->SetRelativePos(Vec3(300.f, 0.f, 500.f));
	//pObj->Transform()->SetRelativeScale(Vec3(200.f, 200.f, 1.f));

	//pObj->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	//pObj->Collider2D()->SetScale(Vec3(100.f, 100.f, 1.f));

	//pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	//pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));
	//pObj->MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Character.png", L"texture\\Character.png"));

	//pTempLevel->AddObject(pObj, L"Player", false);

	//// Particle Object
	//CGameObject* pParticleObj = new CGameObject;
	//pParticleObj->SetName(L"Particle");

	//pParticleObj->AddComponent(new CTransform);
	//pParticleObj->AddComponent(new CParticleSystem);

	//pParticleObj->Transform()->SetRelativePos(Vec3(0.f, 0.f, 200.f));

	//pTempLevel->AddObject(pParticleObj, L"Player", false);


	//// Monst Object 생성
	//pObj = new CGameObject;
	//pObj->SetName(L"Monster");

	//pObj->AddComponent(new CTransform);
	//pObj->AddComponent(new CCollider2D);
	//pObj->AddComponent(new CMeshRender);

	//pObj->Transform()->SetRelativePos(Vec3(300.f, 0.f, 500.f));
	//pObj->Transform()->SetRelativeScale(Vec3(200.f, 200.f, 1.f));

	//pObj->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	//pObj->Collider2D()->SetScale(Vec3(100.f, 100.f, 1.f));

	//pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	//pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));
	//pObj->MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Character.png", L"texture\\Character.png"));

	//pTempLevel->AddObject(pObj, L"Monster", false);

	//CCollisionMgr::GetInst()->LayerCheck(3, 4);

	//CLevelMgr::GetInst()->ChangeLevel(pTempLevel, LEVEL_STATE::PLAY);
}

void CLevelMgr::ChangeLevel(CLevel* _NextLevel, LEVEL_STATE _NextLevelStartState)
{
	tTask task = {};

	task.Type = TASK_TYPE::CHANGE_LEVEL;
	task.Param_1 = (DWORD_PTR)_NextLevel;
	task.Param_2 = (DWORD_PTR)_NextLevelStartState;

	CTaskMgr::GetInst()->AddTask(task);
}

void CLevelMgr::ChangeLevelState(LEVEL_STATE _State)
{
	tTask task = {};

	task.Type = TASK_TYPE::CHANGE_LEVELSTATE;
	task.Param_1 = (DWORD_PTR)m_CurLevel;
	task.Param_2 = (DWORD_PTR)_State;

	CTaskMgr::GetInst()->AddTask(task);
}

void CLevelMgr::ChangeLevel_Task(CLevel* _NextLevel, LEVEL_STATE _NextLevelState)
{
	assert(!(m_CurLevel == _NextLevel));

	if (nullptr != m_CurLevel)
		delete m_CurLevel;

	m_CurLevel = _NextLevel;

	if (nullptr != m_CurLevel)
		m_CurLevel->ChangeState(_NextLevelState);
}


void CLevelMgr::tick()
{
	if (nullptr == m_CurLevel)
		return;

	// 이전 프레임에 등록된 오브젝트들 clear
	m_CurLevel->clear();

	// 레벨이 Play 상태일 경우에만 tick() 호출
	if (m_CurLevel->GetState() == LEVEL_STATE::PLAY)
	{
		m_CurLevel->tick();
	}

	m_CurLevel->finaltick();

	// 충돌 처리
	CCollisionMgr::GetInst()->tick();
}