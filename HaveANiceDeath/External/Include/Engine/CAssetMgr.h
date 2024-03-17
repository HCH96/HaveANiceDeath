#pragma once
#include "singleton.h"

#include "CPathMgr.h"

#include "CTexture.h"
#include "CMesh.h"
#include "CGraphicsShader.h"
#include "CMaterial.h"
#include "CPrefab.h"


template<typename T>
void SaveAssetRef(Ptr<T> _Asset, FILE* _File);

template<typename T>
void LoadAssetRef(Ptr<T>& _Asset, FILE* _File);

class CAssetMgr :
    public CSingleton<CAssetMgr>
{
    SINGLE(CAssetMgr);
private:
    map<wstring, Ptr<CAsset>>   m_mapAsset[(UINT)ASSET_TYPE::END];

public:
    template<typename T>
    const map<wstring, Ptr<CAsset>>& GetAssets();

    const map<wstring, Ptr<CAsset>>& GetAssets(ASSET_TYPE _Type) { return m_mapAsset[(UINT)_Type]; }

    template<typename T>
    void AddAsset(const wstring& _strKey, T* _Asset);

    void AddAsset(const wstring& _strKey, CAsset* _Asset);

    template<typename T>
    Ptr<T> FindAsset(const wstring& _strKey);

    template<typename T>
    Ptr<T> Load(const wstring& _strKey, const wstring& _strRelativePath);

    // _Flag : D3D11_BIND_FLAG
    Ptr<CTexture> CreateTexture(const wstring& _strKey, UINT _Width, UINT _Height, DXGI_FORMAT _Format, UINT _Flag, D3D11_USAGE _Usage = D3D11_USAGE_DEFAULT);
    Ptr<CTexture> CreateTexture(const wstring& _strKey, ComPtr<ID3D11Texture2D> _Tex2D);

    // ������ Ÿ���� ��� ������ �̸��� �޾ƿ´�
    void GetAssetName(ASSET_TYPE _Type, vector<string>& _Out);

public:
    void init();

private:
    void InitSound();
    void CreateDefaultMesh();
    void CreateDefaultGraphicsShader();
    void CreateDefaultComputeShader();
    void CreateDefaultMaterial();

private:
    // ������ ������ �����Ѵ�.
    template<typename T>
    void DeleteAsset(const wstring& _strKey);
    void DeleteAsset(ASSET_TYPE _Type, const wstring& _strKey);


    friend class CTaskMgr;
};

template<typename T>
ASSET_TYPE GetAssetType()
{
    ASSET_TYPE Type = ASSET_TYPE::END;

    if constexpr (std::is_same_v<CMesh, T>)
        Type = ASSET_TYPE::MESH;
    if constexpr (std::is_same_v<CTexture, T>)
        Type = ASSET_TYPE::TEXTURE;
    if constexpr (std::is_same_v<CGraphicsShader, T>)
        Type = ASSET_TYPE::GRAPHICS_SHADER;
    //if constexpr (std::is_same_v<CComputeShader, T>)
    //    Type = ASSET_TYPE::COMPUTE_SHADER;
    if constexpr (std::is_same_v<CMaterial, T>)
        Type = ASSET_TYPE::MATERIAL;
    if constexpr (std::is_same_v<CPrefab, T>)
        Type = ASSET_TYPE::PREFAB;
    //if constexpr (std::is_same_v<CSound, T>)
    //    Type = ASSET_TYPE::SOUND;
    //if constexpr (std::is_same_v<CFSM, T>)
    //    Type = ASSET_TYPE::FSM;

    return Type;
}

template<typename T>
inline const map<wstring, Ptr<CAsset>>& CAssetMgr::GetAssets()
{
    ASSET_TYPE Type = GetAssetType<T>();

    return m_mapAsset[(UINT)Type];
}

template<typename T>
inline void CAssetMgr::AddAsset(const wstring& _strKey, T* _Asset)
{
    ASSET_TYPE Type = GetAssetType<T>();

    map<wstring, Ptr<CAsset>>::iterator iter = m_mapAsset[(UINT)Type].find(_strKey);
    assert(iter == m_mapAsset[(UINT)Type].end());

    _Asset->SetKey(_strKey);
    m_mapAsset[(UINT)Type].insert(make_pair(_strKey, _Asset));
}

template<typename T>
Ptr<T> CAssetMgr::FindAsset(const wstring& _strKey)
{
    ASSET_TYPE Type = GetAssetType<T>();

    map<wstring, Ptr<CAsset>>::iterator iter = m_mapAsset[(UINT)Type].find(_strKey);

    if (iter == m_mapAsset[(UINT)Type].end())
    {
        return nullptr;
    }

    return (T*)iter->second.Get();
}


template<typename T>
Ptr<T> CAssetMgr::Load(const wstring& _strKey, const wstring& _strRelativePath)
{
    Ptr<T> pAsset = FindAsset<T>(_strKey);

    // �ε��� �� ����� Ű�� �̹� �ٸ� ������ �ִٸ�
    if (nullptr != pAsset)
    {
        return (T*)pAsset.Get();
    }

    wstring strFilePath = CPathMgr::GetContentPath();
    strFilePath += _strRelativePath;

    pAsset = new T;
    if (FAILED(pAsset->Load(strFilePath)))
    {
        MessageBox(nullptr, L"���� �ε� ����", L"���� �ε� ����", MB_OK);
        pAsset = nullptr;
        return nullptr;
    }

    pAsset->SetKey(_strKey);
    pAsset->SetRelativePath(_strRelativePath);

    AddAsset<T>(_strKey, (T*)pAsset.Get());

    return (T*)pAsset.Get();
}

template<typename T>
inline void CAssetMgr::DeleteAsset(const wstring& _strKey)
{
    ASSET_TYPE AssetType = GetAssetType<T>();

    map<wstring, Ptr<CAsset>>::iterator iter = m_mapAsset[(UINT)AssetType].find(_strKey);

    assert(!(iter == m_mapAsset[(UINT)AssetType].end()));

    m_mapAsset[(UINT)AssetType].erase(iter);
}


// ========================
// Asset Save Load Function
// ========================


template<typename T>
void SaveAssetRef(Ptr<T> _Asset, FILE* _File)
{
    bool bAssetExist = false;
    _Asset == nullptr ? bAssetExist = false : bAssetExist = true;

    fwrite(&bAssetExist, sizeof(bool), 1, _File);

    if (bAssetExist)
    {
        SaveWString(_Asset->GetKey(), _File);
        SaveWString(_Asset->GetRelativePath(), _File);
    }
}

template<typename T>
void LoadAssetRef(Ptr<T>& _Asset, FILE* _File)
{
    bool bAssetExist = false;
    fread(&bAssetExist, sizeof(bool), 1, _File);

    if (bAssetExist)
    {
        wstring strKey, strRelativePath;

        LoadWString(strKey, _File);
        LoadWString(strRelativePath, _File);

        _Asset = CAssetMgr::GetInst()->Load<T>(strKey, strRelativePath);
    }
}