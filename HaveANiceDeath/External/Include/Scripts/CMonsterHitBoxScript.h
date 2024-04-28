#pragma once

#include <Engine/CScript.h>

class CMonsterHitBoxScript :
    public CScript
{
private:
    Vec3    m_ColOffset;
    Vec3    m_ColScale;

    float   m_Damage;

    float   m_Acc;
    float   m_Duration;   

    bool    m_Active;

public:
    void SetOffset(Vec3 _Offset) { m_ColOffset = _Offset; }
    void SetScale(Vec3 _Scale) { m_ColScale = _Scale; }
    void SetDuration(float _Duration) { m_Duration = _Duration; }
    void SetDamage(float _Damage) { m_Damage = _Damage; }

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
    CLONE(CMonsterHitBoxScript);
    CMonsterHitBoxScript();
    CMonsterHitBoxScript(const CMonsterHitBoxScript& _Origin);
    ~CMonsterHitBoxScript();

};

