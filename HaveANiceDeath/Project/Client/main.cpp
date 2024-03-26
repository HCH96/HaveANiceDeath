#include "pch.h"
#include "framework.h"
#include "Client.h"

#include <dwmapi.h>



#include <Engine\CEngine.h>
#include <Engine\CDevice.h>

#define MAX_LOADSTRING 100

//#define _RELEASE_GAME

HINSTANCE   hInst;
HWND        hWnd;
Vec2        Resolution;

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow){
    // Memory Leak Check
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(55512);
    
    MyRegisterClass(hInstance);
    
    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));
    MSG msg;

#ifndef _RELEASE_GAME
    // 해상도 
    Resolution = Vec2(1919.f, 1001.f);

    RECT rt = { 0,0,(int)Resolution.x, (int)Resolution.y };
    AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
    SetWindowPos(hWnd, nullptr, -7, 0, rt.right - rt.left, rt.bottom - rt.top, 0);

    BOOL USE_DARK_MODE = true;
    BOOL SET_IMMERSIVE_DARK_MODE_SUCCESS = SUCCEEDED(DwmSetWindowAttribute(
        hWnd, DWMWINDOWATTRIBUTE::DWMWA_USE_IMMERSIVE_DARK_MODE,
        &USE_DARK_MODE, sizeof(USE_DARK_MODE)));

    COLORREF DARK_COLOR = 0x00505050;
    BOOL SET_BORDER_COLOR = SUCCEEDED(DwmSetWindowAttribute(
        hWnd, DWMWINDOWATTRIBUTE::DWMWA_BORDER_COLOR,
        &DARK_COLOR, sizeof(DARK_COLOR)));

    //COLORREF DARK_COLOR = 0x00505050;
    BOOL SET_CAPTION_COLOR = SUCCEEDED(DwmSetWindowAttribute(
        hWnd, DWMWINDOWATTRIBUTE::DWMWA_CAPTION_COLOR,
        &DARK_COLOR, sizeof(DARK_COLOR)));

#else
    Resolution = Vec2(1600.f, 900.f);
    // 현재 윈도우 스타일 가져오기
    LONG_PTR style = GetWindowLongPtr(hWnd, GWL_STYLE);

    // 윈도우를 전체 화면으로 변경하기 위해 스타일을 WS_POPUP으로 변경
    style &= ~WS_OVERLAPPEDWINDOW;
    style |= WS_POPUP;

    // 윈도우 스타일 설정
    SetWindowLongPtr(hWnd, GWL_STYLE, style);

    // 전체 화면으로 윈도우 크기 및 위치 설정
    SetWindowPos(hWnd, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), SWP_FRAMECHANGED | SWP_SHOWWINDOW);
#endif


    // CEngine 초기화 실패 -> 프로그램 종료
    if (FAILED(CEngine::GetInst()->init(hWnd, Resolution)))
    {
        MessageBox(nullptr, L"CEngine 초기화 실패", L"초기화 실패", MB_OK);
        return 0;
    }

    CPrefab::GAMEOBJECT_SAVE = &CLevelSaveLoad::SaveGameObject;
    CPrefab::GAMEOBJECT_LOAD = &CLevelSaveLoad::LoadGameObject;



#ifndef _RELEASE_GAME
    // 임시 레벨 생성
    CCreateTempLevel::Init();
    CCreateTempLevel::CreateTempLevel();

    const map<wstring, Ptr<CAsset>> test = CAssetMgr::GetInst()->GetAssets<CTexture>();

    // EditorObjectManager 초기화
    CEditorObjMgr::GetInst()->init();

    // ImGui 초기화
    CImGuiMgr::GetInst()->init(hWnd, DEVICE, CONTEXT);
    CImGuiMgr::GetInst()->begin();
#endif

    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                break;

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            // Engine Update
            CEngine::GetInst()->progress();



#ifndef _RELEASE_GAME
            // EditorObj
            CEditorObjMgr::GetInst()->progress();

            // ImGui Update
            CImGuiMgr::GetInst()->progress();
#endif

            // 출력
            CDevice::GetInst()->Present();
        }
    }

    return (int) msg.wParam;
}


ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLIENT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = nullptr; //MAKEINTRESOURCEW(IDC_CLIENT);
    wcex.lpszClassName  = L"GameWindow";
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   hWnd = CreateWindowW(L"GameWindow", L"Have A Nice Death", WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
        return true;

    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 메뉴 선택을 구문 분석합니다:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_DPICHANGED:
        if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_DpiEnableScaleViewports)
        {
            //const int dpi = HIWORD(wParam);
            //printf("WM_DPICHANGED to %d (%.0f%%)\n", dpi, (float)dpi / 96.0f * 100.0f);
            const RECT* suggested_rect = (RECT*)lParam;
            ::SetWindowPos(hWnd, nullptr, suggested_rect->left, suggested_rect->top, suggested_rect->right - suggested_rect->left, suggested_rect->bottom - suggested_rect->top, SWP_NOZORDER | SWP_NOACTIVATE);
        }
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
