#pragma once
#include "CComponent.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"

#include "CAssetMgr.h"

#include "CGameObject.h"
#include "components.h"


class CScript :
    public CComponent
{
private:
    const UINT m_ScriptType;

public:
    UINT GetScriptType() { return m_ScriptType; }

protected:
    void Instantiate(Ptr<CPrefab> _Prefab, Vec3 _vWorldPos, int _LayerIdx);

public:
    virtual void finaltick() final {}

    virtual void BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider) {}
    virtual void Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider) {}
    virtual void EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider) {}

    virtual void SaveToFile(FILE* _File) = 0;
    virtual void LoadFromFile(FILE* _File) = 0;
public:
    CScript(UINT _ScriptType);
    ~CScript();
    CScript* Clone() = 0;
};

