#include "pch.h"
#include "CAssetMgr.h"

#include "CMesh.h"
#include "CGraphicsShader.h"
#include "CMaterial.h"

void CAssetMgr::init()
{
	InitSound();

	CreateDefaultMesh();

	CreateDefaultGraphicsShader();

	CreateDefaultComputeShader();

	CreateDefaultMaterial();
}


void CAssetMgr::CreateDefaultMesh()
{
	CMesh* pMesh = nullptr;


	// ==========
	// Point Mesh
	// ==========

	Vtx vPoint;
	UINT Idx = 0;
	pMesh = new CMesh(true);
	pMesh->Create(&vPoint, 1, &Idx, 1);
	AddAsset(L"PointMesh", pMesh);


	// =========
	// Rect Mesh
	// =========
	
	//    0 ----- 1	     
	//    |   \   |	     
	//    3 ----- 2

	Vtx arrVtx[4] = {};

	arrVtx[0].vPos = Vec3(-0.5f, 0.5f, 0.f);
	arrVtx[0].vColor = Vec4(0.f, 0.f, 0.f, 1.f);
	arrVtx[0].vUV = Vec2(0.f, 0.f);

	arrVtx[1].vPos = Vec3(0.5f, 0.5f, 0.f);
	arrVtx[1].vColor = Vec4(0.f, 0.f, 0.f, 1.f);
	arrVtx[1].vUV = Vec2(1.f, 0.f);

	arrVtx[2].vPos = Vec3(0.5f, -0.5f, 0.f);
	arrVtx[2].vColor = Vec4(0.f, 0.f, 0.f, 1.f);
	arrVtx[2].vUV = Vec2(1.f, 1.f);

	arrVtx[3].vPos = Vec3(-0.5f, -0.5f, 0.f);
	arrVtx[3].vColor = Vec4(0.f, 0.f, 0.f, 1.f);
	arrVtx[3].vUV = Vec2(0.f, 1.f);

	// 인덱스

	UINT arrIdx[6] = {0, 1, 2, 0, 2, 3};

	pMesh = new CMesh(true);
	pMesh->Create(arrVtx, 4, arrIdx, 6);
	AddAsset(L"RectMesh", pMesh);


	
	// ==============
	// RectMesh_Debug
	// ==============
	// Topology LineStrip 용도	

	//    0 ----- 1	     
	//    |		  |	     
	//    3 ----- 2

	arrIdx[0] = 0;	arrIdx[1] = 1;	arrIdx[2] = 2;	arrIdx[3] = 3; 	arrIdx[4] = 0;

	pMesh = new CMesh(true);
	pMesh->Create(arrVtx, 4, arrIdx, 5);
	AddAsset(L"RectMesh_Debug", pMesh);

	// =================
	// CircleMesh 만들기
	// =================

	vector<Vtx> vecVtx;
	vector<UINT> vecIdx;
	Vtx v;

	// 중심 점
	v.vPos = Vec3(0.f, 0.f, 0.f);
	v.vColor = Vec4(1.f, 1.f, 1.f, 1.f);
	v.vUV = Vec2(0.5f, 0.5f);
	vecVtx.push_back(v);

	UINT iSlice = 40;
	float fTheta = 0.f;
	float fRadius = 0.5f;

	for (UINT i = 0; i <= iSlice; ++i)
	{
		fTheta = (XM_2PI / iSlice) * i;

		v.vPos = Vec3(fRadius * cosf(fTheta), fRadius * sinf(fTheta), 0.f);
		v.vColor = Vec4(1.f, 1.f, 1.f, 1.f);
		v.vUV = Vec2(0.f, 0.f);

		vecVtx.push_back(v);
	}

	for (UINT i = 0; i < iSlice; ++i)
	{
		vecIdx.push_back(0);
		vecIdx.push_back(i + 2);
		vecIdx.push_back(i + 1);
	}

	pMesh = new CMesh(true);
	pMesh->Create(vecVtx.data(), (UINT)vecVtx.size(), vecIdx.data(), (UINT)vecIdx.size());
	AddAsset(L"CircleMesh", pMesh);

	vecIdx.clear();

	// ================
	// CircleMesh_Debug
	// ================

	for (int i = 1; i < vecVtx.size(); ++i)
	{
		vecIdx.push_back(i);
	}

	pMesh = new CMesh(true);
	pMesh->Create(vecVtx.data(), (UINT)vecVtx.size(), vecIdx.data(), (UINT)vecIdx.size());
	AddAsset(L"CircleMesh_Debug", pMesh);

	vecVtx.clear();
	vecIdx.clear();

	// =========
	// CrossMesh
	// =========

	v.vUV = Vec2(0.f, 0.f);
	v.vColor = Vec4(0.f, 1.f, 0.f, 1.f);

	v.vPos = Vec3(0.f, 0.5f, 0.f);
	vecVtx.push_back(v);

	v.vPos = Vec3(0.f, -0.5f, 0.f);
	vecVtx.push_back(v);

	v.vPos = Vec3(-0.5f, 0.f, 0.f);
	vecVtx.push_back(v);

	v.vPos = Vec3(0.5f, 0.f, 0.f);
	vecVtx.push_back(v);

	vecIdx.push_back(0); vecIdx.push_back(1);
	vecIdx.push_back(2); vecIdx.push_back(3);

	pMesh = new CMesh(true);
	pMesh->Create(vecVtx.data(), (UINT)vecVtx.size(), vecIdx.data(), (UINT)vecIdx.size());
	AddAsset(L"CrossMesh", pMesh);

	vecVtx.clear();
	vecIdx.clear();
}

void CAssetMgr::CreateDefaultGraphicsShader()
{
	// =================================
	// Std2DShader
	// =================================
	Ptr<CGraphicsShader> pShader = nullptr;

	pShader = new CGraphicsShader;
	pShader->CreateVertexShader(L"shader\\std2d.fx", "VS_Std2D");
	pShader->CreatePixelShader(L"shader\\std2d.fx", "PS_Std2D");

	pShader->SetRSType(RS_TYPE::CULL_NONE);
	pShader->SetDSType(DS_TYPE::LESS);
	pShader->SetBSType(BS_TYPE::ALPHA_BLEND);
	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_MASKED);

	// Parameter	
	pShader->AddScalarParam(SCALAR_PARAM::INT_0, "Test Param");
	pShader->AddTexParam(TEX_PARAM::TEX_0, "Output Texture 0");


	AddAsset(L"Std2DShader", pShader.Get());

	// =================================
	// EffectShader
	// =================================

	pShader = new CGraphicsShader;
	pShader->CreateVertexShader(L"shader\\std2d.fx", "VS_Std2D");
	pShader->CreatePixelShader(L"shader\\std2d.fx", "PS_Std2D_Effect");

	pShader->SetRSType(RS_TYPE::CULL_NONE);
	pShader->SetDSType(DS_TYPE::LESS);
	pShader->SetBSType(BS_TYPE::ALPHA_BLEND);

	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_TRANSPARENT);

	AddAsset(L"EffectShader", pShader.Get());


	// =============
	// TileMapShader
	// =============

	pShader = new CGraphicsShader;
	pShader->CreateVertexShader(L"shader\\tilemap.fx", "VS_TileMap");
	pShader->CreatePixelShader(L"shader\\tilemap.fx", "PS_TileMap");

	pShader->SetRSType(RS_TYPE::CULL_NONE);
	pShader->SetDSType(DS_TYPE::LESS);
	pShader->SetBSType(BS_TYPE::DEFAULT);

	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_MASKED);

	AddAsset(L"TileMapShader", pShader.Get());

	// ====================
	// ParticleRenderShader
	// ====================

	pShader = new CGraphicsShader;
	pShader->CreateVertexShader(L"shader\\particle.fx", "VS_Particle");
	pShader->CreateGeometryShader(L"shader\\particle.fx", "GS_Particle");
	pShader->CreatePixelShader(L"shader\\particle.fx", "PS_Particle");

	pShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
	pShader->SetRSType(RS_TYPE::CULL_NONE);
	pShader->SetDSType(DS_TYPE::NO_WRITE);		// 깊이 테스트는 진행, 깊이는 기록 X
	pShader->SetBSType(BS_TYPE::ALPHA_BLEND);

	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_TRANSPARENT);

	AddAsset(L"ParticleRenderShader", pShader.Get());

	// =================================
	// GrayFilter Shader
	// Mesh			: RectMesh
	// RS_TYPE		: CULL_BACK
	// DS_TYPE		: NO_TEST_NO_WRITE
	// BS_TYPE		: Default
	// Domain		: DOMAIN_POSTPROCESS
	// =================================

	pShader = new CGraphicsShader;
	pShader->CreateVertexShader(L"shader\\postprocess.fx", "VS_GrayFilter");
	pShader->CreatePixelShader(L"shader\\postprocess.fx", "PS_GrayFilter");

	pShader->SetRSType(RS_TYPE::CULL_BACK);
	pShader->SetDSType(DS_TYPE::NO_TEST_NO_WRITE);
	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_POSTPROCESS);

	AddAsset(L"GrayFilterShader", pShader.Get());

	// =================================
	// Distortion Shader	
	// RS_TYPE		: CULL_BACK
	// DS_TYPE		: NO_TEST_NO_WRITE
	// BS_TYPE		: Default
	// Domain		: DOMAIN_POSTPROCESS
	// =================================

	pShader = new CGraphicsShader;
	pShader->CreateVertexShader(L"shader\\postprocess.fx", "VS_Distortion");
	pShader->CreatePixelShader(L"shader\\postprocess.fx", "PS_Distortion");

	pShader->SetRSType(RS_TYPE::CULL_NONE);
	pShader->SetDSType(DS_TYPE::NO_TEST_NO_WRITE);
	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_POSTPROCESS);

	AddAsset(L"DistortionShader", pShader.Get());

	// =================================
	// DebugShape Shader
	// =================================

	pShader = new CGraphicsShader;
	pShader->CreateVertexShader(L"shader\\debug.fx", "VS_DebugShape");
	pShader->CreatePixelShader(L"shader\\debug.fx", "PS_DebugShape");

	pShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
	pShader->SetRSType(RS_TYPE::CULL_NONE);
	pShader->SetBSType(BS_TYPE::DEFAULT);
	pShader->SetDSType(DS_TYPE::NO_TEST_NO_WRITE);

	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_DEBUG);

	AddAsset(L"DebugShapeShader", pShader.Get());



	// =================================
	// PlayerShader
	// =================================
	pShader = nullptr;

	pShader = new CGraphicsShader;
	pShader->CreateVertexShader(L"shader\\Player.fx", "VS_Player");
	pShader->CreatePixelShader(L"shader\\Player.fx", "PS_Player");

	pShader->SetRSType(RS_TYPE::CULL_NONE);
	pShader->SetDSType(DS_TYPE::LESS);
	pShader->SetBSType(BS_TYPE::DEFAULT);
	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_MASKED);

	// Parameter	
	pShader->AddScalarParam(SCALAR_PARAM::INT_0, "Anim Dir");
	pShader->AddTexParam(TEX_PARAM::TEX_0, "Default Tex");

	AddAsset(L"PlayerShader", pShader.Get());


	// =================================
	// Std2DGlowShader
	// =================================
	pShader = nullptr;

	pShader = new CGraphicsShader;
	pShader->CreateVertexShader(L"shader\\StdGlow.fx", "VS_Std2D_Glow");
	pShader->CreatePixelShader(L"shader\\StdGlow.fx", "PS_Std2D_Glow");

	pShader->SetRSType(RS_TYPE::CULL_NONE);
	pShader->SetDSType(DS_TYPE::LESS);
	pShader->SetBSType(BS_TYPE::ALPHA_BLEND);
	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_TRANSPARENT);

	// Parameter	
	pShader->AddScalarParam(SCALAR_PARAM::INT_0, "Anim Dir");
	pShader->AddScalarParam(SCALAR_PARAM::INT_1, "Glow Enable");
	pShader->AddScalarParam(SCALAR_PARAM::FLOAT_0, "Threshold");
	pShader->AddScalarParam(SCALAR_PARAM::VEC4_0, "Glow Color");

	pShader->AddTexParam(TEX_PARAM::TEX_0, "Default Tex");

	AddAsset(L"StdGlowShader", pShader.Get());

	// =================================
	// StdAirPerspectiveShader
	// =================================

	pShader = nullptr;

	pShader = new CGraphicsShader;
	pShader->CreateVertexShader(L"shader\\StdAirperspective.fx", "VS_Std2D_AirPersp");
	pShader->CreatePixelShader(L"shader\\StdAirperspective.fx", "PS_Std2D_AirPersp");

	pShader->SetRSType(RS_TYPE::CULL_NONE);
	pShader->SetDSType(DS_TYPE::LESS);
	pShader->SetBSType(BS_TYPE::ALPHA_BLEND);
	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_TRANSPARENT);

	// Parameter	
	pShader->AddScalarParam(SCALAR_PARAM::INT_0, "AirPersp Enable");
	pShader->AddScalarParam(SCALAR_PARAM::FLOAT_0, "ObjDepth");
	pShader->AddScalarParam(SCALAR_PARAM::VEC4_0, "Air Color");

	pShader->AddTexParam(TEX_PARAM::TEX_0, "Default Tex");

	AddAsset(L"StdAirPerspShader", pShader.Get());

	// =================================
	// StormBackgroundShader
	// =================================

	pShader = nullptr;

	pShader = new CGraphicsShader;
	pShader->CreateVertexShader(L"shader\\StormBackground.fx", "VS_StormBackground");
	pShader->CreatePixelShader(L"shader\\StormBackground.fx", "PS_StormBackground");

	pShader->SetRSType(RS_TYPE::CULL_NONE);
	pShader->SetDSType(DS_TYPE::LESS);
	pShader->SetBSType(BS_TYPE::ALPHA_BLEND);
	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_TRANSPARENT);

	// Parameter	
	pShader->AddScalarParam(SCALAR_PARAM::FLOAT_0, "Object Scale X");
	pShader->AddScalarParam(SCALAR_PARAM::FLOAT_1, "Object Scale Y");

	pShader->AddTexParam(TEX_PARAM::TEX_0, "StormBackground Tex");
	pShader->AddTexParam(TEX_PARAM::TEX_1, "Noise Tex");

	AddAsset(L"StormBackground", pShader.Get());
}

void CAssetMgr::CreateDefaultMaterial()
{
	CMaterial* pMtrl = nullptr;

	// =========
	// Std2DMtrl
	// =========

	pMtrl = new CMaterial(true);
	pMtrl->SetShader(FindAsset<CGraphicsShader>(L"Std2DShader"));
	AddAsset<CMaterial>(L"Std2DMtrl", pMtrl);

	// ==============
	// BackgroundMtrl
	// ==============
	
	pMtrl = new CMaterial(true);
	pMtrl->SetShader(FindAsset<CGraphicsShader>(L"Std2DShader"));
	AddAsset<CMaterial>(L"BackgroundMtrl", pMtrl);

	// ===========
	// TileMapMtrl
	// ===========

	pMtrl = new CMaterial(true);
	pMtrl->SetShader(FindAsset<CGraphicsShader>(L"TileMapShader"));
	AddAsset<CMaterial>(L"TileMapMtrl", pMtrl);

	// ============
	// ParticleMtrl
	// ============

	pMtrl = new CMaterial(true);
	pMtrl->SetShader(FindAsset<CGraphicsShader>(L"ParticleRenderShader"));
	AddAsset<CMaterial>(L"ParticleMtrl", pMtrl);

	// ==============
	// GrayFilterMtrl
	// ==============

	pMtrl = new CMaterial(true);
	pMtrl->SetShader(FindAsset<CGraphicsShader>(L"GrayFilterShader"));
	AddAsset<CMaterial>(L"GrayFilterMtrl", pMtrl);


	// ==============
	// DistortionMtrl
	// ==============

	pMtrl = new CMaterial(true);
	pMtrl->SetShader(FindAsset<CGraphicsShader>(L"DistortionShader"));
	AddAsset<CMaterial>(L"DistortionMtrl", pMtrl);

	// ==============
	// DebugShapeMtrl
	// ==============

	pMtrl = new CMaterial(true);
	pMtrl->SetShader(FindAsset<CGraphicsShader>(L"DebugShapeShader"));
	AddAsset<CMaterial>(L"DebugShapeMtrl", pMtrl);
}


#include "CParticleUpdate.h"
#include "CDownSampling.h"
#include "CUpsampling.h"
#include "CCombine.h"
#include "CBlurX.h"
#include "CBlurY.h"
#include "CSetColor.h"

void CAssetMgr::CreateDefaultComputeShader()
{
	Ptr<CComputeShader> pShader = nullptr;

	// ParticleUpdateShader
	pShader = new CParticleUpdate;
	AddAsset(L"ParticleUpdateShader", pShader.Get());

	// SamplingShader
	pShader = new CDownSampling;
	AddAsset(L"DownSamplingShader", pShader.Get());

	pShader = new CUpsampling;
	AddAsset(L"UpSamplingShader", pShader.Get());

	pShader = new CCombine;
	AddAsset(L"CombineShader", pShader.Get());

	pShader = new CBlurX;
	AddAsset(L"BlurXShader", pShader.Get());

	pShader = new CBlurY;
	AddAsset(L"BlurYShader", pShader.Get());

	// SetColorShader
	pShader = new CSetColorShader;
	AddAsset(L"SetColorShader", pShader.Get());

}


void CAssetMgr::InitSound()
{
	FMOD::System_Create(&CSound::g_pFMOD);

	if (nullptr == CSound::g_pFMOD)
	{
		assert(nullptr);
	}

	// 32개 채널 생성
	CSound::g_pFMOD->init(32, FMOD_DEFAULT, nullptr);
}
