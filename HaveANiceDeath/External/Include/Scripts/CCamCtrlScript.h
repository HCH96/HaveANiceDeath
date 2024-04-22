#pragma once

#include <Engine/CScript.h>
#include <deque>

enum class CAMEFFECT_TYPE
{
    SHAKE,
    TRANSITION_OFF,
    TRANSITION_ON,
    END,
};

struct FCamEffect
{
    CAMEFFECT_TYPE Type;
    float fPlayTime = 0.f;
    float fAccTime = 0.f;
    float fVar = 0.f;
};

class CGameObject;

class CCamCtrlScript :
    public CScript
{
private:
    CGameObject*        m_Target;
    Vec3                m_CamOffset;
    Vec3                m_Move;
    float               m_Speed;
    float               m_SpeedScale;

    bool                m_IsTracking;

    deque<FCamEffect>   m_Effect;
    CGameObject* m_Transition;

public:
    Vec3 GetMove() { return m_Move; }

    void SetTarget(CGameObject* _Target) { m_Target = _Target; }
    void PushEffect(FCamEffect _Effect);
    void PushTransition(bool _Start);

private:
    Vec3 CheckCamArea(Vec3 _Pos);

public:
    virtual void begin() override;
    virtual void tick() override;

public:
    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;

public:
    CLONE(CCamCtrlScript);
    CCamCtrlScript();
    CCamCtrlScript(const CCamCtrlScript& _Origin);
    ~CCamCtrlScript();
};

