#include "pch.h"
#include "CCrush.h"

#include <Engine/CMovement.h>
#include <Engine/CMeshRender.h>

CCrush::CCrush()
	:CState(CRUSH)
{
}

CCrush::~CCrush()
{
}
void CCrush::finaltick()
{
	GetOwnerObj()->Movement()->SetVelocityX(0.f);
	GetOwnerObj()->Movement()->SetVelocityY(0.f);

	if (GetOwnerObj()->Animator2D()->IsCurAnimFinished())
	{
		ChangeState(L"Idle");
	}
}

void CCrush::Enter()
{
	GetOwnerObj()->MeshRender()->GetMaterial()->SetScalarParam(SCALAR_PARAM::INT_1, 1);
	GetOwnerObj()->Animator2D()->Play(L"LD_CRUSH", true);
}

void CCrush::Exit()
{
	GetOwnerObj()->MeshRender()->GetMaterial()->SetScalarParam(SCALAR_PARAM::INT_1, 0);
}


