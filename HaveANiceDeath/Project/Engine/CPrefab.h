#pragma once
#include "CAsset.h"

typedef void(*SAVE_TYPE)(CGameObject*, FILE*);
typedef CGameObject* (*LOAD_TYPE)(FILE*);

class CPrefab :
    public CAsset
{
private:
    CGameObject* m_ProtoObj;

public:
    static SAVE_TYPE GAMEOBJECT_SAVE;
    static LOAD_TYPE GAMEOBJECT_LOAD;

public:
    void SetGameObject(CGameObject* _Object);
    CGameObject* Instantiate();
    CGameObject* GetProtoObj() { return m_ProtoObj; }

public:
    virtual int Save(const wstring& _strRelativePath);
    virtual int Load(const wstring& _strFilePath);

public:
    CLONE_DISABLE(CPrefab);
    CPrefab(bool _Engine = false);
    CPrefab(CGameObject* _Proto, bool _Engine = false);
    ~CPrefab();
};

