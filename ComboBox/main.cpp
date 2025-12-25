#include <Windows.h>
#include <cstdio>
#include "resource.h"

CONST CHAR* g_sz_VALUES[] = { "This", "is", "my", "first","Combo","Box" };

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
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);
		
		HWND hCombo = GetDlgItem(hwnd, IDC_COMBO);
		for (int i = 0; i < sizeof(g_sz_VALUES) / sizeof(g_sz_VALUES[0]); i++)
		{
			SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)g_sz_VALUES[i]);
		}
	}
		break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDOK: 
		{
			//получаем ID ComboBox
			HWND hCombo = GetDlgItem(hwnd, IDC_COMBO);
			
			//объявляем переменную и записываем в нее номер выбранной строки
			int index = 0;
			index= SendMessage(hCombo, CB_GETCURSEL, 0, 0);
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			//переменная для итогового сообщения
			CHAR final_message[SIZE] = {};

			if (index!= CB_ERR)
			//получаем выбранную в ComboBox строку по индексу, если что-то выбрано
			//ВОПРОС!!! Можно ли без индекса? Тут без разницы, все равно нужно выводить его, а если индекс в остальном не нужен?
			//TODO Добавить if, если ничего не выбрано
			{ 			
			SendMessage(hCombo, CB_GETLBTEXT, index, (LPARAM)sz_buffer);
			//объединяем индекс и текст в 
			sprintf_s(final_message, SIZE, "Выбран пункт %d с текстом %s", (index+1), sz_buffer);
			}
			//если ничего не выбрано
			else
				sprintf_s(final_message, SIZE, "ComboBox пустой, ничего не выбрано", (index + 1), sz_buffer);

			//выводим конечное сообщение		
			MessageBox(hwnd, final_message, "User's choice", MB_OK | MB_ICONINFORMATION);
		}
			 break;
		case IDCANCEL: EndDialog(hwnd, 0); break;
		}
	}

		break;
	case WM_CLOSE:
		EndDialog(hwnd,0);
	}
	return FALSE;
}