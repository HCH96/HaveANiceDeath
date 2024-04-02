#pragma once

#include <Engine\CScript.h>


class CPlatformScript :
    public CScript
{
private:
    bool    m_SideCollision;
    float   m_PermitRange;

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

private:
    void UpCollision(CGameObject* _Obj, float _PlatformTop, float _ObjColScaleY);
    void DownCollision(CGameObject* _Obj, float _PlatformBottom, float _ObjColScaleY);
    void LeftCollision(CGameObject* _Obj, float _PlatformLeft, float _ObjColScaleX);
    void RightCollision(CGameObject* _Obj, float _PlatformRight, float _ObjColScaleX);


public:
    CLONE(CPlatformScript);
    CPlatformScript();
    CPlatformScript(const CPlatformScript& _OriginScript);
    ~CPlatformScript();

};

