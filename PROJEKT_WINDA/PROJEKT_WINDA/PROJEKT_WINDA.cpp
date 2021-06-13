

// WINDA_PROJEKT.cpp : Definiuje punkt wejœcia dla aplikacji.
//

#include "framework.h"
#include "PROJEKT_WINDA.h"
#include <vector>
#include <stdlib.h>
#define MAX_LOADSTRING 100

#define ID_PRZYCISK1 501
#define ID_PRZYCISK2 502
#define ID_PRZYCISK3 503
#define ID_PRZYCISK4 504
#define ID_PRZYCISK5 505
#define ID_PRZYCISK6 506
#define ID_PRZYCISK7 507
#define ID_PRZYCISK8 508
#define ID_PRZYCISK9 509
#define ID_PRZYCISK10 510
#define ID_PRZYCISK11 511
#define ID_PRZYCISK12 512
#define ID_PRZYCISK13 513
#define ID_PRZYCISK14 514
#define ID_PRZYCISK15 515
#define ID_PRZYCISK16 516
#define ID_PRZYCISK17 517
#define ID_PRZYCISK18 518
#define ID_PRZYCISK19 519
#define ID_PRZYCISK20 520
#define ID_PRZYCISK21 521

using namespace std;

bool start = false;
bool wysiada = false;
bool wsiada = false;

bool w_dol = true;
bool w_gore = false;

bool pietro_pierwsze = true;
bool pietro_drugie = false;
bool pietro_trzecie = false;
bool pietro_czwarte = false;
bool pietro_piate = false;

int polozenie = 0;
int wysokosc, szerokosc;

vector < int > winda, wchodza, wychodza;
vector < int > do_odwiedzenia;
vector < int > pietro_pie;
vector < int > pietro_dru;
vector < int > pietro_trze;
vector < int > pietro_czwa;
vector < int > pietro_pia;

void rysuj_wage(HDC hdc, HWND hWnd, vector<int>winda);
void rysuj_blok_czyszczacy_prawa(int wysokosc, int szerokosc, HWND hWnd, HDC hdc, HPEN hPenOld, HPEN hLinePen, COLORREF qLineColor);
void rysuj_blok_czyszczacy_lewa(int wysokosc, int szerokosc, HWND hWnd, HDC hdc, HPEN hPenOld, HPEN hLinePen, COLORREF qLineColor);
void rysuj_blok_czyszczacy_winda(int& polozenie, HWND hWnd, HDC hdc, HPEN hPenOld, HPEN hLinePen, COLORREF qLineColor);
void rysuj_pietro_prawa(vector<int> pietro, int wysokosc, int szerokosc, HWND hWnd, HDC hdc, HPEN hPenOld, HPEN hLinePen, COLORREF qLineColor);
void rysuj_pietro_lewa(vector<int> pietro, int wysokosc, int szerokosc, HWND hWnd, HDC hdc, HPEN hPenOld, HPEN hLinePen, COLORREF qLineColor);
void rysuj_winda(vector<int> winda, int& polozenie, int wysokosc, int szerokosc, HWND hWnd, HDC hdc, HPEN hPenOld, HPEN hLinePen, COLORREF qLineColor);
void wjazd_windy(int wysokosc, int szerokosc, vector<int> winda, int& polozenie, HWND hWnd, HDC hdc, HPEN hPenOld, HPEN hLinePen, COLORREF qLineColor);
void zjazd_windy(int wysokosc, int szerokosc, vector<int> winda, int& polozenie, HWND hWnd, HDC hdc, HPEN hPenOld, HPEN hLinePen, COLORREF qLineColor);
void zamykanie_drzwi_prawa(int wysokosc, int szerokosc, HWND hWnd, HDC hdc, HPEN hPenOld, HPEN hLinePen, COLORREF qLineColor);
void otwieranie_drzwi_prawa(int wysokosc, int szerokosc, HWND hWnd, HDC hdc, HPEN hPenOld, HPEN hLinePen, COLORREF qLineColor);
void otwieranie_drzwi_lewa(int wysokosc, int szerokosc, HWND hWnd, HDC hdc, HPEN hPenOld, HPEN hLinePen, COLORREF qLineColor);
void zamykanie_drzwi_lewa(int wysokosc, int szerokosc, HWND hWnd, HDC hdc, HPEN hPenOld, HPEN hLinePen, COLORREF qLineColor);
//void wchodzenie_do_windy_prawa(vector<int> wchodza, vector<int> pietro, int wysokosc, int szerokosc, int& z, HWND hWnd, HDC hdc, HPEN hPenOld, HPEN hLinePen, COLORREF qLineColor);
//void wychodzenie_z_windy_lewa(vector<int> winda, vector<int> pietro, int wysokosc, int& x, int szerokosc, int& polozenie, HWND hWnd, HDC hdc, HPEN hPenOld, HPEN hLinePen, COLORREF qLineColor);



// Zmienne globalne:
HINSTANCE hInst;                                // bie¿¹ce wyst¹pienie
WCHAR szTitle[MAX_LOADSTRING];                  // Tekst paska tytu³u
WCHAR szWindowClass[MAX_LOADSTRING];            // nazwa klasy okna g³ównego

// Przeka¿ dalej deklaracje funkcji do³¹czone w tym module kodu:
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

    // TODO: W tym miejscu umieœæ kod.


    // Inicjuj ci¹gi globalne
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PROJEKTWINDA, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Wykonaj inicjowanie aplikacji:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PROJEKTWINDA));

    MSG msg;

    // G³ówna pêtla komunikatów:
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
//  PRZEZNACZENIE: Rejestruje klasê okna.
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
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDC_PROJEKTWINDA));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_PROJEKTWINDA);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNKCJA: InitInstance(HINSTANCE, int)
//
//   PRZEZNACZENIE: Zapisuje dojœcie wyst¹pienia i tworzy okno g³ówne
//
//   KOMENTARZE:
//
//        W tej funkcji dojœcie wyst¹pienia jest zapisywane w zmiennej globalnej i
//        jest tworzone i wyœwietlane okno g³ówne programu.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Przechowuj dojœcie wyst¹pienia w naszej zmiennej globalnej

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    HWND hButton1 = CreateWindowEx(WS_EX_CLIENTEDGE, L"BUTTON", L"2", WS_CHILD | WS_VISIBLE |
        WS_BORDER, 800, 515, 30, 30, hWnd, (HMENU)ID_PRZYCISK1, hInstance, NULL),
        hButton2 = CreateWindowEx(WS_EX_CLIENTEDGE, L"BUTTON", L"3", WS_CHILD | WS_VISIBLE |
            WS_BORDER, 840, 515, 30, 30, hWnd, (HMENU)ID_PRZYCISK2, hInstance, NULL),
        hButton3 = CreateWindowEx(WS_EX_CLIENTEDGE, L"BUTTON", L"4", WS_CHILD | WS_VISIBLE |
            WS_BORDER, 800, 555, 30, 30, hWnd, (HMENU)ID_PRZYCISK3, hInstance, NULL),
        hButton4 = CreateWindowEx(WS_EX_CLIENTEDGE, L"BUTTON", L"5", WS_CHILD | WS_VISIBLE |
            WS_BORDER, 840, 555, 30, 30, hWnd, (HMENU)ID_PRZYCISK4, hInstance, NULL),

        hButton5 = CreateWindowEx(WS_EX_CLIENTEDGE, L"BUTTON", L"1", WS_CHILD | WS_VISIBLE |
            WS_BORDER, 30, 400, 30, 30, hWnd, (HMENU)ID_PRZYCISK5, hInstance, NULL),
        hButton6 = CreateWindowEx(WS_EX_CLIENTEDGE, L"BUTTON", L"3", WS_CHILD | WS_VISIBLE |
            WS_BORDER, 70, 400, 30, 30, hWnd, (HMENU)ID_PRZYCISK6, hInstance, NULL),
        hButton7 = CreateWindowEx(WS_EX_CLIENTEDGE, L"BUTTON", L"4", WS_CHILD | WS_VISIBLE |
            WS_BORDER, 30, 440, 30, 30, hWnd, (HMENU)ID_PRZYCISK7, hInstance, NULL),
        hButton8 = CreateWindowEx(WS_EX_CLIENTEDGE, L"BUTTON", L"5", WS_CHILD | WS_VISIBLE |
            WS_BORDER, 70, 440, 30, 30, hWnd, (HMENU)ID_PRZYCISK8, hInstance, NULL),

        hButton9 = CreateWindowEx(WS_EX_CLIENTEDGE, L"BUTTON", L"1", WS_CHILD | WS_VISIBLE |
            WS_BORDER, 800, 290, 30, 30, hWnd, (HMENU)ID_PRZYCISK9, hInstance, NULL),
        hButton10 = CreateWindowEx(WS_EX_CLIENTEDGE, L"BUTTON", L"2", WS_CHILD | WS_VISIBLE |
            WS_BORDER, 840, 290, 30, 30, hWnd, (HMENU)ID_PRZYCISK10, hInstance, NULL),
        hButton11 = CreateWindowEx(WS_EX_CLIENTEDGE, L"BUTTON", L"4", WS_CHILD | WS_VISIBLE |
            WS_BORDER, 800, 330, 30, 30, hWnd, (HMENU)ID_PRZYCISK11, hInstance, NULL),
        hButton12 = CreateWindowEx(WS_EX_CLIENTEDGE, L"BUTTON", L"5", WS_CHILD | WS_VISIBLE |
            WS_BORDER, 840, 330, 30, 30, hWnd, (HMENU)ID_PRZYCISK12, hInstance, NULL),

        hButton13 = CreateWindowEx(WS_EX_CLIENTEDGE, L"BUTTON", L"1", WS_CHILD | WS_VISIBLE |
            WS_BORDER, 30, 170, 30, 30, hWnd, (HMENU)ID_PRZYCISK13, hInstance, NULL),
        hButton14 = CreateWindowEx(WS_EX_CLIENTEDGE, L"BUTTON", L"2", WS_CHILD | WS_VISIBLE |
            WS_BORDER, 70, 170, 30, 30, hWnd, (HMENU)ID_PRZYCISK14, hInstance, NULL),
        hButton15 = CreateWindowEx(WS_EX_CLIENTEDGE, L"BUTTON", L"3", WS_CHILD | WS_VISIBLE |
            WS_BORDER, 30, 210, 30, 30, hWnd, (HMENU)ID_PRZYCISK15, hInstance, NULL),
        hButton16 = CreateWindowEx(WS_EX_CLIENTEDGE, L"BUTTON", L"5", WS_CHILD | WS_VISIBLE |
            WS_BORDER, 70, 210, 30, 30, hWnd, (HMENU)ID_PRZYCISK16, hInstance, NULL),

        hButton17 = CreateWindowEx(WS_EX_CLIENTEDGE, L"BUTTON", L"1", WS_CHILD | WS_VISIBLE |
            WS_BORDER, 800, 60, 30, 30, hWnd, (HMENU)ID_PRZYCISK17, hInstance, NULL),
        hButton18 = CreateWindowEx(WS_EX_CLIENTEDGE, L"BUTTON", L"2", WS_CHILD | WS_VISIBLE |
            WS_BORDER, 840, 60, 30, 30, hWnd, (HMENU)ID_PRZYCISK18, hInstance, NULL),
        hButton19 = CreateWindowEx(WS_EX_CLIENTEDGE, L"BUTTON", L"3", WS_CHILD | WS_VISIBLE |
            WS_BORDER, 800, 100, 30, 30, hWnd, (HMENU)ID_PRZYCISK19, hInstance, NULL),
        hButton20 = CreateWindowEx(WS_EX_CLIENTEDGE, L"BUTTON", L"4", WS_CHILD | WS_VISIBLE |
            WS_BORDER, 840, 100, 30, 30, hWnd, (HMENU)ID_PRZYCISK20, hInstance, NULL),
        hButton21 = CreateWindowEx(WS_EX_CLIENTEDGE, L"BUTTON", L"START !", WS_CHILD | WS_VISIBLE |
            WS_BORDER, 1000, 275, 100, 100, hWnd, (HMENU)ID_PRZYCISK21, hInstance, NULL);



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
//  PRZEZNACZENIE: Przetwarza komunikaty dla okna g³ównego.
//
//  WM_COMMAND  - przetwarzaj menu aplikacji
//  WM_PAINT    - Maluj okno g³ówne
//  WM_DESTROY  - opublikuj komunikat o wyjœciu i wróæ
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
            pietro_pie.push_back(2);
            do_odwiedzenia.push_back(1);
            InvalidateRect(hWnd, 0, TRUE);
            break;
        case ID_PRZYCISK2:
            pietro_pie.push_back(3);
            do_odwiedzenia.push_back(1);
            InvalidateRect(hWnd, 0, TRUE);
            break;
        case ID_PRZYCISK3:
            pietro_pie.push_back(4);
            do_odwiedzenia.push_back(1);
            InvalidateRect(hWnd, 0, TRUE);
            break;
        case ID_PRZYCISK4:
            pietro_pie.push_back(5);
            do_odwiedzenia.push_back(1);
            InvalidateRect(hWnd, 0, TRUE);
            break;
        case ID_PRZYCISK5:
            pietro_dru.push_back(1);
            do_odwiedzenia.push_back(2);
            InvalidateRect(hWnd, 0, TRUE);
            break;
        case ID_PRZYCISK6:
            pietro_dru.push_back(3);
            do_odwiedzenia.push_back(2);
            InvalidateRect(hWnd, 0, TRUE);
            break;
        case ID_PRZYCISK7:
            pietro_dru.push_back(4);
            do_odwiedzenia.push_back(2);
            InvalidateRect(hWnd, 0, TRUE);
            break;
        case ID_PRZYCISK8:
            pietro_dru.push_back(5);
            do_odwiedzenia.push_back(2);
            InvalidateRect(hWnd, 0, TRUE);
            break;
        case ID_PRZYCISK9:
            pietro_trze.push_back(1);
            do_odwiedzenia.push_back(3);
            InvalidateRect(hWnd, 0, TRUE);
            break;
        case ID_PRZYCISK10:
            pietro_trze.push_back(2);
            do_odwiedzenia.push_back(3);
            InvalidateRect(hWnd, 0, TRUE);
            break;
        case ID_PRZYCISK11:
            pietro_trze.push_back(4);
            do_odwiedzenia.push_back(3);
            InvalidateRect(hWnd, 0, TRUE);
            break;
        case ID_PRZYCISK12:
            pietro_trze.push_back(5);
            do_odwiedzenia.push_back(3);
            InvalidateRect(hWnd, 0, TRUE);
            break;
        case ID_PRZYCISK13:
            pietro_czwa.push_back(1);
            do_odwiedzenia.push_back(4);
            InvalidateRect(hWnd, 0, TRUE);
            break;
        case ID_PRZYCISK14:
            pietro_czwa.push_back(2);
            do_odwiedzenia.push_back(4);
            InvalidateRect(hWnd, 0, TRUE);
            break;
        case ID_PRZYCISK15:
            pietro_czwa.push_back(3);
            do_odwiedzenia.push_back(4);
            InvalidateRect(hWnd, 0, TRUE);
            break;
        case ID_PRZYCISK16:
            pietro_czwa.push_back(5);
            do_odwiedzenia.push_back(4);
            InvalidateRect(hWnd, 0, TRUE);
            break;
        case ID_PRZYCISK17:
            pietro_pia.push_back(1);
            do_odwiedzenia.push_back(5);
            InvalidateRect(hWnd, 0, TRUE);
            break;
        case ID_PRZYCISK18:
            pietro_pia.push_back(2);
            do_odwiedzenia.push_back(5);
            InvalidateRect(hWnd, 0, TRUE);
            break;
        case ID_PRZYCISK19:
            pietro_pia.push_back(3);
            do_odwiedzenia.push_back(5);
            InvalidateRect(hWnd, 0, TRUE);
            break;
        case ID_PRZYCISK20:
            pietro_pia.push_back(4);
            do_odwiedzenia.push_back(5);
            InvalidateRect(hWnd, 0, TRUE);
            break;
        case ID_PRZYCISK21:
            start = true;
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
        // TODO: Tutaj dodaj kod rysuj¹cy u¿ywaj¹cy elementu hdc...
        HPEN hPenOld;
        HPEN hLinePen;
        COLORREF qLineColor;
        qLineColor = RGB(0, 0, 0);
        hLinePen = CreatePen(PS_SOLID, 7, qLineColor);
        hPenOld = (HPEN)SelectObject(hdc, hLinePen);

        MoveToEx(hdc, 350, 10, NULL);
        LineTo(hdc, 350, 630);
        MoveToEx(hdc, 350, 10, NULL);
        LineTo(hdc, 550, 10);
        MoveToEx(hdc, 350, 630, NULL);
        LineTo(hdc, 550, 630);

        MoveToEx(hdc, 550, 10, NULL);
        LineTo(hdc, 550, 630);

        qLineColor = RGB(0, 0, 0);
        hLinePen = CreatePen(PS_SOLID, 6, qLineColor);
        hPenOld = (HPEN)SelectObject(hdc, hLinePen);

        Rectangle(hdc, 360, 510 - polozenie, 540, 620 - polozenie);

        qLineColor = RGB(87, 542, 0);
        hLinePen = CreatePen(PS_SOLID, 4, qLineColor);
        hPenOld = (HPEN)SelectObject(hdc, hLinePen);
        MoveToEx(hdc, 100, 500, NULL);
        LineTo(hdc, 340, 500);
        qLineColor = RGB(255, 12, 0);
        hLinePen = CreatePen(PS_SOLID, 4, qLineColor);
        hPenOld = (HPEN)SelectObject(hdc, hLinePen);
        MoveToEx(hdc, 560, 380, NULL);
        LineTo(hdc, 800, 380);
        qLineColor = RGB(21, 255, 12);
        hLinePen = CreatePen(PS_SOLID, 4, qLineColor);
        hPenOld = (HPEN)SelectObject(hdc, hLinePen);
        MoveToEx(hdc, 100, 270, NULL);
        LineTo(hdc, 340, 270);
        qLineColor = RGB(255, 25, 436);
        hLinePen = CreatePen(PS_SOLID, 4, qLineColor);
        hPenOld = (HPEN)SelectObject(hdc, hLinePen);
        MoveToEx(hdc, 560, 160, NULL);
        LineTo(hdc, 800, 160);
        qLineColor = RGB(73, 142, 23);
        hLinePen = CreatePen(PS_SOLID, 4, qLineColor);
        hPenOld = (HPEN)SelectObject(hdc, hLinePen);
        MoveToEx(hdc, 560, 615, NULL);
        LineTo(hdc, 800, 615);

        TextOut(hdc, 800, 10, L"WAGA :", 6);


        if (pietro_pie.size() > 0)
        {
            szerokosc = 560;
            wysokosc = 600;
            hdc = GetDC(hWnd);
            rysuj_pietro_prawa(pietro_pie, wysokosc, szerokosc, hWnd, hdc, hPenOld, hLinePen, qLineColor);
            ReleaseDC(hWnd, hdc);
        }
        if (pietro_dru.size() > 0)
        {
            szerokosc = 335;
            wysokosc = 490;
            hdc = GetDC(hWnd);
            rysuj_pietro_lewa(pietro_dru, wysokosc, szerokosc, hWnd, hdc, hPenOld, hLinePen, qLineColor);
            ReleaseDC(hWnd, hdc);
        }
        if (pietro_trze.size() > 0)
        {
            szerokosc = 560;
            wysokosc = 370;
            hdc = GetDC(hWnd);
            rysuj_pietro_prawa(pietro_trze, wysokosc, szerokosc, hWnd, hdc, hPenOld, hLinePen, qLineColor);
            ReleaseDC(hWnd, hdc);
        }
        if (pietro_czwa.size() > 0)
        {
            szerokosc = 335;
            wysokosc = 260;
            hdc = GetDC(hWnd);
            rysuj_pietro_lewa(pietro_czwa, wysokosc, szerokosc, hWnd, hdc, hPenOld, hLinePen, qLineColor);
            ReleaseDC(hWnd, hdc);
        }
        if (pietro_pia.size() > 0)
        {
            szerokosc = 560;
            wysokosc = 145;
            rysuj_pietro_prawa(pietro_pia, wysokosc, szerokosc, hWnd, hdc, hPenOld, hLinePen, qLineColor);
            ReleaseDC(hWnd, hdc);
        }
        while (start == true)
        {
            if (w_gore == true)
            {
                if (pietro_pierwsze == true)
                {
                    polozenie = 0;
                    szerokosc = 560;
                    wysokosc = 600;

                    if (pietro_pie.size() > 0 && winda.size() < 10)
                    {
                        while (winda.size() != 10 && pietro_pie.size() != 0)
                        {
                            int czl = pietro_pie.front();
                            winda.push_back(czl);
                            wchodza.push_back(czl);
                            pietro_pie.erase(pietro_pie.begin());
                        }
                        rysuj_wage(hdc, hWnd, winda);
                        /*int z = 0;
                        while (z < 185)
                        {
                            wchodzenie_do_windy_prawa(wchodza, pietro_pie, wysokosc, szerokosc, z, hWnd, hdc, hPenOld, hLinePen, qLineColor);
                        }*/
                        hdc = GetDC(hWnd);
                        rysuj_winda(winda, polozenie, wysokosc, szerokosc, hWnd, hdc, hPenOld, hLinePen, qLineColor);
                        Sleep(50);
                        rysuj_blok_czyszczacy_prawa(wysokosc, szerokosc, hWnd, hdc, hPenOld, hLinePen, qLineColor);
                        rysuj_pietro_prawa(pietro_pie, wysokosc, szerokosc, hWnd, hdc, hPenOld, hLinePen, qLineColor);
                        zamykanie_drzwi_prawa(wysokosc, szerokosc, hWnd, hdc, hPenOld, hLinePen, qLineColor);
                        ReleaseDC(hWnd, hdc);
                    }
                    hdc = GetDC(hWnd);
                    while (polozenie < 112)
                    {
                        wjazd_windy(wysokosc, szerokosc, winda, polozenie, hWnd, hdc, hPenOld, hLinePen, qLineColor);
                    }
                    ReleaseDC(hWnd, hdc);

                    pietro_pierwsze = false;
                    pietro_drugie = true;

                }
                if (pietro_drugie == true)
                {
                    polozenie = 112;
                    szerokosc = 335;
                    wysokosc = 490;
                    int m = winda.size();
                    for (int i = 0; i < m; i++)
                    {
                        if (winda[i] == 2)
                        {
                            wysiada = true;
                            break;
                        }
                    }
                    int p = pietro_dru.size();
                    for (int i = 0; i < p; i++)
                    {
                        if (pietro_dru[i] == 3 || pietro_dru[i] == 4 || pietro_dru[i] == 5)
                        {
                            wsiada = true;
                            break;
                        }
                    }

                    if (wsiada == true || wysiada == true)
                    {
                        hdc = GetDC(hWnd);
                        otwieranie_drzwi_lewa(wysokosc, szerokosc, hWnd, hdc, hPenOld, hLinePen, qLineColor);
                        ReleaseDC(hWnd, hdc);
                    }
                    if (wysiada == true)
                    {
                        for (int i = 0; i < m; i++)
                        {
                            int czl = winda.front();
                            if (czl != 2)
                            {
                                winda.push_back(czl);
                            }
                            winda.erase(winda.begin());
                        }
                    }
                    if (wsiada == true)
                    {
                        for (int i = 0; i < p; i++)
                        {
                            int czl = pietro_dru.front();
                            if ((czl == 3 || czl == 4 || czl == 5) && winda.size() < 10)
                            {
                                winda.push_back(czl);
                            }
                            else {
                                pietro_dru.push_back(czl);
                            }
                            pietro_dru.erase(pietro_dru.begin());
                        }
                    }
                    hdc = GetDC(hWnd);
                    rysuj_wage(hdc, hWnd, winda);
                    rysuj_blok_czyszczacy_winda(polozenie, hWnd, hdc, hPenOld, hLinePen, qLineColor);
                    rysuj_winda(winda, polozenie, wysokosc, szerokosc, hWnd, hdc, hPenOld, hLinePen, qLineColor);
                    rysuj_blok_czyszczacy_lewa(wysokosc, szerokosc, hWnd, hdc, hPenOld, hLinePen, qLineColor);
                    rysuj_pietro_lewa(pietro_dru, wysokosc, szerokosc, hWnd, hdc, hPenOld, hLinePen, qLineColor);
                    Sleep(50);
                    ReleaseDC(hWnd, hdc);
                    if (wsiada == true || wysiada == true)
                    {
                        hdc = GetDC(hWnd);
                        zamykanie_drzwi_lewa(wysokosc, szerokosc, hWnd, hdc, hPenOld, hLinePen, qLineColor);
                        ReleaseDC(hWnd, hdc);
                    }

                    /* int x = 0;
                    while (x < 460)
                    {
                        wychodzenie_z_windy_lewa(winda, pietro_dru, wysokosc, x, szerokosc, polozenie, hWnd, hdc, hPenOld, hLinePen, qLineColor);
                    }*/
                    wysiada = false;
                    wsiada = false;
                    if (winda.empty() && pietro_czwa.empty() && pietro_pia.empty() && pietro_trze.empty())
                    {
                        w_gore = false;
                        w_dol = true;
                    }
                    else
                    {
                        hdc = GetDC(hWnd);
                        while (polozenie < 224)
                        {
                            wjazd_windy(wysokosc, szerokosc, winda, polozenie, hWnd, hdc, hPenOld, hLinePen, qLineColor);
                        }
                        ReleaseDC(hWnd, hdc);
                        pietro_drugie = false;
                        pietro_trzecie = true;
                    }
                }
                if (pietro_trzecie == true)
                {
                    polozenie = 224;
                    szerokosc = 560;
                    wysokosc = 370;

                    int m = winda.size();
                    for (int i = 0; i < m; i++)
                    {
                        if (winda[i] == 3)
                        {
                            wysiada = true;
                            break;
                        }
                    }
                    int p = pietro_trze.size();
                    for (int i = 0; i < p; i++)
                    {
                        if (pietro_trze[i] == 4 || pietro_trze[i] == 5)
                        {
                            wsiada = true;
                            break;
                        }
                    }
                    if (wsiada == true || wysiada == true)
                    {
                        hdc = GetDC(hWnd);
                        otwieranie_drzwi_prawa(wysokosc, szerokosc, hWnd, hdc, hPenOld, hLinePen, qLineColor);
                        ReleaseDC(hWnd, hdc);
                    }
                    if (wysiada == true)
                    {

                        for (int i = 0; i < m; i++)
                        {
                            int czl = winda.front();
                            if (czl != 3)
                            {
                                winda.push_back(czl);
                            }
                            winda.erase(winda.begin());
                        }

                    }
                    if (wsiada == true)
                    {
                        for (int i = 0; i < p; i++)
                        {
                            int czl = pietro_trze.front();
                            if ((czl == 4 || czl == 5) && winda.size() < 10)
                            {
                                winda.push_back(czl);
                            }
                            else {
                                pietro_trze.push_back(czl);
                            }
                            pietro_trze.erase(pietro_trze.begin());
                        }
                    }
                    hdc = GetDC(hWnd);
                    rysuj_wage(hdc, hWnd, winda);
                    rysuj_blok_czyszczacy_winda(polozenie, hWnd, hdc, hPenOld, hLinePen, qLineColor);
                    rysuj_winda(winda, polozenie, wysokosc, szerokosc, hWnd, hdc, hPenOld, hLinePen, qLineColor);
                    rysuj_blok_czyszczacy_prawa(wysokosc, szerokosc, hWnd, hdc, hPenOld, hLinePen, qLineColor);
                    rysuj_pietro_prawa(pietro_trze, wysokosc, szerokosc, hWnd, hdc, hPenOld, hLinePen, qLineColor);
                    Sleep(50);
                    ReleaseDC(hWnd, hdc);

                    if (wsiada == true || wysiada == true)
                    {
                        hdc = GetDC(hWnd);
                        zamykanie_drzwi_prawa(wysokosc, szerokosc, hWnd, hdc, hPenOld, hLinePen, qLineColor);
                        ReleaseDC(hWnd, hdc);
                    }

                    wysiada = false;
                    wsiada = false;

                    if (winda.empty() && pietro_czwa.empty() && pietro_pia.empty())
                    {
                        w_gore = false;
                        w_dol = true;
                    }
                    else
                    {
                        hdc = GetDC(hWnd);
                        while (polozenie < 336)
                        {
                            wjazd_windy(wysokosc, szerokosc, winda, polozenie, hWnd, hdc, hPenOld, hLinePen, qLineColor);
                        }
                        ReleaseDC(hWnd, hdc);
                        pietro_trzecie = false;
                        pietro_czwarte = true;
                    }
                }
                if (pietro_czwarte == true)
                {
                    polozenie = 336;
                    szerokosc = 335;
                    wysokosc = 260;
                    int m = winda.size();
                    for (int i = 0; i < m; i++)
                    {
                        if (winda[i] == 4)
                        {
                            wysiada = true;
                            break;
                        }
                    }
                    int p = pietro_czwa.size();
                    for (int i = 0; i < p; i++)
                    {
                        if (pietro_czwa[i] == 5)
                        {
                            wsiada = true;
                            break;
                        }
                    }
                    if (wsiada == true || wysiada == true)
                    {
                        hdc = GetDC(hWnd);
                        otwieranie_drzwi_lewa(wysokosc, szerokosc, hWnd, hdc, hPenOld, hLinePen, qLineColor);
                        ReleaseDC(hWnd, hdc);
                    }
                    if (wysiada == true)
                    {
                        for (int i = 0; i < m; i++)
                        {
                            int czl = winda.front();
                            if (czl != 4)
                            {
                                winda.push_back(czl);
                            }
                            winda.erase(winda.begin());
                        }
                    }
                    if (wsiada == true)
                    {
                        for (int i = 0; i < p; i++)
                        {
                            int czl = pietro_czwa.front();
                            if ((czl == 5) && winda.size() < 10)
                            {
                                winda.push_back(czl);
                            }
                            else {
                                pietro_czwa.push_back(czl);
                            }
                            pietro_czwa.erase(pietro_czwa.begin());
                        }
                    }
                    hdc = GetDC(hWnd);
                    rysuj_wage(hdc, hWnd, winda);
                    rysuj_blok_czyszczacy_winda(polozenie, hWnd, hdc, hPenOld, hLinePen, qLineColor);
                    rysuj_winda(winda, polozenie, wysokosc, szerokosc, hWnd, hdc, hPenOld, hLinePen, qLineColor);
                    rysuj_blok_czyszczacy_lewa(wysokosc, szerokosc, hWnd, hdc, hPenOld, hLinePen, qLineColor);
                    rysuj_pietro_lewa(pietro_czwa, wysokosc, szerokosc, hWnd, hdc, hPenOld, hLinePen, qLineColor);
                    Sleep(50);
                    ReleaseDC(hWnd, hdc);

                    if (wsiada == true || wysiada == true)
                    {
                        hdc = GetDC(hWnd);
                        zamykanie_drzwi_lewa(wysokosc, szerokosc, hWnd, hdc, hPenOld, hLinePen, qLineColor);
                        ReleaseDC(hWnd, hdc);
                    }

                    wysiada = false;
                    wsiada = false;



                    if (winda.empty() && pietro_pia.empty())
                    {
                        w_gore = false;
                        w_dol = true;
                    }
                    else
                    {
                        hdc = GetDC(hWnd);
                        while (polozenie < 450)
                        {
                            wjazd_windy(wysokosc, szerokosc, winda, polozenie, hWnd, hdc, hPenOld, hLinePen, qLineColor);
                        }
                        ReleaseDC(hWnd, hdc);
                        pietro_czwarte = false;
                        pietro_piate = true;
                    }
                }
                if (pietro_piate == true)
                {
                    szerokosc = 560;
                    wysokosc = 145;

                    int m = winda.size();
                    for (int i = 0; i < m; i++)
                    {
                        if (winda[i] == 5)
                        {
                            wysiada = true;
                            break;
                        }
                    }
                    int p = pietro_pia.size();
                    for (int i = 0; i < p; i++)
                    {
                        if (pietro_pia.size() > 0)
                        {
                            wsiada = true;
                            break;
                        }
                    }
                    if (wsiada == true || wysiada == true)
                    {
                        hdc = GetDC(hWnd);
                        otwieranie_drzwi_prawa(wysokosc, szerokosc, hWnd, hdc, hPenOld, hLinePen, qLineColor);
                        ReleaseDC(hWnd, hdc);
                    }
                    if (wysiada == true)
                    {

                        for (int i = 0; i < m; i++)
                        {
                            int czl = winda.front();
                            if (czl != 5)
                            {
                                winda.push_back(czl);
                            }
                            winda.erase(winda.begin());
                        }

                    }
                    if (wsiada == true)
                    {
                        for (int i = 0; i < p; i++)
                        {
                            int czl = pietro_pia.front();
                            if (winda.size() < 10 && pietro_pia.size() > 0)
                            {
                                winda.push_back(czl);
                            }
                            else {
                                pietro_pia.push_back(czl);
                            }
                            pietro_pia.erase(pietro_pia.begin());
                        }
                    }
                    hdc = GetDC(hWnd);
                    rysuj_wage(hdc, hWnd, winda);
                    rysuj_blok_czyszczacy_winda(polozenie, hWnd, hdc, hPenOld, hLinePen, qLineColor);
                    rysuj_winda(winda, polozenie, wysokosc, szerokosc, hWnd, hdc, hPenOld, hLinePen, qLineColor);
                    rysuj_blok_czyszczacy_prawa(wysokosc, szerokosc, hWnd, hdc, hPenOld, hLinePen, qLineColor);
                    rysuj_pietro_prawa(pietro_pia, wysokosc, szerokosc, hWnd, hdc, hPenOld, hLinePen, qLineColor);
                    Sleep(50);
                    ReleaseDC(hWnd, hdc);

                    if (wsiada == true || wysiada == true)
                    {
                        hdc = GetDC(hWnd);
                        zamykanie_drzwi_prawa(wysokosc, szerokosc, hWnd, hdc, hPenOld, hLinePen, qLineColor);
                        ReleaseDC(hWnd, hdc);
                    }

                    wysiada = false;
                    wsiada = false;

                    w_dol = true;
                    w_gore = false;
                }
            }
            if (w_dol == true)
            {
                if (pietro_piate == true)
                {
                    polozenie = 440;
                    szerokosc = 560;
                    wysokosc = 145;
                    hdc = GetDC(hWnd);
                    while (polozenie > 336)
                    {
                        zjazd_windy(wysokosc, szerokosc, winda, polozenie, hWnd, hdc, hPenOld, hLinePen, qLineColor);
                    }
                    ReleaseDC(hWnd, hdc);
                    pietro_czwarte = true;
                    pietro_piate = false;
                }
                if (pietro_czwarte == true)
                {
                    polozenie = 336;
                    szerokosc = 335;
                    wysokosc = 260;

                    int m = winda.size();
                    for (int i = 0; i < m; i++)
                    {
                        if (winda[i] == 4)
                        {
                            wysiada = true;
                            break;
                        }
                    }
                    int p = pietro_czwa.size();
                    for (int i = 0; i < p; i++)
                    {
                        if (pietro_czwa[i] != 5)
                        {
                            wsiada = true;
                            break;
                        }
                    }
                    if (wsiada == true || wysiada == true)
                    {
                        hdc = GetDC(hWnd);
                        otwieranie_drzwi_lewa(wysokosc, szerokosc, hWnd, hdc, hPenOld, hLinePen, qLineColor);
                    }
                    if (wysiada == true)
                    {
                        for (int i = 0; i < m; i++)
                        {
                            int czl = winda.front();
                            if (czl != 4)
                            {
                                winda.push_back(czl);
                            }
                            winda.erase(winda.begin());
                        }
                    }
                    if (wsiada == true)
                    {
                        for (int i = 0; i < p; i++)
                        {
                            int czl = pietro_czwa.front();
                            if ((czl != 5) && winda.size() < 10)
                            {
                                winda.push_back(czl);
                            }
                            else {
                                pietro_czwa.push_back(czl);
                            }
                            pietro_czwa.erase(pietro_czwa.begin());
                        }
                    }
                    hdc = GetDC(hWnd);
                    rysuj_wage(hdc, hWnd, winda);
                    rysuj_blok_czyszczacy_winda(polozenie, hWnd, hdc, hPenOld, hLinePen, qLineColor);
                    rysuj_winda(winda, polozenie, wysokosc, szerokosc, hWnd, hdc, hPenOld, hLinePen, qLineColor);
                    rysuj_blok_czyszczacy_lewa(wysokosc, szerokosc, hWnd, hdc, hPenOld, hLinePen, qLineColor);
                    rysuj_pietro_lewa(pietro_czwa, wysokosc, szerokosc, hWnd, hdc, hPenOld, hLinePen, qLineColor);
                    Sleep(50);
                    ReleaseDC(hWnd, hdc);

                    if (wsiada == true || wysiada == true)
                    {
                        hdc = GetDC(hWnd);
                        zamykanie_drzwi_lewa(wysokosc, szerokosc, hWnd, hdc, hPenOld, hLinePen, qLineColor);
                        ReleaseDC(hWnd, hdc);
                    }

                    wysiada = false;
                    wsiada = false;
                    if (winda.empty() && (!pietro_pia.empty()) && pietro_czwa.empty() && pietro_dru.empty() && pietro_pie.empty())
                    {
                        w_gore = true;
                        w_dol = false;
                    }
                    else
                    {
                        hdc = GetDC(hWnd);
                        while (polozenie > 222)
                        {
                            zjazd_windy(wysokosc, szerokosc, winda, polozenie, hWnd, hdc, hPenOld, hLinePen, qLineColor);
                            ReleaseDC(hWnd, hdc);
                        }
                        pietro_trzecie = true;
                        pietro_czwarte = false;
                    }
                }
                if (pietro_trzecie == true)
                {
                    polozenie = 224;
                    szerokosc = 560;
                    wysokosc = 370;

                    int m = winda.size();
                    for (int i = 0; i < m; i++)
                    {
                        if (winda[i] == 3)
                        {
                            wysiada = true;
                            break;
                        }
                    }
                    int p = pietro_trze.size();
                    for (int i = 0; i < p; i++)
                    {
                        if (pietro_trze[i] == 2 || pietro_trze[i] == 1)
                        {
                            wsiada = true;
                            break;
                        }
                    }
                    if (wsiada == true || wysiada == true)
                    {
                        hdc = GetDC(hWnd);
                        otwieranie_drzwi_prawa(wysokosc, szerokosc, hWnd, hdc, hPenOld, hLinePen, qLineColor);
                        ReleaseDC(hWnd, hdc);
                    }
                    if (wysiada == true)
                    {
                        for (int i = 0; i < m; i++)
                        {
                            int czl = winda.front();
                            if (czl != 3)
                            {
                                winda.push_back(czl);
                            }
                            winda.erase(winda.begin());
                        }
                    }
                    if (wsiada == true)
                    {
                        for (int i = 0; i < p; i++)
                        {
                            int czl = pietro_trze.front();
                            if ((czl == 1 || czl == 2) && winda.size() < 10)
                            {
                                winda.push_back(czl);
                            }
                            else {
                                pietro_trze.push_back(czl);
                            }
                            pietro_trze.erase(pietro_trze.begin());
                        }
                    }
                    hdc = GetDC(hWnd);
                    rysuj_wage(hdc, hWnd, winda);
                    rysuj_blok_czyszczacy_winda(polozenie, hWnd, hdc, hPenOld, hLinePen, qLineColor);
                    rysuj_winda(winda, polozenie, wysokosc, szerokosc, hWnd, hdc, hPenOld, hLinePen, qLineColor);
                    rysuj_blok_czyszczacy_prawa(wysokosc, szerokosc, hWnd, hdc, hPenOld, hLinePen, qLineColor);
                    rysuj_pietro_prawa(pietro_trze, wysokosc, szerokosc, hWnd, hdc, hPenOld, hLinePen, qLineColor);
                    Sleep(50);
                    ReleaseDC(hWnd, hdc);

                    if (wsiada == true || wysiada == true)
                    {
                        hdc = GetDC(hWnd);
                        zamykanie_drzwi_prawa(wysokosc, szerokosc, hWnd, hdc, hPenOld, hLinePen, qLineColor);
                        ReleaseDC(hWnd, hdc);
                    }

                    wysiada = false;
                    wsiada = false;
                    if (winda.empty() && (!pietro_pia.empty() || !pietro_czwa.empty()) && pietro_dru.empty() && pietro_pie.empty())
                    {
                        w_gore = true;
                        w_dol = false;
                    }
                    else
                    {
                        hdc = GetDC(hWnd);
                        while (polozenie > 112)
                        {
                            zjazd_windy(wysokosc, szerokosc, winda, polozenie, hWnd, hdc, hPenOld, hLinePen, qLineColor);
                            ReleaseDC(hWnd, hdc);
                        }
                        pietro_drugie = true;
                        pietro_trzecie = false;
                    }
                }
                if (pietro_drugie == true)
                {
                    polozenie = 112;
                    szerokosc = 335;
                    wysokosc = 490;

                    int m = winda.size();
                    for (int i = 0; i < m; i++)
                    {
                        if (winda[i] == 2)
                        {
                            wysiada = true;
                            break;
                        }
                    }
                    int p = pietro_dru.size();
                    for (int i = 0; i < p; i++)
                    {
                        if (pietro_dru[i] == 1)
                        {
                            wsiada = true;
                            break;
                        }
                    }
                    if (wsiada == true || wysiada == true)
                    {
                        hdc = GetDC(hWnd);
                        otwieranie_drzwi_lewa(wysokosc, szerokosc, hWnd, hdc, hPenOld, hLinePen, qLineColor);
                        ReleaseDC(hWnd, hdc);
                    }
                    if (wysiada == true)
                    {
                        for (int i = 0; i < m; i++)
                        {
                            int czl = winda.front();
                            if (czl != 2)
                            {
                                winda.push_back(czl);
                            }
                            winda.erase(winda.begin());
                        }
                    }
                    if (wsiada == true)
                    {
                        for (int i = 0; i < p; i++)
                        {
                            int czl = pietro_dru.front();
                            if ((czl == 1) && winda.size() < 10)
                            {
                                winda.push_back(czl);
                            }
                            else {
                                pietro_dru.push_back(czl);
                            }
                            pietro_dru.erase(pietro_dru.begin());
                        }
                    }
                    hdc = GetDC(hWnd);
                    rysuj_wage(hdc, hWnd, winda);
                    rysuj_blok_czyszczacy_winda(polozenie, hWnd, hdc, hPenOld, hLinePen, qLineColor);
                    rysuj_winda(winda, polozenie, wysokosc, szerokosc, hWnd, hdc, hPenOld, hLinePen, qLineColor);
                    rysuj_blok_czyszczacy_lewa(wysokosc, szerokosc, hWnd, hdc, hPenOld, hLinePen, qLineColor);
                    rysuj_pietro_lewa(pietro_dru, wysokosc, szerokosc, hWnd, hdc, hPenOld, hLinePen, qLineColor);
                    Sleep(50);
                    ReleaseDC(hWnd, hdc);

                    if (wsiada == true || wysiada == true)
                    {
                        hdc = GetDC(hWnd);
                        zamykanie_drzwi_lewa(wysokosc, szerokosc, hWnd, hdc, hPenOld, hLinePen, qLineColor);
                        ReleaseDC(hWnd, hdc);
                    }

                    /* int x = 0;
                    while (x < 460)
                    {
                        wychodzenie_z_windy_lewa(winda, pietro_dru, wysokosc, x, szerokosc, polozenie, hWnd, hdc, hPenOld, hLinePen, qLineColor);
                    }*/
                    wysiada = false;
                    wsiada = false;
                    if (winda.empty() && (!pietro_pia.empty() || !pietro_czwa.empty() || !pietro_trze.empty()) && pietro_pie.empty())
                    {
                        w_gore = true;
                        w_dol = false;
                    }
                    else
                    {
                        hdc = GetDC(hWnd);
                        while (polozenie > -10)
                        {
                            zjazd_windy(wysokosc, szerokosc, winda, polozenie, hWnd, hdc, hPenOld, hLinePen, qLineColor);
                        }
                        ReleaseDC(hWnd, hdc);
                        pietro_pierwsze = true;
                        pietro_drugie = false;
                    }
                }
                if (pietro_pierwsze == true)
                {
                    polozenie = 0;
                    szerokosc = 560;
                    wysokosc = 600;
                    if (pietro_pie.size() > 0 || winda.size() > 0)
                    {
                        hdc = GetDC(hWnd);
                        otwieranie_drzwi_prawa(wysokosc, szerokosc, hWnd, hdc, hPenOld, hLinePen, qLineColor);
                        ReleaseDC(hWnd, hdc);
                    }
                    int m = winda.size();
                    for (int i = 0; i < m; i++)
                    {
                        int czl = winda.front();
                        if (czl != 1)
                        {
                            winda.push_back(czl);
                        }
                        winda.erase(winda.begin());
                    }
                    hdc = GetDC(hWnd);
                    polozenie = -6;
                    rysuj_blok_czyszczacy_winda(polozenie, hWnd, hdc, hPenOld, hLinePen, qLineColor);
                    polozenie = 0;
                    rysuj_winda(winda, polozenie, wysokosc, szerokosc, hWnd, hdc, hPenOld, hLinePen, qLineColor);
                    rysuj_wage(hdc, hWnd, winda);
                    ReleaseDC(hWnd, hdc);
                    w_dol = false;
                    w_gore = true;

                    if (winda.empty() && pietro_czwa.empty() && pietro_dru.empty() && pietro_trze.empty() && pietro_pia.empty() && pietro_pie.empty())
                    {
                        hdc = GetDC(hWnd);
                        zamykanie_drzwi_prawa(wysokosc, szerokosc, hWnd, hdc, hPenOld, hLinePen, qLineColor);
                        ReleaseDC(hWnd, hdc);
                        start = false;
                        w_dol = true;
                        w_gore = false;
                    }
                }
            }
        }
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

// Procedura obs³ugi komunikatów dla okna informacji o programie.
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
void rysuj_wage(HDC hdc, HWND hWnd, vector<int>winda)
{
    hdc = GetDC(hWnd);
    if (winda.size() == 0)
        TextOut(hdc, 800, 30, L"000", 3);
    else if (winda.size() == 1)
        TextOut(hdc, 800, 30, L"070", 3);
    else if (winda.size() == 2)
        TextOut(hdc, 800, 30, L"140", 3);
    else if (winda.size() == 3)
        TextOut(hdc, 800, 30, L"210", 3);
    else if (winda.size() == 4)
        TextOut(hdc, 800, 30, L"280", 3);
    else if (winda.size() == 5)
        TextOut(hdc, 800, 30, L"350", 3);
    else if (winda.size() == 6)
        TextOut(hdc, 800, 30, L"420", 3);
    else if (winda.size() == 7)
        TextOut(hdc, 800, 30, L"490", 3);
    else if (winda.size() == 8)
        TextOut(hdc, 800, 30, L"560", 3);
    else if (winda.size() == 9)
        TextOut(hdc, 800, 30, L"630", 3);
    else if (winda.size() == 10)
        TextOut(hdc, 800, 30, L"700", 3);

    ReleaseDC(hWnd, hdc);
}
void rysuj_blok_czyszczacy_prawa(int wysokosc, int szerokosc, HWND hWnd, HDC hdc, HPEN hPenOld, HPEN hLinePen, COLORREF qLineColor)
{
    hdc = GetDC(hWnd);
    qLineColor = RGB(255, 255, 255);
    hLinePen = CreatePen(PS_SOLID, 5, qLineColor);
    hPenOld = (HPEN)SelectObject(hdc, hLinePen);
    Rectangle(hdc, szerokosc - 3, wysokosc, szerokosc + 600, wysokosc - 45);
    ReleaseDC(hWnd, hdc);
}
void rysuj_blok_czyszczacy_lewa(int wysokosc, int szerokosc, HWND hWnd, HDC hdc, HPEN hPenOld, HPEN hLinePen, COLORREF qLineColor)
{
    hdc = GetDC(hWnd);
    qLineColor = RGB(255, 255, 255);
    hLinePen = CreatePen(PS_SOLID, 5, qLineColor);
    hPenOld = (HPEN)SelectObject(hdc, hLinePen);
    Rectangle(hdc, szerokosc + 5, wysokosc, szerokosc - 600, wysokosc - 45);
    ReleaseDC(hWnd, hdc);
}
void rysuj_blok_czyszczacy_winda(int& polozenie, HWND hWnd, HDC hdc, HPEN hPenOld, HPEN hLinePen, COLORREF qLineColor)
{
    hdc = GetDC(hWnd);
    qLineColor = RGB(255, 255, 255);
    hLinePen = CreatePen(PS_SOLID, 5, qLineColor);
    hPenOld = (HPEN)SelectObject(hdc, hLinePen);
    Rectangle(hdc, 375, 603 - polozenie, 530, 550 - polozenie);
    ReleaseDC(hWnd, hdc);
}
void rysuj_pietro_prawa(vector<int> pietro, int wysokosc, int szerokosc, HWND hWnd, HDC hdc, HPEN hPenOld, HPEN hLinePen, COLORREF qLineColor)
{
    hdc = GetDC(hWnd);
    for (int i = 0; i < pietro.size(); i++)
    {
        if (pietro[i] == 2)
        {
            qLineColor = RGB(87, 542, 0);
            hLinePen = CreatePen(PS_SOLID, 5, qLineColor);
            hPenOld = (HPEN)SelectObject(hdc, hLinePen);
            Rectangle(hdc, szerokosc + (15 * i), wysokosc, szerokosc + 5 + (15 * i), wysokosc - 45);
        }
        if (pietro[i] == 3)
        {
            qLineColor = RGB(255, 12, 0);
            hLinePen = CreatePen(PS_SOLID, 5, qLineColor);
            hPenOld = (HPEN)SelectObject(hdc, hLinePen);
            Rectangle(hdc, szerokosc + (15 * i), wysokosc, szerokosc + 5 + (15 * i), wysokosc - 45);
        }
        if (pietro[i] == 4)
        {
            qLineColor = RGB(21, 255, 12);
            hLinePen = CreatePen(PS_SOLID, 5, qLineColor);
            hPenOld = (HPEN)SelectObject(hdc, hLinePen);
            Rectangle(hdc, szerokosc + (15 * i), wysokosc, szerokosc + 5 + (15 * i), wysokosc - 45);
        }
        if (pietro[i] == 5)
        {
            qLineColor = RGB(255, 25, 436);
            hLinePen = CreatePen(PS_SOLID, 5, qLineColor);
            hPenOld = (HPEN)SelectObject(hdc, hLinePen);
            Rectangle(hdc, szerokosc + (15 * i), wysokosc, szerokosc + 5 + (15 * i), wysokosc - 45);
        }
        if (pietro[i] == 1)
        {
            qLineColor = RGB(73, 142, 23);
            hLinePen = CreatePen(PS_SOLID, 5, qLineColor);
            hPenOld = (HPEN)SelectObject(hdc, hLinePen);
            Rectangle(hdc, szerokosc + (15 * i), wysokosc, szerokosc + 5 + (15 * i), wysokosc - 45);
        }
    }
    ReleaseDC(hWnd, hdc);
}
void rysuj_pietro_lewa(vector<int> pietro, int wysokosc, int szerokosc, HWND hWnd, HDC hdc, HPEN hPenOld, HPEN hLinePen, COLORREF qLineColor)
{
    hdc = GetDC(hWnd);
    for (int i = 0; i < pietro.size(); i++)
    {
        if (pietro[i] == 2)
        {
            qLineColor = RGB(87, 542, 0);
            hLinePen = CreatePen(PS_SOLID, 5, qLineColor);
            hPenOld = (HPEN)SelectObject(hdc, hLinePen);
            Rectangle(hdc, szerokosc - (15 * i), wysokosc, szerokosc + 5 - (15 * i), wysokosc - 45);
        }
        if (pietro[i] == 3)
        {
            qLineColor = RGB(255, 12, 0);
            hLinePen = CreatePen(PS_SOLID, 5, qLineColor);
            hPenOld = (HPEN)SelectObject(hdc, hLinePen);
            Rectangle(hdc, szerokosc - (15 * i), wysokosc, szerokosc + 5 - (15 * i), wysokosc - 45);
        }
        if (pietro[i] == 4)
        {
            qLineColor = RGB(21, 255, 12);
            hLinePen = CreatePen(PS_SOLID, 5, qLineColor);
            hPenOld = (HPEN)SelectObject(hdc, hLinePen);
            Rectangle(hdc, szerokosc - +(15 * i), wysokosc, szerokosc + 5 - +(15 * i), wysokosc - 45);
        }
        if (pietro[i] == 5)
        {
            qLineColor = RGB(255, 25, 436);
            hLinePen = CreatePen(PS_SOLID, 5, qLineColor);
            hPenOld = (HPEN)SelectObject(hdc, hLinePen);
            Rectangle(hdc, szerokosc - (15 * i), wysokosc, szerokosc + 5 - (15 * i), wysokosc - 45);
        }
        if (pietro[i] == 1)
        {
            qLineColor = RGB(73, 142, 23);
            hLinePen = CreatePen(PS_SOLID, 5, qLineColor);
            hPenOld = (HPEN)SelectObject(hdc, hLinePen);
            Rectangle(hdc, szerokosc - (15 * i), wysokosc, szerokosc + 5 - (15 * i), wysokosc - 45);
        }
    }
    ReleaseDC(hWnd, hdc);
}
void rysuj_winda(vector<int> winda, int& polozenie, int wysokosc, int szerokosc, HWND hWnd, HDC hdc, HPEN hPenOld, HPEN hLinePen, COLORREF qLineColor)
{
    hdc = GetDC(hWnd);
    for (int i = 0; i < winda.size(); i++)
    {
        if (winda[i] == 2)
        {
            qLineColor = RGB(87, 542, 0);
            hLinePen = CreatePen(PS_SOLID, 5, qLineColor);
            hPenOld = (HPEN)SelectObject(hdc, hLinePen);
            Rectangle(hdc, 375 + (15 * i), 600 - polozenie, 380 + (15 * i), 555 - polozenie);
        }
        if (winda[i] == 3)
        {
            qLineColor = RGB(255, 12, 0);
            hLinePen = CreatePen(PS_SOLID, 5, qLineColor);
            hPenOld = (HPEN)SelectObject(hdc, hLinePen);
            Rectangle(hdc, 375 + (15 * i), 600 - polozenie, 380 + (15 * i), 555 - polozenie);
        }
        if (winda[i] == 4)
        {
            qLineColor = RGB(21, 255, 12);
            hLinePen = CreatePen(PS_SOLID, 5, qLineColor);
            hPenOld = (HPEN)SelectObject(hdc, hLinePen);
            Rectangle(hdc, 375 + (15 * i), 600 - polozenie, 380 + (15 * i), 555 - polozenie);
        }
        if (winda[i] == 1)
        {
            qLineColor = RGB(73, 142, 23);
            hLinePen = CreatePen(PS_SOLID, 5, qLineColor);
            hPenOld = (HPEN)SelectObject(hdc, hLinePen);
            Rectangle(hdc, 375 + (15 * i), 600 - polozenie, 380 + (15 * i), 555 - polozenie);
        }
        if (winda[i] == 5)
        {
            qLineColor = RGB(255, 25, 436);
            hLinePen = CreatePen(PS_SOLID, 5, qLineColor);
            hPenOld = (HPEN)SelectObject(hdc, hLinePen);
            Rectangle(hdc, 375 + (15 * i), 600 - polozenie, 380 + (15 * i), 555 - polozenie);
        }
    }
    ReleaseDC(hWnd, hdc);
}
void wjazd_windy(int wysokosc, int szerokosc, vector<int> winda, int& polozenie, HWND hWnd, HDC hdc, HPEN hPenOld, HPEN hLinePen, COLORREF qLineColor)
{
    hdc = GetDC(hWnd);
    qLineColor = RGB(255, 255, 255);
    hLinePen = CreatePen(PS_SOLID, 7, qLineColor);
    hPenOld = (HPEN)SelectObject(hdc, hLinePen);
    Rectangle(hdc, 360, 519 - polozenie, 540, 619 - polozenie);

    qLineColor = RGB(0, 0, 0);
    hLinePen = CreatePen(PS_SOLID, 6, qLineColor);
    hPenOld = (HPEN)SelectObject(hdc, hLinePen);
    Rectangle(hdc, 360, 510 - polozenie, 540, 610 - polozenie);

    if (winda.size() > 0)
    {
        rysuj_winda(winda, polozenie, wysokosc, szerokosc, hWnd, hdc, hPenOld, hLinePen, qLineColor);
    }
    polozenie++;
    Sleep(10);
    ReleaseDC(hWnd, hdc);
}
void zjazd_windy(int wysokosc, int szerokosc, vector<int> winda, int& polozenie, HWND hWnd, HDC hdc, HPEN hPenOld, HPEN hLinePen, COLORREF qLineColor)
{
    hdc = GetDC(hWnd);
    qLineColor = RGB(255, 255, 255);
    hLinePen = CreatePen(PS_SOLID, 7, qLineColor);
    hPenOld = (HPEN)SelectObject(hdc, hLinePen);
    Rectangle(hdc, 360, 490 - polozenie, 540, 609 - polozenie);

    qLineColor = RGB(0, 0, 0);
    hLinePen = CreatePen(PS_SOLID, 6, qLineColor);
    hPenOld = (HPEN)SelectObject(hdc, hLinePen);
    Rectangle(hdc, 360, 510 - polozenie, 540, 610 - polozenie);

    if (winda.size() > 0)
    {
        rysuj_winda(winda, polozenie, wysokosc, szerokosc, hWnd, hdc, hPenOld, hLinePen, qLineColor);
    }
    polozenie--;
    Sleep(10);
    ReleaseDC(hWnd, hdc);
}
void zamykanie_drzwi_prawa(int wysokosc, int szerokosc, HWND hWnd, HDC hdc, HPEN hPenOld, HPEN hLinePen, COLORREF qLineColor)
{
    hdc = GetDC(hWnd);
    int a = 0;
    while (a < 90)
    {
        qLineColor = RGB(0, 0, 0);
        hLinePen = CreatePen(PS_SOLID, 6, qLineColor);
        hPenOld = (HPEN)SelectObject(hdc, hLinePen);
        Rectangle(hdc, szerokosc - 10, wysokosc - 75, szerokosc - 8, wysokosc - 72 + a);
        Rectangle(hdc, szerokosc - 21, wysokosc - 75, szerokosc - 20, wysokosc - 72 + a);
        a++;
        Sleep(10);
    }
    ReleaseDC(hWnd, hdc);
}
void otwieranie_drzwi_prawa(int wysokosc, int szerokosc, HWND hWnd, HDC hdc, HPEN hPenOld, HPEN hLinePen, COLORREF qLineColor)
{
    hdc = GetDC(hWnd);
    int a = 0;

    while (a < 80)
    {
        qLineColor = RGB(255, 255, 255);
        hLinePen = CreatePen(PS_SOLID, 7, qLineColor);
        hPenOld = (HPEN)SelectObject(hdc, hLinePen);
        Rectangle(hdc, szerokosc - 21, wysokosc + 7, szerokosc - 8, wysokosc + 7 - a);
        a++;
        Sleep(10);
    }
    ReleaseDC(hWnd, hdc);
}
void otwieranie_drzwi_lewa(int wysokosc, int szerokosc, HWND hWnd, HDC hdc, HPEN hPenOld, HPEN hLinePen, COLORREF qLineColor)
{
    hdc = GetDC(hWnd);
    int a = 0;

    while (a < 80)
    {
        qLineColor = RGB(255, 255, 255);
        hLinePen = CreatePen(PS_SOLID, 7, qLineColor);
        hPenOld = (HPEN)SelectObject(hdc, hLinePen);
        Rectangle(hdc, szerokosc + 25, wysokosc + 2, szerokosc + 15, wysokosc + 2 - a);
        a++;
        Sleep(10);
    }
    ReleaseDC(hWnd, hdc);
}
void zamykanie_drzwi_lewa(int wysokosc, int szerokosc, HWND hWnd, HDC hdc, HPEN hPenOld, HPEN hLinePen, COLORREF qLineColor)
{
    hdc = GetDC(hWnd);
    int a = 0;
    while (a < 90)
    {
        qLineColor = RGB(0, 0, 0);
        hLinePen = CreatePen(PS_SOLID, 6, qLineColor);
        hPenOld = (HPEN)SelectObject(hdc, hLinePen);
        Rectangle(hdc, szerokosc + 17, wysokosc - 82, szerokosc + 15, wysokosc - 85 + a);
        Rectangle(hdc, szerokosc + 25, wysokosc - 82, szerokosc + 26, wysokosc - 85 + a);
        a++;
        Sleep(10);
    }
    ReleaseDC(hWnd, hdc);
}

/*void wchodzenie_do_windy_prawa(vector<int> wchodza, vector<int> pietro, int wysokosc, int szerokosc, int &z, HWND hWnd, HDC hdc, HPEN hPenOld, HPEN hLinePen, COLORREF qLineColor)
{
    hdc = GetDC(hWnd);
    for (int i = 0; i < wchodza.size(); i++)
    {
        if (wchodza[i] == 1)
        {
            qLineColor = RGB(255, 255, 255);
            hLinePen = CreatePen(PS_SOLID, 5, qLineColor);
            hPenOld = (HPEN)SelectObject(hdc, hLinePen);
            Rectangle(hdc, szerokosc + 1 - z + (15 * i), wysokosc, szerokosc + 6 - z + (15 * i), wysokosc - 45);
            qLineColor = RGB(73, 142, 23);
            hLinePen = CreatePen(PS_SOLID, 5, qLineColor);
            hPenOld = (HPEN)SelectObject(hdc, hLinePen);
            Rectangle(hdc, szerokosc - z + (15 * i), wysokosc, szerokosc + 5 - z + (15 * i), wysokosc - 45);
        }
        if (wchodza[i] == 2)
        {
            qLineColor = RGB(255, 255, 255);
            hLinePen = CreatePen(PS_SOLID, 5, qLineColor);
            hPenOld = (HPEN)SelectObject(hdc, hLinePen);
            Rectangle(hdc, szerokosc + 1 - z + (15 * i), wysokosc, szerokosc + 6 - z + (15 * i), wysokosc - 45);
            qLineColor = RGB(87, 542, 0);
            hLinePen = CreatePen(PS_SOLID, 5, qLineColor);
            hPenOld = (HPEN)SelectObject(hdc, hLinePen);
            Rectangle(hdc, szerokosc - z + (15 * i), wysokosc, szerokosc + 5 - z + (15 * i), wysokosc - 45);
        }
        if (wchodza[i] == 3)
        {
            qLineColor = RGB(255, 255, 255);
            hLinePen = CreatePen(PS_SOLID, 5, qLineColor);
            hPenOld = (HPEN)SelectObject(hdc, hLinePen);
            Rectangle(hdc, szerokosc + 1 - z + (15 * i), wysokosc, szerokosc + 6 - z + (15 * i), wysokosc - 45);
            qLineColor = RGB(255, 12, 0);
            hLinePen = CreatePen(PS_SOLID, 5, qLineColor);
            hPenOld = (HPEN)SelectObject(hdc, hLinePen);
            Rectangle(hdc, szerokosc - z + (15 * i), wysokosc, szerokosc + 5 - z + (15 * i), wysokosc - 45);
        }
        if (wchodza[i] == 4)
        {
            qLineColor = RGB(255, 255, 255);
            hLinePen = CreatePen(PS_SOLID, 5, qLineColor);
            hPenOld = (HPEN)SelectObject(hdc, hLinePen);
            Rectangle(hdc, szerokosc + 1 - z + (15 * i), wysokosc, szerokosc + 6 - z + (15 * i), wysokosc - 45);
            qLineColor = RGB(21, 255, 12);
            hLinePen = CreatePen(PS_SOLID, 5, qLineColor);
            hPenOld = (HPEN)SelectObject(hdc, hLinePen);
            Rectangle(hdc, szerokosc - z + (15 * i), wysokosc, szerokosc + 5 - z + (15 * i), wysokosc - 45);
        }
        if (wchodza[i] == 5)
        {
            qLineColor = RGB(255, 255, 255);
            hLinePen = CreatePen(PS_SOLID, 5, qLineColor);
            hPenOld = (HPEN)SelectObject(hdc, hLinePen);
            Rectangle(hdc, szerokosc + 1 - z + (15 * i), wysokosc, szerokosc + 6 - z + (15 * i), wysokosc - 45);
            qLineColor = RGB(255, 25, 436);
            hLinePen = CreatePen(PS_SOLID, 5, qLineColor);
            hPenOld = (HPEN)SelectObject(hdc, hLinePen);
            Rectangle(hdc, szerokosc - z + (15 * i), wysokosc, szerokosc + 5 - z + (15 * i), wysokosc - 45);
        }
    }
    int roz = wchodza.size();
    if (z < 151)
    {
        for (int i = 0; i < pietro.size(); i++)
        {
            if (pietro[i] == 1)
            {
                qLineColor = RGB(255, 255, 255);
                hLinePen = CreatePen(PS_SOLID, 5, qLineColor);
                hPenOld = (HPEN)SelectObject(hdc, hLinePen);
                Rectangle(hdc, szerokosc + 1 - z + (15 * (i + roz)), wysokosc, szerokosc + 6 - z + (15 * (i + roz)), wysokosc - 45);
                qLineColor = RGB(73, 142, 23);
                hLinePen = CreatePen(PS_SOLID, 5, qLineColor);
                hPenOld = (HPEN)SelectObject(hdc, hLinePen);
                Rectangle(hdc, szerokosc - z + (15 * (i + roz)), wysokosc, szerokosc + 5 - z + (15 * (i + roz)), wysokosc - 45);
            }
            if (pietro[i] == 2)
            {
                qLineColor = RGB(255, 255, 255);
                hLinePen = CreatePen(PS_SOLID, 5, qLineColor);
                hPenOld = (HPEN)SelectObject(hdc, hLinePen);
                Rectangle(hdc, szerokosc + 1 - z + (15 * (i + roz)), wysokosc, szerokosc + 6 - z + (15 * (i + roz)), wysokosc - 45);
                qLineColor = RGB(87, 542, 0);
                hLinePen = CreatePen(PS_SOLID, 5, qLineColor);
                hPenOld = (HPEN)SelectObject(hdc, hLinePen);
                Rectangle(hdc, szerokosc - z + (15 * (i + roz)), wysokosc, szerokosc + 5 - z + (15 * (i + roz)), wysokosc - 45);
            }
            if (pietro[i] == 3)
            {
                qLineColor = RGB(255, 255, 255);
                hLinePen = CreatePen(PS_SOLID, 5, qLineColor);
                hPenOld = (HPEN)SelectObject(hdc, hLinePen);
                Rectangle(hdc, szerokosc + 1 - z + (15 * (i + roz)), wysokosc, szerokosc + 6 - z + (15 * (i + roz)), wysokosc - 45);
                qLineColor = RGB(255, 12, 0);
                hLinePen = CreatePen(PS_SOLID, 5, qLineColor);
                hPenOld = (HPEN)SelectObject(hdc, hLinePen);
                Rectangle(hdc, szerokosc - z + (15 * (i + roz)), wysokosc, szerokosc + 5 - z + (15 * (i + roz)), wysokosc - 45);
            }
            if (pietro[i] == 4)
            {
                qLineColor = RGB(255, 255, 255);
                hLinePen = CreatePen(PS_SOLID, 5, qLineColor);
                hPenOld = (HPEN)SelectObject(hdc, hLinePen);
                Rectangle(hdc, szerokosc + 1 - z + (15 * (i + roz)), wysokosc, szerokosc + 6 - z + (15 * (i + roz)), wysokosc - 45);
                qLineColor = RGB(21, 255, 12);
                hLinePen = CreatePen(PS_SOLID, 5, qLineColor);
                hPenOld = (HPEN)SelectObject(hdc, hLinePen);
                Rectangle(hdc, szerokosc - z + (15 * (i + roz)), wysokosc, szerokosc + 5 - z + (15 * (i + roz)), wysokosc - 45);
            }
            if (pietro[i] == 5)
            {
                qLineColor = RGB(255, 255, 255);
                hLinePen = CreatePen(PS_SOLID, 5, qLineColor);
                hPenOld = (HPEN)SelectObject(hdc, hLinePen);
                Rectangle(hdc, szerokosc + 1 - z + (15 * (i + roz)), wysokosc, szerokosc + 6 - z + (15 * (i + roz)), wysokosc - 45);
                qLineColor = RGB(255, 25, 436);
                hLinePen = CreatePen(PS_SOLID, 5, qLineColor);
                hPenOld = (HPEN)SelectObject(hdc, hLinePen);
                Rectangle(hdc, szerokosc - z + (15 * (i + roz)), wysokosc, szerokosc + 5 - z + (15 * (i + roz)), wysokosc - 45);
            }
        }
    }
    z++;
    Sleep(10);
    ReleaseDC(hWnd, hdc);
}*/
/*void wychodzenie_z_windy_lewa(vector<int> winda, vector<int> pietro, int wysokosc,int &x,  int szerokosc, int& polozenie, HWND hWnd, HDC hdc, HPEN hPenOld, HPEN hLinePen, COLORREF qLineColor)
{
    hdc = GetDC(hWnd);
    for (int i = 0; i < winda.size(); i++)
    {
        if (winda[i] == 2)
        {
            qLineColor = RGB(255, 255, 255);
            hLinePen = CreatePen(PS_SOLID, 5, qLineColor);
            hPenOld = (HPEN)SelectObject(hdc, hLinePen);
            Rectangle(hdc, 376 - x + (15 * i), 490, 381 - x + (15 * i), 445);
            qLineColor = RGB(87, 542, 0);
            hLinePen = CreatePen(PS_SOLID, 5, qLineColor);
            hPenOld = (HPEN)SelectObject(hdc, hLinePen);
            Rectangle(hdc, 375 - x + (15 * i), 490, 380 - x + (15 * i), 445);
        }
    }
    x++;
    Sleep(10);
    rysuj_winda(winda, polozenie, wysokosc, szerokosc, hWnd, hdc, hPenOld, hLinePen, qLineColor);
    rysuj_pietro_lewa(pietro, wysokosc, szerokosc, hWnd, hdc, hPenOld, hLinePen, qLineColor);

    qLineColor = RGB(255, 255, 255);
    hLinePen = CreatePen(PS_SOLID, 5, qLineColor);
    hPenOld = (HPEN)SelectObject(hdc, hLinePen);
    Rectangle(hdc, 0, wysokosc, 60, wysokosc - 45);
    ReleaseDC(hWnd, hdc);

}*/