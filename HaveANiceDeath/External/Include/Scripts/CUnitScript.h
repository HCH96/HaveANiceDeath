#pragma once

#include <Engine\CScript.h>


class CUnitScript :
    public CScript
{
protected:
    tUnitInfo m_CurUnitInfo;
    tUnitInfo m_NextUnitInfo;

    bool m_DirLock;

public:
    tUnitInfo& GetUnitInfo() { return m_CurUnitInfo; }
    tUnitInfo& GetNextInfo() { return m_NextUnitInfo; }

    ANIM_DIR GetDir() { return m_CurUnitInfo.Dir; }

    void SetLock(bool _Lock) { m_DirLock = _Lock; }
    bool IsLock() { return m_DirLock; }

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
    ~CUnitScript();
};

