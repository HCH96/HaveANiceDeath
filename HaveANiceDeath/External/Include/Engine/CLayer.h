#pragma once
#include "CEntity.h"

class CGameObject;

class CLayer :
    public CEntity
{
private:
    vector<CGameObject*>    m_vecParent;
    vector<CGameObject*>    m_vecObjects;
    int                     m_LayerIdx;

public:
    const vector<CGameObject*>& GetParentObjects() { return  m_vecParent; }
    const vector<CGameObject*>& GetLayerObjects() { return m_vecObjects; }
    int GetLayerIdx() { return m_LayerIdx; }

public:
    // 특정 오브젝트를 레이어에서 제거
    void AddObject(CGameObject* _Object, bool _bMove);
    void AddObject_Load(CGameObject* _Object, bool _bMove);
    void RegisterGameObject(CGameObject* _Object) { m_vecObjects.push_back(_Object); }
    void DetachGameObject(CGameObject* _Object);

private:
    void begin();
    void tick();
    void finaltick();

public:
    CLONE(CLayer);
    CLayer();
    CLayer(const CLayer& _OriginLayer);
    ~CLayer();

    friend class CLevel;
};