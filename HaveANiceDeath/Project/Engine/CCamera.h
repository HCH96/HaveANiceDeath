#pragma once
#include "CComponent.h"

enum class PROJ_TYPE
{
    ORTHOGRAPHIC, // ���� ����
    PERSPECTIVE,  // ���� ����
};

class CCamera :
    public CComponent
{
private:
    PROJ_TYPE               m_ProjType;     // ���� ���

    // ��������(Perspective)
    float                   m_FOV;          // �þ� ��(Filed Of View)

    // ��������(Orthographic)
    float                   m_Width;        // �������� ���� ����
    float                   m_Scale;        // �������� ����

    // Both
    float                   m_AspectRatio;  // ��Ⱦ��, ���� ���μ��� ����
    float                   m_Far;          // ���� �ִ� �Ÿ�

    // ��ȯ ���
    Matrix                  m_matView;
    Matrix                  m_matProj;
    UINT                    m_LayerCheck;
    int                     m_CameraPriority;

    // ��ü �з�
    vector<CGameObject*>    m_vecOpaque;
    vector<CGameObject*>    m_vecMasked;
    vector<CGameObject*>    m_vecTransparent;
    vector<CGameObject*>    m_vecPostProcess;

public:
    PROJ_TYPE GetProjType() { return m_ProjType; }
    float GetWidth() { return m_Width; }
    float GetScale() { return m_Scale; }
    float GetFOV() { return m_FOV; }
    float GetFar() { return m_Far; }
    int GetPriority() { return m_CameraPriority; }

    const Matrix& GetViewMat() { return m_matView; }
    const Matrix& GetProjMat() { return m_matProj; }

    void SetProjType(PROJ_TYPE _Type) { m_ProjType = _Type; }
    void SetWidth(float _Width) { m_Width = _Width; }
    void SetScale(float _Scale) { m_Scale = _Scale; }
    void SetFOV(float _FOV) { m_FOV = _FOV; }
    void SetFar(float _Far) { m_Far = _Far; }

    // Layer üũ Ȯ��
    bool IsLayerCheck(UINT _LayerIdx);
    bool IsLayerCheck(const wstring& _strLayerName);


    void SetCameraPriority(int _Priority) { m_CameraPriority = _Priority; }
    void LayerCheck(UINT _LayerIdx, bool _bCheck);
    void LayerCheck(const wstring& _strLayerName, bool _bCheck);
    void LayerCheckAll() { m_LayerCheck = 0xffffffff; }
    void LayerCheckOffAll() { m_LayerCheck = 0x00000000; }

    // ���ڷ� ������ ���� ī�޶� ���� Diff ����
    Vec2 GetWorldPosInWindow(Vec2 _Diff);

public:
    virtual void begin() override;
    virtual void finaltick() override;
    void SortObject();
    void render();

private:
    void render(vector<CGameObject*>& _vecObj);
    void render_postprocess();
    void render_Bloom();

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;

public:
    CLONE(CCamera);
    CCamera();
    ~CCamera();
};