#include "pch.h"
#include "CMeshRender.h"

#include "CGameObject.h"

#include "CMaterial.h"
#include "CMesh.h"
#include "CGraphicsShader.h"

#include "CRenderMgr.h"

#include "CGameObject.h"
#include "CAnimator2D.h"

#include "CTransform.h"

CMeshRender::CMeshRender()
	: CRenderComponent(COMPONENT_TYPE::MESHRENDER)
{
}

CMeshRender::~CMeshRender()
{
}


void CMeshRender::finaltick()
{

}

void CMeshRender::UpdateData()
{
	if (nullptr != GetMaterial())
	{
		GetMaterial()->UpdateData();
	}

	Transform()->UpdateData();
}

void CMeshRender::render()
{
	if (nullptr == GetMesh() || nullptr == GetMaterial())
		return;

	if (Animator2D())
	{
		Animator2D()->UpdateData();
	}
	else
	{
		Animator2D()->Clear();
	}

	UpdateData();

	GetMesh()->render();
}