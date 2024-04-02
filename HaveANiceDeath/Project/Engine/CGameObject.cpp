#include "pch.h"
#include "CGameObject.h"

#include "CRenderMgr.h"

#include "CComponent.h"
#include "CRenderComponent.h"

#include "CScript.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CLayer.h"

#include "CGC.h"

CGameObject::CGameObject()
	: m_arrCom{}
	, m_RenderCom(nullptr)
	, m_Parent(nullptr)
	, m_LayerIdx(-1)
	, m_bDead(false)
{
}

CGameObject::CGameObject(const CGameObject& _OriginObject)
	: CEntity(_OriginObject)
	, m_arrCom{}
	, m_RenderCom(nullptr)
	, m_Parent(nullptr)
	, m_LayerIdx(-1)
	, m_bDead(false)
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (nullptr == _OriginObject.m_arrCom[i])
			continue;

		AddComponent(_OriginObject.m_arrCom[i]->Clone());
	}

	for (size_t i = 0; i < _OriginObject.m_vecScript.size(); ++i)
	{
		AddComponent(_OriginObject.m_vecScript[i]->Clone());
	}


	// 복사되는 GameObject 는 부모만 레이어소속을 -1 로 하고, 
	// 자식들은 원본객체랑 동일한 레이어소속을 유지한다.
	for (size_t i = 0; i < _OriginObject.m_vecChild.size(); ++i)
	{
		CGameObject* ChildClone = _OriginObject.m_vecChild[i]->Clone();
		AddChild(ChildClone);
		ChildClone->m_LayerIdx = _OriginObject.m_vecChild[i]->m_LayerIdx;
	}
}


CGameObject::~CGameObject()
{
	Delete_Vec(m_vecChild);
	Delete_Array(m_arrCom);
	Delete_Vec(m_vecScript);
}

void CGameObject::AddComponent(CComponent* _Comonent)
{
	COMPONENT_TYPE type = _Comonent->GetType();

	if (type == COMPONENT_TYPE::SCRIPT)
	{
		// Script 타입 Component 가 실제로 Script 클래스가 아닌 경우
		assert(dynamic_cast<CScript*>(_Comonent));

		m_vecScript.push_back((CScript*)_Comonent);
		_Comonent->m_Owner = this;
	}
	else
	{
		if (m_arrCom[(UINT)type])
		{
			MessageBoxA(nullptr, "이미 해당 컴포넌트를 가지고 있습니다!", "Add Component Failed!", MB_OK);
			delete _Comonent;
			return;
		}


		m_arrCom[(UINT)type] = _Comonent;
		_Comonent->m_Owner = this;

		CRenderComponent* pRenderCom = dynamic_cast<CRenderComponent*>(_Comonent);
		if (nullptr != pRenderCom)
		{
			// 이미 한 종류 이상의 RenderComponent 를 보유하고 있는 경우
			if (m_RenderCom)
			{
				MessageBoxA(nullptr, "이미 랜더 컴포넌트를 가지고 있습니다!", "Add Render Component Failed!", MB_OK);
				return;
			}


			m_RenderCom = pRenderCom;
		}
	}
}

void CGameObject::DeleteComponent(COMPONENT_TYPE _Type)
{
	CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	
	if (LEVEL_STATE::PLAY == pLevel->GetState() || LEVEL_STATE::PAUSE == pLevel->GetState())
	{
		return;
	}

	if (m_arrCom[(UINT)_Type])
	{
		delete m_arrCom[(UINT)_Type];
		m_arrCom[(UINT)_Type] = nullptr;

		if (COMPONENT_TYPE::MESHRENDER == _Type || COMPONENT_TYPE::TILEMAP == _Type || COMPONENT_TYPE::PARTICLESYSTEM == _Type)
		{
			m_RenderCom = nullptr;
		}
	}
}

int CGameObject::ChangeLayer(int _Idx)
{
	DisconnectWithLayer();
	CLevelMgr::GetInst()->GetCurrentLevel()->AddObject(this, _Idx, false);

	return 0;
}

int CGameObject::DisconnectWithParent()
{
	// 부모가 없는 오브젝트에 DisconnectWithParent 함수를 호출했으면
	if (nullptr == m_Parent)
		return -1;

	bool bSuccess = false;
	vector<CGameObject*>::iterator iter = m_Parent->m_vecChild.begin();
	for (; iter != m_Parent->m_vecChild.end(); ++iter)
	{
		if (*iter == this)
		{
			m_Parent->m_vecChild.erase(iter);
			m_Parent = nullptr;
			bSuccess = true;
			break;
		}
	}

	// 부모는 자식을 가리키기지 않고 있는데, 자식은 부모를 가리키고 있는 경우
	if (!bSuccess)
	{
		assert(nullptr);
	}

	int LayerIdx = m_LayerIdx;

	m_LayerIdx = -1;

	return LayerIdx;
}

int CGameObject::DisconnectWithLayer()
{
	if (-1 == m_LayerIdx)
		return -1;

	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	CLayer* pCurLayer = pCurLevel->GetLayer(m_LayerIdx);

	int LayerIdx = m_LayerIdx;
	pCurLayer->DetachGameObject(this);

	return LayerIdx;
}

void CGameObject::AddChild(CGameObject* _Child)
{
	if (-1 == _Child->m_LayerIdx)
	{
		// 레벨에 속하지 않았던 오브젝트가 자식으로 들어올때는 부모의 레이어를 따라간다.
		_Child->m_LayerIdx = m_LayerIdx;
	}
	else if (_Child->m_Parent)
	{
		// 이전 부모 오브젝트랑 연결 해제
		// 원래 레이어를 유지한다.
		int LayerIdx = _Child->DisconnectWithParent();
		_Child->m_LayerIdx = LayerIdx;
	}
	else
	{
		// 자식으로 들어오는 오브젝트가 최상위 부모타입이면,
		// 소속 레이어의 Parent 오브젝트 목록에서 제거되어야 한다.
		// 제거되기 전의 레이어를 유지한다.
		int LayerIdx = _Child->DisconnectWithLayer();
		_Child->m_LayerIdx = LayerIdx;
	}

	// 부모 자식 연결
	_Child->m_Parent = this;
	m_vecChild.push_back(_Child);
}

void CGameObject::Destroy()
{
	GamePlayStatic::DestroyGameObject(this);
}

bool CGameObject::IsAncestor(CGameObject* _Other)
{
	CGameObject* pParent = m_Parent;

	while (pParent)
	{
		if (pParent == _Other)
			return true;

		pParent = pParent->m_Parent;
	}

	return false;
}


void CGameObject::begin()
{
	size_t ChildvecSize = m_vecChild.size();

	for (UINT i = 0; i < UINT(COMPONENT_TYPE::END); ++i)
	{
		if (nullptr != m_arrCom[i])
		{
			m_arrCom[i]->begin();
		}
	}

	for (size_t i = 0; i < m_vecScript.size(); ++i)
	{
		m_vecScript[i]->begin();
	}

	for (size_t i = 0; i < ChildvecSize; ++i)
	{
		m_vecChild[i]->begin();
	}
}

void CGameObject::tick()
{
	for (UINT i = 0; i < UINT(COMPONENT_TYPE::END); ++i)
	{
		if (nullptr != m_arrCom[i])
		{
			m_arrCom[i]->tick();
		}
	}

	for (size_t i = 0; i < m_vecScript.size(); ++i)
	{
		m_vecScript[i]->tick();
	}

	for (size_t i = 0; i < m_vecChild.size(); ++i)
	{
		m_vecChild[i]->tick();
	}
}


void CGameObject::finaltick()
{
	// Component finaltick
	for (UINT i = 0; i < UINT(COMPONENT_TYPE::END); ++i)
	{
		if (nullptr != m_arrCom[i])
		{
			m_arrCom[i]->finaltick();
		}
	}

	// render를 위해 Object 등록
	CLayer* pCurLayer = CLevelMgr::GetInst()->GetCurrentLevel()->GetLayer(m_LayerIdx);
	pCurLayer->RegisterGameObject(this);

	// 삭제 처리
	vector<CGameObject*>::iterator iter = m_vecChild.begin();
	for (; iter != m_vecChild.end();)
	{
		(*iter)->finaltick();

		if ((*iter)->m_bDead)
		{
			CGC::GetInst()->Add(*iter);
			iter = m_vecChild.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	// UI, Camera 는 크로스헤어 안그림

	if (GetLayerIdx() == 31 || (Camera() != nullptr))
		return;

	if (CRenderMgr::GetInst()->IsDebugPosition())
	{
		GamePlayStatic::DrawDebugCross(Transform()->GetWorldPos(), 20.f, Vec3(0.f, 1.f, 0.f), true);
	}

}

void CGameObject::render()
{
	if (nullptr != m_RenderCom)
	{
		m_RenderCom->render();
	}
}