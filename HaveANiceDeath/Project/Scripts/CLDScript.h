#pragma once
#include "CUnitScript.h"



class CLDScript :
    public CUnitScript
{
private:

    int m_NextComboStand;

    bool m_DirChanged;
    bool m_IsDownCollision;



public:
    bool IsDownCollision() { return m_IsDownCollision; }
    bool IsDirChanged() { return m_DirChanged; }
    void SetDir(ANIM_DIR _Dir) { m_CurUnitInfo.Dir = _Dir; }
    void SetDownCollision(bool _IsDown) { m_IsDownCollision = _IsDown; }
    void ResetComboStand() { m_NextComboStand = 1; }

    void PlayComboStand();

public:
    virtual void BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider) override;
    virtual void Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider) override;
    virtual void EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider) override;


public:
    virtual void begin() override;
    virtual void tick() override;

public:
    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;

public:
    CLONE(CLDScript);
    CLDScript();
    CLDScript(const CLDScript& _Origin);
    ~CLDScript();
};

