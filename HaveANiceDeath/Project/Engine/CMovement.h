#pragma once
#include "CComponent.h"

// ====================================================
// CComponent: �̵� ���� ���
// ====================================================

class CPlayer;

typedef short MovementDir;

enum MovementDirFlag
{
    MV_UP = 0x01,
    MV_DOWN = 0x02,
    MV_LEFT = 0x04,
    MV_RIGHT = 0x08,
};

class CMovement :
    public CComponent
{
private:
    MovementDir m_Dir;

    Vec3        m_vForce;            // ������ ��
    Vec3        m_vAccel;            // ���� ���ӵ�
    Vec3        m_vVelocity;         // ���� �ӵ�
    Vec3        m_vGravityForce;     // �߷� ����, ����
    float       m_fMass;             // ����
    float       m_fInitSpeed;        // �ּ�(�ʱ�ȭ) �ӷ�
    float       m_fMaxSpeed_Ground;  // ���� �ִ� �ӷ�
    float       m_fMaxSpeed_InAir;   // ���� �ִ� �ӷ�
    float       m_fFrictionScale;    // ���� ũ��
    bool        m_bUseGravity;       // �߷� ���
    bool        m_bGround;           // �� ��

public:
    virtual void begin() override;
    virtual void finaltick() override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;

public:
    MovementDir GetDir() { return m_Dir; }
    void CalDir();

public:
    void AddForce(Vec3 _vForce) { m_vForce += _vForce; }
    void SetVelocity(Vec3 _vVelocity) { m_vVelocity = _vVelocity; }
    void SetGravityForce(Vec3 _vGravityForce) { m_vGravityForce = _vGravityForce; }
    void SetMass(float _Mass) { m_fMass = _Mass; }
    void SetInitSpeed(float _Speed) { m_fInitSpeed = _Speed; }
    void SetMaxSpeed_Ground(float _Speed) { m_fMaxSpeed_Ground = _Speed; }
    void SetMaxSpeed_InAir(float _Speed) { m_fMaxSpeed_InAir = _Speed; }
    void SetFrictionScale(float _F) { m_fFrictionScale = _F; }
    void SetGround(bool _Ground) { if (_Ground) { m_vVelocity.y = 0.f; } m_bGround = _Ground; }
    void UseGravity(bool _Use) { m_bUseGravity = _Use; }
    Vec3 MakeMoveToForce(){ return m_vAccel * m_fMass;}
    void SetVelocityX(float _XSpeed) { m_vVelocity.x = _XSpeed; }
    void SetVelocityY(float _YSpeed) { m_vVelocity.y = _YSpeed; }


    Vec3 GetForce() { return m_vForce; }
    Vec3 GetVelocity() {return m_vVelocity;}
    Vec3 GetGravityForce() { return m_vGravityForce; }
    float GetMass() { return m_fMass; }
    float GetInitSpeed() { return m_fInitSpeed; }
    float GetMaxSpeed_Ground() { return m_fMaxSpeed_Ground; }
    float GetMaxSpeed_InAir() { return m_fMaxSpeed_InAir; }
    float GetFrictionScale() { return m_fFrictionScale; }
    bool IsUseGravity() { return m_bUseGravity; }
    bool IsGround() { return m_bGround; }

public:
    CLONE(CMovement);
    CMovement();
    CMovement(const CMovement& _Origin);
    ~CMovement();
};