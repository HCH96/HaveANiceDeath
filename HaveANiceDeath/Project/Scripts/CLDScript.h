#pragma once
#include "CUnitScript.h"



class CLDScript :
    public CUnitScript
{
private:
    bool m_DirChanged;


public:
    bool IsDirChanged() { return m_DirChanged; }

public:
    virtual void begin() override;
    virtual void tick() override;

public:
    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;

public:
    CLONE(CLDScript);
    CLDScript();
    ~CLDScript();
};

