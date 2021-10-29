// 您有一份礼物带签收.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "一个小惊喜.h"
#include <stdio.h>
#include <time.h>

#define MAX_LOADSTRING 100

#define WINDX		640
#define WINDY		420

#define MENU		31
#define CHEEK		8
#define BLANK		20

#define BUTTON1X	140
#define BUTTON1Y	280

#define BUTTON2X	380
#define BUTTON2Y	280

#define BUTTON3X	470
#define BUTTON3Y	300

#define BUTTONLONG	120
#define BUTTONWIDE	50

#define BITMAP1X	210
#define BITMAP1Y	80

#define BITMAP2X	210
#define BITMAP2Y	110

#define TEXT1X		130
#define TEXT1Y		20

#define TEXT2X		130
#define TEXT2Y		40

#define TEXTLONG	400
#define TEXTWIDE	140

#define BUTTON1	"同意"
#define BUTTON2	"不同意"
#define BUTTON3	"我是傻逼"

#define BITMAP1	IDB_BITMAP1
#define BITMAP2	IDB_BITMAP2

#define TEXT1	"我说你是傻逼，你敢同意吗？"
#define TEXT2	"看吧，我就知道你会同意的！"


// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名
DLGPROC OldButtonProc;
HWND CD1, CD2;


// 此代码模块中包含的函数的前向声明:
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: 在此处放置代码。

	// 初始化全局字符串
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_MY, szWindowClass, MAX_LOADSTRING);


	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOWFRAME);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	RegisterClassExW(&wcex);

	// 执行应用程序初始化:
	hInst = hInstance; // 将实例句柄存储在全局变量中

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, 
		CW_USEDEFAULT, 0, WINDX, WINDY, nullptr, nullptr, hInstance, nullptr);//WS_DLGFRAME

	if (!hWnd)
		return FALSE;


	ShowWindow(hWnd, SW_SHOW);
	InvalidateRect(hWnd, NULL, true);
	UpdateWindow(hWnd);

	MSG msg;

	// 主消息循环:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}


//
//  函数: ButtonProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理截获的控件消息。
//
INT_PTR CALLBACK ButtonProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_MOUSEMOVE:
	{
		//处理鼠标移动消息

		//移动窗口
		MoveWindow(hWnd, rand() % (WINDX - BLANK * 2 - BUTTONLONG - CHEEK) + BLANK, rand() % (WINDY - BLANK * 2 - BUTTONWIDE - MENU) + BLANK, BUTTONLONG, BUTTONWIDE, TRUE);
		InvalidateRect(hWnd, NULL, FALSE);
	}
	break;
	case WM_LBUTTONDOWN:
	{
		//处理点击消息
		RECT rect1, rect2, rectP;

		//获取控件位置
		GetWindowRect(CD1, &rect1);
		GetWindowRect(hWnd, &rect2);
		GetWindowRect(GetParent(hWnd), &rectP);

		//移动窗口
		MoveWindow(CD1, rect2.left - rectP.left - CHEEK, rect2.top - rectP.top - MENU, BUTTONLONG, BUTTONWIDE, TRUE);
		MoveWindow(hWnd, rect1.left - rectP.left - CHEEK, rect1.top - rectP.top - MENU, BUTTONLONG, BUTTONWIDE, TRUE);

		InvalidateRect(CD1, NULL, FALSE);
		InvalidateRect(hWnd, NULL, FALSE);
	}
	break;
	default:
		return OldButtonProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}


//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND BD1, BD2, TD1, TD2, CD3;
	static HBITMAP BIT1, BIT2;
	static HFONT Font1;
	static HBRUSH BR1;

	switch (message)
	{
	case WM_CREATE:
	{
		//初始化伪随机数
		srand((unsigned)time(NULL));

		//加载字体
		Font1 = CreateFont(27, 0, 0, 0, 100, FALSE, FALSE, 0,
			GB2312_CHARSET, OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
			DEFAULT_PITCH | FF_MODERN, TEXT("Arial"));

		//加载位图
		//BIT1 = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCEW(IDB_BITMAP1), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);
		BIT1 = LoadBitmap(hInst, MAKEINTRESOURCEW(BITMAP1));
		BIT2 = LoadBitmap(hInst, MAKEINTRESOURCEW(BITMAP2));

		//创建按钮
		CD1 = CreateWindowW(TEXT("Button"), TEXT(BUTTON1), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_FLAT,
			BUTTON1X, BUTTON1Y, BUTTONLONG, BUTTONWIDE, hWnd, NULL, hInst, NULL);
		CD2 = CreateWindowW(TEXT("Button"), TEXT(BUTTON2), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_FLAT,
			BUTTON2X, BUTTON2Y, BUTTONLONG, BUTTONWIDE, hWnd, NULL, hInst, NULL);
		CD3= CreateWindowW(TEXT("Button"), TEXT(BUTTON3), WS_CHILD | BS_PUSHBUTTON | BS_FLAT,
			BUTTON3X, BUTTON3Y, BUTTONLONG, BUTTONWIDE, hWnd, NULL, hInst, NULL);

		//创建静态位图控件
		BD1 = CreateWindowW(TEXT("static"), TEXT("#130"), WS_CHILD | WS_VISIBLE | SS_BITMAP,
			BITMAP1X, BITMAP1Y, 0, 0, hWnd, NULL, hInst, NULL);
		BD2 = CreateWindowW(TEXT("static"), TEXT("#132"), WS_CHILD | SS_BITMAP,
			BITMAP2X, BITMAP2Y, 0, 0, hWnd, NULL, hInst, NULL);

		//创建静态文本控件
		TD1 = CreateWindowW(TEXT("static"), TEXT(TEXT1), WS_CHILD | WS_VISIBLE | SS_LEFT | BS_OWNERDRAW,
			TEXT1X, TEXT1Y, TEXTLONG, TEXTWIDE, hWnd, NULL, hInst, NULL);
		TD2 = CreateWindowW(TEXT("static"), TEXT(TEXT2), WS_CHILD | SS_LEFT | BS_OWNERDRAW,
			TEXT2X, TEXT2Y, TEXTLONG, TEXTWIDE, hWnd, NULL, hInst, NULL);


		//创建画刷
		BR1 = CreateSolidBrush(RGB(0, 0, 0));


		//设置控件字体
		SendMessage(CD1, WM_SETFONT, (WPARAM)Font1, MAKELPARAM(TRUE, 0));
		SendMessage(CD2, WM_SETFONT, (WPARAM)Font1, MAKELPARAM(TRUE, 0));
		SendMessage(CD3, WM_SETFONT, (WPARAM)Font1, MAKELPARAM(TRUE, 0));
		SendMessage(TD1, WM_SETFONT, (WPARAM)Font1, MAKELPARAM(TRUE, 0));
		SendMessage(TD2, WM_SETFONT, (WPARAM)Font1, MAKELPARAM(TRUE, 0));

		//设置控件位图
		SendMessage(BD1, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BIT1);
		SendMessage(BD1, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BIT2);

		//更改控件回调函数
		OldButtonProc = (DLGPROC)SetWindowLong(CD2, GWL_WNDPROC, (LONG)&ButtonProc);
	}
	break;
	case WM_CTLCOLORSTATIC:
	{
		if ((HWND)lParam == TD1 || (HWND)lParam == TD2)
		{
			//SetBkColor((HDC)wParam, RGB(0, 0, 0));//背景颜色
			SetTextColor((HDC)wParam, RGB(255, 20, 20));//字体颜色
		}
		else
			goto defwindow;

		return(INT_PTR)BR1;
	}
	break;
	case WM_SYSCOMMAND:
		//阻止关闭
		if (wParam == SC_CLOSE)
		{
			MessageBoxW(hWnd, TEXT("还想关掉我？你想多了！"), TEXT("别关了，快同意吧"), MB_OK | MB_ICONSTOP);//MB_ICONWARNING
			return 0;
		}
		else
			goto defwindow;
		break;
	case WM_GETMINMAXINFO:
	{
		//限制窗体大小
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = WINDX;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = WINDY;
		((MINMAXINFO*)lParam)->ptMaxTrackSize.x = WINDX;
		((MINMAXINFO*)lParam)->ptMaxTrackSize.y = WINDY;
	}
	break;
	case WM_COMMAND:
	{
		//处理按键信息
		if ((HWND)lParam == CD1)
		{
			ShowWindow(CD1, SW_HIDE);
			ShowWindow(CD2, SW_HIDE);
			ShowWindow(BD1, SW_HIDE);
			ShowWindow(TD1, SW_HIDE);

			ShowWindow(CD3, SW_SHOW);
			ShowWindow(BD2, SW_SHOW);
			ShowWindow(TD2, SW_SHOW);
		}
		else if ((HWND)lParam == CD3)
			goto destroy;
		else
			goto defwindow;
	}
	break;
	case WM_PAINT:
	{
		//绘制客户区
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		//填充客户区
		RECT re = { 0,0,WINDX,WINDY };
		FillRect(hdc, &re, (HBRUSH)(COLOR_WINDOWFRAME));


		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
	destroy:
		CloseHandle(BD1);
		CloseHandle(BD2);
		CloseHandle(TD1);
		CloseHandle(TD2);
		CloseHandle(CD1);
		CloseHandle(CD2);
		CloseHandle(CD3);
		CloseHandle(BIT1);
		CloseHandle(BIT2);
		CloseHandle(Font1);
		CloseHandle(BR1);
		PostQuitMessage(0);
		break;
	default:
	defwindow:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}