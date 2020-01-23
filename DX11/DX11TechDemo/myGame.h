#pragma once
#include <d3d11.h>
#include <dxgi.h>
#include <d3dx11.h>
#include <windows.h>
#include <WindowsX.h>
//#include <dxerr.h>
#include "Camera.h"
#include <assert.h>
#include <DxErr.h>
#include <xnamath.h>
#include <math.h>
#include "text2D.h"
#include "objfilemodel.h"
#include "Model.h"
#include <array>
#include <MMSystem.h>
#include <dinput.h>



class myGame
{
	private:
	HWND m_Wnd;
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

public:
	#define _XM_NO_INTRINSICS_
	#define XM_NO_ALIGNMENT

	//////////////////////////////////////////////////////////////////////////////////////
	//	Global Variables
	//////////////////////////////////////////////////////////////////////////////////////
	HINSTANCE	g_hInst = NULL;
	HWND		g_hWnd = NULL;


	XMVECTOR g_directional_light_shines_from;
	XMVECTOR g_directional_light_colour;
	XMVECTOR g_ambient_light_colour;

	D3D_DRIVER_TYPE         g_driverType = D3D_DRIVER_TYPE_NULL;
	D3D_FEATURE_LEVEL       g_featureLevel = D3D_FEATURE_LEVEL_11_0;
	ID3D11DepthStencilView* g_pZBuffer;
	ID3D11Device* g_pD3DDevice = NULL;
	ID3D11DeviceContext* g_pImmediateContext = NULL;
	IDXGISwapChain* g_pSwapChain = NULL;
	ID3D11RenderTargetView* g_pBackBufferRTView = NULL;

	ID3D11Buffer* g_pVertexBuffer;
	ID3D11Buffer* g_pConstantBuffer0;
	ID3D11VertexShader* g_pVertexShader;
	ID3D11PixelShader* g_pPixelShader;
	ID3D11InputLayout* g_pInputLayout;
	ID3D11ShaderResourceView* g_pTexture0;
	ID3D11SamplerState* g_pSampler0;

	XMMATRIX projection, world, view;
	Text2D* g_2DText;
	Model* obj_Enemy;
	Model* obj_Player;
	Model* obj_Terrain;
	vector<Model*> obj_Collectable;
	vector<Model*> obj_jellyWall;

	Camera* myCamera;
	//Define vertex structure
	struct POS_COL_TEX_NORM_VERTEX//This will be added to and renamed in future tutorials
	{
		XMFLOAT3	pos;
		XMFLOAT4	Col;
		XMFLOAT2	Texture0;
		XMFLOAT3	Normal;
	};


	float g_clear_colour[4] = { 0.2f, 0.2f, 0.5f, 1.0f };

	// Rename for each tutorial – This will appear in the title bar of the window
	char		g_TutorialName[100] = "Pig in oblivion\0";

	//////////////////////////////////////////////////////////////////////////////////////
	//	Forward declarations
	//////////////////////////////////////////////////////////////////////////////////////
	HRESULT InitialiseWindow(HINSTANCE hInstance, int nCmdShow);
	HRESULT InitialiseD3D();
	HRESULT InitialiseGraphics(void);

	void RenderFrame(void);
	void ShutdownD3D();
	void updateSubResource();
	HRESULT inputManager();
	void ReadInputStates();
	bool IsKeyPressed(unsigned char DI_keycode);


	int xAxis = 0;
	int yAxis = 0;
	int zAxis = 0;
	int radians = 0;
	int degrees = 0;
	int patrolDistance = 40; // by default
	int amountOfBoxes = 32;
	int amountOfCoins = 32;

	int score;

	float terrainHeight = 8;
	float speed = 0.04f;
	float rotationSpeed = 0.15f;
	

	int mainFunction(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);


	IDirectInput8* g_direct_input;
	IDirectInputDevice8* g_keyboard_device;
	unsigned char g_keyboard_keys_state[256];
};