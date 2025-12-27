#include <Windows.h>
#include "resource.h"
#include <cstdio>


CONST CHAR* g_sz_VALUES[] = { "It's", "my", "first","List","Box","not","Combo","Box" };
CHAR ADD[256] = {};
CHAR ADD_MOUSE[256] = {};
INT FLAG = 0;

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

BOOL CALLBACK DlgProc_1(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

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

	{
		if (HIWORD(wParam) == LBN_DBLCLK)
		{
			//вызываем Edit Control, как-то передаем туда выбранное значение из List Box
			//меняем значение, как-то передаем из Edit Control в ListBox

			HWND hList = GetDlgItem(hwnd, IDC_LIST);
			int index = 0;
			index = SendMessage(hList, LB_GETCURSEL, 0, 0);
			SendMessage(hList, LB_GETTEXT, index, (LPARAM)ADD_MOUSE);
			FLAG = 1;
			DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG2), NULL, DlgProc_1, 0);
			SendMessage(hList, LB_DELETESTRING, index, 0);
			SendMessage(hList, LB_INSERTSTRING, -1, (LPARAM)ADD_MOUSE);

			FLAG = 0;


		}

		switch (LOWORD(wParam))
		{
		case IDC_ADD:
		{
			HWND hList = GetDlgItem(hwnd, IDC_LIST);
			
			DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG2), NULL, DlgProc_1, 0);
			SendMessage(hList, LB_INSERTSTRING, -1, (LPARAM)ADD);
		}
		break;

		case IDC_DELETE:
		{
			HWND hList = GetDlgItem(hwnd, IDC_LIST);
			int index = 0;
			index = SendMessage(hList, LB_GETCURSEL, 0, 0);
			SendMessage(hList, LB_DELETESTRING, index,0);
		}
		break;
		{
		case IDOK:
				//получаем ID ListBox
				HWND hList = GetDlgItem(hwnd, IDC_LIST);
				int index = 0;
				index = SendMessage(hList, LB_GETCURSEL, 0, 0);
				CONST INT SIZE = 256;
				CHAR sz_buffer[SIZE] = {};
				//переменная для итогового сообщения
				CHAR final_message[SIZE] = {};
						
				SendMessage(hList, LB_GETTEXT, index, (LPARAM)sz_buffer);
					//объединяем индекс и текст в 
					sprintf_s(final_message, SIZE, "Выбран пункт %d с текстом %s", (index + 1), sz_buffer);
				
				//выводим конечное сообщение		
				MessageBox(hwnd, final_message, "User's choice", MB_OK | MB_ICONINFORMATION);
		}
		break;
	case IDCANCEL: EndDialog(hwnd, 0); break;
		}
	}

		break;

	case WM_CLOSE:		
		EndDialog(hwnd, 0);
	}
	return FALSE;
}

BOOL CALLBACK DlgProc_1(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		if (FLAG == 1)
		{
			HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
			SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)ADD_MOUSE);
		}
	}
		break;
	case WM_COMMAND:
	{

		
		switch (LOWORD(wParam))
		{
		
		case(IDOK2):
			{
			if (FLAG == 0)
			{
				HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
				SendMessage(hEdit, WM_GETTEXT, 256, (LPARAM)ADD);
				EndDialog(hwnd, 0);
			}
			if (FLAG==1)
			{
				HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
				SendMessage(hEdit, WM_GETTEXT, 256, (LPARAM)ADD_MOUSE);
				EndDialog(hwnd, 0);
			}
			}
			break;
		case IDCANCEL2: EndDialog(hwnd, 0); break;
		}
	}

		break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
	}
	
	return FALSE;
}