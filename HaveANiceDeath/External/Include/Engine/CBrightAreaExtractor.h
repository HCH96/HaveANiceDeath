#pragma once
#include "CComputeShader.h"
class CBrightAreaExtractor :
    public CComputeShader
{
private:
    Ptr<CTexture>   m_TargetTex;


public:
    CBrightAreaExtractor();
    ~CBrightAreaExtractor();
};

