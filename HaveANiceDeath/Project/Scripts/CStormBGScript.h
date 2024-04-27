#pragma once

#include <Engine/CScript.h>


class CStormBGScript :
    public CScript
{
public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToFile(FILE* _File);
    virtual void LoadFromFile(FILE* _File);

public:
    CLONE(CStormBGScript);
    CStormBGScript();
    ~CStormBGScript();

};

