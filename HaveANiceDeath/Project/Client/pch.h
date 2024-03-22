#pragma once

#define IMGUI_DEFINE_MATH_OPERATORS
//#define _RELEASE_GAME

// Engine global 헤더
#include <Engine\global.h>
#include <Engine\CEngine.h>
#include <Engine\CDevice.h>
#include <Engine/CPrefab.h>

#include "CLevelSaveLoad.h"

// Engine lib
#ifdef _DEBUG
#pragma comment(lib, "Engine\\Engine_d.lib")
#else
#pragma comment(lib, "Engine\\Engine.lib")
#endif

// State lib
#ifdef _DEBUG
#pragma comment(lib, "States\\States_d.lib")
#else
#pragma comment(lib, "States\\States.lib")
#endif

// Scripts lib
#ifdef _DEBUG
#pragma comment(lib, "Scripts\\Scripts_d.lib")
#else
#pragma comment(lib, "Scripts\\Scripts.lib")
#endif

// std 표준 라일브러리
#include <string.h>
using std::string;
using std::wstring;

#include <crtdbg.h>

// imgui
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

#include "CImGuiMgr.h"
#include "CEditorObjMgr.h"
#include "CCreateTempLevel.h"