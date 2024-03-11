#pragma once
#include "CEntity.h"

#include "Ptr.h"

class CAsset :
    public CEntity
{
private:
    wstring             m_Key;
    wstring             m_RelativePath;
    int                 m_RefCount;
    const ASSET_TYPE    m_Type;
    const bool          m_EngineAsset;

public:
    const wstring& GetKey() { return m_Key; }
    const wstring& GetRelativePath() { return m_RelativePath; }
    ASSET_TYPE GetType() { return m_Type; }
    int GetRefCount() { return m_RefCount; }
    bool IsEngineAsset() { return m_EngineAsset; }

private:
    void SetKey(const wstring& _Key) { m_Key = _Key; }
    void SetRelativePath(const wstring& _RelativePath) { m_RelativePath = _RelativePath; }

    void AddRef() { ++m_RefCount; }
    void Release()
    {
        --m_RefCount;
        if (0 >= m_RefCount)
        {
            delete this;
        }
    }

    virtual int Save(const wstring& _strRelativePath) { return E_FAIL; }
    virtual int Load(const wstring& _strFilePath) { return E_FAIL; }

public:
    virtual CAsset* Clone() = 0;

    CAsset(ASSET_TYPE _Type, bool _bEngineAsset);
    ~CAsset();

    friend class CAssetMgr;

    template<typename T>
    friend class Ptr;
};