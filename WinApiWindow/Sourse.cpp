#include <windows.h>
#include <stdio.h>
WCHAR szTest_1[100];
DWORD s = 65535;
DWORD* ml = &s;
DWORD* n_k = ml;
WCHAR szTest_2[100];
WCHAR szTest_3[100];
LRESULT CALLBACK WndProc(_In_ HWND hWnd, _In_ UINT message, _In_ WPARAM wParam, _In_ LPARAM lParam) {
	switch (message)
	{
		case WM_CREATE: {
			HWND hButton = CreateWindow(L"BUTTON", L"+", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 10, 50, 50, hWnd, (HMENU)2, NULL, NULL);
			break;
		}
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		case WM_PAINT: {
			swprintf(szTest_1, 100, L"Адрес указателя: %p", &ml);
			swprintf(szTest_2, 100, L"На этот адрес указывает: %p", n_k);
			swprintf(szTest_3, 100, L"Разыменование указателя: %d", *(DWORD*)n_k);
			PAINTSTRUCT ps;
			HDC hds = BeginPaint(hWnd, &ps);
			TextOut(hds, 100, 100, szTest_1, 100);
			TextOut(hds, 100, 120, szTest_2, 100);
			TextOut(hds, 100, 140, szTest_3, 100);
			EndPaint(hWnd, &ps);
			break;
		}
		case WM_COMMAND: {
			switch (LOWORD(wParam))
			{
				case 2: {
					s += 1;
					InvalidateRect(hWnd, NULL, TRUE);
				}
			}
			break;
		}
		default: {
			return DefWindowProc(hWnd, message, wParam, lParam);
			break;
		}		
	}
	return 0;
}
int CALLBACK WinMain(_In_ HINSTANCE hInstance,_In_opt_ HINSTANCE hPrevInstance,_In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
	WNDCLASSEX wc;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = L"MyAppClass";
	wc.hIconSm = LoadIcon(wc.hInstance, IDI_APPLICATION);
	if (!RegisterClassEx(&wc)) {
		return EXIT_FAILURE;
	}
	else {
		HWND hWnd = CreateWindowEx(WS_EX_TOPMOST,wc.lpszClassName,L"Byte++", WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,0,0,500,300,NULL,NULL,wc.hInstance,NULL);
		if (!hWnd) {
			return EXIT_FAILURE;
		}
		else {
			ShowWindow(hWnd, nCmdShow);
			UpdateWindow(hWnd);
			MSG msg;
			while (GetMessage(&msg,NULL,0,0)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			return (int)msg.wParam;
		}
	}
}
