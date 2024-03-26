#pragma once
#include "UI.h"

class ObjectController 
{
private:
	vector<string>      m_vecLayerName;
	string				m_CurLayer;

public:
	void tick();
	void render();


public:
    ObjectController();
    ~ObjectController();

};

