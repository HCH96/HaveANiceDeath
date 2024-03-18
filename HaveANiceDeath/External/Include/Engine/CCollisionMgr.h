#pragma once
#include "singleton.h"

union COL_ID
{
    struct
    {
        UINT LeftID;
        UINT RightID;
    };

    LONGLONG ID;
};

class CCollider2D;

class CCollisionMgr :
    public CSingleton<CCollisionMgr>
{
    SINGLE(CCollisionMgr);
private:
    UINT                m_Matrix[(UINT)LAYER_MAX];
    map<LONGLONG, bool> m_ColInfo;



public:
    void LayerCheck(UINT _LayerLeftIdx, UINT _LayerRightIdx);
    void LayerCheck(const wstring& _LeftLayer, const wstring& _RightLayer);
    void Clear()
    {
        for (int i = 0; i < LAYER_MAX; ++i)
        {
            m_Matrix[i] = 0;
        }
    }

public:
    void tick();


private:
    void CollisionBtwLayers(UINT _Left, UINT _Right);
    void CollisionBtwCollider2D(CCollider2D* _LeftCol, CCollider2D* _RightCol);
    bool IsCollision(CCollider2D* _LeftCol, CCollider2D* _RightCol);
};

