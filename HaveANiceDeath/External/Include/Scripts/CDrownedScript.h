#pragma once
#include "CMonsterScript.h"

class CDrownedScript :
    public CMonsterScript
{
public:
    virtual void Hit(float _Damage) override;

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
    CLONE(CDrownedScript);
    CDrownedScript();
    ~CDrownedScript();

};

