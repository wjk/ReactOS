#include <windows.h>
#include <windowsx.h>
#include <uxtheme.h>
#include <tmschema.h>
#include <string.h>

#define WM_EXIT_THEME_ERROR          WM_USER + 1

static LPWSTR MainWndClass = L"UxThemeTestWindowClass";

const INT SPACING = 6;
const INT TEXT_HEIGHT = 100;

static BOOL expanded = FALSE, hover = FALSE, pressed = FALSE;
static INT expandoWidth, expandoHeight;

static void GetExpandoSizes(HWND hWnd)
{
    if (!IsAppThemed())
    {
        const LPWSTR message = _wcsdup(L"Visual styles must be enabled.");
        PostMessageW(hWnd, WM_EXIT_THEME_ERROR, (WPARAM)message, 0);
        return;
    }

    HTHEME hTheme = OpenThemeData(hWnd, L"TASKDIALOG");
    BOOL error = FALSE;

    HRESULT hr = GetThemeInt(hTheme, TDLG_EXPANDOBUTTON, 0, TMT_WIDTH, &expandoWidth);
    if (FAILED(hr)) error = TRUE;
    hr = GetThemeInt(hTheme, TDLG_EXPANDOBUTTON, 0, TMT_HEIGHT, &expandoHeight);
    if (FAILED(hr)) error = TRUE;

    CloseThemeData(hTheme);

    if (error)
    {
        const LPWSTR message = _wcsdup(L"Could not TDLG_EXPANDOBUTTON width or height");
        PostMessageW(hWnd, WM_EXIT_THEME_ERROR, (WPARAM)message, 0);
    }
}

static LRESULT WINAPI
MainWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_CREATE:
            GetExpandoSizes(hWnd);
            break;

        case WM_THEMECHANGED:
            GetExpandoSizes(hWnd);
            InvalidateRect(hWnd, NULL, TRUE);
            break;

        case WM_PAINT:
            {
                HRESULT hr;
                PAINTSTRUCT ps;
                HDC hDC = BeginPaint(hWnd, &ps);

                HTHEME hTheme = OpenThemeData(hWnd, L"TEXTSTYLE");

                LOGFONTW lf;
                hr = GetThemeFont(hTheme, hDC, TEXT_MAININSTRUCTION, 0, TMT_FONT, &lf);
                if (FAILED(hr))
                {
                    const LPWSTR message = _wcsdup(L"GetThemeFont(TEXT_MAININSTRUCTION) failed");
                    PostMessageW(hWnd, WM_EXIT_THEME_ERROR, (WPARAM)message, 0);
                    EndPaint(hWnd, &ps);
                    break;
                }

                HFONT hFont = CreateFontIndirectW(&lf);

                RECT clientRect;
                GetClientRect(hWnd, &clientRect);

                RECT drawRect;
                drawRect.left = SPACING;
                drawRect.right = clientRect.right - SPACING;
                drawRect.top = SPACING;
                drawRect.bottom = SPACING + TEXT_HEIGHT;

                COLORREF foreColor = GetSysColor(COLOR_BTNTEXT);
                hr = GetThemeColor(hTheme, TEXT_MAININSTRUCTION, 0, TMT_TEXTCOLOR, &foreColor);
                if (FAILED(hr))
                {
                    const LPWSTR message = _wcsdup(L"Could not get TEXT_MAININSTRUCTION text color.");
                    PostMessageW(hWnd, WM_EXIT_THEME_ERROR, (WPARAM)message, 0);
                    EndPaint(hWnd, &ps);
                    break;
                }

                COLORREF oldColor = SetTextColor(hDC, foreColor);
                HFONT hOldFont = SelectObject(hDC, hFont);
                int oldMode = SetBkMode(hDC, TRANSPARENT);
                DrawTextW(hDC, L"This is main instruction text", -1, &drawRect, DT_LEFT | DT_NOPREFIX);
                SelectObject(hDC, hOldFont);
                SetTextColor(hDC, oldColor);
                SetBkMode(hDC, oldMode);
                CloseThemeData(hTheme);

                INT state;
                if (expanded && pressed) state = TDLGEBS_EXPANDEDPRESSED;
                else if (!expanded && pressed) state = TDLGEBS_PRESSED;
                else if (expanded && hover) state = TDLGEBS_EXPANDEDHOVER;
                else if (expanded) state = TDLGEBS_EXPANDEDNORMAL;
                else if (hover) state = TDLGEBS_HOVER;
                else state = TDLGEBS_NORMAL;

                RECT expandoRect;
                expandoRect.top = SPACING + TEXT_HEIGHT + SPACING;
                expandoRect.bottom = expandoRect.top + expandoHeight;
                expandoRect.left = SPACING;
                expandoRect.right = expandoRect.left + expandoWidth;

                hTheme = OpenThemeData(hWnd, L"TASKDIALOG");
                hr = DrawThemeBackground(hTheme, hDC, TDLG_EXPANDOBUTTON, state, &expandoRect, NULL);
                CloseThemeData(hTheme);

                if (FAILED(hr))
                {
                    LPWSTR message;
                    if (expanded && pressed) message = L"DrawThemeBackground(TDLG_EXPANDOBUTTON, TDLGEBS_EXPANDEDPRESSED) failed";
                    else if (!expanded && pressed) message = L"DrawThemeBackground(TDLG_EXPANDOBUTTON, TDLGEBS_PRESSED) failed";
                    else if (expanded && hover) message = L"DrawThemeBackground(TDLG_EXPANDOBUTTON, TDLGEBS_EXPANDEDHOVER) failed";
                    else if (expanded) message = L"DrawThemeBackground(TDLG_EXPANDOBUTTON, TDLGEBS_EXPANDED) failed";
                    else if (hover) message = L"DrawThemeBackground(TDLG_EXPANDOBUTTON, TDLGEBS_HOVER) failed";
                    else message = L"DrawThemeBackground(TDLG_EXPANDOBUTTON, TDLGEBS_NORMAL) failed";

                    message = _wcsdup(message);
                    PostMessageW(hWnd, WM_EXIT_THEME_ERROR, (WPARAM)message, 0);
                }

                EndPaint(hWnd, &ps);
            };
            break;

        case WM_MOUSEMOVE:
            {
                POINT pt;
                pt.x = GET_X_LPARAM(lParam);
                pt.y = GET_Y_LPARAM(lParam);

                RECT expandoRect;
                expandoRect.top = SPACING + TEXT_HEIGHT + SPACING;
                expandoRect.bottom = expandoRect.top + expandoHeight;
                expandoRect.left = SPACING;
                expandoRect.right = expandoRect.left + expandoWidth;

                hover = PtInRect(&expandoRect, pt);
                InvalidateRect(hWnd, NULL, TRUE);
                return 0;
            };
            break;

        case WM_LBUTTONDOWN:
            if (hover)
            {
                pressed = TRUE;
                InvalidateRect(hWnd, NULL, TRUE);
            }

        case WM_LBUTTONUP:
            if (pressed)
            {
                pressed = FALSE;
                expanded = !expanded;
                InvalidateRect(hWnd, NULL, TRUE);
            }
            break;

        case WM_CLOSE:
            DestroyWindow(hWnd);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        case WM_EXIT_THEME_ERROR:
            {
                LPWSTR message = (LPWSTR)wParam;
                MessageBoxW(hWnd, message, L"Error", MB_ICONERROR | MB_OK);
                free(message);

                DestroyWindow(hWnd);
            }
            break;

        default:
            break;
    };

    return DefWindowProcW(hWnd, msg, wParam, lParam);
}

static BOOL
RegisterMainWindowClass(void)
{
    WNDCLASSEX wc;

    wc.cbSize = sizeof(wc);
    wc.lpszClassName = MainWndClass;
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = &MainWndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hCursor = (HICON)LoadImageW(NULL, IDC_ARROW, IMAGE_CURSOR, 0, 0, LR_SHARED);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    return (RegisterClassEx(&wc)) ? TRUE : FALSE;
}

int WINAPI
wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpwszCmdLine, int nCmdShow)
{
    HWND hMainWindow;
    MSG msg;

    if (!IsAppThemed())
    {
        MessageBox(HWND_DESKTOP, L"Visual styles must be enabled.", L"Error", MB_ICONERROR | MB_OK);
        return 0;
    }

    if (!RegisterMainWindowClass())
    {
        MessageBox(HWND_DESKTOP, L"Could not register the main window class.", L"Error", MB_ICONERROR | MB_OK);
        return 0;
    }

    hMainWindow = CreateWindowEx(0, MainWndClass, MainWndClass,
                        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                        CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

    ShowWindow(hMainWindow, nCmdShow);
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    return (int)msg.wParam;
}
