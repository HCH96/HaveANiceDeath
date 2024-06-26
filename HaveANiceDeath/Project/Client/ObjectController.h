#pragma once
#include "UI.h"

class CGameObject;

class ObjectController 
{
private:
	vector<string>					m_vecLayerName;
	vector<CGameObject*>			m_vecObject;
	string							m_CurLayer;

	CGameObject*					m_ClickedObject;


public:
	// 오브젝트 위치로 에디터 카메라 위치 변경
	void FocusObject(CGameObject* _Object);
	void SetTargetObject(CGameObject* _Object) { m_ClickedObject = _Object; }


public:
	void tick();
	void render();

private:
	void FindObject(vector<CGameObject*>& _OutObject, Vec2 _MouseWorldPos);
	CGameObject* FindObject(Vec2 _MouseWorldPos);


public:
    ObjectController();
    ~ObjectController();

};

