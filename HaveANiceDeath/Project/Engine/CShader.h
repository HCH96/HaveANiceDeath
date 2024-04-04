#pragma once
#include "CAsset.h"

struct tScalarParam
{
    SCALAR_PARAM    Type;
    string          Desc;
};

struct tTexParam
{
    TEX_PARAM       Type;
    string          Desc;
};

class CShader :
    public CAsset
{
protected:
    ComPtr<ID3DBlob>    m_ErrBlob;

    // Shader 파라미터 목록
    vector<tScalarParam>            m_ScalarParam;
    vector<tTexParam>               m_TexParam;


public:
    virtual int UpdateData() = 0;
    void AddScalarParam(SCALAR_PARAM _Param, const string& _Desc) { m_ScalarParam.push_back(tScalarParam{ _Param , _Desc }); }
    void AddTexParam(TEX_PARAM _Param, const string& _Desc) { m_TexParam.push_back(tTexParam{ _Param , _Desc }); }



public:
    CShader(ASSET_TYPE _Type, bool _Engine = true);
    ~CShader();

    CLONE_DISABLE(CShader);
};
