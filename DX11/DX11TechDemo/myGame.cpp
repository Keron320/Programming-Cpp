#include "myGame.h"
//The #include order is important
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
#include <thread>
#include <dinput.h>
#include "myGame.h"

#define _XM_NO_INTRINSICS_
#define XM_NO_ALIGNMENT


HRESULT myGame::inputManager()
{
	HRESULT hr;
	ZeroMemory(g_keyboard_keys_state, sizeof(g_keyboard_keys_state));

	hr = DirectInput8Create(g_hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_direct_input, NULL);
	if (FAILED(hr))
		return hr;

	hr = g_direct_input->CreateDevice(GUID_SysKeyboard, &g_keyboard_device, NULL);
	if (FAILED(hr))
		return hr;

	hr = g_keyboard_device->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr))
		return hr;

	hr = g_keyboard_device->SetCooperativeLevel(g_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(hr))
		return hr;

	hr = g_keyboard_device->Acquire();
	if (FAILED(hr))
		return hr;

	return S_OK;
}

void myGame::ReadInputStates()
{
	HRESULT hr;
	hr = g_keyboard_device->GetDeviceState(sizeof(g_keyboard_keys_state), (LPVOID)&g_keyboard_keys_state);

	if (FAILED(hr))
	{
		if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
		{
			g_keyboard_device->Acquire();
		}
	}
}

bool myGame::IsKeyPressed(unsigned char DI_keycode)
{
	return g_keyboard_keys_state[DI_keycode] & 0x80;
}

int myGame::mainFunction(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
#if defined(DEBUG) | defined(DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);


	if (FAILED(InitialiseWindow(hInstance, nCmdShow)))
	{
		DXTRACE_MSG("Failed to create Window");
		return 0;
	}

	if (FAILED(InitialiseD3D()))
	{
		DXTRACE_MSG("Failed to create Device");
		return 0;
	}

	if (FAILED(InitialiseGraphics()))
	{
		DXTRACE_MSG("Failed to initalise graphics");
	}

	//	//Input stuff
	inputManager();

	// Main message loop
	MSG msg = { 0 };

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// do something
			RenderFrame();
		}
	}

	ShutdownD3D();

	return (int)msg.wParam;
}

HRESULT myGame::InitialiseWindow(HINSTANCE hInstance, int nCmdShow)
{
	// Give your app your own name
	char Name[100] = "Piggy in oblivion\0";

	// Register class
	WNDCLASSEX wcex = { 0 };
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.hInstance = hInstance;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	//wcex.hbrBackground = (HBRUSH )( COLOR_WINDOW + 1); // Needed for non-D3D apps
	wcex.lpszClassName = Name;

	if (!RegisterClassEx(&wcex)) return E_FAIL;

	// Create window
	g_hInst = hInstance;
	RECT rc = { 0, 0, 1024, 800 }; // change window size here

	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	g_hWnd = CreateWindow(Name, g_TutorialName, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left,
		rc.bottom - rc.top, NULL, NULL, hInstance, NULL);
	if (!g_hWnd)
		return E_FAIL;

	ShowWindow(g_hWnd, nCmdShow);

	return S_OK;
}

void playMusic()
{
	//PlaySound(TEXT("kenjoy.wav"), NULL, SND_FILENAME | SND_ASYNC);
	PlaySound(TEXT("kentris.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
	// http://advsys.net/ken/ Sound copyright: Ken Silverman
}

//////////////////////////////////////////////////////////////////////////////////////
// Called every time the application receives a message
//////////////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK myGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	///////////////////////////////////////////////////////////////////////////////////////////
	// https://stackoverflow.com/questions/21369256/how-to-use-wndproc-as-a-class-function/////
	///////////////////////////////////////////////////////////////////////////////////////////
	myGame* pThis;

	if (message == WM_NCCREATE)
	{
		pThis = static_cast<myGame*>(reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams);

		SetLastError(0);
		if (!SetWindowLongPtr(hWnd, GWL_USERDATA, reinterpret_cast<LONG_PTR>(pThis)))
		{
			if (GetLastError() != 0)
				return FALSE;
		}
	}
	else
	{
		pThis = reinterpret_cast<myGame*>(GetWindowLongPtr(hWnd, GWL_USERDATA));
	}

	if (pThis)
	{
		// use pThis->member as needed...
	}

	PAINTSTRUCT ps;
	HDC hdc;


	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

		return 0;


	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

//////////////////////////////////////////////////////////////////////////////////////
// Create D3D device and swap chain
//////////////////////////////////////////////////////////////////////////////////////
HRESULT myGame::InitialiseD3D()
{
	HRESULT hr = S_OK;

	RECT rc;
	GetClientRect(g_hWnd, &rc);
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;

	UINT createDeviceFlags = 0;

#if defined(DEBUG) || defined(_DEBUG) 
#endif

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE, // comment out this line if you need to test D3D 11.0 functionality on hardware that doesn't support it
		D3D_DRIVER_TYPE_WARP, // comment this out also to use reference device
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = g_hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = true;

	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
	{
		g_driverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDeviceAndSwapChain(NULL, g_driverType, NULL,
			createDeviceFlags, featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION, &sd, &g_pSwapChain,
			&g_pD3DDevice, &g_featureLevel, &g_pImmediateContext);
		if (SUCCEEDED(hr))
			break;
	}

	if (FAILED(hr))
	{
		MessageBox(0, "D3D11CreateDevice Failed", 0, 0);
		DXTrace(__FILE__, (DWORD)__LINE__, hr, "DX11CREATEDEVICE", true);
		return hr;
	}

	// Get pointer to back buffer texture
	ID3D11Texture2D* pBackBufferTexture;
	hr = g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D),
		(LPVOID*)&pBackBufferTexture);

	if (FAILED(hr)) return hr;

	// Use the back buffer texture pointer to create the render target view
	hr = g_pD3DDevice->CreateRenderTargetView(pBackBufferTexture, NULL,
		&g_pBackBufferRTView);
	pBackBufferTexture->Release();

	if (FAILED(hr)) return hr;

	//Create Z buffer texture
	D3D11_TEXTURE2D_DESC tex2dDesc;
	ZeroMemory(&tex2dDesc, sizeof(tex2dDesc));

	tex2dDesc.Width = width;
	tex2dDesc.Height = height;
	tex2dDesc.ArraySize = 1;
	tex2dDesc.MipLevels = 1;
	tex2dDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	tex2dDesc.SampleDesc.Count = sd.SampleDesc.Count;
	tex2dDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	tex2dDesc.Usage = D3D11_USAGE_DEFAULT;

	ID3D11Texture2D* pZBufferTexture;
	hr = g_pD3DDevice->CreateTexture2D(&tex2dDesc, NULL, &pZBufferTexture);

	if (FAILED(hr)) return hr;

	//Create the Z buffer
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
	ZeroMemory(&dsvDesc, sizeof(dsvDesc));

	dsvDesc.Format = tex2dDesc.Format;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

	g_pD3DDevice->CreateDepthStencilView(pZBufferTexture, &dsvDesc, &g_pZBuffer);
	pZBufferTexture->Release();

	// Set the render target view
	g_pImmediateContext->OMSetRenderTargets(1, &g_pBackBufferRTView, g_pZBuffer);

	// Set the viewport
	D3D11_VIEWPORT viewport;

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = (FLOAT)width;
	viewport.Height = (FLOAT)height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	g_pImmediateContext->RSSetViewports(1, &viewport);
	g_2DText = new Text2D(("assets/font1.bmp"), g_pD3DDevice, g_pImmediateContext);


	//Play music only once
	std::thread thread_object(playMusic);
	thread_object.join();

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////////////
// Clean up D3D objects
//////////////////////////////////////////////////////////////////////////////////////
void myGame::ShutdownD3D()
{
	if (g_pVertexBuffer) g_pVertexBuffer->Release();
	if (g_pInputLayout) g_pInputLayout->Release();
	if (g_pVertexShader) g_pVertexShader->Release();
	if (g_pPixelShader) g_pPixelShader->Release();


	if (g_pSwapChain) g_pSwapChain->Release();
	if (g_pTexture0) g_pTexture0->Release();
	if (g_pSampler0) g_pTexture0->Release();

	if (g_pImmediateContext) g_pImmediateContext->Release();
	if (g_pD3DDevice) g_pD3DDevice->Release();
	if (g_pBackBufferRTView) g_pBackBufferRTView->Release();

	if (g_keyboard_device)
	{
		g_keyboard_device->Unacquire();
		g_keyboard_device->Release();
	}
	if (g_direct_input) g_direct_input->Release();

	delete g_2DText;
	g_2DText = nullptr;
	delete myCamera;
	myCamera = nullptr;
	delete obj_Enemy;
	obj_Enemy = nullptr;
	delete obj_Player;
	obj_Player = nullptr;
	delete obj_Terrain;
	obj_Terrain = nullptr;
	//delete obj_Collectable;
	//obj_Collectable = nullptr;

	//// clean up causes errors when exiting the application for some reason
	// I tried different methods to do so

	//for (int i = 0; i < obj_jellyWall.size(); i++)
	//{ 
	//delete obj_jellyWall[0];
	////obj_jellyWall[i] = nullptr;
	//}

	//for (auto model : obj_jellyWall)
	//{
	//	delete model;
	//}
	//obj_jellyWall.clear();

	//for (Model* obj : obj_jellyWall)
	//	delete obj;
	//obj_jellyWall.clear();
}
HRESULT myGame::InitialiseGraphics()
{
	HRESULT hr = S_OK;

	myCamera = new Camera(0.0f, 10.0f, -50.0f, 0.0f);

	char filename[] = "assets/Sphere.obj";

	obj_Enemy = new Model(g_pD3DDevice, g_pImmediateContext);
	obj_Player = new Model(g_pD3DDevice, g_pImmediateContext);
	obj_Terrain = new Model(g_pD3DDevice, g_pImmediateContext);
	//obj_Collectable = new Model(g_pD3DDevice, g_pImmediateContext);

	for (int i = 0; i < amountOfBoxes; i++)
		obj_jellyWall.push_back(new Model(g_pD3DDevice, g_pImmediateContext));

	for (int i = 0; i < amountOfBoxes; i++)
		obj_Collectable.push_back(new Model(g_pD3DDevice, g_pImmediateContext));

	D3DX11CreateShaderResourceViewFromFile(g_pD3DDevice, "assets/texture.bmp", NULL, NULL, &g_pTexture0, NULL);


	if (FAILED(obj_Enemy->LoadObjModel((char*)"assets/Sphere.obj", (char*)"assets/eyeball.bmp")))
	{
		MessageBox(g_hWnd, "Graphics Initialisation failed", NULL, MB_OK);
		return hr;
	}


	if (FAILED(obj_Player->LoadObjModel((char*)"assets/piggy.obj", (char*)"assets/texture_pinky.bmp")))
	{
		MessageBox(g_hWnd, "Graphics Initialisation failed", NULL, MB_OK);
		return hr;
	}

	for (int i = 0; i < obj_jellyWall.size(); i++)
	{
		if (FAILED(obj_jellyWall[i]->LoadObjModel((char*)"assets/cube.obj", (char*)"assets/texture_jelly.bmp")))
		{
			MessageBox(g_hWnd, "Graphics Initialisation failed", NULL, MB_OK);
			return hr;
		}
	}

	if (FAILED(obj_Terrain->LoadObjModel((char*)"assets/terrain.obj", (char*)"assets/texture_rc.bmp")))
	{
		MessageBox(g_hWnd, "Graphics Initialisation failed", NULL, MB_OK);
		return hr;
	}
	//Set position once TODO: Function for it
	obj_Enemy->setPos(obj_Enemy->m_x, terrainHeight, obj_Enemy->m_z);

	for (int i = 0; i < obj_Collectable.size(); i++)
	{
		if (FAILED(obj_Collectable[i]->LoadObjModel((char*)"assets/coin.obj", (char*)"assets/texture_coin.bmp")))
		{
			MessageBox(g_hWnd, "Graphics Initialisation failed", NULL, MB_OK);
			return hr;
		}
	}


	for (int i = 0; i < 4; i++)
	{
		int distanceMultiplier = 4;

		for (int j = 0; j < 4; j++)
		{
			obj_Collectable[i]->setPos((-8 * i) * distanceMultiplier, terrainHeight, j * distanceMultiplier);
			obj_Collectable[i]->Draw(&view, &projection);
		}
	}

	return S_OK;
}

// Render frame
void myGame::RenderFrame(void)
{
	XMMATRIX myMatrix = myCamera->GetViewMatrix();

	//Keyboard
	ReadInputStates();

	if (IsKeyPressed(DIK_ESCAPE))
		DestroyWindow(g_hWnd);


	if (IsKeyPressed(DIK_LSHIFT))
	{
		speed = 0.8;
		rotationSpeed = 0.25f;
	}

	if (IsKeyPressed(DIK_F))
	{
		speed = 0.04f;
		rotationSpeed = 0.15f;
	}

	if (IsKeyPressed(DIK_RSHIFT))
	{
		speed = 0.24;
		rotationSpeed = 0.55f;
	}

	if (IsKeyPressed(DIK_NUMPAD4))
		radians += speed;
	if (IsKeyPressed(DIK_NUMPAD6))
		degrees += speed;
	if (IsKeyPressed(DIK_NUMPAD8))
		zAxis += speed;
	if (IsKeyPressed(DIK_NUMPAD2))
		zAxis -= speed;
	if (IsKeyPressed(DIK_HOME))
		yAxis -= speed;
	if (IsKeyPressed(DIK_END))
		yAxis += speed;
	if (IsKeyPressed(DIK_INSERT))
		xAxis -= speed;
	if (IsKeyPressed(DIK_DELETE))
		xAxis += speed;
	// camera move
	if (IsKeyPressed(DIK_UP) || IsKeyPressed(DIK_W))
		myCamera->Forward(speed);
	if (IsKeyPressed(DIK_DOWN) || IsKeyPressed(DIK_S))
		myCamera->Forward(-speed);
	if (IsKeyPressed(DIK_RIGHT) || IsKeyPressed(DIK_D))
	{
		myCamera->Rotate(rotationSpeed);
		obj_Player->setRotation(rotationSpeed);
	}
	if (IsKeyPressed(DIK_LEFT) || IsKeyPressed(DIK_A))
	{
		myCamera->Rotate(-rotationSpeed);
		obj_Player->setRotation(-rotationSpeed);
	}
	if (IsKeyPressed(DIK_E))
		myCamera->Strife(speed);
	if (IsKeyPressed(DIK_Q))
		myCamera->Strife(-speed);
	if (IsKeyPressed(DIK_SPACE))
		myCamera->MoveUpDown(speed);
	if (IsKeyPressed(DIK_C))
		myCamera->MoveUpDown(-speed);
	if (IsKeyPressed(DIK_NUMPAD8))
		myCamera->Pitch(speed);
	if (IsKeyPressed(DIK_NUMPAD2))
		myCamera->Pitch(-speed);

	//updateSubResource();
	g_directional_light_shines_from = XMVectorSet(0.0f, 1.0f, -1.0f, 0.0f);
	g_directional_light_colour = XMVectorSet(0.4f, 0.2f, 0.1f, 0.0f);
	g_ambient_light_colour = XMVectorSet(0.1f, 0.1f, 0.1f, 1.0f);//dark grey - always use a small value for ambient lighting

	// Clear the back buffer - choose a colour you like
	g_pImmediateContext->ClearRenderTargetView(g_pBackBufferRTView, g_clear_colour);
	g_pImmediateContext->ClearDepthStencilView(g_pZBuffer, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	projection = XMMatrixPerspectiveFovLH(XMConvertToRadians(45.0), 640.0 / 480.0, 1.0, 100.0);
	//CONSTANT_BUFFER0 cb0_values;
	view = myCamera->GetViewMatrix();

	//Set vertex buffer 
	UINT stride = sizeof(POS_COL_TEX_NORM_VERTEX);
	UINT offset = 0;
	g_pImmediateContext->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);

	obj_Enemy->patrol(patrolDistance);

	obj_Enemy->Draw(&view, &projection);

	obj_Terrain->setPos(0, -4, 0);

	obj_Terrain->Draw(&view, &projection);
	

	obj_Player->setPos(myCamera->m_x - 1, myCamera->m_y - 2.5, myCamera->m_z + 15);

	string scoreString = std::to_string(score);
	string hud_Message = "Score:" + scoreString;

	obj_Player->CheckCollision(obj_Enemy);
	if (obj_Player->CheckCollision(obj_Enemy) == true)
	{
		hud_Message = "Ow";

	}

	//If player position is less than -10 in y axis
	if (obj_Player->m_y < -10)
	{
		hud_Message = "Falling";
	}

	obj_Player->Draw(&view, &projection);

	// Loops through all the wall and coin objects to detect collision, set position and draw
	for (int i = 0; i < 4; i++)
	{
		int distanceMultiplier = 32;
		for (int j = 0; j < 4; j++)
		{
			obj_jellyWall[i]->setPos((-1 * i) * distanceMultiplier, terrainHeight, j * distanceMultiplier);

			if (obj_Player->CheckCollision(obj_jellyWall[i]) == true)
			{
				hud_Message = "Ew, jelly";
				speed = 0.01f;
				rotationSpeed = 0.05f;
			}
			obj_jellyWall[i]->Draw(&view, &projection);
		}
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (obj_Player->CheckCollision(obj_Collectable[i]) == true)
			{
				score += 1;
				obj_Collectable[i]->setPos(999, 999, 999); // bad solution on how to dissapear a coin
			}
			obj_Collectable[i]->Draw(&view, &projection);
		}

	}
	
	bool falling = true;
	obj_Player->CheckCollision(obj_Terrain);
	if (obj_Player->CheckCollision(obj_Terrain) == true)
	{
		falling = false;
	}

	if (falling == true)
		myCamera->MoveUpDown(-0.05);

	g_2DText->RenderText();
	// Display what has just been rendered
	g_pSwapChain->Present(0, 0);

	//if (g_pD3DDevice) g_pD3DDevice->Release();
	//if (g_pConstantBuffer0) g_pConstantBuffer0->Release();
	g_2DText->AddText(hud_Message, -1.0f, +1.0f, 0.2f);
}

//Const buffer structs. Pack to 16 bytes. Don't let any single element cross 16 byte boundarie
struct CONSTANT_BUFFER0
{
	XMMATRIX WorldViewProjection;	//	64 bytes
	XMVECTOR directional_light_vector;//  16 bytes
	XMVECTOR directional_light_colour;//  16 bytes
	XMVECTOR ambient_light_colour;	//  16 bytes
	float RedAmount;				//	4 bytes
	float Scale;					//	4 bytes
	XMFLOAT2 packing;				//	8 bytes
};

void myGame::updateSubResource()
{
	XMMATRIX transpose;
	float redValue = 1.0f;
	float scaleValue = 1.0f;

	CONSTANT_BUFFER0 cb0_values;

	cb0_values.RedAmount = redValue;
	cb0_values.Scale = scaleValue;

	world = XMMatrixTranslation(xAxis, yAxis, zAxis);
	world *= XMMatrixRotationY(XMConvertToRadians(radians));
	world *= XMMatrixRotationZ(XMConvertToDegrees(degrees));

	transpose = XMMatrixTranspose(world); // model world matrix
	cb0_values.directional_light_colour = g_directional_light_colour;
	cb0_values.ambient_light_colour = g_ambient_light_colour;
	cb0_values.directional_light_vector = XMVector3Transform(g_directional_light_shines_from, transpose);
	cb0_values.directional_light_vector = XMVector3Normalize(cb0_values.directional_light_vector);

	projection = XMMatrixPerspectiveFovLH(XMConvertToRadians(45.0), 640.0 / 480.0, 1.0, 100.0);
	view = myCamera->GetViewMatrix();
	cb0_values.WorldViewProjection = world * view * projection;

	g_pImmediateContext->UpdateSubresource(g_pConstantBuffer0, 0, 0, &cb0_values, 0, 0);
}
