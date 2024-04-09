#include "pch.h"
#include "CCrushDown.h"

#include <Engine/CMovement.h>
#include <Engine/CMeshRender.h>

CCrushDown::CCrushDown()
	: CState(CRUSHDOWN)
{
}

CCrushDown::~CCrushDown()
{
}


void CCrushDown::finaltick()
{
	GetOwnerObj()->Movement()->SetVelocityX(0.f);
	GetOwnerObj()->Movement()->SetVelocityY(-5000.f);

	if (GetOwnerObj()->Movement()->IsGround())
	{
		ChangeState(L"Crush");
	}
}

void CCrushDown::Enter()
{
	GetOwnerObj()->MeshRender()->GetMaterial()->SetScalarParam(SCALAR_PARAM::INT_1, 1);

	GetOwnerObj()->Animator2D()->Play(L"LD_CRUSHDOWN", true);
}

void CCrushDown::Exit()
{
	GetOwnerObj()->MeshRender()->GetMaterial()->SetScalarParam(SCALAR_PARAM::INT_1, 0);
}

