#pragma once

class CEngine :
    public CSingleton<CEngine>
{
    SINGLE(CEngine);

private:
    HWND        m_MainWindow;             // ���� ������ �ڵ�
    Vec2		m_Resolution;			// �ػ� ����

public:
    HWND GetMainWindow() { return m_MainWindow; }

public:
    int init(HWND _HWND, Vec2 _Resolution);
    void progress();
};

