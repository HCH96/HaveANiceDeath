#pragma once
#include "CEntity.h"

enum class BB_DATA
{
    INT,
    FLOAT,
    VEC2,
    VEC3,
    VEC4,
    OBJECT,
};

struct tBlackboardData
{
    BB_DATA     Type;
    void* pData;
};

class CBlackboard :
    public CEntity
{
private:
    map<wstring, tBlackboardData>   m_mapBBData;

public:
    void* GetBlackboardData(const wstring& _strKey);

    void AddBlackboardData(const wstring& _strKey, BB_DATA _Type, void* _Data);

public:
    CLONE(CBlackboard);
    CBlackboard();
    CBlackboard(const CBlackboard& _board);
    ~CBlackboard();
};

