#pragma once

// Engine global 헤더
#include <Engine/global.h>

#ifdef _DEBUG
#pragma comment(lib, "Engine\\Engine_d.lib")
#else
#pragma comment(lib, "Engine\\Engine.lib")
#endif

// std 표준 라일브러리
#include <string.h>
using std::string;
using std::wstring;

#include <crtdbg.h>