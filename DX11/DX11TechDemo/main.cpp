#include "myGame.h"

#define _XM_NO_INTRINSICS_
#define XM_NO_ALIGNMENT

myGame newGame;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	newGame.mainFunction(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
}