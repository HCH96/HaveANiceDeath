#pragma once
#include "singleton.h"

#include "CTexture.h"

class CConstBuffer;

class CDevice :
    public CSingleton<CDevice>
{
    SINGLE(CDevice);

private:
    HWND                            m_RenderWnd;
    Vec2                            m_RenderResolution;

	ComPtr<ID3D11Device>			m_Device;			// GPU 메모리 관리, 객체 생성
	ComPtr<ID3D11DeviceContext>		m_Context;			// GPU 렌더링 명령

	ComPtr<IDXGISwapChain>			m_SwapChain;		// SwapChain(출력 버퍼 지정)

	//OM(OutputMergeState)
	Ptr<CTexture>					m_RTTex;
	Ptr<CTexture>					m_DSTex;			// DepthSpencil Tex

	// ConstBuffer
	CConstBuffer*					m_arrCB[(UINT)CB_TYPE::END];

	// State
	ComPtr<ID3D11RasterizerState>	m_arrRS[(UINT)RS_TYPE::END];
	ComPtr<ID3D11DepthStencilState>	m_arrDS[(UINT)DS_TYPE::END];
	ComPtr<ID3D11BlendState>		m_arrBS[(UINT)BS_TYPE::END];

	ComPtr<ID3D11SamplerState>		m_arrSampler[2];

public:
	ID3D11Device* GetDevice() { return m_Device.Get(); }
	ID3D11DeviceContext* GetContext() { return m_Context.Get(); }
	Vec2 GetRenderResolution() { return m_RenderResolution; }

	CConstBuffer* GetConstBuffer(CB_TYPE _Type) { return m_arrCB[(UINT)_Type]; }

	ComPtr<ID3D11RasterizerState> GetRSState(RS_TYPE _Type) { return m_arrRS[(UINT)_Type]; }
	ComPtr<ID3D11DepthStencilState> GetDSState(DS_TYPE _Type) { return m_arrDS[(UINT)_Type]; }
	ComPtr<ID3D11BlendState> GetBSState(BS_TYPE _Type) { return m_arrBS[(UINT)_Type]; }

public:
	int init(HWND _hWnd, Vec2 _vResolution);
	void ClearRenderTarget(float(&Color)[4]);
	void Present();

	void SetRenderTarget();
	void ClearRenderTarget();
	void SetViewPort(Vec2 _Resolution);

private:
	int CreateSwapChain();
	int CreateTargetView();
	int CreateRasterizerState();
	int CreateDepthStencilState();
	int CreateBlendState();
	int CreateSamplerState();
	int CreateConstBuffer();
};

