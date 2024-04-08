#pragma once
#include "CEntity.h"

#define GET_COMPONENT(Type, TYPE) class C##Type* Type() { return (C##Type*)m_arrCom[(UINT)COMPONENT_TYPE::##TYPE]; }

class CComponent;
class CScript;
class CCamera;
class CCollider2D;
class CLight2D;
class CStateMachine;
class CMovement;

class CRenderComponent;
class CMeshRender;
class CTileMap;
class CParticleSystem;

class CGameObject :
    public CEntity
{
private:
    CGameObject*            m_Parent;
    vector<CGameObject*>    m_vecChild;
    int                     m_LayerIdx;
    bool                    m_bDead;

    CComponent*             m_arrCom[(UINT)COMPONENT_TYPE::END];
    CRenderComponent*       m_RenderCom;
    vector<CScript*>        m_vecScript;



public:
    CGameObject* GetParent() { return m_Parent; }
    const vector<CGameObject*>& GetChild() { return m_vecChild; }
    CGameObject* GetChild(const wstring& _ChildName);
    int GetLayerIdx() { return m_LayerIdx; }

    CComponent* GetComponent(COMPONENT_TYPE _Type) { return m_arrCom[(UINT)_Type]; }
    CRenderComponent* GetRenderComponent() { return m_RenderCom; }
    const vector<CScript*>& GetScripts() { return m_vecScript; }
    void SetLayerIdx(int _LayerIdx) { m_LayerIdx = _LayerIdx; }


    GET_COMPONENT(Transform, TRANSFORM);
    GET_COMPONENT(Collider2D, COLLIDER2D);
    GET_COMPONENT(Animator2D, ANIMATOR2D);
    GET_COMPONENT(Light2D, LIGHT2D);
    GET_COMPONENT(Camera, CAMERA);
    GET_COMPONENT(StateMachine, STATEMACHINE);
    GET_COMPONENT(Movement, MOVEMENT);

    GET_COMPONENT(MeshRender, MESHRENDER);
    GET_COMPONENT(TileMap, TILEMAP);
    GET_COMPONENT(ParticleSystem, PARTICLESYSTEM);

    template<typename T>
    T* GetScript()
    {
        for (size_t i = 0; i < m_vecScript.size(); ++i)
        {
            if (dynamic_cast<T*>(m_vecScript[i]))
                return (T*)m_vecScript[i];
        }
        return nullptr;
    }

public:
    void AddComponent(CComponent* _Comonent);
    void DeleteComponent(COMPONENT_TYPE _Type);
    int  ChangeLayer(int _Idx);

    int DisconnectWithParent();
    int DisconnectWithLayer();

    void AddChild(CGameObject* _Child);
    void AddChild_Load(CGameObject* _Child);

    bool IsDead() { return m_bDead; }

    void Destroy();

    bool IsAncestor(CGameObject* _Other);

public:
    void begin();
    void tick();
    virtual void finaltick();
    void render();

public:
    CLONE(CGameObject);
    CGameObject();
    CGameObject(const CGameObject& _OriginObject);
    ~CGameObject();

    friend class CLayer;
    friend class CTaskMgr;
};