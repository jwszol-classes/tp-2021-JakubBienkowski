// DZWIG.cpp : Definiuje punkt wejścia dla aplikacji.
//

#include "framework.h"
#include "DZWIG.h"
#include <windows.h>

#define MAX_LOADSTRING 100
#define ID_PRZYCISK1 501
#define ID_PRZYCISK2 502
#define ID_PRZYCISK3 503
#define ID_PRZYCISK4 504
#define ID_PRZYCISK5 505
#define ID_PRZYCISK6 506


bool Podnies = false;
bool Opusc = false;
bool mozna = false;
bool lewo = false;
bool prawo = false;

int x = 0;
int b = 0;
int zas_poziom = 0;
int zas_pion = 0;


// Zmienne globalne:
HINSTANCE hInst;                                // bieżące wystąpienie
WCHAR szTitle[MAX_LOADSTRING];                  // Tekst paska tytułu
WCHAR szWindowClass[MAX_LOADSTRING];            // nazwa klasy okna głównego

// Przekaż dalej deklaracje funkcji dołączone w tym module kodu:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: W tym miejscu umieść kod.

    // Inicjuj ciągi globalne
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DZWIG, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Wykonaj inicjowanie aplikacji:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DZWIG));

    MSG msg;

    // Główna pętla komunikatów:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}



//
//  FUNKCJA: MyRegisterClass()
//
//  PRZEZNACZENIE: Rejestruje klasę okna.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DZWIG));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_DZWIG);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNKCJA: InitInstance(HINSTANCE, int)
//
//   PRZEZNACZENIE: Zapisuje dojście wystąpienia i tworzy okno główne
//
//   KOMENTARZE:
//
//        W tej funkcji dojście wystąpienia jest zapisywane w zmiennej globalnej i
//        jest tworzone i wyświetlane okno główne programu.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Przechowuj dojście wystąpienia w naszej zmiennej globalnej

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    HWND hButton1 = CreateWindowEx(WS_EX_CLIENTEDGE, L"BUTTON", L"Podnies towar", WS_CHILD | WS_VISIBLE |
        WS_BORDER, 950, 400, 150, 30, hWnd, (HMENU)ID_PRZYCISK1, hInstance, NULL),
        hButton2 = CreateWindowEx(WS_EX_CLIENTEDGE, L"BUTTON", L"Opusc towar", WS_CHILD | WS_VISIBLE |
            WS_BORDER, 1150, 400, 150, 30, hWnd, (HMENU)ID_PRZYCISK2, hInstance, NULL),
        hButton3 = CreateWindowEx(WS_EX_CLIENTEDGE, L"BUTTON", L"mniej niz 5 ton", WS_CHILD | WS_VISIBLE |
            WS_BORDER, 950, 300, 150, 30, hWnd, (HMENU)ID_PRZYCISK3, hInstance, NULL),
        hButton4 = CreateWindowEx(WS_EX_CLIENTEDGE, L"BUTTON", L"ponad 5 ton", WS_CHILD | WS_VISIBLE |
            WS_BORDER, 1150, 300, 150, 30, hWnd, (HMENU)ID_PRZYCISK4, hInstance, NULL),
        hButton5 = CreateWindowEx(WS_EX_CLIENTEDGE, L"BUTTON", L"przesun w lewo", WS_CHILD | WS_VISIBLE |
            WS_BORDER, 950, 500, 150, 30, hWnd, (HMENU)ID_PRZYCISK5, hInstance, NULL),
        hButton6 = CreateWindowEx(WS_EX_CLIENTEDGE, L"BUTTON", L"przesun w prawo", WS_CHILD | WS_VISIBLE |
            WS_BORDER, 1150, 500, 150, 30, hWnd, (HMENU)ID_PRZYCISK6, hInstance, NULL),
        hStatic = CreateWindowEx(0, L"STATIC", NULL, WS_CHILD | WS_VISIBLE |
            SS_CENTER, 1050, 250, 150, 20, hWnd, NULL, hInstance, NULL);
    SetWindowText(hStatic, L"Ile waży towar?");


    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

//
//  FUNKCJA: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PRZEZNACZENIE: Przetwarza komunikaty dla okna głównego.
//
//  WM_COMMAND  - przetwarzaj menu aplikacji
//  WM_PAINT    - Maluj okno główne
//  WM_DESTROY  - opublikuj komunikat o wyjściu i wróć
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Analizuj zaznaczenia menu:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        case ID_PRZYCISK1:
            if (mozna == true)
            {
                Podnies = true;
                Opusc = false;
                zas_pion = zas_pion + 10;
                if (zas_pion > 410)
                {
                    zas_pion = 410;
                }
            }
            InvalidateRect(hWnd, 0, TRUE);
            break;
        case ID_PRZYCISK2:
            if (mozna == true)
            {
                Opusc = true;
                Podnies = false;
                zas_pion = zas_pion - 10;
                if (zas_pion < 0)
                {
                    zas_pion = 0;
                }
            }
            InvalidateRect(hWnd, 0, TRUE);
            break;
        case ID_PRZYCISK3:
            mozna = true;
            InvalidateRect(hWnd, 0, TRUE);
            break;
        case ID_PRZYCISK4:
            mozna = false;
            InvalidateRect(hWnd, 0, TRUE);
            break;
        case ID_PRZYCISK5:
            if (mozna == true)
            {
                lewo = true;
                prawo = false;
                zas_poziom = zas_poziom + 10;
                if (zas_poziom > 180)
                {
                    zas_poziom = 180;
                }
            }
            InvalidateRect(hWnd, 0, TRUE);
            break;
        case ID_PRZYCISK6:
            if (mozna == true)
            {
                prawo = true;
                lewo = false;
                zas_poziom = zas_poziom - 10;
                if (zas_poziom < -350)
                {
                    zas_poziom = -350;
                }
            }
            InvalidateRect(hWnd, 0, TRUE);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: Tutaj dodaj kod rysujący używający elementu hdc...
        HPEN hPenOld;

        HPEN hLinePen;
        COLORREF qLineColor;
        qLineColor = RGB(255, 225, 0);
        hLinePen = CreatePen(PS_SOLID, 8, qLineColor);
        hPenOld = (HPEN)SelectObject(hdc, hLinePen);

        MoveToEx(hdc, 250, 70, NULL);
        LineTo(hdc, 250, 700);
        MoveToEx(hdc, 300, 40, NULL);
        LineTo(hdc, 300, 700);
        MoveToEx(hdc, 300, 40, NULL);
        LineTo(hdc, 250, 70);
        MoveToEx(hdc, 250, 700, NULL);
        LineTo(hdc, 300, 700);
        MoveToEx(hdc, 130, 135, NULL);
        LineTo(hdc, 1000, 135);
        MoveToEx(hdc, 130, 175, NULL);
        LineTo(hdc, 1030, 175);
        MoveToEx(hdc, 1000, 135, NULL);
        LineTo(hdc, 1030, 175);

        qLineColor = RGB(0, 0, 0);
        hLinePen = CreatePen(PS_SOLID, 8, qLineColor);
        hPenOld = (HPEN)SelectObject(hdc, hLinePen);
        MoveToEx(hdc, 100, 80, NULL);
        LineTo(hdc, 100, 220);
        MoveToEx(hdc, 70, 80, NULL);
        LineTo(hdc, 70, 220);
        MoveToEx(hdc, 130, 80, NULL);
        LineTo(hdc, 130, 220);
        MoveToEx(hdc, 40, 220, NULL);
        LineTo(hdc, 130, 220);
        MoveToEx(hdc, 40, 80, NULL);
        LineTo(hdc, 130, 80);
        MoveToEx(hdc, 40, 80, NULL);
        LineTo(hdc, 40, 220);
        MoveToEx(hdc, 140, 708, NULL);
        LineTo(hdc, 410, 708);
        MoveToEx(hdc, 140, 708, NULL);
        LineTo(hdc, 140, 750);
        MoveToEx(hdc, 410, 708, NULL);
        LineTo(hdc, 410, 750);
        MoveToEx(hdc, 140, 750, NULL);
        LineTo(hdc, 410, 750);
        MoveToEx(hdc, 410, 750, NULL);
        LineTo(hdc, 460, 800);
        MoveToEx(hdc, 140, 750, NULL);
        LineTo(hdc, 90, 800);
        MoveToEx(hdc, 200, 750, NULL);
        LineTo(hdc, 200, 540);
        MoveToEx(hdc, 350, 750, NULL);
        LineTo(hdc, 350, 540);
        MoveToEx(hdc, 200, 600, NULL);
        LineTo(hdc, 350, 600);
        MoveToEx(hdc, 200, 650, NULL);
        LineTo(hdc, 350, 650);
        MoveToEx(hdc, 200, 540, NULL);
        LineTo(hdc, 350, 540);


        qLineColor = RGB(0, 0, 0);
        hLinePen = CreatePen(PS_SOLID, 3, qLineColor);
        hPenOld = (HPEN)SelectObject(hdc, hLinePen);
        MoveToEx(hdc, 300, 34, NULL);
        LineTo(hdc, 130, 135);
        MoveToEx(hdc, 300, 34, NULL);
        LineTo(hdc, 995, 129);
        MoveToEx(hdc, 300, 34, NULL);
        LineTo(hdc, 670, 130);



        if (mozna == true && Podnies == false)
        {
            while (x >= zas_pion)
            {
                qLineColor = RGB(255, 255, 255);
                hLinePen = CreatePen(PS_SOLID, 6, qLineColor);
                hPenOld = (HPEN)SelectObject(hdc, hLinePen);
                Rectangle(hdc, 620 - zas_poziom, 599 - x, 720 - zas_poziom, 769 - x);


                qLineColor = RGB(0, 0, 0);
                hLinePen = CreatePen(PS_SOLID, 6, qLineColor);
                hPenOld = (HPEN)SelectObject(hdc, hLinePen);
                Rectangle(hdc, 620 - zas_poziom, 600 - x, 720 - zas_poziom, 770 - x);
                MoveToEx(hdc, 670 - zas_poziom, 600 - x, NULL);
                LineTo(hdc, 670 - zas_poziom, 179);
                MoveToEx(hdc, 622 - zas_poziom, 602 - x, NULL);
                LineTo(hdc, 718 - zas_poziom, 768 - x);
                MoveToEx(hdc, 622 - zas_poziom, 768 - x, NULL);
                LineTo(hdc, 718 - zas_poziom, 602 - x);
                x--;
                Sleep(1);
            }
        }

        if (mozna == true && Podnies == true)
        {
            while (x <= zas_pion)
            {
                qLineColor = RGB(255, 255, 255);
                hLinePen = CreatePen(PS_SOLID, 6, qLineColor);
                hPenOld = (HPEN)SelectObject(hdc, hLinePen);
                Rectangle(hdc, 620 - zas_poziom, 601 - x, 720 - zas_poziom, 771 - x);

                qLineColor = RGB(0, 0, 0);
                hLinePen = CreatePen(PS_SOLID, 6, qLineColor);
                hPenOld = (HPEN)SelectObject(hdc, hLinePen);
                Rectangle(hdc, 620 - zas_poziom, 600 - x, 720 - zas_poziom, 770 - x);
                MoveToEx(hdc, 670 - zas_poziom, 600 - x, NULL);
                LineTo(hdc, 670 - zas_poziom, 179);
                MoveToEx(hdc, 622 - zas_poziom, 602 - x, NULL);
                LineTo(hdc, 718 - zas_poziom, 768 - x);
                MoveToEx(hdc, 622 - zas_poziom, 768 - x, NULL);
                LineTo(hdc, 718 - zas_poziom, 602 - x);
                x++;
                Sleep(1);
            }
        }
        if (mozna == true && lewo == false)
        {
            while (b >= zas_poziom)
            {
                qLineColor = RGB(255, 255, 255);
                hLinePen = CreatePen(PS_SOLID, 6, qLineColor);
                hPenOld = (HPEN)SelectObject(hdc, hLinePen);
                Rectangle(hdc, 619 - b, 599 - zas_pion, 719 - b, 771 - zas_pion);
                MoveToEx(hdc, 669 - b, 600 - zas_pion, NULL);
                LineTo(hdc, 669 - b, 181);



                qLineColor = RGB(0, 0, 0);
                hLinePen = CreatePen(PS_SOLID, 6, qLineColor);
                hPenOld = (HPEN)SelectObject(hdc, hLinePen);
                Rectangle(hdc, 620 - b, 600 - zas_pion, 720 - b, 770 - zas_pion);
                MoveToEx(hdc, 670 - b, 600 - zas_pion, NULL);
                LineTo(hdc, 670 - b, 181);
                MoveToEx(hdc, 622 - b, 602 - zas_pion, NULL);
                LineTo(hdc, 718 - b, 768 - zas_pion);
                MoveToEx(hdc, 622 - b, 768 - zas_pion, NULL);
                LineTo(hdc, 718 - b, 602 - zas_pion);
                b--;
                Sleep(1);
            }
        }
        if (mozna == true && lewo == true)
        {
            while (b <= zas_poziom)
            {
                qLineColor = RGB(255, 255, 255);
                hLinePen = CreatePen(PS_SOLID, 6, qLineColor);
                hPenOld = (HPEN)SelectObject(hdc, hLinePen);
                Rectangle(hdc, 621 - b, 599 - zas_pion, 721 - b, 771 - zas_pion);
                MoveToEx(hdc, 671 - b, 600 - zas_pion, NULL);
                LineTo(hdc, 671 - b, 181);

                qLineColor = RGB(0, 0, 0);
                hLinePen = CreatePen(PS_SOLID, 6, qLineColor);
                hPenOld = (HPEN)SelectObject(hdc, hLinePen);
                Rectangle(hdc, 620 - b, 600 - zas_pion, 720 - b, 770 - zas_pion);
                MoveToEx(hdc, 670 - b, 600 - zas_pion, NULL);
                LineTo(hdc, 670 - b, 181);
                MoveToEx(hdc, 622 - b, 602 - zas_pion, NULL);
                LineTo(hdc, 718 - b, 768 - zas_pion);
                MoveToEx(hdc, 622 - b, 768 - zas_pion, NULL);
                LineTo(hdc, 718 - b, 602 - zas_pion);
                b++;
                Sleep(1);
            }
        }

        qLineColor = RGB(0, 0, 0);
        hLinePen = CreatePen(PS_SOLID, 6, qLineColor);
        hPenOld = (HPEN)SelectObject(hdc, hLinePen);
        Rectangle(hdc, 620 - zas_poziom, 600 - zas_pion, 720 - zas_poziom, 770 - zas_pion);
        MoveToEx(hdc, 670 - zas_poziom, 600 - zas_pion, NULL);
        LineTo(hdc, 670 - zas_poziom, 179);
        MoveToEx(hdc, 622 - zas_poziom, 602 - zas_pion, NULL);
        LineTo(hdc, 718 - zas_poziom, 768 - zas_pion);
        MoveToEx(hdc, 622 - zas_poziom, 768 - zas_pion, NULL);
        LineTo(hdc, 718 - zas_poziom, 602 - zas_pion);


        SelectObject(hdc, hPenOld);
        DeleteObject(hLinePen);



        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Procedura obsługi komunikatów dla okna informacji o programie.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}