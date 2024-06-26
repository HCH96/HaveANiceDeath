#pragma once

#include <Engine\CScript.h>

class CPlayerMgrScript :
    public CScript
{
private:


public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void UpdateData() override;

public:
    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;


public:
    CLONE(CPlayerMgrScript);
    CPlayerMgrScript();
    ~CPlayerMgrScript();
};

