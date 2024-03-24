#include "pch.h"
#include "StateMachineUI.h"

#include <Engine\CStateMachine.h>

StateMachineUI::StateMachineUI()
	: ComponentUI("StateMachine", "##StateMachine", COMPONENT_TYPE::STATEMACHINE)
{
	SetSize(ImVec2(0.f, 140.f));
	SetComopnentTitle("StateMachine");
}

StateMachineUI::~StateMachineUI()
{
}

void StateMachineUI::render_update()
{
	if (nullptr == GetTargetObject())
		return;

	ComponentUI::render_update();


}