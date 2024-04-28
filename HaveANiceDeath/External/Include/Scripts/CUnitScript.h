#pragma once

#include <Engine\CScript.h>

class CGameObject;

class CUnitScript :
    public CScript
{
protected:
    tUnitInfo m_CurUnitInfo;
    tUnitInfo m_PrevUnitInfo;

    bool m_DirLock;

    vector<CGameObject*> m_Ground;
    int  m_OverlapGround;

public:
    bool IsLock() { return m_DirLock; }
    ANIM_DIR GetDir() { return m_CurUnitInfo.Dir; }
    int GetOverlapGround() { return m_OverlapGround; }
    tUnitInfo& GetPrevInfo() { return m_PrevUnitInfo; }
    tUnitInfo& GetUnitInfo() { return m_CurUnitInfo; }

    void SetLock(bool _Lock) { m_DirLock = _Lock; }
    virtual void Hit(float _Damage) {}


    bool IsOverlapGround(CGameObject* _pObject);
    void AddOverlapGround(CGameObject* _pObejct);
    void SubOverlapGround(CGameObject* _pObejct);

public:
    virtual void begin() override;
    virtual void tick() override;

public:
    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;

public:
    CLONE(CUnitScript);
    CUnitScript();
    CUnitScript(UINT _ScriptType);
    CUnitScript(const CUnitScript& _Origin);
    ~CUnitScript();
};

