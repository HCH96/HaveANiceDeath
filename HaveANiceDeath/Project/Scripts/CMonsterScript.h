#pragma once
#include "CUnitScript.h"
class CMonsterScript :
    public CUnitScript
{
private:
    Vec4    m_VarColor;
    float m_Acc;
    float m_Duration;

    bool m_IsVariation;

protected:
    void Variation();
    void Knockback();


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
    CLONE(CMonsterScript);
    CMonsterScript();
    CMonsterScript(UINT _ScriptType);
    ~CMonsterScript();

};

