#undef UNICODE
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>

CONST CHAR g_sz_CLASS_NAME[] = "Main Window PV_522"; //имя класса окна

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)

{
	WNDCLASSEX wClass;
	ZeroMemory(&wClass, sizeof(wClass));
	wClass.style = NULL;
	wClass.cbSize = sizeof(wClass);
	wClass.cbClsExtra = 0;  //cb - Count Bytes
	wClass.cbWndExtra = 0;

	wClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wClass.hbrBackground = (HBRUSH)COLOR_WINDOW;

	wClass.hInstance;
	wClass.lpszMenuName = NULL; //главное меню (Файл, Edit...)
	wClass.lpszClassName = g_sz_CLASS_NAME;
	wClass.lpfnWndProc = WndProc;

	if (!RegisterClassEx(&wClass))
	{
		MessageBox(NULL, "Class registration failed", NULL, MB_OK | MB_ICONERROR);
		return 0;
	}

	INT screen_width = GetSystemMetrics(SM_CXSCREEN);  //получаем ширину экрана в пикселях
	INT screen_height = GetSystemMetrics(SM_CYSCREEN); //получаем высоту экрана в пикселях
	INT window_width = screen_width * 3 / 4;           //определяем размер окна:
	INT window_height = screen_height * 3 / 4;		   //нам надо 75% от размера экрана, значит берем размер экрана и от него 75%
	INT window_start_x = screen_width / 8;			   //определяем начальную точку расположения окна (в условии задачи по центру)
	INT window_start_y = screen_height / 8;			   //если окно 3/4 экрана, то 1/4 - отступы. Их два, сверху и снизу, а расположение - по центру, значит делим
													   //эти отсупы ровно пополам, половина снизу, половина сверху, то есть 1/8 часть на каждый отступ
	//теперь в CreateWindowEx вписываем рассчитанные параметры в начальную позицию окна и в размер окна (начальные я закомментирую, чтобы не удалять закомменитрованных)

	
	HWND hwnd = CreateWindowEx
	(
		NULL,             //exStyles
		g_sz_CLASS_NAME,  //className
		g_sz_CLASS_NAME,  //window title
		WS_OVERLAPPEDWINDOW,   //Стиль окна, набор стилей всегда зависит от класса окна. 
							   //Стиль главного окна всегда вот этот
		
		//CW_USEDEFAULT, CW_USEDEFAULT, //Начальная позиция окна (при запуске)
		window_start_x,window_start_y,
		//CW_USEDEFAULT, CW_USEDEFAULT, //Размер окна
		window_width,window_height,
		NULL,			//Parent Window
		NULL,			//hMenu. Для главного окна этот параметр определяет главное меню
		//Для дочернего окна (control) этот параметр содержить ID ресурса (RESOURCE_ID) дочергенр окна
		//Благодаря hMenu дочернее окно всегда можно найти при помощи функции GetDlgItem()
		hInstance,
		NULL
	);
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window creation failed", NULL, MB_OK | MB_ICONERROR);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);

	//запуск цикла сообщений

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
	{
		HWND hStatic = CreateWindowEx
		(
			NULL,										    //exStyle
			"Static",									    //Window class
			"Этот текст создан функцией CreateWindowEx()",  //Window text SendMessage (hwnd,WM_SETTEXT...)
			WS_CHILD|WS_VISIBLE,							//Window styles (дочернее окно)
			10,10,											//Position
			500,25,											//Size
			hwnd,											//Parant Window
			(HMENU)1000,									//ResourceID
			GetModuleHandle (NULL),							//hInstance
			NULL
		);
		HWND hEdit = CreateWindowEx
		(
			NULL,
			"Edit",
			"",
			WS_CHILD | WS_VISIBLE|WS_BORDER,
			10, 40,
			500, 22,
			hwnd,
			(HMENU)1001,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			NULL,
			"Button",
			"Применить",
			WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
			410,70,
			100,25,
			hwnd,
			(HMENU)1002,
			GetModuleHandle(NULL),
			NULL
		);
	}
		break;
	case WM_SIZE:					//для отображения размера окна в заголовке окна
	case WM_MOVE:					//для отображения координат окна в заголовке окна
	{
		//получаем координаты окна
		RECT rect;					//RECT это структура. Хранит в себе адрес левого верхнего и правого нижнего углов прямоугольника
		GetWindowRect(hwnd,&rect);  //из документации. ПЕРЕДАЕМ АДРЕС!! &rect, а не просто rect
		//"загоняем" информацию в заголовок окна
		CHAR sz_title[MAX_PATH] = {};
		sprintf
		(
			sz_title, "%s - Position: %ix%i, Size: %ix%i", 
			g_sz_CLASS_NAME, rect.left, rect.top,
			rect.right-rect.left, rect.bottom-rect.top
		);
		SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sz_title);
	}
		break;
	case WM_COMMAND:
	{
		switch(LOWORD(wParam))
	case 1002:
		{
			CHAR sz_buffer[MAX_PATH] = {};
			HWND hStatic = GetDlgItem(hwnd, 1000);
			HWND hEdit = GetDlgItem(hwnd, 1001);
			SendMessage(hEdit, WM_GETTEXT, MAX_PATH, (LPARAM)sz_buffer);
			SendMessage(hStatic, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}
		break;
	}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return FALSE;
}