#include "pch.h"
#include "CCreateTempLevel.h"


#include <Engine/CCollisionMgr.h>

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CLayer.h>
#include <Engine/CGameObject.h>
#include <Engine/components.h>

#include <Scripts/CPlayerScript.h>
#include <Scripts/CBackgroundScript.h>

#include <Engine/CMesh.h>
#include <Engine/CGraphicsShader.h>
#include <Engine/CTexture.h>

#include "CLevelSaveLoad.h"
#include <Scripts/CMissileScript.h>
#include <Scripts/CMonsterScript.h>

#include <Engine/CAssetMgr.h>
#include <Engine/CPrefab.h>
#include <Engine/CFSM.h>

#include <States\CIdleState.h>


void CCreateTempLevel::Init()
{
	// Missile Prefab 생성
	/*CGameObject* pObj = nullptr;

	pObj = new CGameObject;
	pObj->SetName(L"Missile");
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CMissileScript);

	pObj->Transform()->SetRelativeScale(Vec3(50.f, 50.f, 1.f));

	pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));

	Ptr<CPrefab> pMissilePrefab = new CPrefab(pObj,true);
	CAssetMgr::GetInst()->AddAsset<CPrefab>(L"MissilePrefab", pMissilePrefab.Get());*/


	//pMissilePrefab->Save(L"prefab\\missile.pref");
	

	// 임시 FSM 객체 에셋 하나 생성하기
	//CFSM* pFSM = new CFSM(nullptr,false);

	//pFSM->AddState(L"IdleState", new CIdleState);
	////pFSM->AddState(L"TraceState", new CTraceState);

	//wchar_t szPath[255] = {};
	//wstring FilePath = CPathMgr::GetContentPath();

	//swprintf_s(szPath, L"FSM\\TestFSM.fsm");

	//pFSM->SetName(szPath);
	//pFSM->Save(szPath);

	//CAssetMgr::GetInst()->AddAsset<CFSM>(szPath, pFSM);


	// 임시 FSM 객체 에셋 하나 생성하기
	//Ptr<CFSM>	pFSM = new CFSM(nullptr, true);

	//pFSM->AddState(L"IdleState", new CIdleState);

	//CAssetMgr::GetInst()->AddAsset<CFSM>(L"NormalMonsterFSM", pFSM.Get());


}

#include <Engine\CBlurX.h>
#include <Engine\CBlurY.h>
#include <Engine\CDownSampling.h>
#include <Engine\CUpsampling.h>
#include <Engine\CCombine.h>
#include <Engine\CSetColor.h>

void CCreateTempLevel::CreateTempLevel()
{
	//CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Background.jpg", L"texture\\Background.jpg");
	Ptr<CMaterial> pBackgroudMtrl = CAssetMgr::GetInst()->FindAsset<CMaterial>(L"BackgroundMtrl");
	Ptr<CMaterial> pStd2DMtrl = CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl");

	Ptr<CTexture> pPlayerTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Fighter.bmp", L"texture\\Fighter.bmp");

	pStd2DMtrl->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Fighter.bmp", L"texture\\Fighter.bmp"));

	Ptr<CTexture> pTestTex = CAssetMgr::GetInst()->CreateTexture(L"TestTex", pPlayerTex->GetWidth(), pPlayerTex->GetHeight(), DXGI_FORMAT_R8G8B8A8_UNORM, D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS);
	Ptr<CBlurY> pCS = (CBlurY*)CAssetMgr::GetInst()->FindAsset<CComputeShader>(L"BlurYShader").Get();
	pCS->SetResourceTex(CAssetMgr::GetInst()->FindAsset<CTexture>(L"texture\\Fighter.bmp"));
	pCS->SetTargetTexture(pTestTex);
	pCS->Execute();


	Ptr<CTexture> pDownTest = CAssetMgr::GetInst()->CreateTexture(L"Downtest", pPlayerTex->GetWidth()/2, pPlayerTex->GetHeight()/2, DXGI_FORMAT_R8G8B8A8_UNORM, D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS);
	Ptr<CDownSampling> pCSDown = (CDownSampling*)CAssetMgr::GetInst()->FindAsset<CComputeShader>(L"DownSamplingShader").Get();
	pCSDown->SetResourceTex(pPlayerTex);
	pCSDown->SetTargetTexture(pDownTest);
	pCSDown->Execute();


	Ptr<CTexture> pUpTest = CAssetMgr::GetInst()->CreateTexture(L"Uptest", pPlayerTex->GetWidth() * 2, pPlayerTex->GetHeight() * 2, DXGI_FORMAT_R8G8B8A8_UNORM, D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS);
	Ptr<CUpsampling> pCSUp = (CUpsampling*)CAssetMgr::GetInst()->FindAsset<CComputeShader>(L"UpSamplingShader").Get();
	pCSUp->SetResourceTex(pPlayerTex);
	pCSUp->SetTargetTexture(pUpTest);
	pCSUp->Execute();

	Ptr<CTexture> pComTest = CAssetMgr::GetInst()->CreateTexture(L"ComTest", pPlayerTex->GetWidth() * 2, pPlayerTex->GetHeight() * 2, DXGI_FORMAT_R8G8B8A8_UNORM, D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS);
	Ptr<CCombine> pCSCom = (CCombine*)CAssetMgr::GetInst()->FindAsset<CComputeShader>(L"CombineShader").Get();
	Ptr<CTexture> pComTest2 = CAssetMgr::GetInst()->CreateTexture(L"ComTest2", pPlayerTex->GetWidth() * 2, pPlayerTex->GetHeight() * 2, DXGI_FORMAT_R8G8B8A8_UNORM, D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS);

	Ptr<CSetColorShader> pCSSetColor = (CSetColorShader*)CAssetMgr::GetInst()->FindAsset<CComputeShader>(L"SetColorShader").Get();
	pCSSetColor->SetColor(Vec3(1.f, 0.f, 0.f));
	pCSSetColor->SetTargetTexture(pComTest);
	pCSSetColor->Execute();

	pCSCom->SetBloomTex(pComTest);
	pCSCom->SetRenderTargetCopyTex(pUpTest);
	pCSCom->SetRenderTargetTex(pComTest2);
	pCSCom->Execute();





	// 충돌 설정
	CCollisionMgr::GetInst()->LayerCheck(5, 7);
	//CCollisionMgr::GetInst()->LayerCheck(4, 4);


	CLevel* pLevel = CLevelSaveLoad::LoadLevel(L"level\\Lv1.lv");
	CLevelMgr::GetInst()->ChangeLevel(pLevel, LEVEL_STATE::STOP);
	return;


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

	//pCamObj->Transform()->SetRelativePos(Vec3(0.5f, 0.f, 0.f));
	//pCamObj->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 0.f));

	//pCamObj->Camera()->SetProjType(PROJ_TYPE::ORTHOGRAPHIC);
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
	//pObj->AddComponent(new CBackgroundScript);

	//pObj->Transform()->SetRelativePos(Vec3(0.f, 0.f, 600.f));
	//pObj->Transform()->SetRelativeScale(Vec3(1600.f, 800.f, 1.f));

	//pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	//pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"BackgroundMtrl"));

	//Ptr<CTexture> pTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Background.png", L"texture\\Background.png");
	//pObj->MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, pTex);

	//pTempLevel->AddObject(pObj, L"Background", false);

	//// Player Object 생성
	//pObj = new CGameObject;
	//pObj->SetName(L"Player");

	//pObj->AddComponent(new CTransform);
	//pObj->AddComponent(new CMeshRender);
	//pObj->AddComponent(new CCollider2D);
	//pObj->AddComponent(new CAnimator2D);
	//pObj->AddComponent(new CStateMachine);
	//pObj->AddComponent(new CPlayerScript);
	//pObj->AddComponent(new CMovement);

	//pObj->Transform()->SetRelativePos(Vec3(0.f, 0.f, 500.f));
	//pObj->Transform()->SetRelativeScale(Vec3(200.f, 200.f, 1.f));

	//pObj->Collider2D()->SetAbsolute(true);
	//pObj->Collider2D()->SetScale(Vec3(100.f, 100.f,1.f));
	//pObj->Collider2D()->SetOffset(Vec3(0.f, 0.f,0.f));

	//pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	//pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));
	//pObj->MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Fighter.bmp", L"texture\\Fighter.bmp"));

	//Ptr<CTexture> pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\link.png", L"texture\\link.png");
	//pObj->Animator2D()->Create(L"IDLE_UP", pAltasTex, Vec2(0.f, 260.f), Vec2(120.f, 130.f), Vec2(0.f, 0.f), Vec2(200.f, 200.f), 1, 10);
	//pObj->Animator2D()->Create(L"IDLE_DOWN", pAltasTex, Vec2(0.f, 0.f), Vec2(120.f, 130.f), Vec2(0.f, 0.f), Vec2(200.f, 200.f), 3, 10);
	//pObj->Animator2D()->Create(L"IDLE_LEFT", pAltasTex, Vec2(0.f, 130.f), Vec2(120.f, 130.f), Vec2(0.f, 0.f), Vec2(200.f, 200.f), 3, 10);
	//pObj->Animator2D()->Create(L"IDLE_RIGHT", pAltasTex, Vec2(0.f, 390.f), Vec2(120.f, 130.f), Vec2(0.f, 0.f), Vec2(200.f, 200.f), 3, 10);

	//pObj->Movement()->SetVelocity(Vec3(1000.f, 0.f, 0.f));


	////wchar_t szPath[255] = {};
	////wstring FilePath = CPathMgr::GetContentPath();

	////swprintf_s(szPath, L"FSM\\TestFSM.fsm");

	////pObj->StateMachine()->SetFSM(CAssetMgr::GetInst()->Load<CFSM>(szPath));



	//pTempLevel->AddObject(pObj, L"Player", false);

	//// Particle Object
	//CGameObject* pParticleObj = new CGameObject;
	//pParticleObj->SetName(L"Particle");

	//pParticleObj->AddComponent(new CTransform);
	//pParticleObj->AddComponent(new CParticleSystem);

	//pParticleObj->Transform()->SetRelativePos(Vec3(0.f, 0.f, 200.f));

	//pObj->AddChild(pParticleObj);


	//// Monster Object 생성
	//pObj = new CGameObject;
	//pObj->SetName(L"Monster");

	//pObj->AddComponent(new CTransform);
	//pObj->AddComponent(new CMeshRender);
	//pObj->AddComponent(new CCollider2D);
	//pObj->AddComponent(new CStateMachine);
	//pObj->AddComponent(new CMonsterScript);

	//pObj->Transform()->SetRelativePos(Vec3(500.f, 0.f, 500.f));
	//pObj->Transform()->SetRelativeScale(Vec3(200.f, 200.f, 1.f));

	//pObj->Collider2D()->SetAbsolute(true);
	//pObj->Collider2D()->SetScale(Vec3(120.f, 120.f, 1.f));
	//pObj->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));

	//pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	//pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));
	//pObj->MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Fighter.bmp", L"texture\\Fighter.bmp"));

	//pObj->StateMachine()->SetFSM(CAssetMgr::GetInst()->FindAsset<CFSM>(L"NormalMonsterFSM"));

	//pTempLevel->AddObject(pObj, L"Monster", false);


	//CLevelMgr::GetInst()->ChangeLevel(pTempLevel, LEVEL_STATE::STOP);




	//CLevelSaveLoad::SaveLevel(pTempLevel, L"level\\temp.lv");
}