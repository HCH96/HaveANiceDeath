#pragma once

// Engine global ���
#include <Engine/global.h>

#ifdef _DEBUG
#pragma comment(lib, "Engine\\Engine_d.lib")
#else
#pragma comment(lib, "Engine\\Engine.lib")
#endif

// std ǥ�� ���Ϻ귯��
#include <string.h>
using std::string;
using std::wstring;

#include <crtdbg.h>