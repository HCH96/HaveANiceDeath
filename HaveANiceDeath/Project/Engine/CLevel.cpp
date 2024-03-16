#include "pch.h"
#include "CLevel.h"

#include "CTimeMgr.h"
//#include "CRenderMgr.h"

#include "CLayer.h"
#include "CGameObject.h"


CLevel::CLevel()
	: m_arrLayer{}
	, m_State(LEVEL_STATE::NONE)
{
	for (UINT i = 0; i < LAYER_MAX; ++i)
	{
		m_arrLayer[i] = new CLayer;
		m_arrLayer[i]->m_LayerIdx = i;
	}
}

CLevel::CLevel(const CLevel& _OriginLevel)
	: CEntity(_OriginLevel)
	, m_State(LEVEL_STATE::NONE)
	, m_arrLayer{}
{
	for (UINT i = 0; i < LAYER_MAX; ++i)
	{
		m_arrLayer[i] = _OriginLevel.m_arrLayer[i]->Clone();
	}
}

CLevel::~CLevel()
{
	Delete_Array(m_arrLayer);
}

void CLevel::begin()
{
	for (int i = 0; i < LAYER_MAX; ++i)
	{
		m_arrLayer[i]->begin();
	}
}

void CLevel::tick()
{
	for (int i = 0; i < LAYER_MAX; ++i)
	{
		m_arrLayer[i]->tick();
	}
}

void CLevel::finaltick()
{
	for (int i = 0; i < LAYER_MAX; ++i)
	{
		m_arrLayer[i]->finaltick();
	}
}

CLayer* CLevel::GetLayer(const wstring& _strLayerName)
{
	for (int i = 0; i < LAYER_MAX; ++i)
	{
		if (_strLayerName == m_arrLayer[i]->GetName())
		{
			return m_arrLayer[i];
		}
	}

	return nullptr;
}

void CLevel::AddObject(CGameObject* _Object, int _LayerIdx, bool _bChildMove)
{
	m_arrLayer[_LayerIdx]->AddObject(_Object, _bChildMove);
}

void CLevel::AddObject(CGameObject* _Object, const wstring& _strLayerName, bool _bChildMove)
{
	CLayer* pLayer = GetLayer(_strLayerName);
	if (nullptr == pLayer)
		return;

	pLayer->AddObject(_Object, _bChildMove);
}

CGameObject* CLevel::FindObjectByName(const wstring& _strName)
{
	// 이름이 같은 첫번째 오브젝트 리턴

	for (UINT i = 0; i < LAYER_MAX; ++i)
	{
		const vector<CGameObject*>& vecParent = m_arrLayer[i]->GetParentObjects();

		for (size_t j = 0; j < vecParent.size(); ++j)
		{
			list<CGameObject*> queue;
			queue.push_back(vecParent[j]);

			// 레이어에 입력되는 오브젝트 포함, 그 밑에 달린 자식들까지 모두 확인
			while (!queue.empty())
			{
				CGameObject* pObject = queue.front();
				queue.pop_front();

				const vector<CGameObject*>& vecChild = pObject->GetChild();
				for (size_t k = 0; k < vecChild.size(); ++k)
				{
					queue.push_back(vecChild[k]);
				}

				if (_strName == pObject->GetName())
				{
					return pObject;
				}
			}
		}
	}

	return nullptr;
}

void CLevel::FindObjectsByName(const wstring& _strName, vector<CGameObject*>& _vecObj)
{
	// 해당 이름을 가진 모든 Object를 리턴
	for (UINT i = 0; i < LAYER_MAX; ++i)
	{
		const vector<CGameObject*>& vecParent = m_arrLayer[i]->GetParentObjects();

		for (size_t j = 0; j < vecParent.size(); ++j)
		{
			list<CGameObject*> queue;
			queue.push_back(vecParent[j]);

			// 레이어에 입력되는 오브젝트 포함, 그 밑에 달린 자식들까지 모두 확인
			while (!queue.empty())
			{
				CGameObject* pObject = queue.front();
				queue.pop_front();

				const vector<CGameObject*>& vecChild = pObject->GetChild();
				for (size_t k = 0; k < vecChild.size(); ++k)
				{
					queue.push_back(vecChild[k]);
				}

				if (_strName == pObject->GetName())
				{
					_vecObj.push_back(pObject);
				}
			}
		}
	}
}

void CLevel::ChangeState(LEVEL_STATE _NextState)
{
	if (m_State == _NextState)
		return;

	// 정지 -> 플레이
	if ((LEVEL_STATE::STOP == m_State || LEVEL_STATE::PAUSE == m_State || LEVEL_STATE::NONE == m_State) && LEVEL_STATE::PLAY == _NextState)
	{
		CTimeMgr::GetInst()->LockDeltaTime(false);

		// 레벨 카메라 모드
		CRenderMgr::GetInst()->ActiveEditorMode(false);

		// None, Stop -> Play Begin 호출
		if (LEVEL_STATE::STOP == m_State || LEVEL_STATE::NONE == m_State)
		{
			begin();
		}

		// 레벨 스테이트 변경
		m_State = _NextState;

	}
	// 플레이 -> 정지 or 일시정지
	else if ((LEVEL_STATE::PLAY == m_State || LEVEL_STATE::NONE == m_State) && (LEVEL_STATE::STOP == _NextState || LEVEL_STATE::PAUSE == _NextState || LEVEL_STATE::NONE == _NextState))
	{
		// 레벨 스테이트 변경
		m_State = _NextState;

		CTimeMgr::GetInst()->LockDeltaTime(true);

		// 에디터 카메라 모드
		CRenderMgr::GetInst()->ActiveEditorMode(true);
	}
}

void CLevel::clear()
{
	for (UINT i = 0; i < LAYER_MAX; ++i)
	{
		m_arrLayer[i]->m_vecObjects.clear();
	}
}