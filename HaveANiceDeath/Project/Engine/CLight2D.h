#pragma once
#include "CComponent.h"


class CLight2D :
    public CComponent
{
private:
    tLightInfo      m_Info;

public:
    const tLightInfo& GetLightInfo() { return m_Info; }
    Vec4 GetLightColor(Vec3 _vColor) { return m_Info.vColor; }
    Vec4 GetSpecular(Vec3 _vSpec) { return m_Info.vSpecular; }
    Vec4 GetAmbient(Vec3 _vAmb) { return m_Info.vAmbient; }
    LIGHT_TYPE GetLightType() { return (LIGHT_TYPE)m_Info.LightType; }
    float GetRadius() { return m_Info.fRadius; }
    float GetAngle() { return m_Info.fAngle; }

    void SetLightColor(Vec3 _vColor) { m_Info.vColor = _vColor; }
    void SetSpecular(Vec3 _vSpec) { m_Info.vSpecular = _vSpec; }
    void SetAmbient(Vec3 _vAmb) { m_Info.vAmbient = _vAmb; }
    void SetLightType(LIGHT_TYPE _type) { m_Info.LightType = (int)_type; }
    void SetRadius(float _Radius) { m_Info.fRadius = _Radius; }
    void SetAngle(float _Angle) { m_Info.fAngle = _Angle; }

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;

public:
    virtual void finaltick() override;

public:
    CLONE(CLight2D);
    CLight2D();
    ~CLight2D();
};
