#include "pch.h"
#include "Inspector.h"

#include "ScriptUI.h"

void Inspector::CreateChildUI()
{
	CreateComponentUI();

	CreateAssetUI();
}


#include "TransformUI.h"
#include "MeshRenderUI.h"
#include "Collider2DUI.h"
#include "Light2DUI.h"
#include "Animator2DUI.h"
#include "StateMachineUI.h"
#include "PrefabUI.h"
#include "CameraUI.h"

#include "ObjectController.h"

void Inspector::CreateComponentUI()
{
	m_arrComUI[(UINT)COMPONENT_TYPE::TRANSFORM] = new TransformUI;
	m_arrComUI[(UINT)COMPONENT_TYPE::TRANSFORM]->Deactivate();
	AddChildUI(m_arrComUI[(UINT)COMPONENT_TYPE::TRANSFORM]);

	m_arrComUI[(UINT)COMPONENT_TYPE::COLLIDER2D] = new Collider2DUI;
	m_arrComUI[(UINT)COMPONENT_TYPE::COLLIDER2D]->Deactivate();
	AddChildUI(m_arrComUI[(UINT)COMPONENT_TYPE::COLLIDER2D]);

	m_arrComUI[(UINT)COMPONENT_TYPE::ANIMATOR2D] = new Animator2DUI;
	m_arrComUI[(UINT)COMPONENT_TYPE::ANIMATOR2D]->Deactivate();
	AddChildUI(m_arrComUI[(UINT)COMPONENT_TYPE::ANIMATOR2D]);

	m_arrComUI[(UINT)COMPONENT_TYPE::CAMERA] = new CameraUI;
	m_arrComUI[(UINT)COMPONENT_TYPE::CAMERA]->Deactivate();
	AddChildUI(m_arrComUI[(UINT)COMPONENT_TYPE::CAMERA]);

	m_arrComUI[(UINT)COMPONENT_TYPE::STATEMACHINE] = new StateMachineUI;
	m_arrComUI[(UINT)COMPONENT_TYPE::STATEMACHINE]->Deactivate();
	AddChildUI(m_arrComUI[(UINT)COMPONENT_TYPE::STATEMACHINE]);

	m_arrComUI[(UINT)COMPONENT_TYPE::LIGHT2D] = new Light2DUI;
	m_arrComUI[(UINT)COMPONENT_TYPE::LIGHT2D]->Deactivate();
	AddChildUI(m_arrComUI[(UINT)COMPONENT_TYPE::LIGHT2D]);

	m_arrComUI[(UINT)COMPONENT_TYPE::MESHRENDER] = new MeshRenderUI;
	m_arrComUI[(UINT)COMPONENT_TYPE::MESHRENDER]->Deactivate();
	AddChildUI(m_arrComUI[(UINT)COMPONENT_TYPE::MESHRENDER]);

	m_ObjController = new ObjectController;


}

#include "TextureUI.h"
#include "MeshDataUI.h"
#include "MeshUI.h"
#include "MaterialUI.h"
#include "GraphicsShaderUI.h"
#include "ComputeShaderUI.h"
#include "SoundUI.h"
#include "FSMUI.h"

void Inspector::CreateAssetUI()
{
	m_arrAssetUI[(UINT)ASSET_TYPE::MESH] = new MeshUI;
	AddChildUI(m_arrAssetUI[(UINT)ASSET_TYPE::MESH]);

	m_arrAssetUI[(UINT)ASSET_TYPE::MESHDATA] = new MeshDataUI;
	AddChildUI(m_arrAssetUI[(UINT)ASSET_TYPE::MESHDATA]);

	m_arrAssetUI[(UINT)ASSET_TYPE::TEXTURE] = new TextureUI;
	AddChildUI(m_arrAssetUI[(UINT)ASSET_TYPE::TEXTURE]);

	m_arrAssetUI[(UINT)ASSET_TYPE::GRAPHICS_SHADER] = new GraphicsShader;
	AddChildUI(m_arrAssetUI[(UINT)ASSET_TYPE::GRAPHICS_SHADER]);

	m_arrAssetUI[(UINT)ASSET_TYPE::COMPUTE_SHADER] = new ComputeShaderUI;
	AddChildUI(m_arrAssetUI[(UINT)ASSET_TYPE::COMPUTE_SHADER]);

	m_arrAssetUI[(UINT)ASSET_TYPE::MATERIAL] = new MaterialUI;
	AddChildUI(m_arrAssetUI[(UINT)ASSET_TYPE::MATERIAL]);

	m_arrAssetUI[(UINT)ASSET_TYPE::SOUND] = new SoundUI;
	AddChildUI(m_arrAssetUI[(UINT)ASSET_TYPE::SOUND]);

	m_arrAssetUI[(UINT)ASSET_TYPE::PREFAB] = new PrefabUI;
	AddChildUI(m_arrAssetUI[(UINT)ASSET_TYPE::PREFAB]);

	m_arrAssetUI[(UINT)ASSET_TYPE::FSM] = new FSMUI;
	AddChildUI(m_arrAssetUI[(UINT)ASSET_TYPE::FSM]);
}

void Inspector::ResizeScriptUI(UINT _Size)
{
	int AddSize = _Size - m_vecScriptUI.size();

	// ��ũ��Ʈ�� �� ���ٸ�
	if (_Size > m_vecScriptUI.size())
	{
		// ��ũ��Ʈ UI�� �߰�
		for (int i = 0; i < AddSize; ++i)
		{
			ScriptUI* pScriptUI = new ScriptUI;
			AddChildUI(pScriptUI);
			m_vecScriptUI.push_back(pScriptUI);
		}
	}
	else
	{
		for (int i = m_vecScriptUI.size() + AddSize; i < m_vecScriptUI.size(); ++i)
		{
			m_vecScriptUI[i]->Deactivate();
		}
	}
}
