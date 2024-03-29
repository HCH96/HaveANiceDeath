#pragma once
#include "singleton.h"

class CLevel;

class CLevelMgr :
    public CSingleton<CLevelMgr>
{
    SINGLE(CLevelMgr);
private:
    CLevel* m_CurLevel;

public:
    CLevel* GetCurrentLevel() { return m_CurLevel; }

public:
    void ChangeLevel(CLevel* _NextLevel, LEVEL_STATE _NextStartState);
    void ChangeLevelState(LEVEL_STATE _State);

private:
    void ChangeLevel_Task(CLevel* _NextLevel, LEVEL_STATE _NextLevelState);

public:
    void init();
    void tick();

    friend class CTaskMgr;
};
