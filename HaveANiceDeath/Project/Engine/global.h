#pragma once

// ǥ�� ���̺귯��
#include <stdlib.h>
#include <Windows.h>
#include <typeinfo>

#include <vector>
#include <list>
#include <map>
#include <string>

using std::vector;
using std::list;
using std::map;
using std::make_pair;
using std::wstring;
using std::string;

#include <wrl.h>
using namespace Microsoft::WRL;

// DirectX ��� �� ���̺귯�� ����
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;


// ���� ��� ����
#include "singleton.h"
#include "define.h"
//#include "struct.h"
//#include "func.h"