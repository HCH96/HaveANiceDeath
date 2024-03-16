#pragma once
#include "CEntity.h"

class CLayer;
class CGameObject;


class CLevel :
	public CEntity
{
private:
	LEVEL_STATE		m_State;
	CLayer*			m_arrLayer[LAYER_MAX];

public:
	LEVEL_STATE GetState() { return m_State; }
	CLayer* GetLayer(int _iLayerIdx) { return m_arrLayer[_iLayerIdx]; }
	CLayer* GetLayer(const wstring& _strLayerName);

public:
	void AddObject(CGameObject* _Object, int _LayerIdx, bool _bChildMove = true);
	void AddObject(CGameObject* _Object, const wstring& _strLayerName, bool _bChildMove = true);
	CGameObject* FindObjectByName(const wstring& _strName);
	void FindObjectsByName(const wstring& _strName, vector<CGameObject*>& _vecObj);

public:
	void ChangeState(LEVEL_STATE _NextState);

public:
	void begin();
	void tick();
	void finaltick();

private:
	void clear();

public:
	CLONE(CLevel);
	CLevel();
	CLevel(const CLevel& _OriginLevel);
	~CLevel();

	friend class CLevelMgr;
};