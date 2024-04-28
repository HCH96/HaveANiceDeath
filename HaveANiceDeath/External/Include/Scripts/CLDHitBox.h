#pragma once
#include <Engine\CScript.h>
class CLDHitBox :
    public CScript
{
private:
    float m_Damage;

    float m_Acc;
    float m_StartTime;
    float m_Duration;

    bool m_Active;
    bool m_IsColliderActive;

public:
    void On();
    void Off();

    void Activate();

public:
    virtual void begin() override;
    virtual void tick() override;

public:
    virtual void BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider) override;
    virtual void Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider) override;
    virtual void EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider) override;

public:
    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;

public:
    CLONE(CLDHitBox);
    CLDHitBox();
    CLDHitBox(const CLDHitBox& _Origin);
    ~CLDHitBox();
};

