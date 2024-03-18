#pragma once

class CEngine :
    public CSingleton<CEngine>
{
    SINGLE(CEngine);

private:
    HWND        m_MainWindow;             // 메인 윈도우 핸들
    Vec2		m_Resolution;			// 해상도 정보

public:
    HWND GetMainWindow() { return m_MainWindow; }

public:
    int init(HWND _HWND, Vec2 _Resolution);
    void progress();
};

