#pragma once
#include "CEntity.h"

class CConstBuffer :
    public CEntity
{
private:
    D3D11_BUFFER_DESC       m_Desc;
    ComPtr<ID3D11Buffer>    m_CB;

    CB_TYPE                 m_Type;

    UINT                    m_ElementSize;
    UINT                    m_ElementCount;

public:
    void SetData(void* _Src, UINT _ElementCount = 0);

public:
    int Create(UINT _ElementSize, UINT _ElementCount);
    void UpdateData();
    void UpdateData_CS();

public:
    CConstBuffer(CB_TYPE _Type);
    ~CConstBuffer();

    CLONE_DISABLE(CConstBuffer);
};
