#include <Windows.h>
#include "resource.h"



CONST CHAR* g_sz_VALUES[] = { "It's", "my", "first","List","Box","not","Combo","Box" };

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM Wparam, LPARAM LParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc, 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{	
		HWND hList = GetDlgItem(hwnd, IDC_LIST);
		for (int i = 0; i < sizeof(g_sz_VALUES) / sizeof(g_sz_VALUES[0]); i++)
		{
			SendMessage(hList, LB_INSERTSTRING, -1, (LPARAM)g_sz_VALUES[i]); //WpARAM -1 обозначает, что ставим в конец списка
		}
	}
	break;

	case WM_COMMAND:
		break;

	case WM_CLOSE:		
		EndDialog(hwnd, 0);
	}
	return FALSE;
}