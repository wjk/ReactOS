/*
 * PROJECT:     ReactOS Cicero
 * LICENSE:     LGPL-2.1-or-later (https://spdx.org/licenses/LGPL-2.1-or-later)
 * PURPOSE:     Cicero UIF Library
 * COPYRIGHT:   Copyright 2023 Katayama Hirofumi MZ <katayama.hirofumi.mz@gmail.com>
 */

#pragma once

#include "cicarray.h"

// This is Cicero UIF Library to support the IME UI interface.
// Cicero UIF Library implements some GUI parts for IMEs and Language Bar.
// The GUI parts of UIF Library requires special handling because:
//
// 1. To avoid interfering with IME input, the GUI part should not receive focus.
// 2. The IME popup window has WS_DISABLED style, so it cannot receive mouse messages
//    directly.

class CUIFSystemInfo;
class CUIFTheme;
    class CUIFObject;
        class CUIFWindow;
            class CUIFToolTip;
            class CUIFShadow;
            class CUIFBalloonWindow;
        class CUIFButton;
            class CUIFButton2;
                class CUIFToolbarMenuButton;
                class CUIFToolbarButtonElement;
            class CUIFBalloonButton;
        class CUIFToolbarButton;
        class CUIFWndFrame;
        class CUIFGripper;
class CUIFObjectArray;
class CUIFColorTable;
    class CUIFColorTableSys;
    class CUIFColorTableOff10;
class CUIFBitmapDC;
class CUIFIcon;
class CUIFSolidBrush;
class CUIFScheme;

/////////////////////////////////////////////////////////////////////////////

class CUIFSystemInfo : OSVERSIONINFO
{
public:
    static CUIFSystemInfo *s_pSystemInfo;
    DWORD m_cBitsPixels;
    BOOL m_bHighContrast1;
    BOOL m_bHighContrast2;

    CUIFSystemInfo();
    void GetSystemMetrics();
    void Initialize();
};

DECLSPEC_SELECTANY CUIFSystemInfo *CUIFSystemInfo::s_pSystemInfo = NULL;

void cicInitUIFSys(void);
void cicDoneUIFSys(void);
void cicUpdateUIFSys(void);

/////////////////////////////////////////////////////////////////////////////

#include <uxtheme.h>
#include <vsstyle.h>

// uxtheme.dll
using FN_OpenThemeData = decltype(&OpenThemeData);
using FN_CloseThemeData = decltype(&CloseThemeData);
using FN_DrawThemeBackground = decltype(&DrawThemeBackground);
using FN_DrawThemeParentBackground = decltype(&DrawThemeParentBackground);
using FN_DrawThemeText = decltype(&DrawThemeText);
using FN_DrawThemeIcon = decltype(&DrawThemeIcon);
using FN_GetThemeBackgroundExtent = decltype(&GetThemeBackgroundExtent);
using FN_GetThemeBackgroundContentRect = decltype(&GetThemeBackgroundContentRect);
using FN_GetThemeTextExtent = decltype(&GetThemeTextExtent);
using FN_GetThemePartSize = decltype(&GetThemePartSize);
using FN_DrawThemeEdge = decltype(&DrawThemeEdge);
using FN_GetThemeColor = decltype(&GetThemeColor);
using FN_GetThemeMargins = decltype(&GetThemeMargins);
using FN_GetThemeFont = decltype(&GetThemeFont);
using FN_GetThemeSysColor = decltype(&GetThemeSysColor);
using FN_GetThemeSysSize = decltype(&GetThemeSysSize);

/////////////////////////////////////////////////////////////////////////////

class CUIFTheme
{
public:
    LPCWSTR m_pszClassList;
    INT m_iPartId;
    INT m_iStateId;
    HTHEME m_hTheme;
    static HINSTANCE s_hUXTHEME;
    static FN_OpenThemeData s_fnOpenThemeData;
    static FN_CloseThemeData s_fnCloseThemeData;
    static FN_DrawThemeBackground s_fnDrawThemeBackground;
    static FN_DrawThemeParentBackground s_fnDrawThemeParentBackground;
    static FN_DrawThemeText s_fnDrawThemeText;
    static FN_DrawThemeIcon s_fnDrawThemeIcon;
    static FN_GetThemeBackgroundExtent s_fnGetThemeBackgroundExtent;
    static FN_GetThemeBackgroundContentRect s_fnGetThemeBackgroundContentRect;
    static FN_GetThemeTextExtent s_fnGetThemeTextExtent;
    static FN_GetThemePartSize s_fnGetThemePartSize;
    static FN_DrawThemeEdge s_fnDrawThemeEdge;
    static FN_GetThemeColor s_fnGetThemeColor;
    static FN_GetThemeMargins s_fnGetThemeMargins;
    static FN_GetThemeFont s_fnGetThemeFont;
    static FN_GetThemeSysColor s_fnGetThemeSysColor;
    static FN_GetThemeSysSize s_fnGetThemeSysSize;

    HRESULT InternalOpenThemeData(HWND hWnd);
    HRESULT EnsureThemeData(HWND hWnd);
    HRESULT CloseThemeData();

    STDMETHOD(DrawThemeBackground)(HDC hDC, int iStateId, LPCRECT pRect, LPCRECT pClipRect);
    STDMETHOD(DrawThemeParentBackground)(HWND hwnd, HDC hDC, LPRECT prc);
    STDMETHOD(DrawThemeText)(HDC hDC, int iStateId, LPCWSTR pszText, int cchText, DWORD dwTextFlags, DWORD dwTextFlags2, LPCRECT pRect);
    STDMETHOD(DrawThemeIcon)(HDC hDC, int iStateId, LPCRECT pRect, HIMAGELIST himl, int iImageIndex);
    STDMETHOD(GetThemeBackgroundExtent)(HDC hDC, int iStateId, LPCRECT pContentRect, LPRECT pExtentRect);
    STDMETHOD(GetThemeBackgroundContentRect)(HDC hDC, int iStateId, LPCRECT pBoundingRect, LPRECT pContentRect);
    STDMETHOD(GetThemeTextExtent)(HDC hDC, int iStateId, LPCWSTR pszText, int cchCharCount, DWORD dwTextFlags, LPCRECT pBoundingRect, LPRECT pExtentRect);
    STDMETHOD(GetThemePartSize)(HDC hDC, int iStateId, LPRECT prc, THEMESIZE eSize, SIZE *psz);
    STDMETHOD(DrawThemeEdge)(HDC hDC, int iStateId, LPCRECT pDestRect, UINT uEdge, UINT uFlags, LPRECT pContentRect);
    STDMETHOD(GetThemeColor)(int iStateId, int iPropId, COLORREF *pColor);
    STDMETHOD(GetThemeMargins)(HDC hDC, int iStateId, int iPropId, LPRECT prc, MARGINS *pMargins);
    STDMETHOD(GetThemeFont)(HDC hDC, int iStateId, int iPropId, LOGFONTW *pFont);
    STDMETHOD_(COLORREF, GetThemeSysColor)(INT iColorId);
    STDMETHOD_(int, GetThemeSysSize)(int iSizeId);
    STDMETHOD_(void, SetActiveTheme)(LPCWSTR pszClassList, INT iPartId, INT iStateId);
};

// static members
DECLSPEC_SELECTANY HINSTANCE CUIFTheme::s_hUXTHEME = NULL;
DECLSPEC_SELECTANY FN_OpenThemeData CUIFTheme::s_fnOpenThemeData = NULL;
DECLSPEC_SELECTANY FN_CloseThemeData CUIFTheme::s_fnCloseThemeData = NULL;
DECLSPEC_SELECTANY FN_DrawThemeBackground CUIFTheme::s_fnDrawThemeBackground = NULL;
DECLSPEC_SELECTANY FN_DrawThemeParentBackground CUIFTheme::s_fnDrawThemeParentBackground = NULL;
DECLSPEC_SELECTANY FN_DrawThemeText CUIFTheme::s_fnDrawThemeText = NULL;
DECLSPEC_SELECTANY FN_DrawThemeIcon CUIFTheme::s_fnDrawThemeIcon = NULL;
DECLSPEC_SELECTANY FN_GetThemeBackgroundExtent CUIFTheme::s_fnGetThemeBackgroundExtent = NULL;
DECLSPEC_SELECTANY FN_GetThemeBackgroundContentRect CUIFTheme::s_fnGetThemeBackgroundContentRect = NULL;
DECLSPEC_SELECTANY FN_GetThemeTextExtent CUIFTheme::s_fnGetThemeTextExtent = NULL;
DECLSPEC_SELECTANY FN_GetThemePartSize CUIFTheme::s_fnGetThemePartSize = NULL;
DECLSPEC_SELECTANY FN_DrawThemeEdge CUIFTheme::s_fnDrawThemeEdge = NULL;
DECLSPEC_SELECTANY FN_GetThemeColor CUIFTheme::s_fnGetThemeColor = NULL;
DECLSPEC_SELECTANY FN_GetThemeMargins CUIFTheme::s_fnGetThemeMargins = NULL;
DECLSPEC_SELECTANY FN_GetThemeFont CUIFTheme::s_fnGetThemeFont = NULL;
DECLSPEC_SELECTANY FN_GetThemeSysColor CUIFTheme::s_fnGetThemeSysColor = NULL;
DECLSPEC_SELECTANY FN_GetThemeSysSize CUIFTheme::s_fnGetThemeSysSize = NULL;

/////////////////////////////////////////////////////////////////////////////

class CUIFObjectArray : public CicArray<CUIFObject*>
{
public:
    CUIFObjectArray() { }

    BOOL Add(CUIFObject *pObject)
    {
        if (!pObject || Find(pObject) >= 0)
            return FALSE;

        CUIFObject **ppNew = Append(1);
        if (!ppNew)
            return FALSE;

        *ppNew = pObject;
        return TRUE;
    }

    BOOL Remove(CUIFObject *pObject)
    {
        if (!pObject)
            return FALSE;

        ssize_t iItem = Find(pObject);
        if (iItem < 0)
            return FALSE;

        if (size_t(iItem) + 1 < size())
            MoveMemory(&data()[iItem], &data()[iItem + 1],
                       (size() - (iItem + 1)) * sizeof(CUIFObject*));

        --m_cItems;
        return TRUE;
    }

    CUIFObject *GetLast() const
    {
        if (empty())
            return NULL;
        return (*this)[size() - 1];
    }
};

/////////////////////////////////////////////////////////////////////////////

class CUIFObject : public CUIFTheme
{
protected:
    CUIFObject *m_pParent;
    CUIFWindow *m_pWindow;
    CUIFScheme *m_pScheme;
    CUIFObjectArray m_ObjectArray;
    DWORD m_nObjectID;
    DWORD m_style;
    RECT m_rc;
    BOOL m_bEnable;
    BOOL m_bVisible;
    HFONT m_hFont;
    BOOL m_bHasCustomFont;
    LPWSTR m_pszToolTip;
    DWORD m_dwUnknown4[2]; //FIXME: name and type
    friend class CUIFWindow;
    friend class CUIFToolTip;
    friend class CUIFBalloonWindow;

public:
    CUIFObject(CUIFObject *pParent, DWORD nObjectID, LPCRECT prc, DWORD style);
    virtual ~CUIFObject();

    void StartCapture();
    void EndCapture();
    BOOL IsCapture();
    BOOL IsRTL();
    LRESULT NotifyCommand(WPARAM wParam, LPARAM lParam);
    CUIFObject* ObjectFromPoint(POINT pt);
    void SetScheme(CUIFScheme *scheme);

    STDMETHOD_(void, Initialize)();
    STDMETHOD_(void, OnPaint)(HDC hDC);
    STDMETHOD_(void, OnUnknown9)() { } // FIXME: name
    STDMETHOD_(void, OnLButtonDown)(LONG x, LONG y) { }
    STDMETHOD_(void, OnMButtonDown)(LONG x, LONG y) { }
    STDMETHOD_(void, OnRButtonDown)(LONG x, LONG y) { }
    STDMETHOD_(void, OnLButtonUp)(LONG x, LONG y) { }
    STDMETHOD_(void, OnMButtonUp)(LONG x, LONG y) { }
    STDMETHOD_(void, OnRButtonUp)(LONG x, LONG y) { }
    STDMETHOD_(void, OnMouseMove)(LONG x, LONG y) { }
    STDMETHOD_(void, OnMouseIn)(LONG x, LONG y) { }
    STDMETHOD_(void, OnMouseOut)(LONG x, LONG y) { }
    STDMETHOD_(BOOL, OnSetCursor)(UINT uMsg, LONG x, LONG y);
    STDMETHOD_(void, GetRect)(LPRECT prc);
    STDMETHOD_(void, SetRect)(LPCRECT prc);
    STDMETHOD_(BOOL, PtInObject)(POINT pt);
    STDMETHOD_(void, PaintObject)(HDC hDC, LPCRECT prc);
    STDMETHOD_(void, CallOnPaint)();
    STDMETHOD_(void, Enable)(BOOL bEnable);
    STDMETHOD_(void, Show)(BOOL bVisible);
    STDMETHOD_(void, SetFontToThis)(HFONT hFont);
    STDMETHOD_(void, SetFont)(HFONT hFont);
    STDMETHOD_(void, SetStyle)(DWORD style);
    STDMETHOD_(void, AddUIObj)(CUIFObject *pObject);
    STDMETHOD_(void, RemoveUIObj)(CUIFObject *pObject);
    STDMETHOD_(LRESULT, OnObjectNotify)(CUIFObject *pObject, WPARAM wParam, LPARAM lParam);
    STDMETHOD_(void, SetToolTip)(LPCWSTR pszToolTip);
    STDMETHOD_(LPCWSTR, GetToolTip)();
    STDMETHOD_(LRESULT, OnShowToolTip)();
    STDMETHOD_(void, OnHideToolTip)() { }
    STDMETHOD_(void, DetachWndObj)();
    STDMETHOD_(void, ClearWndObj)();
    STDMETHOD_(BOOL, OnPaintTheme)(HDC hDC);
    STDMETHOD_(void, OnPaintNoTheme)(HDC hDC);
    STDMETHOD_(void, ClearTheme)();
};

/////////////////////////////////////////////////////////////////////////////

class CUIFColorTable
{
public:
    CUIFColorTable() { }
    virtual ~CUIFColorTable() { }

    STDMETHOD_(void, InitColor)() = 0;
    STDMETHOD_(void, DoneColor)() { }
    STDMETHOD_(void, InitBrush)() = 0;
    STDMETHOD_(void, DoneBrush)() = 0;

    void Update()
    {
        DoneColor();
        DoneBrush();
        InitColor();
        InitBrush();
    }
};

class CUIFColorTableSys : public CUIFColorTable
{
protected:
    COLORREF m_rgbColors[16];
    HBRUSH m_hBrushes[16];

public:
    CUIFColorTableSys() { }

    COLORREF GetColor(INT iColor) const { return m_rgbColors[iColor]; }
    HBRUSH GetBrush(INT iColor);

    STDMETHOD_(void, InitColor)() override;
    STDMETHOD_(void, InitBrush)() override;
    STDMETHOD_(void, DoneBrush)() override;
};

class CUIFColorTableOff10 : public CUIFColorTable
{
protected:
    COLORREF m_rgbColors[32];
    HBRUSH m_hBrushes[32];

public:
    CUIFColorTableOff10() { }

    COLORREF GetColor(INT iColor) const { return m_rgbColors[iColor]; }
    HBRUSH GetBrush(INT iColor);

    STDMETHOD_(void, InitColor)() override;
    STDMETHOD_(void, InitBrush)() override;
    STDMETHOD_(void, DoneBrush)() override;
};

/////////////////////////////////////////////////////////////////////////////

class CUIFSolidBrush
{
public:
    HBRUSH m_hBrush;

    operator HBRUSH() const { return m_hBrush; }

    CUIFSolidBrush(COLORREF rgbColor)
    {
        m_hBrush = ::CreateSolidBrush(rgbColor);
    }
    ~CUIFSolidBrush()
    {
        if (m_hBrush)
        {
            ::DeleteObject(m_hBrush);
            m_hBrush = NULL;
        }
    }
};

/////////////////////////////////////////////////////////////////////////////

class CUIFIcon
{
public:
    HICON m_hIcon;
    HIMAGELIST m_hImageList;

    CUIFIcon& operator=(HICON hIcon)
    {
        m_hIcon = hIcon;
        if (m_hImageList)
        {
            ImageList_Destroy(m_hImageList);
            m_hImageList = NULL;
        }
        return *this;
    }

    HIMAGELIST GetImageList(BOOL bMirror);
};

BOOL cicGetIconSize(HICON hIcon, LPSIZE pSize);

/////////////////////////////////////////////////////////////////////////////

class CUIFBitmapDC
{
protected:
    HBITMAP m_hBitmap;
    HGDIOBJ m_hOldBitmap;
    HGDIOBJ m_hOldObject;
    HDC m_hDC;

public:
    static BOOL s_fInitBitmapDCs;
    static CUIFBitmapDC *s_phdcSrc;
    static CUIFBitmapDC *s_phdcMask;
    static CUIFBitmapDC *s_phdcDst;

    CUIFBitmapDC(BOOL bMemory);
    ~CUIFBitmapDC();
    operator HDC() const { return m_hDC; }

    void Uninit(BOOL bKeep = FALSE);

    BOOL SetBitmap(HBITMAP hBitmap);
    BOOL SetBitmap(LONG cx, LONG cy, WORD cPlanes, WORD cBitCount);
    BOOL SetDIB(LONG cx, LONG cy, WORD cPlanes, WORD cBitCount);

    HBITMAP DetachBitmap()
    {
        HBITMAP hOldBitmap = m_hBitmap;
        m_hBitmap = NULL;
        return hOldBitmap;
    }
};

DECLSPEC_SELECTANY BOOL CUIFBitmapDC::s_fInitBitmapDCs = FALSE;
DECLSPEC_SELECTANY CUIFBitmapDC *CUIFBitmapDC::s_phdcSrc = NULL;
DECLSPEC_SELECTANY CUIFBitmapDC *CUIFBitmapDC::s_phdcMask = NULL;
DECLSPEC_SELECTANY CUIFBitmapDC *CUIFBitmapDC::s_phdcDst = NULL;

void cicInitUIFUtil(void);
void cicDoneUIFUtil(void);

HBITMAP cicMirrorBitmap(HBITMAP hBitmap, HBRUSH hbrBack);
HBRUSH cicCreateDitherBrush(VOID);
HBITMAP cicCreateDisabledBitmap(LPCRECT prc, HBITMAP hbmMask, HBRUSH hbr1, HBRUSH hbr2,
                                BOOL bPressed);
HBITMAP cicCreateShadowMaskBmp(LPRECT prc, HBITMAP hbm1, HBITMAP hbm2, HBRUSH hbr1, HBRUSH hbr2);
HBITMAP cicChangeBitmapColor(LPCRECT prc, HBITMAP hbm, COLORREF rgbBack, COLORREF rgbFore);
HBITMAP cicConvertBlackBKGBitmap(LPCRECT prc, HBITMAP hbm1, HBITMAP hbm2, HBRUSH hBrush);
HBITMAP cicCreateMaskBmp(LPCRECT prc, HBITMAP hbm1, HBITMAP hbm2, HBRUSH hbr,
                         COLORREF rgbColor, COLORREF rgbBack);
BOOL cicGetIconBitmaps(HICON hIcon, HBITMAP *hbm1, HBITMAP *hbm2, const SIZE *pSize);

/////////////////////////////////////////////////////////////////////////////

// Flags for dwDrawFlags
enum
{
    UIF_DRAW_PRESSED = 0x10,
    UIF_DRAW_DISABLED = 0x20,
};

class CUIFScheme
{
public:
    static CUIFColorTableSys *s_pColorTableSys;
    static CUIFColorTableOff10 *s_pColorTableOff10;
    BOOL m_bMirroring;

    CUIFScheme() : m_bMirroring(FALSE) { }
    virtual ~CUIFScheme() { }

    STDMETHOD_(DWORD, GetType)() = 0;
    STDMETHOD_(COLORREF, GetColor)(INT iColor) = 0;
    STDMETHOD_(HBRUSH, GetBrush)(INT iColor) = 0;
    STDMETHOD_(INT, CyMenuItem)(INT cyText) = 0;
    STDMETHOD_(INT, CxSizeFrame)() = 0;
    STDMETHOD_(INT, CySizeFrame)() = 0;
    STDMETHOD_(INT, CxWndBorder)() = 0;
    STDMETHOD_(INT, CyWndBorder)() = 0;
    STDMETHOD_(void, FillRect)(HDC hDC, LPCRECT prc, INT iColor);
    STDMETHOD_(void, FrameRect)(HDC hDC, LPCRECT prc, INT iColor);
    STDMETHOD_(void, DrawSelectionRect)(HDC hDC, LPCRECT prc, int) = 0;
    STDMETHOD_(INT, GetCtrlFaceOffset)(DWORD, DWORD dwDrawFlags, LPSIZE pSize) = 0;
    STDMETHOD_(void, DrawCtrlBkgd)(HDC hDC, LPCRECT prc, DWORD dwUnknownFlags, DWORD dwDrawFlags) = 0;
    STDMETHOD_(void, DrawCtrlEdge)(HDC hDC, LPCRECT prc, DWORD dwUnknownFlags, DWORD dwDrawFlags) = 0;
    STDMETHOD_(void, DrawCtrlText)(HDC hDC, LPCRECT prc, LPCWSTR pszText, INT cchText, DWORD dwDrawFlags, BOOL bRight) = 0;
    STDMETHOD_(void, DrawCtrlIcon)(HDC hDC, LPCRECT prc, HICON hIcon, DWORD dwDrawFlags, LPSIZE pSize) = 0;
    STDMETHOD_(void, DrawCtrlBitmap)(HDC hDC, LPCRECT prc, HBITMAP hbm1, HBITMAP hbm2, DWORD dwDrawFlags) = 0;
    STDMETHOD_(void, DrawMenuBitmap)(HDC hDC, LPCRECT prc, HBITMAP hbm1, HBITMAP hbm2, DWORD dwDrawFlags) = 0;
    STDMETHOD_(void, DrawMenuSeparator)(HDC hDC, LPCRECT prc) = 0;
    STDMETHOD_(void, DrawFrameCtrlBkgd)(HDC hDC, LPCRECT prc, DWORD dwUnknownFlags, DWORD dwDrawFlags) = 0;
    STDMETHOD_(void, DrawFrameCtrlEdge)(HDC hDC, LPCRECT prc, DWORD dwUnknownFlags, DWORD dwDrawFlags) = 0;
    STDMETHOD_(void, DrawFrameCtrlIcon)(HDC hDC, LPCRECT prc, HICON hIcon, DWORD dwDrawFlags, LPSIZE pSize) = 0;
    STDMETHOD_(void, DrawFrameCtrlBitmap)(HDC hDC, LPCRECT prc, HBITMAP hbm1, HBITMAP hbm2, DWORD dwDrawFlags) = 0;
    STDMETHOD_(void, DrawWndFrame)(HDC hDC, LPCRECT prc, DWORD type, DWORD unused1, DWORD unused2) = 0;
    STDMETHOD_(void, DrawDragHandle)(HDC hDC, LPCRECT prc, BOOL bVertical) = 0;
    STDMETHOD_(void, DrawSeparator)(HDC hDC, LPCRECT prc, BOOL bVertical) = 0;
};

class CUIFSchemeDef : public CUIFScheme
{
protected:
    DWORD m_dwType;

public:
    CUIFSchemeDef(DWORD dwType) : m_dwType(dwType) { }

    STDMETHOD_(DWORD, GetType)() override;
    STDMETHOD_(COLORREF, GetColor)(INT iColor) override;
    STDMETHOD_(HBRUSH, GetBrush)(INT iColor) override;
    STDMETHOD_(INT, CyMenuItem)(INT cyText) override;
    STDMETHOD_(INT, CxSizeFrame)() override;
    STDMETHOD_(INT, CySizeFrame)() override;
    STDMETHOD_(INT, CxWndBorder)() override;
    STDMETHOD_(INT, CyWndBorder)() override;
    STDMETHOD_(void, DrawSelectionRect)(HDC hDC, LPCRECT prc, int) override;
    STDMETHOD_(INT, GetCtrlFaceOffset)(DWORD, DWORD dwDrawFlags, LPSIZE pSize) override;
    STDMETHOD_(void, DrawCtrlBkgd)(HDC hDC, LPCRECT prc, DWORD dwUnknownFlags, DWORD dwDrawFlags) override;
    STDMETHOD_(void, DrawCtrlEdge)(HDC hDC, LPCRECT prc, DWORD dwUnknownFlags, DWORD dwDrawFlags) override;
    STDMETHOD_(void, DrawCtrlText)(HDC hDC, LPCRECT prc, LPCWSTR pszText, INT cchText, DWORD dwDrawFlags, BOOL bRight) override;
    STDMETHOD_(void, DrawCtrlIcon)(HDC hDC, LPCRECT prc, HICON hIcon, DWORD dwDrawFlags, LPSIZE pSize) override;
    STDMETHOD_(void, DrawCtrlBitmap)(HDC hDC, LPCRECT prc, HBITMAP hbm1, HBITMAP hbm2, DWORD dwDrawFlags) override;
    STDMETHOD_(void, DrawMenuBitmap)(HDC hDC, LPCRECT prc, HBITMAP hbm1, HBITMAP hbm2, DWORD dwDrawFlags) override;
    STDMETHOD_(void, DrawMenuSeparator)(HDC hDC, LPCRECT prc) override;
    STDMETHOD_(void, DrawFrameCtrlBkgd)(HDC hDC, LPCRECT prc, DWORD dwUnknownFlags, DWORD dwDrawFlags) override;
    STDMETHOD_(void, DrawFrameCtrlEdge)(HDC hDC, LPCRECT prc, DWORD dwUnknownFlags, DWORD dwDrawFlags) override;
    STDMETHOD_(void, DrawFrameCtrlIcon)(HDC hDC, LPCRECT prc, HICON hIcon, DWORD dwDrawFlags, LPSIZE pSize) override;
    STDMETHOD_(void, DrawFrameCtrlBitmap)(HDC hDC, LPCRECT prc, HBITMAP hbm1, HBITMAP hbm2, DWORD dwDrawFlags) override;
    STDMETHOD_(void, DrawWndFrame)(HDC hDC, LPCRECT prc, DWORD type, DWORD unused1, DWORD unused2) override;
    STDMETHOD_(void, DrawDragHandle)(HDC hDC, LPCRECT prc, BOOL bVertical) override;
    STDMETHOD_(void, DrawSeparator)(HDC hDC, LPCRECT prc, BOOL bVertical) override;
};

DECLSPEC_SELECTANY CUIFColorTableSys *CUIFScheme::s_pColorTableSys = NULL;
DECLSPEC_SELECTANY CUIFColorTableOff10 *CUIFScheme::s_pColorTableOff10 = NULL;

void cicInitUIFScheme(void);
void cicUpdateUIFScheme(void);
void cicDoneUIFScheme(void);
CUIFScheme *cicCreateUIFScheme(DWORD type);

/////////////////////////////////////////////////////////////////////////////

// m_style flags for CUIFWindow
enum
{
    UIF_WINDOW_CHILD = 0x1,
    UIF_WINDOW_TOPMOST = 0x2,
    UIF_WINDOW_TOOLWINDOW = 0x4,
    UIF_WINDOW_DLGFRAME = 0x8,
    UIF_WINDOW_TOOLTIP = 0x20,
    UIF_WINDOW_SHADOW = 0x40,
    UIF_WINDOW_WORKAREA = 0x80,
    UIF_WINDOW_MONITOR = 0x100,
    UIF_WINDOW_LAYOUTRTL = 0x200,
    UIF_WINDOW_NOMOUSEMSG = 0x400,
    UIF_WINDOW_ENABLETHEMED = 0x80000000,
};

class CUIFWindow : public CUIFObject
{
protected:
    INT m_nLeft;
    INT m_nTop;
    INT m_nHeight;
    INT m_nWidth;
    HINSTANCE m_hInst;
    HWND m_hWnd;
    CUIFWindow *m_pUnknown7;
    CUIFObject *m_pCaptured;
    CUIFObject *m_pPointed;
    BOOL m_bPointing;
    CUIFWindow *m_pPointingWindow;
    CUIFToolTip *m_pToolTip;
    CUIFShadow *m_pShadow;
    BOOL m_bShowShadow;
    friend class CUIFObject;
    friend class CUIFShadow;
    friend class CUIFToolTip;
    friend class CUIFButton;

public:
    enum { POINTING_TIMER_ID = 0x7982 };
    operator HWND() const { return m_hWnd; }
    CUIFWindow(HINSTANCE hInst, DWORD style);
    ~CUIFWindow() override;

    static CUIFWindow* GetThis(HWND hWnd);
    static void SetThis(HWND hWnd, LONG_PTR dwNewLong);

    STDMETHOD_(void, Initialize)() override;
    STDMETHOD_(void, Show)(BOOL bVisible) override;
    STDMETHOD_(void, SetRect)(LPCRECT prc) override;
    STDMETHOD_(void, PaintObject)(HDC hDC, LPCRECT prc) override;
    STDMETHOD_(void, RemoveUIObj)(CUIFObject *pRemove) override;

    void SetCaptureObject(CUIFObject *pCaptured);
    void SetObjectPointed(CUIFObject *pPointed, POINT pt);
    void CreateScheme();
    BOOL GetWorkArea(LPCRECT prcWnd, LPRECT prcWorkArea);
    void AdjustWindowPosition();

    static LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    STDMETHOD_(LPCTSTR, GetClassName)();
    STDMETHOD_(LPCTSTR, GetWndTitle)();
    STDMETHOD_(DWORD, GetWndStyle)();
    STDMETHOD_(DWORD, GetWndStyleEx)();
    STDMETHOD_(HWND, CreateWnd)(HWND hwndParent);
    STDMETHOD_(void, Move)(INT x, INT y, INT nWidth, INT nHeight);
    STDMETHOD_(BOOL, AnimateWnd)(DWORD dwTime, DWORD dwFlags);
    STDMETHOD_(void, OnObjectMoved)(CUIFObject *pObject);
    STDMETHOD_(void, OnPointingEnded)(LONG x, LONG y);
    STDMETHOD_(void, OnCreate)(HWND hWnd);
    STDMETHOD_(void, OnDestroy)(HWND hWnd);
    STDMETHOD_(void, OnNCDestroy)(HWND hWnd);
    STDMETHOD_(void, OnSetFocus)(HWND hWnd);
    STDMETHOD_(void, OnKillFocus)(HWND hWnd);
    STDMETHOD_(void, OnNotify)(HWND hWnd, WPARAM wParam, LPARAM lParam);
    STDMETHOD_(void, OnTimer)(WPARAM wParam);
    STDMETHOD_(void, OnSysColorChange)();
    STDMETHOD_(void, OnEndSession)(HWND hWnd, WPARAM wParam, LPARAM lParam);
    STDMETHOD_(void, OnKeyDown)(HWND hWnd, WPARAM wParam, LPARAM lParam);
    STDMETHOD_(void, OnKeyUp)(HWND, WPARAM wParam, LPARAM lParam);
    STDMETHOD_(void, OnUser)(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    STDMETHOD_(LRESULT, OnActivate)(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    STDMETHOD_(LRESULT, OnWindowPosChanged)(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    STDMETHOD_(LRESULT, OnWindowPosChanging)(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    STDMETHOD_(LRESULT, OnNotifyFormat)(HWND hWnd, WPARAM wParam, LPARAM lParam);
    STDMETHOD_(LRESULT, OnShowWindow)(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    STDMETHOD_(LRESULT, OnSettingChange)(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    STDMETHOD_(LRESULT, OnDisplayChange)(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    STDMETHOD_(LRESULT, OnGetObject)(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    STDMETHOD_(LRESULT, WindowProc)(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    STDMETHOD_(BOOL, OnEraseBkGnd)(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    STDMETHOD_(void, OnThemeChanged)(HWND hWnd, WPARAM wParam, LPARAM lParam);
    STDMETHOD_(void, UpdateUI)(LPCRECT prc);
    STDMETHOD_(void, SetCapture)(int);
    STDMETHOD_(void, OnPointingMouse)(UINT uMsg, LONG x, LONG y);
    STDMETHOD_(void, OnAnimationStart)();
    STDMETHOD_(void, OnAnimationEnd)();
    STDMETHOD_(void, HandleMouseMsg)(UINT uMsg, LONG x, LONG y);
    STDMETHOD_(void, ClientRectToWindowRect)(LPRECT pRect);
    STDMETHOD_(void, GetWindowFrameSize)(LPSIZE pSize);
};

/////////////////////////////////////////////////////////////////////////////

class CUIFToolTip : public CUIFWindow
{
protected:
    CUIFWindow *m_pToolTipOwner;
    CUIFObject *m_pToolTipTarget;
    LPWSTR m_pszToolTipText;
    BOOL m_bShowToolTip;
    DWORD m_dwUnknown10; //FIXME: name and type
    LONG m_nDelayTimeType2;
    LONG m_nDelayTimeType3;
    LONG m_nDelayTimeType1;
    RECT m_rcToolTipMargin;
    LONG m_cxToolTipWidth;
    BOOL m_bToolTipHasBkColor;
    BOOL m_bToolTipHasTextColor;
    COLORREF m_rgbToolTipBkColor;
    COLORREF m_rgbToolTipTextColor;
    friend class CUIFObject;

public:
    enum { TOOLTIP_TIMER_ID = 0x3216 };
    CUIFToolTip(HINSTANCE hInst, DWORD style, CUIFWindow *pToolTipOwner);
    ~CUIFToolTip() override;

    LONG GetDelayTime(UINT uType);
    void GetMargin(LPRECT prc);
    COLORREF GetTipBkColor();
    COLORREF GetTipTextColor();
    CUIFObject* FindObject(HWND hWnd, POINT pt);

    void ShowTip();
    void HideTip();

    void GetTipWindowSize(LPSIZE pSize);
    void GetTipWindowRect(LPRECT pRect, SIZE toolTipSize, LPCRECT prc);

    void RelayEvent(LPMSG pMsg);

    STDMETHOD_(void, OnPaint)(HDC hDC) override;
    STDMETHOD_(void, Enable)(BOOL bEnable) override;
    STDMETHOD_(void, OnTimer)(WPARAM wParam) override;
};

class CUIFShadow : public CUIFWindow
{
protected:
    CUIFWindow *m_pShadowOwner;
    COLORREF m_rgbShadowColor;
    DWORD m_dwUnknown11[2];
    INT m_xShadowDelta;
    INT m_yShadowDelta;
    BOOL m_bLayerAvailable;

public:
    CUIFShadow(HINSTANCE hInst, DWORD style, CUIFWindow *pShadowOwner);
    ~CUIFShadow() override;

    void InitSettings();
    void InitShadow();
    void AdjustWindowPos();
    void OnOwnerWndMoved(BOOL bDoSize);

    STDMETHOD_(void, Initialize)() override;
    STDMETHOD_(DWORD, GetWndStyleEx)() override;
    STDMETHOD_(void, OnPaint)(HDC hDC) override;
    STDMETHOD_(LRESULT, OnWindowPosChanging)(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) override;
    STDMETHOD_(LRESULT, OnSettingChange)(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) override;
    STDMETHOD_(void, Show)(BOOL bVisible) override;
};

/////////////////////////////////////////////////////////////////////////////

// m_style flags for CUIFButton
enum
{
    UIF_BUTTON_H_ALIGN_LEFT = 0,
    UIF_BUTTON_H_ALIGN_CENTER = 0x1,
    UIF_BUTTON_H_ALIGN_RIGHT = 0x2,
    UIF_BUTTON_H_ALIGN_MASK = UIF_BUTTON_H_ALIGN_CENTER | UIF_BUTTON_H_ALIGN_RIGHT,
    UIF_BUTTON_V_ALIGN_TOP = 0,
    UIF_BUTTON_V_ALIGN_MIDDLE = 0x4,
    UIF_BUTTON_V_ALIGN_BOTTOM = 0x8,
    UIF_BUTTON_V_ALIGN_MASK = UIF_BUTTON_V_ALIGN_MIDDLE | UIF_BUTTON_V_ALIGN_BOTTOM,
    UIF_BUTTON_LARGE_ICON = 0x100,
    UIF_BUTTON_VERTICAL = 0x400,
};

class CUIFButton : public CUIFObject
{
protected:
    UINT m_uButtonStatus;
    LPWSTR m_pszButtonText;
    CUIFIcon m_ButtonIcon;
    DWORD m_dwUnknown9;
    HBITMAP m_hbmButton1;
    HBITMAP m_hbmButton2;
    BOOL m_bPressed;
    SIZE m_IconSize;
    SIZE m_TextSize;
    friend class CUIFToolbarButton;

    void DrawBitmapProc(HDC hDC, LPCRECT prc, BOOL bPressed);
    void DrawEdgeProc(HDC hDC, LPCRECT prc, BOOL bPressed);
    void DrawIconProc(HDC hDC, LPRECT prc, BOOL bPressed);
    void DrawTextProc(HDC hDC, LPCRECT prc, BOOL bPressed);

public:
    CUIFButton(CUIFObject *pParent, DWORD nObjectID, LPCRECT prc, DWORD style);
    ~CUIFButton() override;

    void SetIcon(HICON hIcon);
    void SetText(LPCWSTR pszText);

    void GetIconSize(HICON hIcon, LPSIZE pSize);
    void GetTextSize(LPCWSTR pszText, LPSIZE pSize);

    STDMETHOD_(void, Enable)(BOOL bEnable) override;
    STDMETHOD_(void, OnMouseIn)(LONG x, LONG y) override;
    STDMETHOD_(void, OnMouseOut)(LONG x, LONG y) override;
    STDMETHOD_(void, OnLButtonDown)(LONG x, LONG y) override;
    STDMETHOD_(void, OnLButtonUp)(LONG x, LONG y) override;
    STDMETHOD_(void, OnPaintNoTheme)(HDC hDC) override;
    STDMETHOD_(void, SetStatus)(UINT uStatus);
};

/////////////////////////////////////////////////////////////////////////////

class CUIFButton2 : public CUIFButton
{
protected:
    SIZE m_BitmapSize;

public:
    CUIFButton2(CUIFObject *pParent, DWORD nObjectID, LPCRECT prc, DWORD style);
    ~CUIFButton2() override;

    DWORD MakeDrawFlag();
    STDMETHOD_(BOOL, OnPaintTheme)(HDC hDC) override;
    STDMETHOD_(void, OnPaintNoTheme)(HDC hDC) override;
};

/////////////////////////////////////////////////////////////////////////////

class CUIFToolbarMenuButton : public CUIFButton2
{
public:
    CUIFToolbarButton *m_pToolbarButton;

    CUIFToolbarMenuButton(CUIFToolbarButton *pParent, DWORD nObjectID, LPCRECT prc, DWORD style);
    ~CUIFToolbarMenuButton() override;

    STDMETHOD_(void, OnLButtonUp)(LONG x, LONG y) override;
    STDMETHOD_(BOOL, OnSetCursor)(UINT uMsg, LONG x, LONG y) override;
};

/////////////////////////////////////////////////////////////////////////////

class CUIFToolbarButtonElement : public CUIFButton2
{
public:
    CUIFToolbarButton *m_pToolbarButton;

    CUIFToolbarButtonElement(CUIFToolbarButton *pParent, DWORD nObjectID, LPCRECT prc, DWORD style);

    STDMETHOD_(LPCWSTR, GetToolTip)() override;
    STDMETHOD_(void, OnLButtonUp)(LONG x, LONG y) override;
    STDMETHOD_(void, OnRButtonUp)(LONG x, LONG y) override;
};

/////////////////////////////////////////////////////////////////////////////

class CUIFToolbarButton : public CUIFObject
{
public:
    CUIFToolbarButtonElement *m_pToolbarButtonElement;
    CUIFToolbarMenuButton *m_pToolbarMenuButton;
    DWORD m_dwToolbarButtonFlags;
    LPCWSTR m_pszUnknownText;

    CUIFToolbarButton(
        CUIFObject *pParent,
        DWORD nObjectID,
        LPCRECT prc,
        DWORD style,
        DWORD dwToolbarButtonFlags,
        LPCWSTR pszUnknownText);
    ~CUIFToolbarButton() override { }

    BOOL Init();
    HICON GetIcon();
    void SetIcon(HICON hIcon);

    STDMETHOD_(void, ClearWndObj)() override;
    STDMETHOD_(void, DetachWndObj)() override;
    STDMETHOD_(void, Enable)(BOOL bEnable) override;
    STDMETHOD_(LPCWSTR, GetToolTip)() override;
    STDMETHOD_(void, SetActiveTheme)(LPCWSTR pszClassList, INT iPartId, INT iStateId) override;
    STDMETHOD_(void, SetFont)(HFONT hFont) override;
    STDMETHOD_(void, SetRect)(LPCRECT prc) override;
    STDMETHOD_(void, SetToolTip)(LPCWSTR pszToolTip) override;

    STDMETHOD_(void, OnUnknownMouse0)() { }
    STDMETHOD_(void, OnUnknownMouse1)(LONG x, LONG y) { }
    STDMETHOD_(void, OnUnknownMouse2)(LONG x, LONG y) { }
};

/////////////////////////////////////////////////////////////////////////////

// m_style flags for CUIFGripper
enum
{
    UIF_GRIPPER_VERTICAL = 0x1,
};

class CUIFGripper : public CUIFObject
{
protected:
    POINT m_ptGripper;

public:
    CUIFGripper(CUIFObject *pParent, LPCRECT prc, DWORD style);
    ~CUIFGripper() override;

    STDMETHOD_(void, OnMouseMove)(LONG x, LONG y) override;
    STDMETHOD_(void, OnLButtonDown)(LONG x, LONG y) override;
    STDMETHOD_(void, OnLButtonUp)(LONG x, LONG y) override;
    STDMETHOD_(BOOL, OnPaintTheme)(HDC hDC) override;
    STDMETHOD_(void, OnPaintNoTheme)(HDC hDC) override;
    STDMETHOD_(BOOL, OnSetCursor)(UINT uMsg, LONG x, LONG y) override;
    STDMETHOD_(void, SetStyle)(DWORD style) override;
};

/////////////////////////////////////////////////////////////////////////////

class CUIFWndFrame : public CUIFObject
{
protected:
    DWORD m_dwHitTest;
    POINT m_ptHit;
    RECT m_rcWnd;
    INT m_cxFrame;
    INT m_cyFrame;
    INT m_cxMin;
    INT m_cyMin;

public:
    CUIFWndFrame(CUIFObject *pParent, LPCRECT prc, DWORD style);

    void GetFrameSize(LPSIZE pSize);
    DWORD HitTest(LONG x, LONG y);

    STDMETHOD_(void, OnMouseMove)(LONG x, LONG y) override;
    STDMETHOD_(void, OnLButtonDown)(LONG x, LONG y) override;
    STDMETHOD_(void, OnLButtonUp)(LONG x, LONG y) override;
    STDMETHOD_(BOOL, OnPaintTheme)(HDC hDC) override;
    STDMETHOD_(void, OnPaintNoTheme)(HDC hDC) override;
    STDMETHOD_(BOOL, OnSetCursor)(UINT uMsg, LONG x, LONG y) override;
};

/////////////////////////////////////////////////////////////////////////////

class CUIFBalloonButton : public CUIFButton
{
protected:
    UINT m_nCommandID;
    friend class CUIFBalloonWindow;

public:
    CUIFBalloonButton(CUIFObject *pParent, DWORD nObjectID, LPCRECT prc, DWORD style);

    STDMETHOD_(void, OnPaint)(HDC hDC) override;
    void DrawTextProc(HDC hDC, LPCRECT prc, BOOL bPressed);
};

/////////////////////////////////////////////////////////////////////////////

// m_style flags for CUIFBalloonWindow
enum
{
    UIF_BALLOON_WINDOW_OK = 0x10000,
    UIF_BALLOON_WINDOW_YESNO = 0x20000,
    UIF_BALLOON_WINDOW_TYPE_MASK = 0xF0000,
};

class CUIFBalloonWindow : public CUIFWindow
{
protected:
    LPWSTR m_pszBalloonText;
    HRGN m_hRgn;
    RECT m_rcMargin;
    DWORD m_dwUnknown6;
    BOOL m_bHasBkColor;
    BOOL m_bHasTextColor;
    COLORREF m_rgbBkColor;
    COLORREF m_rgbTextColor;
    POINT m_ptTarget;
    RECT m_rcExclude;
    POINT m_ptBalloon;
    DWORD m_dwUnknown7;
    UINT m_nBalloonType;
    DWORD m_dwUnknown8[2];
    UINT m_cButtons;
    WPARAM m_nActionID;
    HWND m_hwndNotif;
    UINT m_uNotifMsg;

public:
    CUIFBalloonWindow(HINSTANCE hInst, DWORD style);
    ~CUIFBalloonWindow() override;

    STDMETHOD_(void, Initialize)() override;
    STDMETHOD_(LPCTSTR, GetClassName)() override;
    STDMETHOD_(LPCTSTR, GetWndTitle)() override;
    STDMETHOD_(void, OnCreate)(HWND hWnd) override;
    STDMETHOD_(void, OnDestroy)(HWND hWnd) override;
    STDMETHOD_(void, OnKeyDown)(HWND hWnd, WPARAM wParam, LPARAM lParam) override;
    STDMETHOD_(LRESULT, OnObjectNotify)(CUIFObject *pObject, WPARAM wParam, LPARAM lParam) override;
    STDMETHOD_(void, OnPaint)(HDC hDC) override;

    void AddButton(UINT nCommandId);
    void AdjustPos();
    HRGN CreateRegion(LPCRECT prc);
    void DoneWindowRegion();
    CUIFBalloonButton *FindButton(UINT nCommandID);
    CUIFObject *FindUIObject(UINT nObjectID);

    COLORREF GetBalloonBkColor();
    COLORREF GetBalloonTextColor();
    void GetButtonSize(LPSIZE pSize);
    void GetMargin(LPRECT prcMargin);
    void SetExcludeRect(LPCRECT prcExclude);
    void SetTargetPos(POINT ptTarget);
    void SetText(LPCWSTR pszText);

    void InitWindowRegion();
    void LayoutObject();
    void PaintFrameProc(HDC hDC, LPCRECT prc);
    void PaintMessageProc(HDC hDC, LPRECT prc, LPCWSTR pszText);
    void SendNotification(WPARAM wParam);
};

/////////////////////////////////////////////////////////////////////////////

inline void cicInitUIFLib(void)
{
    cicInitUIFSys();
    cicInitUIFScheme();
    cicInitUIFUtil();
}

inline void cicDoneUIFLib(void)
{
    cicDoneUIFScheme();
    cicDoneUIFSys();
    cicDoneUIFUtil();
}

/////////////////////////////////////////////////////////////////////////////

inline CUIFSystemInfo::CUIFSystemInfo()
{
    dwMajorVersion = 4;
    dwMinorVersion = 0;
    dwBuildNumber = 0;
    dwPlatformId = VER_PLATFORM_WIN32_WINDOWS;
    m_cBitsPixels = 8;
    m_bHighContrast1 = m_bHighContrast2 = FALSE;
}

inline void CUIFSystemInfo::GetSystemMetrics()
{
    HDC hDC = ::GetDC(NULL);
    m_cBitsPixels = ::GetDeviceCaps(hDC, BITSPIXEL);
    ::ReleaseDC(NULL, hDC);

    HIGHCONTRAST HighContrast = { sizeof(HighContrast) };
    ::SystemParametersInfo(SPI_GETHIGHCONTRAST, sizeof(HighContrast), &HighContrast, 0);
    m_bHighContrast1 = !!(HighContrast.dwFlags & HCF_HIGHCONTRASTON);
    COLORREF rgbBtnText = ::GetSysColor(COLOR_BTNTEXT);
    COLORREF rgbBtnFace = ::GetSysColor(COLOR_BTNFACE);
    const COLORREF black = RGB(0, 0, 0), white = RGB(255, 255, 255);
    m_bHighContrast2 = (m_bHighContrast1 ||
                        (rgbBtnText == black && rgbBtnFace == white) ||
                        (rgbBtnText == white && rgbBtnFace == black));
}

inline void CUIFSystemInfo::Initialize()
{
    dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    ::GetVersionEx(this);
    GetSystemMetrics();
}

inline void cicInitUIFSys(void)
{
    CUIFSystemInfo::s_pSystemInfo = new(cicNoThrow) CUIFSystemInfo();
    if (CUIFSystemInfo::s_pSystemInfo)
        CUIFSystemInfo::s_pSystemInfo->Initialize();
}

inline void cicDoneUIFSys(void)
{
    if (CUIFSystemInfo::s_pSystemInfo)
    {
        delete CUIFSystemInfo::s_pSystemInfo;
        CUIFSystemInfo::s_pSystemInfo = NULL;
    }
}

inline void cicUpdateUIFSys(void)
{
    if (CUIFSystemInfo::s_pSystemInfo)
        CUIFSystemInfo::s_pSystemInfo->GetSystemMetrics();
}

/////////////////////////////////////////////////////////////////////////////

inline HRESULT CUIFTheme::InternalOpenThemeData(HWND hWnd)
{
    if (!hWnd || !m_pszClassList)
        return E_FAIL;

    if (!cicGetFN(s_hUXTHEME, s_fnOpenThemeData, TEXT("uxtheme.dll"), "OpenThemeData"))
        return E_FAIL;
    m_hTheme = s_fnOpenThemeData(hWnd, m_pszClassList);
    return (m_hTheme ? S_OK : E_FAIL);
}

inline HRESULT CUIFTheme::EnsureThemeData(HWND hWnd)
{
    if (m_hTheme)
        return S_OK;
    return InternalOpenThemeData(hWnd);
}

inline HRESULT CUIFTheme::CloseThemeData()
{
    if (!m_hTheme)
        return S_OK;

    if (!cicGetFN(s_hUXTHEME, s_fnCloseThemeData, TEXT("uxtheme.dll"), "CloseThemeData"))
        return E_FAIL;

    HRESULT hr = s_fnCloseThemeData(m_hTheme);
    m_hTheme = NULL;
    return hr;
}

inline STDMETHODIMP
CUIFTheme::DrawThemeBackground(HDC hDC, int iStateId, LPCRECT pRect, LPCRECT pClipRect)
{
    if (!cicGetFN(s_hUXTHEME, s_fnDrawThemeBackground, TEXT("uxtheme.dll"), "DrawThemeBackground"))
        return E_FAIL;
    return s_fnDrawThemeBackground(m_hTheme, hDC, m_iPartId, iStateId, pRect, pClipRect);
}

inline STDMETHODIMP
CUIFTheme::DrawThemeParentBackground(HWND hwnd, HDC hDC, LPRECT prc)
{
    if (!cicGetFN(s_hUXTHEME, s_fnDrawThemeParentBackground, TEXT("uxtheme.dll"), "DrawThemeParentBackground"))
        return E_FAIL;
    return s_fnDrawThemeParentBackground(hwnd, hDC, prc);
}

inline STDMETHODIMP
CUIFTheme::DrawThemeText(HDC hDC, int iStateId, LPCWSTR pszText, int cchText, DWORD dwTextFlags, DWORD dwTextFlags2, LPCRECT pRect)
{
    if (!cicGetFN(s_hUXTHEME, s_fnDrawThemeText, TEXT("uxtheme.dll"), "DrawThemeText"))
        return E_FAIL;
    return s_fnDrawThemeText(m_hTheme, hDC, m_iPartId, iStateId, pszText, cchText, dwTextFlags, dwTextFlags2, pRect);
}

inline STDMETHODIMP
CUIFTheme::DrawThemeIcon(HDC hDC, int iStateId, LPCRECT pRect, HIMAGELIST himl, int iImageIndex)
{
    if (!cicGetFN(s_hUXTHEME, s_fnDrawThemeIcon, TEXT("uxtheme.dll"), "DrawThemeIcon"))
        return E_FAIL;
    return s_fnDrawThemeIcon(m_hTheme, hDC, m_iPartId, iStateId, pRect, himl, iImageIndex);
}

inline STDMETHODIMP
CUIFTheme::GetThemeBackgroundExtent(HDC hDC, int iStateId, LPCRECT pContentRect, LPRECT pExtentRect)
{
    if (!cicGetFN(s_hUXTHEME, s_fnGetThemeBackgroundExtent, TEXT("uxtheme.dll"), "GetThemeBackgroundExtent"))
        return E_FAIL;
    return s_fnGetThemeBackgroundExtent(m_hTheme, hDC, m_iPartId, iStateId, pContentRect, pExtentRect);
}

inline STDMETHODIMP
CUIFTheme::GetThemeBackgroundContentRect(HDC hDC, int iStateId, LPCRECT pBoundingRect, LPRECT pContentRect)
{
    if (!cicGetFN(s_hUXTHEME, s_fnGetThemeBackgroundContentRect, TEXT("uxtheme.dll"), "GetThemeBackgroundContentRect"))
        return E_FAIL;
    return s_fnGetThemeBackgroundContentRect(m_hTheme, hDC, m_iPartId, iStateId, pBoundingRect, pContentRect);
}

inline STDMETHODIMP
CUIFTheme::GetThemeTextExtent(HDC hDC, int iStateId, LPCWSTR pszText, int cchCharCount, DWORD dwTextFlags, LPCRECT pBoundingRect, LPRECT pExtentRect)
{
    if (!cicGetFN(s_hUXTHEME, s_fnGetThemeTextExtent, TEXT("uxtheme.dll"), "GetThemeTextExtent"))
        return E_FAIL;
    return s_fnGetThemeTextExtent(m_hTheme, hDC, m_iPartId, iStateId, pszText, cchCharCount, dwTextFlags, pBoundingRect, pExtentRect);
}

inline STDMETHODIMP
CUIFTheme::GetThemePartSize(HDC hDC, int iStateId, LPRECT prc, THEMESIZE eSize, SIZE *psz)
{
    if (!cicGetFN(s_hUXTHEME, s_fnGetThemePartSize, TEXT("uxtheme.dll"), "GetThemePartSize"))
        return E_FAIL;
    return s_fnGetThemePartSize(m_hTheme, hDC, m_iPartId, iStateId, prc, eSize, psz);
}

inline STDMETHODIMP
CUIFTheme::DrawThemeEdge(HDC hDC, int iStateId, LPCRECT pDestRect, UINT uEdge, UINT uFlags, LPRECT pContentRect)
{
    if (!cicGetFN(s_hUXTHEME, s_fnDrawThemeEdge, TEXT("uxtheme.dll"), "DrawThemeEdge"))
        return E_FAIL;
    return s_fnDrawThemeEdge(m_hTheme, hDC, m_iPartId, iStateId, pDestRect, uEdge, uFlags, pContentRect);
}

inline STDMETHODIMP
CUIFTheme::GetThemeColor(int iStateId, int iPropId, COLORREF *pColor)
{
    if (!cicGetFN(s_hUXTHEME, s_fnGetThemeColor, TEXT("uxtheme.dll"), "GetThemeColor"))
        return E_FAIL;
    return s_fnGetThemeColor(m_hTheme, m_iPartId, iStateId, iPropId, pColor);
}

inline STDMETHODIMP
CUIFTheme::GetThemeMargins(HDC hDC, int iStateId, int iPropId, LPRECT prc, MARGINS *pMargins)
{
    if (!cicGetFN(s_hUXTHEME, s_fnGetThemeMargins, TEXT("uxtheme.dll"), "GetThemeMargins"))
        return E_FAIL;
    return s_fnGetThemeMargins(m_hTheme, hDC, m_iPartId, iStateId, iPropId, prc, pMargins);
}

inline STDMETHODIMP
CUIFTheme::GetThemeFont(HDC hDC, int iStateId, int iPropId, LOGFONTW *pFont)
{
    if (!cicGetFN(s_hUXTHEME, s_fnGetThemeFont, TEXT("uxtheme.dll"), "GetThemeFont"))
        return E_FAIL;
    return s_fnGetThemeFont(m_hTheme, hDC, m_iPartId, iStateId, iPropId, pFont);
}

inline STDMETHODIMP_(COLORREF)
CUIFTheme::GetThemeSysColor(INT iColorId)
{
    if (!cicGetFN(s_hUXTHEME, s_fnGetThemeSysColor, TEXT("uxtheme.dll"), "GetThemeSysColor"))
        return RGB(0, 0, 0);
    return s_fnGetThemeSysColor(m_hTheme, iColorId);
}

inline STDMETHODIMP_(int)
CUIFTheme::GetThemeSysSize(int iSizeId)
{
    if (!cicGetFN(s_hUXTHEME, s_fnGetThemeSysSize, TEXT("uxtheme.dll"), "GetThemeSysSize"))
        return 0;
    return s_fnGetThemeSysSize(m_hTheme, iSizeId);
}

inline STDMETHODIMP_(void)
CUIFTheme::SetActiveTheme(LPCWSTR pszClassList, INT iPartId, INT iStateId)
{
    m_iPartId = iPartId;
    m_iStateId = iStateId;
    m_pszClassList = pszClassList;
}

/////////////////////////////////////////////////////////////////////////////

/// @unimplemented
inline
CUIFObject::CUIFObject(CUIFObject *pParent, DWORD nObjectID, LPCRECT prc, DWORD style)
{
    m_pszClassList = NULL;
    m_hTheme = NULL;
    m_pParent = pParent;
    m_nObjectID = nObjectID;
    m_style = style;

    if (prc)
        m_rc = *prc;
    else
        m_rc = { 0, 0, 0, 0 };

    if (m_pParent)
    {
        m_pWindow = m_pParent->m_pWindow;
        m_pScheme = m_pParent->m_pScheme;
    }
    else
    {
        m_pWindow = NULL;
        m_pScheme = NULL;
    }

    m_bEnable = m_bVisible = TRUE;

    m_hFont = (HFONT)::GetStockObject(DEFAULT_GUI_FONT);
    m_bHasCustomFont = FALSE;

    m_pszToolTip = NULL;

    m_dwUnknown4[0] = -1; //FIXME: name
    m_dwUnknown4[1] = -1; //FIXME: name
}

inline
CUIFObject::~CUIFObject()
{
    if (m_pWindow)
    {
        CUIFToolTip *pToolTip = m_pWindow->m_pToolTip;
        if (pToolTip && pToolTip->m_pToolTipTarget == this)
            pToolTip->m_pToolTipTarget = NULL;
    }

    if (m_pszToolTip)
    {
        delete[] m_pszToolTip;
        m_pszToolTip = NULL;
    }

    for (;;)
    {
        CUIFObject *pLast = m_ObjectArray.GetLast();
        if (!pLast)
            break;

        m_ObjectArray.Remove(pLast);
        delete pLast;
    }

    if (m_pWindow)
        m_pWindow->RemoveUIObj(this);

    CloseThemeData();
}

inline STDMETHODIMP_(void) CUIFObject::Initialize()
{
}

inline STDMETHODIMP_(void) CUIFObject::OnPaint(HDC hDC)
{
    if (!(m_pWindow->m_style & UIF_WINDOW_ENABLETHEMED) || !OnPaintTheme(hDC))
        OnPaintNoTheme(hDC);
}

inline STDMETHODIMP_(BOOL) CUIFObject::OnSetCursor(UINT uMsg, LONG x, LONG y)
{
    return FALSE;
}

inline STDMETHODIMP_(void) CUIFObject::GetRect(LPRECT prc)
{
    *prc = m_rc;
}

inline STDMETHODIMP_(BOOL) CUIFObject::PtInObject(POINT pt)
{
    return m_bVisible && ::PtInRect(&m_rc, pt);
}

inline STDMETHODIMP_(void) CUIFObject::PaintObject(HDC hDC, LPCRECT prc)
{
    if (!m_bVisible)
        return;

    if (!prc)
        prc = &m_rc;

    OnPaint(hDC);

    for (size_t iItem = 0; iItem < m_ObjectArray.size(); ++iItem)
    {
        CUIFObject *pObject = m_ObjectArray[iItem];
        RECT rc;
        if (::IntersectRect(&rc, prc, &pObject->m_rc))
            pObject->PaintObject(hDC, &rc);
    }
}

inline STDMETHODIMP_(void) CUIFObject::CallOnPaint()
{
    if (m_pWindow)
        m_pWindow->UpdateUI(&m_rc);
}

inline STDMETHODIMP_(void) CUIFObject::Enable(BOOL bEnable)
{
    if (m_bEnable == bEnable)
        return;

    m_bEnable = bEnable;
    for (size_t iItem = 0; iItem < m_ObjectArray.size(); ++iItem)
        m_ObjectArray[iItem]->Enable(bEnable);

    CallOnPaint();
}

inline STDMETHODIMP_(void) CUIFObject::Show(BOOL bVisible)
{
    if (m_bVisible == bVisible)
        return;

    m_bVisible = bVisible;
    for (size_t iItem = 0; iItem < m_ObjectArray.size(); ++iItem)
        m_ObjectArray[iItem]->Show(bVisible);

    if (m_bVisible || m_pParent)
        m_pParent->CallOnPaint();
}

inline STDMETHODIMP_(void) CUIFObject::SetFontToThis(HFONT hFont)
{
    m_bHasCustomFont = !!hFont;
    if (!hFont)
        hFont = (HFONT)::GetStockObject(DEFAULT_GUI_FONT);
    m_hFont = hFont;
}

inline STDMETHODIMP_(void) CUIFObject::SetFont(HFONT hFont)
{
    SetFontToThis(hFont);

    for (size_t iItem = 0; iItem < m_ObjectArray.size(); ++iItem)
        m_ObjectArray[iItem]->SetFont(hFont);

    CallOnPaint();
}

inline STDMETHODIMP_(void) CUIFObject::SetStyle(DWORD style)
{
    m_style = style;
}

inline STDMETHODIMP_(void) CUIFObject::AddUIObj(CUIFObject *pObject)
{
    m_ObjectArray.Add(pObject);
    CallOnPaint();
}

inline STDMETHODIMP_(void) CUIFObject::RemoveUIObj(CUIFObject *pObject)
{
    if (m_ObjectArray.Remove(pObject))
        CallOnPaint();
}

inline STDMETHODIMP_(LRESULT) CUIFObject::OnObjectNotify(CUIFObject *pObject, WPARAM wParam, LPARAM lParam)
{
    if (m_pParent)
        return m_pParent->OnObjectNotify(pObject, wParam, lParam);
    return 0;
}

inline STDMETHODIMP_(void) CUIFObject::SetToolTip(LPCWSTR pszToolTip)
{
    if (m_pszToolTip)
    {
        delete[] m_pszToolTip;
        m_pszToolTip = NULL;
    }

    if (pszToolTip)
    {
        size_t cch = wcslen(pszToolTip);
        m_pszToolTip = new(cicNoThrow) WCHAR[cch + 1];
        if (m_pszToolTip)
            lstrcpynW(m_pszToolTip, pszToolTip, cch + 1);
    }
}

inline STDMETHODIMP_(LPCWSTR) CUIFObject::GetToolTip()
{
    return m_pszToolTip;
}

inline STDMETHODIMP_(LRESULT) CUIFObject::OnShowToolTip()
{
    return 0;
}

inline STDMETHODIMP_(void) CUIFObject::ClearWndObj()
{
    m_pWindow = NULL;
    for (size_t iItem = 0; iItem < m_ObjectArray.size(); ++iItem)
        m_ObjectArray[iItem]->ClearWndObj();
}

inline STDMETHODIMP_(BOOL) CUIFObject::OnPaintTheme(HDC hDC)
{
    return FALSE;
}

inline STDMETHODIMP_(void) CUIFObject::OnPaintNoTheme(HDC hDC)
{
}

inline STDMETHODIMP_(void) CUIFObject::ClearTheme()
{
    CloseThemeData();
    for (size_t iItem = 0; iItem < m_ObjectArray.size(); ++iItem)
        m_ObjectArray[iItem]->ClearTheme();
}

inline void CUIFObject::StartCapture()
{
    if (m_pWindow)
        m_pWindow->SetCaptureObject(this);
}

inline void CUIFObject::EndCapture()
{
    if (m_pWindow)
        m_pWindow->SetCaptureObject(NULL);
}

inline BOOL CUIFObject::IsCapture()
{
    return m_pWindow && (m_pWindow->m_pCaptured == this);
}

inline void CUIFObject::SetRect(LPCRECT prc)
{
    m_rc = *prc;
    if (m_pWindow)
        m_pWindow->OnObjectMoved(this);
    CallOnPaint();
}

inline LRESULT CUIFObject::NotifyCommand(WPARAM wParam, LPARAM lParam)
{
    if (m_pParent)
        return m_pParent->OnObjectNotify(this, wParam, lParam);
    return 0;
}

inline void CUIFObject::DetachWndObj()
{
    if (m_pWindow)
    {
        CUIFToolTip *pToolTip = m_pWindow->m_pToolTip;
        if (pToolTip && pToolTip->m_pToolTipTarget == this)
            pToolTip->m_pToolTipTarget = NULL;

        m_pWindow->RemoveUIObj(this);
        m_pWindow = NULL;
    }
}

inline BOOL CUIFObject::IsRTL()
{
    if (!m_pWindow)
        return FALSE;
    return !!(m_pWindow->m_style & UIF_WINDOW_LAYOUTRTL);
}

inline CUIFObject* CUIFObject::ObjectFromPoint(POINT pt)
{
    if (!PtInObject(pt))
        return NULL;

    CUIFObject *pFound = this;
    for (size_t i = 0; i < m_ObjectArray.size(); ++i)
    {
        CUIFObject *pObject = m_ObjectArray[i]->ObjectFromPoint(pt);
        if (pObject)
            pFound = pObject;
    }
    return pFound;
}

inline void CUIFObject::SetScheme(CUIFScheme *scheme)
{
    m_pScheme = scheme;
    for (size_t i = 0; i < m_ObjectArray.size(); ++i)
    {
        m_ObjectArray[i]->SetScheme(scheme);
    }
}

/////////////////////////////////////////////////////////////////////////////

inline STDMETHODIMP_(void) CUIFColorTableSys::InitColor()
{
    m_rgbColors[0] = ::GetSysColor(COLOR_BTNFACE);
    m_rgbColors[1] = ::GetSysColor(COLOR_BTNSHADOW);
    m_rgbColors[2] = ::GetSysColor(COLOR_ACTIVEBORDER);
    m_rgbColors[3] = ::GetSysColor(COLOR_ACTIVECAPTION);
    m_rgbColors[4] = ::GetSysColor(COLOR_BTNFACE);
    m_rgbColors[5] = ::GetSysColor(COLOR_BTNSHADOW);
    m_rgbColors[6] = ::GetSysColor(COLOR_BTNTEXT);
    m_rgbColors[7] = ::GetSysColor(COLOR_CAPTIONTEXT);
    m_rgbColors[8] = ::GetSysColor(COLOR_GRAYTEXT);
    m_rgbColors[9] = ::GetSysColor(COLOR_HIGHLIGHT);
    m_rgbColors[10] = ::GetSysColor(COLOR_HIGHLIGHTTEXT);
    m_rgbColors[11] = ::GetSysColor(COLOR_INACTIVECAPTION);
    m_rgbColors[12] = ::GetSysColor(COLOR_INACTIVECAPTIONTEXT);
    m_rgbColors[13] = ::GetSysColor(COLOR_MENUTEXT);
    m_rgbColors[14] = ::GetSysColor(COLOR_WINDOW);
    m_rgbColors[15] = ::GetSysColor(COLOR_WINDOWTEXT);
}

inline STDMETHODIMP_(void) CUIFColorTableSys::InitBrush()
{
    ZeroMemory(m_hBrushes, sizeof(m_hBrushes));
}

inline STDMETHODIMP_(void) CUIFColorTableSys::DoneBrush()
{
    for (size_t i = 0; i < _countof(m_hBrushes); ++i)
    {
        if (m_hBrushes[i])
        {
            ::DeleteObject(m_hBrushes[i]);
            m_hBrushes[i] = NULL;
        }
    }
}

inline HBRUSH CUIFColorTableSys::GetBrush(INT iColor)
{
    if (!m_hBrushes[iColor])
        m_hBrushes[iColor] = ::CreateSolidBrush(m_rgbColors[iColor]);
    return m_hBrushes[iColor];
}

inline HBRUSH CUIFColorTableOff10::GetBrush(INT iColor)
{
    if (!m_hBrushes[iColor])
        m_hBrushes[iColor] = ::CreateSolidBrush(m_rgbColors[iColor]);
    return m_hBrushes[iColor];
}

/// @unimplemented
inline STDMETHODIMP_(void) CUIFColorTableOff10::InitColor()
{
    m_rgbColors[0] = ::GetSysColor(COLOR_BTNFACE);
    m_rgbColors[1] = ::GetSysColor(COLOR_WINDOW);
    m_rgbColors[2] = ::GetSysColor(COLOR_WINDOW);
    m_rgbColors[3] = ::GetSysColor(COLOR_BTNFACE);
    m_rgbColors[4] = ::GetSysColor(COLOR_BTNSHADOW);
    m_rgbColors[5] = ::GetSysColor(COLOR_WINDOW);
    m_rgbColors[6] = ::GetSysColor(COLOR_HIGHLIGHT);
    m_rgbColors[7] = ::GetSysColor(COLOR_WINDOWTEXT);
    m_rgbColors[8] = ::GetSysColor(COLOR_HIGHLIGHT);
    m_rgbColors[9] = ::GetSysColor(COLOR_HIGHLIGHT);
    m_rgbColors[10] = ::GetSysColor(COLOR_HIGHLIGHTTEXT);
    m_rgbColors[11] = ::GetSysColor(COLOR_BTNFACE);
    m_rgbColors[12] = ::GetSysColor(COLOR_BTNTEXT);
    m_rgbColors[13] = ::GetSysColor(COLOR_BTNSHADOW);
    m_rgbColors[14] = ::GetSysColor(COLOR_BTNFACE);
    m_rgbColors[15] = ::GetSysColor(COLOR_WINDOW);
    m_rgbColors[16] = ::GetSysColor(COLOR_HIGHLIGHT);
    m_rgbColors[17] = ::GetSysColor(COLOR_BTNTEXT);
    m_rgbColors[18] = ::GetSysColor(COLOR_WINDOW);
    m_rgbColors[19] = ::GetSysColor(COLOR_BTNSHADOW);
    m_rgbColors[20] = ::GetSysColor(COLOR_BTNFACE);
    m_rgbColors[21] = ::GetSysColor(COLOR_BTNSHADOW);
    m_rgbColors[22] = ::GetSysColor(COLOR_BTNFACE);
    m_rgbColors[23] = ::GetSysColor(COLOR_BTNSHADOW);
    m_rgbColors[24] = ::GetSysColor(COLOR_CAPTIONTEXT);
    m_rgbColors[25] = ::GetSysColor(COLOR_HIGHLIGHT);
    m_rgbColors[26] = ::GetSysColor(COLOR_HIGHLIGHTTEXT);
    m_rgbColors[27] = ::GetSysColor(COLOR_BTNFACE);
    m_rgbColors[28] = ::GetSysColor(COLOR_BTNTEXT);
    m_rgbColors[29] = ::GetSysColor(COLOR_BTNSHADOW);
    m_rgbColors[30] = ::GetSysColor(COLOR_BTNTEXT);
    m_rgbColors[31] = ::GetSysColor(COLOR_WINDOWTEXT);
}

inline STDMETHODIMP_(void) CUIFColorTableOff10::InitBrush()
{
    ZeroMemory(m_hBrushes, sizeof(m_hBrushes));
}

inline STDMETHODIMP_(void) CUIFColorTableOff10::DoneBrush()
{
    for (size_t i = 0; i < _countof(m_hBrushes); ++i)
    {
        if (m_hBrushes[i])
        {
            ::DeleteObject(m_hBrushes[i]);
            m_hBrushes[i] = NULL;
        }
    }
}

/////////////////////////////////////////////////////////////////////////////

inline void cicInitUIFScheme(void)
{
    CUIFColorTable *pColorTable;

    pColorTable = CUIFScheme::s_pColorTableSys = new(cicNoThrow) CUIFColorTableSys();
    if (pColorTable)
    {
        pColorTable->InitColor();
        pColorTable->InitBrush();
    }

    pColorTable = CUIFScheme::s_pColorTableOff10 = new(cicNoThrow) CUIFColorTableOff10();
    if (pColorTable)
    {
        pColorTable->InitColor();
        pColorTable->InitBrush();
    }
}

inline void cicUpdateUIFScheme(void)
{
    if (CUIFScheme::s_pColorTableSys)
        CUIFScheme::s_pColorTableSys->Update();
    if (CUIFScheme::s_pColorTableOff10)
        CUIFScheme::s_pColorTableOff10->Update();
}

inline void cicDoneUIFScheme(void)
{
    if (CUIFScheme::s_pColorTableSys)
    {
        delete CUIFScheme::s_pColorTableSys;
        CUIFScheme::s_pColorTableSys = NULL;
    }
    if (CUIFScheme::s_pColorTableOff10)
    {
        delete CUIFScheme::s_pColorTableOff10;
        CUIFScheme::s_pColorTableOff10 = NULL;
    }
}

/// @unimplemented
inline CUIFScheme *cicCreateUIFScheme(DWORD type)
{
    return new(cicNoThrow) CUIFSchemeDef(type);
}

inline STDMETHODIMP_(DWORD) CUIFSchemeDef::GetType()
{
    return m_dwType;
}

inline STDMETHODIMP_(COLORREF) CUIFSchemeDef::GetColor(INT iColor)
{
    return s_pColorTableSys->GetColor(iColor);
}

inline STDMETHODIMP_(HBRUSH) CUIFSchemeDef::GetBrush(INT iColor)
{
    return s_pColorTableSys->GetBrush(iColor);
}

inline STDMETHODIMP_(INT) CUIFSchemeDef::CyMenuItem(INT cyText)
{
    return cyText + 2;
}

inline STDMETHODIMP_(INT) CUIFSchemeDef::CxSizeFrame()
{
    return ::GetSystemMetrics(SM_CXSIZEFRAME);
}

inline STDMETHODIMP_(INT) CUIFSchemeDef::CySizeFrame()
{
    return ::GetSystemMetrics(SM_CYSIZEFRAME);
}

inline STDMETHODIMP_(INT) CUIFSchemeDef::CxWndBorder()
{
    return 1;
}

inline STDMETHODIMP_(INT) CUIFSchemeDef::CyWndBorder()
{
    return 1;
}

inline STDMETHODIMP_(void) CUIFScheme::FillRect(HDC hDC, LPCRECT prc, INT iColor)
{
    ::FillRect(hDC, prc, GetBrush(iColor));
}

inline STDMETHODIMP_(void) CUIFScheme::FrameRect(HDC hDC, LPCRECT prc, INT iColor)
{
    ::FrameRect(hDC, prc, GetBrush(iColor));
}

inline STDMETHODIMP_(void) CUIFSchemeDef::DrawSelectionRect(HDC hDC, LPCRECT prc, int)
{
    ::FillRect(hDC, prc, GetBrush(6));
}

/// @unimplemented
inline STDMETHODIMP_(INT) CUIFSchemeDef::GetCtrlFaceOffset(DWORD, DWORD dwDrawFlags, LPSIZE pSize)
{
    return 0;
}

inline STDMETHODIMP_(void)
CUIFSchemeDef::DrawCtrlBkgd(HDC hDC, LPCRECT prc, DWORD dwUnknownFlags, DWORD dwDrawFlags)
{
    ::FillRect(hDC, prc, GetBrush(9));

    if (!(dwDrawFlags & UIF_DRAW_PRESSED) && (dwDrawFlags & 0x2))
        return;

    HBRUSH hbrDither = cicCreateDitherBrush();
    if (!hbrDither)
        return;

    COLORREF rgbOldText = ::SetTextColor(hDC, ::GetSysColor(COLOR_BTNFACE));
    COLORREF rgbOldBack = ::SetBkColor(hDC, ::GetSysColor(COLOR_BTNHIGHLIGHT));

    RECT rc = *prc;
    ::InflateRect(&rc, -2, -2);
    ::FillRect(hDC, &rc, hbrDither);
    ::SetTextColor(hDC, rgbOldText);
    ::SetBkColor(hDC, rgbOldBack);
    ::DeleteObject(hbrDither);
}

inline STDMETHODIMP_(void)
CUIFSchemeDef::DrawCtrlEdge(
    HDC hDC,
    LPCRECT prc,
    DWORD dwUnknownFlags,
    DWORD dwDrawFlags)
{
    UINT uEdge = BDR_RAISEDINNER;

    if (dwDrawFlags & 0x10)
    {
        if (!(dwUnknownFlags & 0x40))
        {
            if (dwUnknownFlags & 0x80)
                uEdge = BDR_SUNKENOUTER;
            else
                return;
        }
    }
    else if (dwDrawFlags & 0x2)
    {
        if (!(dwUnknownFlags & 0x10))
        {
            if (dwUnknownFlags & 0x20)
                uEdge = BDR_SUNKENOUTER;
            else
                return;
        }
    }
    else if (dwDrawFlags & 0x1)
    {
        if (!(dwUnknownFlags & 0x4))
        {
            if (dwUnknownFlags & 0x8)
                uEdge = BDR_SUNKENOUTER;
            else
                return;
        }
    }
    else if (!(dwUnknownFlags & 0x1))
    {
        return;
    }

    RECT rc = *prc;
    ::DrawEdge(hDC, &rc, uEdge, BF_RECT);
}

inline STDMETHODIMP_(void)
CUIFSchemeDef::DrawCtrlText(
    HDC hDC,
    LPCRECT prc,
    LPCWSTR pszText,
    INT cchText,
    DWORD dwDrawFlags,
    BOOL bRight)
{
    COLORREF rgbOldText = ::GetTextColor(hDC);
    INT OldBkMode = ::SetBkMode(hDC, TRANSPARENT);

    if (cchText == -1)
        cchText = lstrlenW(pszText);

    RECT rc = *prc;
    if (dwDrawFlags & UIF_DRAW_DISABLED)
    {
        ::OffsetRect(&rc, 1, 1);
        ::SetTextColor(hDC, ::GetSysColor(COLOR_BTNHIGHLIGHT));
        ::ExtTextOutW(hDC, (bRight ? rc.right : rc.left), rc.top, ETO_CLIPPED, &rc,
                      pszText, cchText, NULL);
        ::OffsetRect(&rc, -1, -1);
    }

    ::SetTextColor(hDC, ::GetSysColor(COLOR_BTNTEXT));
    ::ExtTextOutW(hDC, (bRight ? rc.right : rc.left), rc.top, ETO_CLIPPED, &rc,
                  pszText, cchText, NULL);

    ::SetTextColor(hDC, rgbOldText);
    ::SetBkMode(hDC, OldBkMode);
}

inline STDMETHODIMP_(void)
CUIFSchemeDef::DrawCtrlIcon(HDC hDC, LPCRECT prc, HICON hIcon, DWORD dwDrawFlags, LPSIZE pSize)
{
    if (m_bMirroring)
    {
        HBITMAP hbm1, hbm2;
        if (cicGetIconBitmaps(hIcon, &hbm1, &hbm2, pSize))
        {
            DrawCtrlBitmap(hDC, prc, hbm1, hbm2, dwDrawFlags);
            ::DeleteObject(hbm1);
            ::DeleteObject(hbm2);
        }
    }
    else
    {
        UINT uFlags = DST_PREFIXTEXT | DST_TEXT;
        if (dwDrawFlags & UIF_DRAW_DISABLED)
            uFlags |= (DSS_MONO | DSS_DISABLED);
        ::DrawState(hDC, 0, 0, (LPARAM)hIcon, 0, prc->left, prc->top, 0, 0, uFlags);
    }
}

inline STDMETHODIMP_(void)
CUIFSchemeDef::DrawCtrlBitmap(HDC hDC, LPCRECT prc, HBITMAP hbm1, HBITMAP hbm2, DWORD dwDrawFlags)
{
    if (m_bMirroring)
    {
        hbm1 = cicMirrorBitmap(hbm1, GetBrush(9));
        hbm2 = cicMirrorBitmap(hbm2, (HBRUSH)GetStockObject(BLACK_BRUSH));
    }

    HBRUSH hBrush = (HBRUSH)UlongToHandle(COLOR_BTNFACE + 1);
    BOOL bBrushCreated = FALSE;
    if (hbm2)
    {
        HBITMAP hBitmap = NULL;
        if (dwDrawFlags & UIF_DRAW_DISABLED)
        {
            hBitmap = cicCreateDisabledBitmap(prc, hbm2, GetBrush(9), GetBrush(11), TRUE);
        }
        else
        {
            if ((dwDrawFlags & UIF_DRAW_PRESSED) && !(dwDrawFlags & 0x2))
            {
                hBrush = cicCreateDitherBrush();
                bBrushCreated = TRUE;
            }

            COLORREF rgbFace = ::GetSysColor(COLOR_BTNFACE);
            COLORREF rgbHighlight = ::GetSysColor(COLOR_BTNHIGHLIGHT);
            hBitmap = cicCreateMaskBmp(prc, hbm1, hbm2, hBrush, rgbFace, rgbHighlight);
        }

        if (hBitmap)
        {
            ::DrawState(hDC, NULL, NULL, (LPARAM)hBitmap, 0,
                        prc->left, prc->top,
                        prc->right - prc->left, prc->bottom - prc->top,
                        DST_BITMAP);
            ::DeleteObject(hBitmap);
        }
    }
    else
    {
        UINT uFlags = DST_BITMAP;
        if (dwDrawFlags & 0x20)
            uFlags |= (DSS_MONO | DSS_DISABLED);

        ::DrawState(hDC, NULL, NULL, (LPARAM)hbm1, 0,
                    prc->left, prc->top,
                    prc->right - prc->left, prc->bottom - prc->top,
                    uFlags);
    }

    if (bBrushCreated)
        ::DeleteObject(hBrush);

    if (m_bMirroring)
    {
        ::DeleteObject(hbm1);
        ::DeleteObject(hbm2);
    }
}

inline STDMETHODIMP_(void)
CUIFSchemeDef::DrawMenuBitmap(HDC hDC, LPCRECT prc, HBITMAP hbm1, HBITMAP hbm2, DWORD dwDrawFlags)
{
    DrawCtrlBitmap(hDC, prc, hbm1, hbm2, dwDrawFlags);
}

inline STDMETHODIMP_(void)
CUIFSchemeDef::DrawMenuSeparator(HDC hDC, LPCRECT prc)
{
    RECT rc = *prc;
    rc.bottom = rc.top + (rc.bottom - rc.top) / 2;
    ::FillRect(hDC, &rc, (HBRUSH)UlongToHandle(COLOR_BTNSHADOW + 1));

    rc = *prc;
    rc.top += (rc.bottom - rc.top) / 2;
    ::FillRect(hDC, &rc, (HBRUSH)UlongToHandle(COLOR_BTNHIGHLIGHT + 1));
}

inline STDMETHODIMP_(void)
CUIFSchemeDef::DrawFrameCtrlBkgd(HDC hDC, LPCRECT prc, DWORD dwUnknownFlags, DWORD dwDrawFlags)
{
    DrawCtrlBkgd(hDC, prc, dwUnknownFlags, dwDrawFlags);
}

inline STDMETHODIMP_(void)
CUIFSchemeDef::DrawFrameCtrlEdge(HDC hDC, LPCRECT prc, DWORD dwUnknownFlags, DWORD dwDrawFlags)
{
    DrawCtrlEdge(hDC, prc, dwUnknownFlags, dwDrawFlags);
}

inline STDMETHODIMP_(void)
CUIFSchemeDef::DrawFrameCtrlIcon(HDC hDC, LPCRECT prc, HICON hIcon, DWORD dwDrawFlags, LPSIZE pSize)
{
    DrawCtrlIcon(hDC, prc, hIcon, dwDrawFlags, pSize);
}

inline STDMETHODIMP_(void)
CUIFSchemeDef::DrawFrameCtrlBitmap(HDC hDC, LPCRECT prc, HBITMAP hbm1, HBITMAP hbm2, DWORD dwDrawFlags)
{
    DrawCtrlBitmap(hDC, prc, hbm1, hbm2, dwDrawFlags);
}

inline STDMETHODIMP_(void)
CUIFSchemeDef::DrawWndFrame(HDC hDC, LPCRECT prc, DWORD type, DWORD unused1, DWORD unused2)
{
    RECT rc = *prc;
    if (type && type <= 2)
        ::DrawEdge(hDC, &rc, BDR_RAISED, BF_RECT);
    else
        FrameRect(hDC, &rc, 14);
}

inline STDMETHODIMP_(void)
CUIFSchemeDef::DrawDragHandle(HDC hDC, LPCRECT prc, BOOL bVertical)
{
    RECT rc;
    if (bVertical)
        rc = { prc->left, prc->top + 1, prc->right, prc->top + 4 };
    else
        rc = { prc->left + 1, prc->top, prc->left + 4, prc->bottom };
    ::DrawEdge(hDC, &rc, BDR_RAISEDINNER, BF_RECT);
}

inline STDMETHODIMP_(void)
CUIFSchemeDef::DrawSeparator(HDC hDC, LPCRECT prc, BOOL bVertical)
{
    HPEN hLightPen = ::CreatePen(PS_SOLID, 0, ::GetSysColor(COLOR_BTNHIGHLIGHT));
    if (!hLightPen)
        return;

    HPEN hShadowPen = CreatePen(PS_SOLID, 0, GetSysColor(COLOR_BTNSHADOW));
    if (!hShadowPen)
    {
        ::DeleteObject(hLightPen);
        return;
    }

    HGDIOBJ hPenOld = ::SelectObject(hDC, hShadowPen);
    if (bVertical)
    {
        ::MoveToEx(hDC, prc->left, prc->top + 1, NULL);
        ::LineTo(hDC, prc->right, prc->top + 1);
        ::SelectObject(hDC, hLightPen);
        ::MoveToEx(hDC, prc->left, prc->top + 2, NULL);
        ::LineTo(hDC, prc->right, prc->top + 2);
    }
    else
    {
        ::MoveToEx(hDC, prc->left + 1, prc->top, NULL);
        ::LineTo(hDC, prc->left + 1, prc->bottom);
        ::SelectObject(hDC, hLightPen);
        ::MoveToEx(hDC, prc->left + 2, prc->top, NULL);
        ::LineTo(hDC, prc->left + 2, prc->bottom);
    }
    ::SelectObject(hDC, hPenOld);

    ::DeleteObject(hShadowPen);
    ::DeleteObject(hLightPen);
}

/////////////////////////////////////////////////////////////////////////////

inline BOOL cicGetIconSize(HICON hIcon, LPSIZE pSize)
{
    ICONINFO IconInfo;
    if (!GetIconInfo(hIcon, &IconInfo))
        return FALSE;

    BITMAP bm;
    ::GetObject(IconInfo.hbmColor, sizeof(bm), &bm);
    ::DeleteObject(IconInfo.hbmColor);
    ::DeleteObject(IconInfo.hbmMask);
    pSize->cx = bm.bmWidth;
    pSize->cy = bm.bmHeight;
    return TRUE;
}

inline HIMAGELIST CUIFIcon::GetImageList(BOOL bMirror)
{
    if (!m_hImageList)
        return NULL;

    if (m_hIcon)
    {
        SIZE iconSize;
        cicGetIconSize(m_hIcon, &iconSize);

        UINT uFlags = ILC_COLOR32 | ILC_MASK;
        if (bMirror)
            uFlags |= ILC_MIRROR;

        m_hImageList = ImageList_Create(iconSize.cx, iconSize.cy, uFlags, 1, 0);
        if (m_hImageList)
            ImageList_ReplaceIcon(m_hImageList, -1, m_hIcon);

        return m_hImageList;
    }

    return NULL;
}

/////////////////////////////////////////////////////////////////////////////

inline CUIFBitmapDC::CUIFBitmapDC(BOOL bMemory)
{
    m_hBitmap = NULL;
    m_hOldBitmap = NULL;
    m_hOldObject = NULL;
    if (bMemory)
        m_hDC = ::CreateCompatibleDC(NULL);
    else
        m_hDC = ::CreateDC(TEXT("DISPLAY"), NULL, NULL, NULL);
}

inline CUIFBitmapDC::~CUIFBitmapDC()
{
    Uninit();
    ::DeleteDC(m_hDC);
}

inline void CUIFBitmapDC::Uninit(BOOL bKeep)
{
    if (m_hOldBitmap)
    {
        ::SelectObject(m_hDC, m_hOldBitmap);
        m_hOldBitmap = NULL;
    }

    if (m_hOldObject)
    {
        ::SelectObject(m_hDC, m_hOldObject);
        m_hOldObject = NULL;
    }

    if (!bKeep)
    {
        if (m_hBitmap)
        {
            ::DeleteObject(m_hBitmap);
            m_hBitmap = NULL;
        }
    }
}

inline BOOL CUIFBitmapDC::SetBitmap(HBITMAP hBitmap)
{
    if (m_hDC)
        m_hOldBitmap = ::SelectObject(m_hDC, hBitmap);
    return TRUE;
}

inline BOOL CUIFBitmapDC::SetBitmap(LONG cx, LONG cy, WORD cPlanes, WORD cBitCount)
{
    m_hBitmap = ::CreateBitmap(cx, cy, cPlanes, cBitCount, 0);
    m_hOldBitmap = ::SelectObject(m_hDC, m_hBitmap);
    return TRUE;
}

inline BOOL CUIFBitmapDC::SetDIB(LONG cx, LONG cy, WORD cPlanes, WORD cBitCount)
{
    BITMAPINFO bmi;
    ZeroMemory(&bmi, sizeof(bmi));
    bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader);
    bmi.bmiHeader.biWidth = cx;
    bmi.bmiHeader.biHeight = cy;
    bmi.bmiHeader.biPlanes = cPlanes;
    bmi.bmiHeader.biBitCount = cBitCount;
    bmi.bmiHeader.biCompression = BI_RGB;
    m_hBitmap = ::CreateDIBSection(m_hDC, &bmi, DIB_RGB_COLORS, NULL, NULL, 0);
    m_hOldBitmap = ::SelectObject(m_hDC, m_hBitmap);
    return TRUE;
}

inline void cicInitUIFUtil(void)
{
    if (!CUIFBitmapDC::s_phdcSrc)
        CUIFBitmapDC::s_phdcSrc = new(cicNoThrow) CUIFBitmapDC(TRUE);

    if (!CUIFBitmapDC::s_phdcMask)
        CUIFBitmapDC::s_phdcMask = new(cicNoThrow) CUIFBitmapDC(TRUE);

    if (!CUIFBitmapDC::s_phdcDst)
        CUIFBitmapDC::s_phdcDst = new(cicNoThrow) CUIFBitmapDC(TRUE);

    if (CUIFBitmapDC::s_phdcSrc && CUIFBitmapDC::s_phdcMask && CUIFBitmapDC::s_phdcDst)
        CUIFBitmapDC::s_fInitBitmapDCs = TRUE;
}

inline void cicDoneUIFUtil(void)
{
    if (CUIFBitmapDC::s_phdcSrc)
    {
        delete CUIFBitmapDC::s_phdcSrc;
        CUIFBitmapDC::s_phdcSrc = NULL;
    }

    if (CUIFBitmapDC::s_phdcMask)
    {
        delete CUIFBitmapDC::s_phdcMask;
        CUIFBitmapDC::s_phdcMask = NULL;
    }

    if (CUIFBitmapDC::s_phdcDst)
    {
        delete CUIFBitmapDC::s_phdcDst;
        CUIFBitmapDC::s_phdcDst = NULL;
    }

    CUIFBitmapDC::s_fInitBitmapDCs = FALSE;
}

inline HBITMAP cicMirrorBitmap(HBITMAP hBitmap, HBRUSH hbrBack)
{
    BITMAP bm;
    if (!CUIFBitmapDC::s_fInitBitmapDCs || !::GetObject(hBitmap, sizeof(bm), &bm))
        return NULL;

    CUIFBitmapDC::s_phdcSrc->SetBitmap(hBitmap);
    CUIFBitmapDC::s_phdcDst->SetDIB(bm.bmWidth, bm.bmHeight, 1, 32);
    CUIFBitmapDC::s_phdcMask->SetDIB(bm.bmWidth, bm.bmHeight, 1, 32);

    RECT rc = { 0, 0, bm.bmWidth, bm.bmHeight };
    FillRect(*CUIFBitmapDC::s_phdcDst, &rc, hbrBack);

    ::SetLayout(*CUIFBitmapDC::s_phdcMask, LAYOUT_RTL);

    ::BitBlt(*CUIFBitmapDC::s_phdcMask, 0, 0, bm.bmWidth, bm.bmHeight, *CUIFBitmapDC::s_phdcSrc, 0, 0, SRCCOPY);

    ::SetLayout(*CUIFBitmapDC::s_phdcMask, LAYOUT_LTR);

    ::BitBlt(*CUIFBitmapDC::s_phdcDst, 0, 0, bm.bmWidth, bm.bmHeight, *CUIFBitmapDC::s_phdcMask, 1, 0, SRCCOPY);

    CUIFBitmapDC::s_phdcSrc->Uninit();
    CUIFBitmapDC::s_phdcMask->Uninit();
    CUIFBitmapDC::s_phdcDst->Uninit(TRUE);
    return CUIFBitmapDC::s_phdcDst->DetachBitmap();
}

inline HBRUSH cicCreateDitherBrush(VOID)
{
    BYTE bytes[16];
    ZeroMemory(&bytes, sizeof(bytes));
    bytes[0] = bytes[4] = bytes[8] = bytes[12] = 0x55;
    bytes[2] = bytes[6] = bytes[10] = bytes[14] = 0xAA;
    HBITMAP hBitmap = ::CreateBitmap(8, 8, 1, 1, bytes);
    if (!hBitmap)
        return NULL;

    LOGBRUSH lb;
    lb.lbHatch = (ULONG_PTR)hBitmap;
    lb.lbStyle = BS_PATTERN;
    HBRUSH hbr = ::CreateBrushIndirect(&lb);
    ::DeleteObject(hBitmap);
    return hbr;
}

inline HBITMAP
cicCreateDisabledBitmap(LPCRECT prc, HBITMAP hbmMask, HBRUSH hbr1, HBRUSH hbr2, BOOL bPressed)
{
    if (!CUIFBitmapDC::s_fInitBitmapDCs)
        return NULL;

    LONG width = prc->right - prc->left, height = prc->bottom - prc->top;

    CUIFBitmapDC::s_phdcDst->SetDIB(width, height, 1, 32);
    CUIFBitmapDC::s_phdcMask->SetBitmap(hbmMask);
    CUIFBitmapDC::s_phdcSrc->SetDIB(width, height, 1, 32);

    RECT rc = { 0, 0, width, height };
    ::FillRect(*CUIFBitmapDC::s_phdcDst, &rc, hbr1);

    HBRUSH hbrWhite = (HBRUSH)GetStockObject(WHITE_BRUSH);
    ::FillRect(*CUIFBitmapDC::s_phdcSrc, &rc, hbrWhite);

    ::BitBlt(*CUIFBitmapDC::s_phdcSrc, 0, 0, width, height, *CUIFBitmapDC::s_phdcMask, 0, 0, SRCINVERT);
    if (bPressed)
        ::BitBlt(*CUIFBitmapDC::s_phdcDst, 1, 1, width, height,
                 *CUIFBitmapDC::s_phdcSrc, 0, 0, SRCPAINT);
    else
        ::BitBlt(*CUIFBitmapDC::s_phdcDst, 0, 0, width, height,
                 *CUIFBitmapDC::s_phdcSrc, 0, 0, SRCPAINT);

    ::FillRect(*CUIFBitmapDC::s_phdcSrc, &rc, hbr2);

    ::BitBlt(*CUIFBitmapDC::s_phdcSrc, 0, 0, width, height, *CUIFBitmapDC::s_phdcMask, 0, 0, SRCPAINT);
    ::BitBlt(*CUIFBitmapDC::s_phdcDst, 0, 0, width, height, *CUIFBitmapDC::s_phdcSrc, 0, 0, SRCAND);

    CUIFBitmapDC::s_phdcSrc->Uninit();
    CUIFBitmapDC::s_phdcMask->Uninit();
    CUIFBitmapDC::s_phdcDst->Uninit(TRUE);
    return CUIFBitmapDC::s_phdcDst->DetachBitmap();
}

inline HBITMAP
cicCreateShadowMaskBmp(LPRECT prc, HBITMAP hbm1, HBITMAP hbm2, HBRUSH hbr1, HBRUSH hbr2)
{
    if (!CUIFBitmapDC::s_fInitBitmapDCs)
        return NULL;

    --prc->left;
    --prc->top;

    LONG width = prc->right - prc->left;
    LONG height = prc->bottom - prc->top;

    CUIFBitmapDC bitmapDC(TRUE);

    CUIFBitmapDC::s_phdcDst->SetDIB(width, height, 1, 32);
    CUIFBitmapDC::s_phdcSrc->SetBitmap(hbm1);
    CUIFBitmapDC::s_phdcMask->SetBitmap(hbm2);
    bitmapDC.SetDIB(width, height, 1, 32);

    RECT rc = { 0, 0, width, height };

    ::FillRect(*CUIFBitmapDC::s_phdcDst, &rc, hbr1);
    ::FillRect(bitmapDC, &rc, hbr2);

    ::BitBlt(bitmapDC, 0, 0, width, height, *CUIFBitmapDC::s_phdcMask, 0, 0, SRCPAINT);
    ::BitBlt(*CUIFBitmapDC::s_phdcDst, 2, 2, width, height, bitmapDC, 0, 0, SRCAND);
    ::BitBlt(*CUIFBitmapDC::s_phdcDst, 0, 0, width, height, *CUIFBitmapDC::s_phdcMask, 0, 0, SRCAND);
    ::BitBlt(*CUIFBitmapDC::s_phdcDst, 0, 0, width, height, *CUIFBitmapDC::s_phdcSrc, 0, 0, SRCINVERT);

    CUIFBitmapDC::s_phdcSrc->Uninit();
    CUIFBitmapDC::s_phdcMask->Uninit();
    CUIFBitmapDC::s_phdcDst->Uninit(TRUE);
    return CUIFBitmapDC::s_phdcDst->DetachBitmap();
}

inline HBITMAP
cicChangeBitmapColor(LPCRECT prc, HBITMAP hbm, COLORREF rgbBack, COLORREF rgbFore)
{
    if (!CUIFBitmapDC::s_fInitBitmapDCs)
        return NULL;

    INT width = prc->right - prc->left;
    INT height = prc->bottom - prc->top;

    CUIFSolidBrush brush(rgbFore);

    CUIFBitmapDC::s_phdcDst->SetDIB(width, height, 1, 32);
    CUIFBitmapDC::s_phdcSrc->SetBitmap(hbm);
    CUIFBitmapDC::s_phdcMask->SetBitmap(width, height, 1, 1);

    ::BitBlt(*CUIFBitmapDC::s_phdcDst, 0, 0, width, height, *CUIFBitmapDC::s_phdcSrc, 0, 0, SRCCOPY);
    ::SelectObject(*CUIFBitmapDC::s_phdcDst, (HBRUSH)brush);
    ::SetBkColor(*CUIFBitmapDC::s_phdcDst, rgbBack);

    ::BitBlt(*CUIFBitmapDC::s_phdcMask, 0, 0, width, height, *CUIFBitmapDC::s_phdcDst, 0, 0, MERGECOPY);
    ::SetBkColor(*CUIFBitmapDC::s_phdcDst, RGB(255, 255, 255));
    ::SetTextColor(*CUIFBitmapDC::s_phdcDst, RGB(0, 0, 0));
    ::BitBlt(*CUIFBitmapDC::s_phdcDst, 0, 0, width, height, *CUIFBitmapDC::s_phdcMask, 0, 0, 0xE20746u);

    CUIFBitmapDC::s_phdcSrc->Uninit();
    CUIFBitmapDC::s_phdcMask->Uninit();
    CUIFBitmapDC::s_phdcDst->Uninit(TRUE);
    return CUIFBitmapDC::s_phdcDst->DetachBitmap();
}

inline HBITMAP
cicConvertBlackBKGBitmap(LPCRECT prc, HBITMAP hbm1, HBITMAP hbm2, HBRUSH hBrush)
{
    if (!CUIFBitmapDC::s_fInitBitmapDCs)
        return NULL;

    if (IS_INTRESOURCE(hBrush))
        hBrush = ::GetSysColorBrush(HandleToLong(hBrush) - 1);

    LOGBRUSH lb;
    ::GetObject(hBrush, sizeof(lb), &lb);
    if (lb.lbStyle || lb.lbColor)
        return NULL;

    INT width = prc->right - prc->left;
    INT height = prc->bottom - prc->top;

    HBITMAP hBitmap = cicChangeBitmapColor(prc, hbm1, 0, RGB(255, 255, 255));
    if ( !hBitmap )
        return NULL;

    CUIFBitmapDC::s_phdcDst->SetDIB(width, height, 1, 32);
    CUIFBitmapDC::s_phdcSrc->SetBitmap(hBitmap);
    CUIFBitmapDC::s_phdcMask->SetBitmap(hbm2);

    RECT rc = { 0, 0, width, height };

    HBRUSH hbrWhite = (HBRUSH)GetStockObject(WHITE_BRUSH);
    ::FillRect(*CUIFBitmapDC::s_phdcDst, &rc, hbrWhite);

    ::BitBlt(*CUIFBitmapDC::s_phdcDst, 0, 0, width, height, *CUIFBitmapDC::s_phdcMask, 0, 0, 0x660046u);
    ::BitBlt(*CUIFBitmapDC::s_phdcDst, 0, 0, width, height, *CUIFBitmapDC::s_phdcSrc, 0, 0, 0x8800C6u);

    CUIFBitmapDC::s_phdcSrc->Uninit();
    CUIFBitmapDC::s_phdcMask->Uninit();
    CUIFBitmapDC::s_phdcDst->Uninit(TRUE);
    ::DeleteObject(hBitmap);
    return CUIFBitmapDC::s_phdcDst->DetachBitmap();
}

inline HBITMAP
cicCreateMaskBmp(LPCRECT prc, HBITMAP hbm1, HBITMAP hbm2,
                 HBRUSH hbr, COLORREF rgbColor, COLORREF rgbBack)
{
    if (!CUIFBitmapDC::s_fInitBitmapDCs)
        return NULL;

    INT width = prc->right - prc->left;
    INT height = prc->bottom - prc->top;
    HBITMAP hBitmap = cicConvertBlackBKGBitmap(prc, hbm1, hbm2, hbr);
    if (hBitmap)
        return hBitmap;

    CUIFBitmapDC::s_phdcDst->SetDIB(width, height, 1, 32);
    CUIFBitmapDC::s_phdcSrc->SetBitmap(hbm1);
    CUIFBitmapDC::s_phdcMask->SetBitmap(hbm2);

    RECT rc = { 0, 0, width, height };

    COLORREF OldTextColor = ::SetTextColor(*CUIFBitmapDC::s_phdcDst, rgbColor);
    COLORREF OldBkColor = ::SetBkColor(*CUIFBitmapDC::s_phdcDst, rgbBack);
    ::FillRect(*CUIFBitmapDC::s_phdcDst, &rc, hbr);
    ::SetTextColor(*CUIFBitmapDC::s_phdcDst, OldTextColor);
    ::SetBkColor(*CUIFBitmapDC::s_phdcDst, OldBkColor);

    ::BitBlt(*CUIFBitmapDC::s_phdcDst, 0, 0, width, height, *CUIFBitmapDC::s_phdcMask, 0, 0, SRCAND);
    ::BitBlt(*CUIFBitmapDC::s_phdcDst, 0, 0, width, height, *CUIFBitmapDC::s_phdcSrc, 0, 0, SRCINVERT);
    CUIFBitmapDC::s_phdcSrc->Uninit();
    CUIFBitmapDC::s_phdcMask->Uninit();
    CUIFBitmapDC::s_phdcDst->Uninit(TRUE);

    return CUIFBitmapDC::s_phdcDst->DetachBitmap();
}

inline BOOL cicGetIconBitmaps(HICON hIcon, HBITMAP *hbm1, HBITMAP *hbm2, const SIZE *pSize)
{
    if (!CUIFBitmapDC::s_fInitBitmapDCs)
        return NULL;

    LONG cx, cy;
    SIZE size;
    if (pSize)
    {
        size = *pSize;
    }
    else
    {
        if (!cicGetIconSize(hIcon, &size))
            return FALSE;
    }

    CUIFBitmapDC::s_phdcSrc->SetDIB(cx, cy, 1, 32);
    CUIFBitmapDC::s_phdcMask->SetBitmap(cx, cy, 1, 1);

    RECT rc = { 0, 0, size.cx, size.cy };
    ::FillRect(*CUIFBitmapDC::s_phdcSrc, &rc, (HBRUSH)GetStockObject(BLACK_BRUSH));

    ::DrawIconEx(*CUIFBitmapDC::s_phdcSrc, 0, 0, hIcon, size.cx, size.cy, 0, 0, DI_NORMAL);
    ::DrawIconEx(*CUIFBitmapDC::s_phdcMask, 0, 0, hIcon, size.cx, size.cy, 0, 0, DI_MASK);

    CUIFBitmapDC::s_phdcSrc->Uninit(TRUE);
    CUIFBitmapDC::s_phdcMask->Uninit(TRUE);
    *hbm1 = CUIFBitmapDC::s_phdcSrc->DetachBitmap();
    *hbm2 = CUIFBitmapDC::s_phdcMask->DetachBitmap();
    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////

inline CUIFWindow::CUIFWindow(HINSTANCE hInst, DWORD style)
    : CUIFObject(NULL, 0, NULL, style)
{
    m_hInst = hInst;
    m_nLeft = 200;
    m_nTop = 200;
    m_nWidth = 200;
    m_nHeight = 200;
    m_hWnd = 0;
    m_pWindow = this;
    m_pCaptured = NULL;
    m_pUnknown7 = NULL;
    m_pPointed = NULL;
    m_bPointing = FALSE;
    m_pToolTip = NULL;
    m_pShadow = NULL;
    m_bShowShadow = TRUE;
    m_pPointingWindow = NULL;
    CUIFWindow::CreateScheme();
}

inline CUIFWindow::~CUIFWindow()
{
    if (m_pToolTip)
    {
        delete m_pToolTip;
        m_pToolTip = NULL;
    }
    if (m_pShadow)
    {
        delete m_pShadow;
        m_pShadow = NULL;
    }
    for (size_t i = m_ObjectArray.size(); i > 0; )
    {
        --i;
        CUIFObject *pObject = m_ObjectArray[i];
        m_ObjectArray[i] = NULL;
        m_ObjectArray.Remove(pObject);
        delete pObject;
    }
    if (m_pScheme)
    {
        delete m_pScheme;
        m_pScheme = NULL;
    }
}

inline STDMETHODIMP_(void)
CUIFWindow::Initialize()
{
    LPCTSTR pszClass = GetClassName();

    WNDCLASSEX wcx;
    ZeroMemory(&wcx, sizeof(wcx));
    wcx.cbSize = sizeof(WNDCLASSEXW);
    if (!::GetClassInfoEx(m_hInst, pszClass, &wcx))
    {
        ZeroMemory(&wcx, sizeof(wcx));
        wcx.cbSize = sizeof(wcx);
        wcx.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
        wcx.lpfnWndProc = CUIFWindow::WindowProcedure;
        wcx.cbClsExtra = 0;
        wcx.cbWndExtra = sizeof(LONG_PTR) * 2;
        wcx.hInstance = m_hInst;
        wcx.hIcon = NULL;
        wcx.hCursor = ::LoadCursor(NULL, IDC_ARROW);
        wcx.lpszClassName = pszClass;
        wcx.hbrBackground = NULL;
        wcx.lpszMenuName = NULL;
        wcx.hIconSm = NULL;
        ::RegisterClassEx(&wcx);
    }

    cicUpdateUIFSys();
    cicUpdateUIFScheme();

    if (m_style & UIF_WINDOW_TOOLTIP)
    {
        DWORD style = (m_style & UIF_WINDOW_LAYOUTRTL) | UIF_WINDOW_TOPMOST | 0x10;
        m_pToolTip = new(cicNoThrow) CUIFToolTip(m_hInst, style, this);
        if (m_pToolTip)
            m_pToolTip->Initialize();
    }

    if (m_style & UIF_WINDOW_SHADOW)
    {
        m_pShadow = new(cicNoThrow) CUIFShadow(m_hInst, UIF_WINDOW_TOPMOST, this);
        if (m_pShadow)
            m_pShadow->Initialize();
    }

    return CUIFObject::Initialize();
}

inline STDMETHODIMP_(void)
CUIFWindow::OnUser(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  ;
}

inline STDMETHODIMP_(LRESULT)
CUIFWindow::OnSettingChange(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
}

inline void CUIFWindow::UpdateUI(LPCRECT prc)
{
    if (::IsWindow(m_hWnd))
        ::InvalidateRect(m_hWnd, prc, FALSE);
}

inline STDMETHODIMP_(void)
CUIFWindow::OnCreate(HWND hWnd)
{
}

inline STDMETHODIMP_(void)
CUIFWindow::OnDestroy(HWND hWnd)
{

}

inline STDMETHODIMP_(void)
CUIFWindow::OnNCDestroy(HWND hWnd)
{
}

inline STDMETHODIMP_(void)
CUIFWindow::OnKeyUp(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
}

inline CUIFWindow*
CUIFWindow::GetThis(HWND hWnd)
{
    return (CUIFWindow *)GetWindowLongPtr(hWnd, GWLP_USERDATA);
}

inline void
CUIFWindow::SetThis(HWND hWnd, LONG_PTR dwNewLong)
{
    ::SetWindowLongPtr(hWnd, GWLP_USERDATA, dwNewLong);
}

inline void CUIFWindow::CreateScheme()
{
    if (m_pScheme)
    {
        delete m_pScheme;
        m_pScheme = NULL;
    }

    INT iScheme = 0;
    if (m_style & 0x10000000)
        iScheme = 1;
    else if (m_style & 0x20000000)
        iScheme = 2;
    else if (m_style & 0x40000000)
        iScheme = 3;
    else
        iScheme = 0;

    m_pScheme = cicCreateUIFScheme(iScheme);
    SetScheme(m_pScheme);
}

inline LPCTSTR CUIFWindow::GetClassName()
{
    return TEXT("CiceroUIWndFrame");
}

inline LPCTSTR CUIFWindow::GetWndTitle()
{
    return TEXT("CiceroUIWndFrame");
}

inline STDMETHODIMP_(DWORD)
CUIFWindow::GetWndStyle()
{
    DWORD ret;

    if (m_style & UIF_WINDOW_CHILD)
        ret = WS_CHILD | WS_CLIPSIBLINGS;
    else
        ret = WS_POPUP | WS_DISABLED;

    if (m_style & 0x10000000)
        ret |= WS_BORDER;
    else if (m_style & UIF_WINDOW_DLGFRAME)
        ret |= WS_DLGFRAME;
    else if ((m_style & 0x20000000) || (m_style & 0x10))
        ret |= WS_BORDER;

    return ret;
}

inline STDMETHODIMP_(DWORD)
CUIFWindow::GetWndStyleEx()
{
    DWORD ret = 0;
    if (m_style & UIF_WINDOW_TOPMOST)
        ret |= WS_EX_TOPMOST;
    if (m_style & UIF_WINDOW_TOOLWINDOW)
        ret |= WS_EX_TOOLWINDOW;
    if (m_style & UIF_WINDOW_LAYOUTRTL)
        ret |= WS_EX_LAYOUTRTL;
    return ret;
}

inline STDMETHODIMP_(HWND)
CUIFWindow::CreateWnd(HWND hwndParent)
{
    HWND hWnd = CreateWindowEx(GetWndStyleEx(), GetClassName(), GetWndTitle(), GetWndStyle(),
                               m_nLeft, m_nTop, m_nWidth, m_nHeight,
                               hwndParent, NULL, m_hInst, this);
    if (m_pToolTip)
        m_pToolTip->CreateWnd(hWnd);
    if (m_pShadow)
        m_pShadow->CreateWnd(hWnd);
    return hWnd;
}

inline void CUIFWindow::Show(BOOL bVisible)
{
    if (!IsWindow(m_hWnd))
        return;

    if (bVisible && (m_style & UIF_WINDOW_TOPMOST))
        ::SetWindowPos(m_hWnd, NULL, 0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE);

    m_bVisible = bVisible;
    ::ShowWindow(m_hWnd, (bVisible ? SW_SHOWNOACTIVATE : 0));
}

inline STDMETHODIMP_(BOOL)
CUIFWindow::AnimateWnd(DWORD dwTime, DWORD dwFlags)
{
    if (!::IsWindow(m_hWnd))
        return FALSE;

    BOOL bVisible = !(dwFlags & 0x10000);
    OnAnimationStart();
    BOOL ret = ::AnimateWindow(m_hWnd, dwTime, dwFlags);
    if (!ret)
        m_bVisible = bVisible;
    OnAnimationEnd();
    return ret;
}

inline void CUIFWindow::SetCaptureObject(CUIFObject *pCaptured)
{
    if (pCaptured)
    {
        m_pCaptured = pCaptured;
        SetCapture(TRUE);
    }
    else
    {
        m_pCaptured = NULL;
        SetCapture(FALSE);
    }
}

inline STDMETHODIMP_(void)
CUIFWindow::SetCapture(BOOL bSet)
{
    if (bSet)
        ::SetCapture(m_hWnd);
    else
        ::ReleaseCapture();
}

inline void CUIFWindow::SetObjectPointed(CUIFObject *pPointed, POINT pt)
{
    if (pPointed == m_pPointed)
        return;

    if (m_pCaptured)
    {
        if (m_pCaptured == m_pPointed && m_pPointed->m_bEnable)
            m_pPointed->OnMouseOut(pt.x, pt.y);
    }
    else if (m_pPointed && m_pPointed->m_bEnable)
    {
        m_pPointed->OnMouseOut(pt.x, pt.y);
    }

    m_pPointed = pPointed;

    if (m_pCaptured)
    {
        if (m_pCaptured == m_pPointed && m_pPointed->m_bEnable)
            m_pPointed->OnMouseIn(pt.x, pt.y);
    }
    else if (m_pPointed && m_pPointed->m_bEnable)
    {
        m_pPointed->OnMouseIn(pt.x, pt.y);
    }
}

inline STDMETHODIMP_(void)
CUIFWindow::OnObjectMoved(CUIFObject *pObject)
{
    if (!::IsWindow(m_hWnd))
        return;

    POINT pt;
    ::GetCursorPos(&pt);
    ::ScreenToClient(m_hWnd, &pt);
    POINT pt2 = pt;
    CUIFObject *pFound = ObjectFromPoint(pt);
    SetObjectPointed(pFound, pt2);
}

inline STDMETHODIMP_(void)
CUIFWindow::SetRect(LPCRECT prc)
{
    RECT Rect = { 0, 0, 0, 0 };

    if (::IsWindow(m_hWnd))
        ::GetClientRect(m_hWnd, &Rect);

    CUIFObject::SetRect(&Rect);
}

inline STDMETHODIMP_(void)
CUIFWindow::ClientRectToWindowRect(LPRECT lpRect)
{
    DWORD style, exstyle;
    if (::IsWindow(m_hWnd))
    {
        style = ::GetWindowLongPtr(m_hWnd, GWL_STYLE);
        exstyle = ::GetWindowLongPtr(m_hWnd, GWL_EXSTYLE);
    }
    else
    {
        style = GetWndStyle();
        exstyle = GetWndStyleEx();
    }
    ::AdjustWindowRectEx(lpRect, style, FALSE, exstyle);
}

inline STDMETHODIMP_(void)
CUIFWindow::GetWindowFrameSize(LPSIZE pSize)
{
    RECT rc = { 0, 0, 0, 0 };

    ClientRectToWindowRect(&rc);
    pSize->cx = (rc.right - rc.left) / 2;
    pSize->cy = (rc.bottom - rc.top) / 2;
}

inline STDMETHODIMP_(void)
CUIFWindow::OnAnimationEnd()
{
    if (m_pShadow && m_bShowShadow)
        m_pShadow->Show(m_bVisible);
}

inline STDMETHODIMP_(void)
CUIFWindow::OnThemeChanged(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    ClearTheme();
}

inline LRESULT
CUIFWindow::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_GETOBJECT:
            return OnGetObject(hWnd, WM_GETOBJECT, wParam, lParam);

        case WM_SYSCOLORCHANGE:
            cicUpdateUIFScheme();
            OnSysColorChange();
            return 0;

        case WM_ENDSESSION:
            OnEndSession(hWnd, wParam, lParam);
            return 0;

        case WM_SHOWWINDOW:
            if (m_pShadow && m_bShowShadow)
                m_pShadow->Show(wParam);
            return OnShowWindow(hWnd, WM_SHOWWINDOW, wParam, lParam);

        case WM_SETTINGCHANGE:
            cicUpdateUIFSys();
            cicUpdateUIFScheme();
            return OnSettingChange(hWnd, WM_SETTINGCHANGE, wParam, lParam);
        case WM_SETCURSOR:
        {
            POINT Point;
            ::GetCursorPos(&Point);
            ::ScreenToClient(m_hWnd, &Point);

            if (m_pPointingWindow)
            {
                m_pPointingWindow->OnPointingMouse(HIWORD(lParam), Point.x, Point.y);
                return TRUE;
            }

            if (!m_bPointing)
            {
                ::SetTimer(m_hWnd, POINTING_TIMER_ID, 1000, NULL);
                m_bPointing = TRUE;
            }

            if (m_pToolTip)
            {
                MSG msg = { m_hWnd, HIWORD(lParam), 0, MAKELPARAM(Point.x, Point.y) };
                m_pToolTip->RelayEvent(&msg);
            }

            if (!(m_style & UIF_WINDOW_NOMOUSEMSG))
                HandleMouseMsg(HIWORD(lParam), Point.x, Point.y);

            return TRUE;
        }
        case WM_MOUSEACTIVATE:
            return MA_NOACTIVATE;
        case WM_ERASEBKGND:
            return OnEraseBkGnd(hWnd, WM_ERASEBKGND, wParam, lParam);
        case WM_CREATE:
            SetRect(NULL);
            OnCreate(hWnd);
            return 0;
        case WM_DESTROY:
            if (m_pToolTip && ::IsWindow(*m_pToolTip))
                ::DestroyWindow(*m_pToolTip);
            if (m_pShadow && ::IsWindow(*m_pShadow))
                ::DestroyWindow(*m_pShadow);
            OnDestroy(hWnd);
            return 0;
        case WM_SIZE:
            SetRect(NULL);
            return 0;
        case WM_ACTIVATE:
            return OnActivate(hWnd, WM_ACTIVATE, wParam, lParam);
        case WM_SETFOCUS:
            OnSetFocus(hWnd);
            return 0;
        case WM_KILLFOCUS:
            OnKillFocus(hWnd);
            return 0;
        case WM_PAINT:
        {
            PAINTSTRUCT Paint;
            HDC hDC = ::BeginPaint(hWnd, &Paint);
            PaintObject(hDC, &Paint.rcPaint);
            ::EndPaint(hWnd, &Paint);
            return 0;
        }
        case WM_PRINTCLIENT:
        {
            PaintObject((HDC)wParam, NULL);
            return 0;
        }
        case WM_THEMECHANGED:
        {
            OnThemeChanged(hWnd, wParam, lParam);
            return 0;
        }
        case WM_COMMAND:
        {
            return 0;
        }
        case WM_TIMER:
        {
            switch (wParam)
            {
                case 0x5461:
                {
                    if (m_pUnknown7)
                        m_pUnknown7->OnUnknown9();
                    break;
                }
                case POINTING_TIMER_ID:
                {
                    POINT pt;
                    ::GetCursorPos(&pt);

                    POINT pt2 = pt;
                    ::ScreenToClient(m_hWnd, &pt2);

                    RECT rc;
                    ::GetWindowRect(m_hWnd, &rc);

                    if (::PtInRect(&rc, pt) && ::WindowFromPoint(pt) == m_hWnd)
                    {
                        m_pPointingWindow->OnPointingMouse(WM_MOUSEMOVE, pt2.x, pt2.y);
                    }
                    else
                    {
                        ::KillTimer(m_hWnd, POINTING_TIMER_ID);
                        m_bPointing = FALSE;
                        SetObjectPointed(NULL, pt2);
                        OnPointingEnded(pt2.x, pt2.y);
                    }

                    if (m_pToolTip)
                    {
                        MSG msg = { m_hWnd, WM_MOUSEMOVE, 0, MAKELPARAM(pt2.x, pt2.y) };
                        m_pToolTip->RelayEvent(&msg);
                    }
                    break;
                }
                default:
                {
                    OnTimer(wParam);
                    break;
                }
            }
            break;
        }
        case WM_MOUSEMOVE:
        case WM_LBUTTONDOWN:
        case WM_LBUTTONDBLCLK:
        case WM_LBUTTONUP:
        case WM_MBUTTONDOWN:
        case WM_MBUTTONDBLCLK:
        case WM_MBUTTONUP:
        case WM_RBUTTONDOWN:
        case WM_RBUTTONDBLCLK:
        case WM_RBUTTONUP:
        {
            if (m_pPointingWindow)
                m_pPointingWindow->OnPointingMouse(uMsg, (SHORT)LOWORD(lParam), (SHORT)HIWORD(lParam));
            else
                HandleMouseMsg(uMsg, (SHORT)LOWORD(lParam), (SHORT)HIWORD(lParam));
            break;
        }
        case WM_KEYUP:
        {
            OnKeyUp(hWnd, wParam, lParam);
            break;
        }
        case WM_WINDOWPOSCHANGING:
        {
            WINDOWPOS *pwp = (WINDOWPOS *)lParam;
            if (m_pShadow && (pwp->flags & SWP_HIDEWINDOW))
                m_pShadow->Show(FALSE);
            if (!(pwp->flags & SWP_NOZORDER) && pwp->hwndInsertAfter == m_pShadow->m_hWnd)
                pwp->flags |= SWP_NOZORDER;
            m_pShadow->OnOwnerWndMoved(!(pwp->flags & SWP_NOSIZE));
            return OnWindowPosChanging(hWnd, WM_WINDOWPOSCHANGING, wParam, lParam);
        }
        case WM_WINDOWPOSCHANGED:
        {
            WINDOWPOS *pwp = (WINDOWPOS *)lParam;
            if (m_pShadow)
                m_pShadow->OnOwnerWndMoved(!(pwp->flags & SWP_NOSIZE));
            return OnWindowPosChanged(hWnd, WM_WINDOWPOSCHANGED, wParam, lParam);
        }
        case WM_NOTIFY:
            OnNotify(hWnd, wParam, lParam);
            return 0;
        case WM_NOTIFYFORMAT:
            return OnNotifyFormat(hWnd, wParam, lParam);
        case WM_DISPLAYCHANGE:
            cicUpdateUIFSys();
            cicUpdateUIFScheme();
            return OnDisplayChange(hWnd, WM_DISPLAYCHANGE, wParam, lParam);
        case WM_NCDESTROY:
            OnNCDestroy(hWnd);
            return 0;
        case WM_KEYDOWN:
            OnKeyDown(hWnd, wParam, lParam);
            return 0;
        default:
        {
            if (uMsg >= WM_USER)
            {
                CUIFWindow *pThis = CUIFWindow::GetThis(hWnd);
                pThis->OnUser(hWnd, uMsg, wParam, lParam);
                break;
            }
            return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
        }
    }

    return 0;
}

inline LRESULT CALLBACK
CUIFWindow::WindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    CUIFWindow *This;

    if (uMsg == WM_NCCREATE)
    {
        This = (CUIFWindow*)((CREATESTRUCT*)lParam)->lpCreateParams;
        CUIFWindow::SetThis(hWnd, (LONG_PTR)This);
        This->m_hWnd = hWnd;
    }
    else
    {
        This = CUIFWindow::GetThis(hWnd);
    }

    if (uMsg == WM_GETMINMAXINFO)
    {
        if (This)
            return This->WindowProc(hWnd, uMsg, wParam, lParam);
        else
            return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
    }

    if (!This)
        return 0;

    if (uMsg == WM_NCDESTROY)
    {
        This->m_hWnd = NULL;
        ::SetWindowLongPtr(hWnd, GWLP_USERDATA, 0);
    }

    return This->WindowProc(hWnd, uMsg, wParam, lParam);
}

inline BOOL
CUIFWindow::GetWorkArea(LPCRECT prcWnd, LPRECT prcWorkArea)
{
    if (!(m_style & (UIF_WINDOW_WORKAREA | UIF_WINDOW_MONITOR)))
        return FALSE;

    HMONITOR hMon = ::MonitorFromRect(prcWnd, MONITOR_DEFAULTTONEAREST);
    MONITORINFO mi;
    mi.cbSize = sizeof(MONITORINFO);
    if (!hMon || !::GetMonitorInfo(hMon, &mi))
    {
        if (m_style & UIF_WINDOW_WORKAREA)
            return ::SystemParametersInfo(SPI_GETWORKAREA, 0, prcWorkArea, 0);

        prcWorkArea->left = prcWorkArea->top = 0;
        prcWorkArea->right = ::GetSystemMetrics(SM_CXSCREEN);
        prcWorkArea->bottom = ::GetSystemMetrics(SM_CYSCREEN);
        return TRUE;
    }

    if (m_style & UIF_WINDOW_WORKAREA)
    {
        *prcWorkArea = mi.rcWork;
        return TRUE;
    }

    *prcWorkArea = mi.rcMonitor;
    return TRUE;
}

inline void
CUIFWindow::AdjustWindowPosition()
{
    RECT rc;
    rc.left = m_nLeft;
    rc.right = m_nLeft + m_nWidth;
    rc.top = m_nTop;
    rc.bottom = m_nTop + m_nHeight;

    RECT rcWorkArea;
    if (!GetWorkArea(&rc, &rcWorkArea))
        return;

    if (m_nLeft < rcWorkArea.left)
        m_nLeft = rcWorkArea.left;
    if (m_nTop < rcWorkArea.top)
        m_nTop = rcWorkArea.top;
    if (m_nLeft + m_nWidth >= rcWorkArea.right)
        m_nLeft = rcWorkArea.right - m_nWidth;
    if (m_nTop + m_nHeight >= rcWorkArea.bottom)
        m_nTop = rcWorkArea.bottom - m_nHeight;
}

/// @unimplemented
inline STDMETHODIMP_(void)
CUIFWindow::PaintObject(HDC hDC, LPCRECT prc)
{
    BOOL bGotDC = FALSE;
    if (!hDC)
    {
        hDC = ::GetDC(m_hWnd);
        bGotDC = TRUE;
    }

    LPCRECT pRect = prc;
    if (!pRect)
        pRect = &m_rc;

    HDC hMemDC = ::CreateCompatibleDC(hDC);
    if (!hMemDC)
        return;

    HBITMAP hbmMem = ::CreateCompatibleBitmap(hDC,
                                              pRect->right - pRect->left,
                                              pRect->bottom - pRect->top);
    if (hbmMem)
    {
        HGDIOBJ hbmOld = ::SelectObject(hMemDC, hbmMem);
        ::SetViewportOrgEx(hMemDC, -pRect->left, -pRect->top, NULL);

        if ((FAILED(CUIFTheme::EnsureThemeData(m_hWnd)) ||
             !(m_style & UIF_WINDOW_CHILD) ||
             FAILED(DrawThemeParentBackground(m_hWnd, hMemDC, &m_rc))) &&
            FAILED(DrawThemeBackground(hMemDC, m_iStateId, &m_rc, 0)))
        {
            if (m_pScheme)
                m_pScheme->FillRect(hMemDC, pRect, 22);
        }
        CUIFObject::PaintObject(hMemDC, pRect);
        ::BitBlt(hDC,
                 pRect->left, pRect->top,
                 pRect->right - pRect->left, pRect->bottom - pRect->top,
                 hMemDC,
                 pRect->left, pRect->top,
                 SRCCOPY);
        ::SelectObject(hMemDC, hbmOld);
        ::DeleteObject(hbmMem);
    }
    ::DeleteDC(hMemDC);

    if (bGotDC)
        ::ReleaseDC(m_hWnd, hDC);
}

inline STDMETHODIMP_(void)
CUIFWindow::Move(INT x, INT y, INT nWidth, INT nHeight)
{
    m_nLeft = x;
    m_nTop = y;
    if (nWidth >= 0)
        m_nWidth = nWidth;
    if (nHeight >= 0)
        m_nHeight = nHeight;
    if (::IsWindow(m_hWnd))
    {
        AdjustWindowPosition();
        ::MoveWindow(m_hWnd, m_nLeft, m_nTop, m_nWidth, m_nHeight, TRUE);
    }
}

inline STDMETHODIMP_(void)
CUIFWindow::RemoveUIObj(CUIFObject *pRemove)
{
    if (pRemove == m_pCaptured)
        SetCaptureObject(NULL);

    if (pRemove == m_pUnknown7)
    {
        m_pUnknown7 = NULL;
        ::KillTimer(m_hWnd, 0x5461);
    }

    if (pRemove == m_pPointed)
        m_pPointed = NULL;
    CUIFObject::RemoveUIObj(pRemove);
}

inline STDMETHODIMP_(void)
CUIFWindow::HandleMouseMsg(UINT uMsg, LONG x, LONG y)
{
    POINT pt = { x, y };

    CUIFObject *pFound = (CUIFWindow *)ObjectFromPoint(pt);

    SetObjectPointed(pFound, pt);

    if (m_pCaptured)
        pFound = m_pCaptured;

    if (!pFound || OnSetCursor(uMsg, pt.x, pt.y))
    {
        HCURSOR hCursor = ::LoadCursor(NULL, IDC_ARROW);
        ::SetCursor(hCursor);
    }

    if (pFound && pFound->m_bEnable)
    {
        switch (uMsg)
        {
            case WM_MOUSEMOVE:
                pFound->OnMouseMove(pt.x, pt.y);
                break;
            case WM_LBUTTONDOWN:
                pFound->OnLButtonDown(pt.x, pt.y);
                break;
            case WM_LBUTTONUP:
                pFound->OnLButtonUp(pt.x, pt.y);
                break;
            case WM_RBUTTONDOWN:
                pFound->OnRButtonDown(pt.x, pt.y);
                break;
            case WM_RBUTTONUP:
                pFound->OnRButtonUp(pt.x, pt.y);
                break;
            case WM_MBUTTONDOWN:
                pFound->OnMButtonDown(pt.x, pt.y);
                break;
            case WM_MBUTTONUP:
                pFound->OnMButtonUp(pt.x, pt.y);
                break;
        }
    }
}

inline STDMETHODIMP_(void)
CUIFWindow::OnSetFocus(HWND hWnd)
{
}

inline STDMETHODIMP_(void)
CUIFWindow::OnPointingEnded(LONG x, LONG y)
{
}

inline STDMETHODIMP_(void)
CUIFWindow::OnKillFocus(HWND hWnd)
{
}

inline STDMETHODIMP_(void)
CUIFWindow::OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
}

inline STDMETHODIMP_(void)
CUIFWindow::OnTimer(WPARAM wParam)
{
}

inline STDMETHODIMP_(void)
CUIFWindow::OnSysColorChange()
{
}

inline STDMETHODIMP_(void)
CUIFWindow::OnEndSession(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
}

inline STDMETHODIMP_(void)
CUIFWindow::OnKeyDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
}

inline STDMETHODIMP_(LRESULT)
CUIFWindow::OnActivate(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    return 0;
}

inline STDMETHODIMP_(LRESULT)
CUIFWindow::OnWindowPosChanged(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    return 0;
}

inline STDMETHODIMP_(LRESULT)
CUIFWindow::OnWindowPosChanging(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    return 0;
}

inline STDMETHODIMP_(LRESULT)
CUIFWindow::OnNotifyFormat(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    return 0;
}

inline STDMETHODIMP_(LRESULT)
CUIFWindow::OnShowWindow(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    return 0;
}

inline STDMETHODIMP_(LRESULT)
CUIFWindow::OnDisplayChange(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    return 0;
}

inline STDMETHODIMP_(LRESULT)
CUIFWindow::OnGetObject(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    return 0;
}

inline STDMETHODIMP_(BOOL)
CUIFWindow::OnEraseBkGnd(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

inline STDMETHODIMP_(void)
CUIFWindow::OnPointingMouse(UINT uMsg, LONG x, LONG y)
{
}

inline STDMETHODIMP_(void)
CUIFWindow::OnAnimationStart()
{
}

/////////////////////////////////////////////////////////////////////////////

/// @unimplemented
inline CUIFShadow::CUIFShadow(HINSTANCE hInst, DWORD style, CUIFWindow *pShadowOwner)
    : CUIFWindow(hInst, (style | UIF_WINDOW_TOOLWINDOW))
{
    m_pShadowOwner = pShadowOwner;
    m_rgbShadowColor = RGB(0, 0, 0);
    m_dwUnknown11[0] = 0;
    m_dwUnknown11[1] = 0;
    m_xShadowDelta = m_yShadowDelta = 0;
    m_bLayerAvailable = FALSE;
}

inline CUIFShadow::~CUIFShadow()
{
    if (m_pShadowOwner)
        m_pShadowOwner->m_pShadow = NULL;
}

/// @unimplemented
inline void CUIFShadow::InitSettings()
{
    m_bLayerAvailable = FALSE;
    m_rgbShadowColor = RGB(128, 128, 128);
    m_xShadowDelta = m_yShadowDelta = 2;
}

/// @unimplemented
inline void CUIFShadow::InitShadow()
{
    if (m_bLayerAvailable)
    {
        //FIXME
    }
}

inline void CUIFShadow::AdjustWindowPos()
{
    HWND hwndOwner = *m_pShadowOwner;
    if (!::IsWindow(m_hWnd))
        return;

    RECT rc;
    ::GetWindowRect(hwndOwner, &rc);
    ::SetWindowPos(m_hWnd, hwndOwner,
                   rc.left + m_xShadowDelta,
                   rc.top + m_yShadowDelta,
                   rc.right - rc.left,
                   rc.bottom - rc.top,
                   SWP_NOOWNERZORDER | SWP_NOACTIVATE);
}

inline void CUIFShadow::OnOwnerWndMoved(BOOL bDoSize)
{
    if (::IsWindow(m_hWnd) && ::IsWindowVisible(m_hWnd))
    {
        AdjustWindowPos();
        if (bDoSize)
            InitShadow();
    }
}

inline STDMETHODIMP_(void)
CUIFShadow::Initialize()
{
    InitSettings();
    CUIFWindow::Initialize();
}

inline STDMETHODIMP_(DWORD)
CUIFShadow::GetWndStyleEx()
{
    DWORD exstyle = CUIFWindow::GetWndStyleEx();
    if (m_bLayerAvailable)
        exstyle |= WS_EX_LAYERED;
    return exstyle;
}

inline STDMETHODIMP_(void)
CUIFShadow::OnPaint(HDC hDC)
{
    RECT rc = m_rc;
    HBRUSH hBrush = ::CreateSolidBrush(m_rgbShadowColor);
    ::FillRect(hDC, &rc, hBrush);
    ::DeleteObject(hBrush);
}

inline STDMETHODIMP_(LRESULT)
CUIFShadow::OnWindowPosChanging(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    WINDOWPOS *wp = (WINDOWPOS *)lParam;
    wp->hwndInsertAfter = *m_pShadowOwner;
    return ::DefWindowProc(hWnd, Msg, wParam, lParam);
}

inline STDMETHODIMP_(LRESULT)
CUIFShadow::OnSettingChange(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    InitSettings();

    DWORD exstyle;
    if (m_bLayerAvailable)
        exstyle = ::GetWindowLongPtr(m_hWnd, GWL_EXSTYLE) | WS_EX_LAYERED;
    else
        exstyle = ::GetWindowLongPtr(m_hWnd, GWL_EXSTYLE) & ~WS_EX_LAYERED;

    ::SetWindowLongPtr(m_hWnd, GWL_EXSTYLE, exstyle);

    AdjustWindowPos();
    InitShadow();

    return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
}

inline STDMETHODIMP_(void)
CUIFShadow::Show(BOOL bVisible)
{
    if (bVisible && ::IsWindow(m_hWnd) && !::IsWindowVisible(m_hWnd))
    {
        AdjustWindowPos();
        InitShadow();
    }

    if (::IsWindow(m_hWnd))
    {
        m_bVisible = bVisible;
        ::ShowWindow(m_hWnd, (bVisible ? SW_SHOWNOACTIVATE : SW_HIDE));
    }
}

/////////////////////////////////////////////////////////////////////////////

inline
CUIFToolTip::CUIFToolTip(HINSTANCE hInst, DWORD style, CUIFWindow *pToolTipOwner)
    : CUIFWindow(hInst, style)
{
    m_pToolTipOwner = pToolTipOwner;
    m_rcToolTipMargin.left = 2;
    m_rcToolTipMargin.top = 2;
    m_rcToolTipMargin.right = 2;
    m_rcToolTipMargin.bottom = 2;
    m_pToolTipTarget = NULL;
    m_pszToolTipText = NULL;
    m_dwUnknown10 = 0; //FIXME: name and type
    m_nDelayTimeType2 = -1;
    m_nDelayTimeType3 = -1;
    m_nDelayTimeType1 = -1;
    m_cxToolTipWidth = -1;
    m_bToolTipHasBkColor = 0;
    m_bToolTipHasTextColor = 0;
    m_rgbToolTipBkColor = 0;
    m_rgbToolTipTextColor = 0;
}

inline
CUIFToolTip::~CUIFToolTip()
{
    if (m_pToolTipOwner)
        m_pToolTipOwner->m_pToolTip = NULL;
    if (m_pszToolTipText)
        delete[] m_pszToolTipText;
}

inline LONG
CUIFToolTip::GetDelayTime(UINT uType)
{
    LONG nDelayTime;
    switch (uType)
    {
        case 1:
        {
            nDelayTime = m_nDelayTimeType1;
            if (nDelayTime == -1)
                return ::GetDoubleClickTime() / 5;
            return nDelayTime;
        }
        case 2:
        {
            nDelayTime = m_nDelayTimeType2;
            if (nDelayTime == -1)
                return 10 * ::GetDoubleClickTime();
            return nDelayTime;
        }
        case 3:
        {
            nDelayTime = m_nDelayTimeType3;
            if (nDelayTime == -1)
                return ::GetDoubleClickTime();
            return nDelayTime;
        }
        default:
        {
            return 0;
        }
    }
}

inline void CUIFToolTip::GetMargin(LPRECT prc)
{
    if (prc)
        *prc = m_rcToolTipMargin;
}

inline COLORREF
CUIFToolTip::GetTipBkColor()
{
    if (m_bToolTipHasBkColor)
        return m_rgbToolTipBkColor;
    return ::GetSysColor(COLOR_INFOBK);
}

inline COLORREF
CUIFToolTip::GetTipTextColor()
{
    if (m_bToolTipHasTextColor)
        return m_rgbToolTipTextColor;
    return ::GetSysColor(COLOR_INFOTEXT);
}

inline CUIFObject*
CUIFToolTip::FindObject(HWND hWnd, POINT pt)
{
    if (hWnd == *m_pToolTipOwner)
        return m_pToolTipOwner->ObjectFromPoint(pt);
    return NULL;
}

inline void
CUIFToolTip::ShowTip()
{
    ::KillTimer(m_hWnd, TOOLTIP_TIMER_ID);

    if (!m_pToolTipTarget)
        return;

    LPCWSTR pszText = m_pToolTipTarget->GetToolTip();
    if (!pszText)
        return;

    if (!m_pToolTipTarget || m_pToolTipTarget->OnShowToolTip())
        return;

    POINT Point;
    ::GetCursorPos(&Point);
    ::ScreenToClient(*m_pToolTipTarget->m_pWindow, &Point);

    RECT rc;
    m_pToolTipTarget->GetRect(&rc);
    if (!::PtInRect(&rc, Point))
        return;

    size_t cchText = wcslen(pszText);
    m_pszToolTipText = new(cicNoThrow) WCHAR[cchText + 1];
    if (!m_pszToolTipText)
        return;

    lstrcpynW(m_pszToolTipText, pszText, cchText + 1);

    SIZE size;
    GetTipWindowSize(&size);

    RECT rc2 = rc;
    ::ClientToScreen(*m_pToolTipTarget->m_pWindow, (LPPOINT)&rc);
    ::ClientToScreen(*m_pToolTipTarget->m_pWindow, (LPPOINT)&rc.right);
    GetTipWindowRect(&rc2, size, &rc);

    m_bShowToolTip = TRUE;
    Move(rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top);
    Show(TRUE);
}

inline void
CUIFToolTip::HideTip()
{
    ::KillTimer(m_hWnd, TOOLTIP_TIMER_ID);
    m_bShowToolTip = FALSE;

    if (m_pToolTipTarget)
        m_pToolTipTarget->OnHideToolTip();

    if (m_bVisible)
    {
        if (m_pszToolTipText)
        {
            delete[] m_pszToolTipText;
            m_pszToolTipText = NULL;
        }
        Show(FALSE);
    }
}

inline void
CUIFToolTip::GetTipWindowSize(LPSIZE pSize)
{
    if (!m_pszToolTipText)
        return;

    HDC hDC = ::GetDC(m_hWnd);
    HGDIOBJ hFontOld = ::SelectObject(hDC, m_hFont);

    RECT rcText = { 0, 0, 0, 0 };
    INT cyText;
    if (m_cxToolTipWidth <= 0)
    {
        cyText = ::DrawTextW(hDC, m_pszToolTipText, -1, &rcText, DT_CALCRECT | DT_SINGLELINE);
    }
    else
    {
        rcText.right = m_cxToolTipWidth;
        cyText = ::DrawTextW(hDC, m_pszToolTipText, -1, &rcText, DT_CALCRECT | DT_WORDBREAK);
    }

    RECT rcMargin;
    GetMargin(&rcMargin);

    RECT rc;
    rc.left     = rcText.left - rcMargin.left;
    rc.top      = rcText.top - rcMargin.top;
    rc.right    = rcText.right + rcMargin.right;
    rc.bottom   = rcText.top + cyText + rcMargin.bottom;
    ClientRectToWindowRect(&rc);

    pSize->cx = rc.right - rc.left;
    pSize->cy = rc.bottom - rc.top;

    ::SelectObject(hDC, hFontOld);
    ::ReleaseDC(m_hWnd, hDC);
}

inline void
CUIFToolTip::GetTipWindowRect(LPRECT pRect, SIZE toolTipSize, LPCRECT prc)
{
    POINT Point;
    GetCursorPos(&Point);

    HCURSOR hCursor = ::GetCursor();
    ICONINFO IconInfo;
    INT yHotspot = 0;
    INT cyCursor = ::GetSystemMetrics(SM_CYCURSOR);
    if (hCursor && ::GetIconInfo(hCursor, &IconInfo))
    {
        BITMAP bm;
        ::GetObject(IconInfo.hbmMask, sizeof(bm), &bm);
        if (!IconInfo.fIcon)
        {
            cyCursor = bm.bmHeight;
            yHotspot = IconInfo.yHotspot;
            if (!IconInfo.hbmColor)
                cyCursor = bm.bmHeight / 2;
        }
        if (IconInfo.hbmColor)
            ::DeleteObject(IconInfo.hbmColor);
        if (IconInfo.hbmMask)
            ::DeleteObject(IconInfo.hbmMask);
    }

    RECT rcMonitor;
    rcMonitor.left = 0;
    rcMonitor.top = 0;
    rcMonitor.right = GetSystemMetrics(SM_CXSCREEN);
    rcMonitor.bottom = GetSystemMetrics(SM_CYSCREEN);

    HMONITOR hMon = ::MonitorFromPoint(Point, MONITOR_DEFAULTTONEAREST);
    MONITORINFO mi;
    if (hMon)
    {
        mi.cbSize = sizeof(MONITORINFO);
        if (::GetMonitorInfo(hMon, &mi))
            rcMonitor = mi.rcMonitor;
    }

    pRect->left   = Point.x;
    pRect->right  = pRect->left + toolTipSize.cx;
    pRect->top    = Point.y + cyCursor - yHotspot;
    pRect->bottom = pRect->top + toolTipSize.cy;

    if (rcMonitor.right < pRect->right)
    {
        pRect->left = rcMonitor.right - toolTipSize.cx;
        pRect->right = rcMonitor.right;
    }
    if (pRect->left < rcMonitor.left)
    {
        pRect->left = rcMonitor.left;
        pRect->right = rcMonitor.left + toolTipSize.cx;
    }
    if (rcMonitor.bottom < pRect->bottom)
    {
        pRect->top = rcMonitor.bottom - toolTipSize.cy;
        pRect->bottom = rcMonitor.bottom;
    }
    if (pRect->top < rcMonitor.top)
    {
        pRect->top = rcMonitor.top;
        pRect->bottom = rcMonitor.top + toolTipSize.cy;
    }
}

inline void
CUIFToolTip::RelayEvent(LPMSG pMsg)
{
    if (!pMsg)
        return;

    switch (pMsg->message)
    {
        case WM_MOUSEMOVE:
        {
            if (m_bEnable &&
                ::GetKeyState(VK_LBUTTON) >= 0 &&
                ::GetKeyState(VK_MBUTTON) >= 0 &&
                ::GetKeyState(VK_RBUTTON) >= 0)
            {
                POINT pt = { (SHORT)LOWORD(pMsg->lParam), (SHORT)HIWORD(pMsg->lParam) };
                CUIFObject *pFound = CUIFToolTip::FindObject(pMsg->hwnd, pt);
                if (pFound)
                {
                    if (m_pToolTipTarget != pFound)
                    {
                        HideTip();

                        LONG DelayTime;
                        if (!m_bVisible)
                            DelayTime = GetDelayTime(3);
                        else
                            DelayTime = GetDelayTime(1);
                        ::SetTimer(m_hWnd, TOOLTIP_TIMER_ID, DelayTime, NULL);
                    }
                }
                else
                {
                    HideTip();
                }
                m_pToolTipTarget = pFound;
            }
            break;
        }
        case WM_LBUTTONDOWN:
        case WM_RBUTTONDOWN:
        case WM_MBUTTONDOWN:
        {
            HideTip();
            break;
        }
    }
}

inline STDMETHODIMP_(void) CUIFToolTip::OnPaint(HDC hDC)
{
    HGDIOBJ hFontOld = SelectObject(hDC, m_hFont);
    INT iBkModeOld = SetBkMode(hDC, TRANSPARENT);

    COLORREF rgbTextColor = GetTipTextColor();
    COLORREF rgbOldTextColor = ::SetTextColor(hDC, rgbTextColor);

    COLORREF rgbBkColor = GetTipBkColor();
    HBRUSH hbrBack = ::CreateSolidBrush(rgbBkColor);
    RECT rc = m_rc;
    if (hbrBack)
    {
        ::FillRect(hDC, &rc, hbrBack);
        ::DeleteObject(hbrBack);
    }

    RECT rcMargin;
    GetMargin(&rcMargin);

    rc.left += rcMargin.left;
    rc.top += rcMargin.top;
    rc.right -= rcMargin.right;
    rc.bottom -= rcMargin.bottom;

    if (m_cxToolTipWidth <= 0)
        ::DrawTextW(hDC, m_pszToolTipText, -1, &rc, DT_SINGLELINE);
    else
        ::DrawTextW(hDC, m_pszToolTipText, -1, &rc, DT_WORDBREAK);

    ::SetTextColor(hDC, rgbOldTextColor);
    ::SetBkMode(hDC, iBkModeOld);
    ::SelectObject(hDC, hFontOld);
}

inline STDMETHODIMP_(void) CUIFToolTip::Enable(BOOL bEnable)
{
    if (!bEnable)
        HideTip();
    CUIFObject::Enable(bEnable);
}

inline STDMETHODIMP_(void) CUIFToolTip::OnTimer(WPARAM wParam)
{
    if (wParam == TOOLTIP_TIMER_ID)
        ShowTip();
}

/////////////////////////////////////////////////////////////////////////////

inline
CUIFButton::CUIFButton(
    CUIFObject *pParent,
    DWORD nObjectID,
    LPCRECT prc,
    DWORD style) : CUIFObject(pParent, nObjectID, prc, style)
{
    m_ButtonIcon.m_hIcon = NULL;
    m_ButtonIcon.m_hImageList = NULL;
    m_dwUnknown9 = 0;
    m_uButtonStatus = 0;
    m_bPressed = FALSE;
    m_hbmButton1 = NULL;
    m_hbmButton2 = NULL;
    m_pszButtonText = NULL;
}

inline CUIFButton::~CUIFButton()
{
    if (m_pszButtonText)
    {
        delete[] m_pszButtonText;
        m_pszButtonText = NULL;
    }

    if (m_ButtonIcon.m_hImageList)
        ImageList_Destroy(m_ButtonIcon.m_hImageList);
}

inline void
CUIFButton::DrawBitmapProc(HDC hDC, LPCRECT prc, BOOL bPressed)
{
    INT width = m_rc.right - m_rc.left;
    INT height = m_rc.bottom - m_rc.top;
    if (m_hbmButton2)
    {
        HBITMAP hbmMask = cicCreateMaskBmp(&m_rc, m_hbmButton1, m_hbmButton2,
                                           (HBRUSH)UlongToHandle(COLOR_BTNFACE + 1), 0, 0);
        ::DrawState(hDC, NULL, NULL, (LPARAM)hbmMask, 0,
                    prc->left + bPressed, prc->top + bPressed,
                    width - bPressed, height - bPressed,
                    (m_bEnable ? 0 : (DSS_MONO | DSS_DISABLED)) | DST_BITMAP);
        ::DeleteObject(hbmMask);
    }
    else
    {
        ::DrawState(hDC, NULL, NULL, (LPARAM)m_hbmButton1, 0,
                    prc->left + bPressed, prc->top + bPressed,
                    width - bPressed, height - bPressed,
                    (m_bEnable ? 0 : (DSS_MONO | DSS_DISABLED)) | DST_BITMAP);
    }
}

inline void
CUIFButton::DrawEdgeProc(HDC hDC, LPCRECT prc, BOOL bPressed)
{
    RECT rc = *prc;
    if (bPressed)
        ::DrawEdge(hDC, &rc, BDR_SUNKENOUTER, BF_RECT);
    else
        ::DrawEdge(hDC, &rc, BDR_RAISEDINNER, BF_RECT);
}

inline void CUIFButton::DrawIconProc(HDC hDC, LPRECT prc, BOOL bPressed)
{
    INT width = prc->right - prc->left;
    INT height = prc->bottom - prc->top;
    RECT rc = { 0, 0, width, height };

    HDC hMemDC = ::CreateCompatibleDC(hDC);
    if (!hMemDC)
        return;

    HBITMAP hbmMem = ::CreateCompatibleBitmap(hDC, width, height);
    if (!hbmMem)
    {
        ::DeleteDC(hMemDC);
        return;
    }

    HGDIOBJ hbmOld = ::SelectObject(hMemDC, hbmMem);
    if (m_bEnable)
    {
        ::BitBlt(hMemDC, rc.left, rc.top, width, height, hDC, prc->left, prc->top, SRCCOPY);
    }
    else
    {
        HBRUSH hbrWhite = (HBRUSH)::GetStockObject(WHITE_BRUSH);
        ::FillRect(hMemDC, &rc, hbrWhite);
    }

    if (m_style & UIF_BUTTON_LARGE_ICON)
    {
        ::DrawIconEx(hMemDC,
                     2 + bPressed, 2 + bPressed,
                     m_ButtonIcon.m_hIcon,
                     width - 4, height - 4,
                     0, NULL, DI_NORMAL);
    }
    else
    {
        ::DrawIconEx(hMemDC,
                     (width - 16) / 2 + bPressed,
                     (height - 16) / 2 + bPressed,
                     m_ButtonIcon.m_hIcon,
                     16, 16,
                     0, NULL, DI_NORMAL);
    }

    ::SelectObject(hMemDC, hbmOld);
    ::DrawState(hDC, NULL, NULL, (LPARAM)hbmMem, 0,
                prc->left, prc->top, width, height,
                (m_bEnable ? 0 : (DSS_MONO | DSS_DISABLED)) | DST_BITMAP);
    ::DeleteObject(hbmMem);
    ::DeleteDC(hMemDC);
}

inline void
CUIFButton::DrawTextProc(HDC hDC, LPCRECT prc, BOOL bPressed)
{
    if (!m_pszButtonText)
        return;

    HGDIOBJ hFontOld = ::SelectObject(hDC, m_hFont);
    INT cchText = lstrlenW(m_pszButtonText);
    SIZE textSize;
    ::GetTextExtentPoint32W(hDC, m_pszButtonText, cchText, &textSize);

    INT xText, yText;
    if ((m_style & UIF_BUTTON_H_ALIGN_MASK) == UIF_BUTTON_H_ALIGN_CENTER)
        xText = (m_rc.right - m_rc.left - textSize.cx) / 2;
    else if ((m_style & UIF_BUTTON_H_ALIGN_MASK) == UIF_BUTTON_H_ALIGN_RIGHT)
        xText = m_rc.right - m_rc.left - textSize.cx;
    else
        xText = 0;

    if ((m_style & UIF_BUTTON_V_ALIGN_MASK) == UIF_BUTTON_V_ALIGN_MIDDLE)
        yText = (m_rc.bottom - m_rc.top - textSize.cy) / 2;
    else if ((m_style & UIF_BUTTON_V_ALIGN_MASK) == UIF_BUTTON_V_ALIGN_BOTTOM)
        yText = m_rc.bottom - m_rc.top - textSize.cy;
    else
        yText = 0;

    ::SetBkMode(hDC, TRANSPARENT);

    if (m_bEnable)
    {
        ::SetTextColor(hDC, ::GetSysColor(COLOR_BTNTEXT));
        ::ExtTextOutW(hDC,
                      xText + prc->left + bPressed, yText + prc->top + bPressed,
                      ETO_CLIPPED, prc,
                      m_pszButtonText, cchText, NULL);
    }
    else
    {
        ::SetTextColor(hDC, ::GetSysColor(COLOR_BTNHILIGHT));
        ::ExtTextOutW(hDC,
                      xText + prc->left + bPressed + 1, yText + prc->top + bPressed + 1,
                      ETO_CLIPPED, prc,
                      m_pszButtonText, cchText, NULL);

        ::SetTextColor(hDC, ::GetSysColor(COLOR_BTNSHADOW));
        ::ExtTextOutW(hDC,
                      xText + prc->left + bPressed, yText + prc->top + bPressed,
                      ETO_CLIPPED, prc,
                      m_pszButtonText, cchText, NULL);
    }

    ::SelectObject(hDC, hFontOld);
}

inline STDMETHODIMP_(void)
CUIFButton::Enable(BOOL bEnable)
{
    CUIFObject::Enable(bEnable);
    if (!m_bEnable)
    {
        SetStatus(0);
        if (IsCapture())
            CUIFObject::EndCapture();
    }
}

inline void
CUIFButton::GetIconSize(HICON hIcon, LPSIZE pSize)
{
    ICONINFO IconInfo;
    if (::GetIconInfo(hIcon, &IconInfo))
    {
        BITMAP bm;
        ::GetObject(IconInfo.hbmColor, sizeof(bm), &bm);
        ::DeleteObject(IconInfo.hbmColor);
        ::DeleteObject(IconInfo.hbmMask);
        pSize->cx = bm.bmWidth;
        pSize->cy = bm.bmHeight;
    }
    else
    {
        pSize->cx = ::GetSystemMetrics(SM_CXSMICON);
        pSize->cy = ::GetSystemMetrics(SM_CYSMICON);
    }
}

inline void
CUIFButton::GetTextSize(LPCWSTR pszText, LPSIZE pSize)
{
    HDC hDC = ::GetDC(NULL);
    INT cchText = lstrlenW(pszText);
    HGDIOBJ hFontOld = ::SelectObject(hDC, m_hFont);

    if (!m_bHasCustomFont && SUCCEEDED(EnsureThemeData(*m_pWindow)))
    {
        RECT rc;
        GetThemeTextExtent(hDC, 0, pszText, cchText, 0, NULL, &rc);
        pSize->cx = rc.right;
        pSize->cy = rc.bottom;
    }
    else
    {
        ::GetTextExtentPoint32W(hDC, pszText, cchText, pSize);
    }

    if (m_style & UIF_BUTTON_VERTICAL)
    {
        INT tmp = pSize->cx;
        pSize->cx = pSize->cy;
        pSize->cy = tmp;
    }

    ::SelectObject(hDC, hFontOld);
    ::ReleaseDC(NULL, hDC);
}

inline STDMETHODIMP_(void)
CUIFButton::OnLButtonDown(LONG x, LONG y)
{
    SetStatus(1);
    StartCapture();
    if ((m_style & 0x30) == 0x20)
        NotifyCommand(1, 0);
}

/// @unimplemented
inline STDMETHODIMP_(void)
CUIFButton::OnLButtonUp(LONG x, LONG y)
{
    POINT pt = { x, y };
    BOOL bCapture = IsCapture();
    if (bCapture)
        EndCapture();

    BOOL bNotInObject = (m_style & 0x30) == 0x20;
    if ((m_style & 0x30) != 0x10)
    {
        bNotInObject = !PtInObject(pt);
        if (bNotInObject)
        {
            SetStatus(0);
            return;
        }
    }
    else
    {
        if (!bNotInObject)
        {
            bNotInObject = !PtInObject(pt);
            if (!bNotInObject)
            {
                SetStatus(2);
                NotifyCommand(1, 0);
                return;
            }
        }
        SetStatus(0);
        return;
    }

    SetStatus(2);

    if (bCapture)
    {
        m_bPressed = !m_bPressed;
        NotifyCommand(1, 0);
    }
}

inline void CUIFButton::OnMouseIn(LONG x, LONG y)
{
    if ((m_style & 0x30) == 0x20)
    {
        if (IsCapture())
            SetStatus(0);
        else
            SetStatus(2);
    }
    else
    {
        if (IsCapture())
            SetStatus(1);
        else
            SetStatus(2);
    }
}

inline void CUIFButton::OnMouseOut(LONG x, LONG y)
{
    if ((m_style & 0x30) == 0x20)
        SetStatus(0);
    else if (IsCapture())
        SetStatus(3);
    else
        SetStatus(0);
}

inline STDMETHODIMP_(void)
CUIFButton::OnPaintNoTheme(HDC hDC)
{
    ::FillRect(hDC, &m_rc, (HBRUSH)UlongToHandle(COLOR_BTNFACE + 1));

    if (m_bPressed && ((m_uButtonStatus == 0) || (m_uButtonStatus == 3)))
    {
        HBRUSH hbr = cicCreateDitherBrush();
        if (hbr)
        {
            COLORREF OldTextColor = ::SetTextColor(hDC, ::GetSysColor(COLOR_BTNFACE));
            COLORREF OldBkColor = ::SetBkColor(hDC, ::GetSysColor(COLOR_BTNHIGHLIGHT));
            RECT rc = m_rc;
            ::InflateRect(&rc, -2, -2);
            ::FillRect(hDC, &rc, hbr);
            ::SetTextColor(hDC, OldTextColor);
            ::SetBkColor(hDC, OldBkColor);
            ::DeleteObject(hbr);
        }
    }

    BOOL bPressed = (m_bPressed || (m_uButtonStatus == 1));
    if (m_hbmButton1)
        DrawBitmapProc(hDC, &m_rc, bPressed);
    else if (m_ButtonIcon.m_hIcon)
        DrawIconProc(hDC, &m_rc, bPressed);
    else
        DrawTextProc(hDC, &m_rc, bPressed);

    if (m_bPressed || (m_uButtonStatus == 1))
        DrawEdgeProc(hDC, &m_rc, TRUE);
    else if (2 <= m_uButtonStatus && m_uButtonStatus <= 3)
        DrawEdgeProc(hDC, &m_rc, FALSE);
}

inline void CUIFButton::SetIcon(HICON hIcon)
{
    m_ButtonIcon = hIcon;

    if (m_ButtonIcon.m_hIcon)
        GetIconSize(m_ButtonIcon.m_hIcon, &m_IconSize);
    else
        m_IconSize.cx = m_IconSize.cy = 0;

    CallOnPaint();
}

inline void CUIFButton::SetStatus(UINT uStatus)
{
    if (uStatus != m_uButtonStatus)
    {
        m_uButtonStatus = uStatus;
        CallOnPaint();
    }
}

inline void CUIFButton::SetText(LPCWSTR pszText)
{
    if (m_pszButtonText)
    {
        delete[] m_pszButtonText;
        m_pszButtonText = NULL;
    }

    m_TextSize.cx = m_TextSize.cy = 0;

    if (pszText)
    {
        INT cch = lstrlenW(pszText);
        m_pszButtonText = new(cicNoThrow) WCHAR[cch + 1];
        if (!m_pszButtonText)
            return;

        lstrcpynW(m_pszButtonText, pszText, cch + 1);
        GetTextSize(m_pszButtonText, &m_TextSize);
    }

    CallOnPaint();
}

/////////////////////////////////////////////////////////////////////////////

inline CUIFButton2::CUIFButton2(
    CUIFObject *pParent,
    DWORD nObjectID,
    LPCRECT prc,
    DWORD style) : CUIFButton(pParent, nObjectID, prc, style)
{
    m_iStateId = 0;
    m_iPartId = BP_PUSHBUTTON;
    m_pszClassList = L"TOOLBAR";
}

inline CUIFButton2::~CUIFButton2()
{
    CloseThemeData();
}

inline DWORD CUIFButton2::MakeDrawFlag()
{
    DWORD dwDrawFlags = 0;
    if (m_bPressed)
        dwDrawFlags |= UIF_DRAW_PRESSED;
    if (m_uButtonStatus == 1)
        dwDrawFlags |= 0x2;
    else if (2 <= m_uButtonStatus && m_uButtonStatus <= 3)
        dwDrawFlags |= 0x1;
    if (!m_bEnable)
        dwDrawFlags |= UIF_DRAW_DISABLED;
    return dwDrawFlags;
}

/// @unimplemented
inline STDMETHODIMP_(BOOL)
CUIFButton2::OnPaintTheme(HDC hDC)
{
    //FIXME
    return FALSE;
}

inline STDMETHODIMP_(void)
CUIFButton2::OnPaintNoTheme(HDC hDC)
{
    if (!m_pScheme)
       return;

    INT width = m_rc.right - m_rc.left;
    INT height = m_rc.bottom - m_rc.top;
    HDC hdcMem = ::CreateCompatibleDC(hDC);
    if (!hdcMem)
        return;

    HBITMAP hbmMem = ::CreateCompatibleBitmap(hDC, width, height);
    if ( !hbmMem )
    {
        ::DeleteDC(hdcMem);
        return;
    }

    HGDIOBJ hbmOld = ::SelectObject(hdcMem, hbmMem);
    HGDIOBJ hFontOld = ::SelectObject(hdcMem, m_hFont);
    RECT rcBack = { 0, 0, width, height };

    INT cxText, cyText, cxContent, cyContent, cxyBorders, cxButton, cyButton;
    if (m_pszButtonText)
    {
        cxText = m_TextSize.cx;
        cyText = m_TextSize.cy;
    }
    else
    {
        cxText = 0;
        cyText = cyText;
    }

    if (m_ButtonIcon.m_hIcon)
    {
        cxContent = m_IconSize.cx;
        cyContent = m_IconSize.cy;
    }
    else if (m_hbmButton1)
    {
        cxContent = m_BitmapSize.cx;
        cyContent = m_BitmapSize.cy;
    }

    if (m_style & UIF_BUTTON_VERTICAL)
    {
        cxyBorders = ((cyText && cyContent) ? 2 : 0);

        cxButton = cxContent;
        cyButton = cyText + cyContent + cxyBorders;
        if (cxText > cxContent)
            cxButton = cxText;
    }
    else
    {
        cxyBorders = ((cxText && cxContent) ? 2 : 0);

        cyButton = cyContent;
        cxButton = cxText + cxContent + cxyBorders;
        if (cyText > cyButton)
            cyButton = cyText;
    }

    INT xOffset, yOffset;
    if ((m_style & UIF_BUTTON_H_ALIGN_MASK) == UIF_BUTTON_H_ALIGN_CENTER)
        xOffset = (rcBack.left + rcBack.right - cxButton) / 2;
    else if ((m_style & UIF_BUTTON_H_ALIGN_MASK) == UIF_BUTTON_H_ALIGN_RIGHT)
        xOffset = rcBack.right - cxText - 2;
    else
        xOffset = rcBack.left + 2;


    if ((m_style & UIF_BUTTON_V_ALIGN_MASK) == UIF_BUTTON_V_ALIGN_MIDDLE)
        yOffset = (rcBack.top + rcBack.bottom - cyButton) / 2;
    else if ((m_style & UIF_BUTTON_V_ALIGN_MASK) == UIF_BUTTON_V_ALIGN_BOTTOM)
        yOffset = rcBack.bottom - cyButton - 2;
    else
        yOffset = rcBack.top + 2;

    RECT rc = { xOffset, yOffset, xOffset + cxButton, cyButton + yOffset };
    SIZE offsetSize = { 0, 0 };
    DWORD dwDrawFlags = MakeDrawFlag();
    m_pScheme->GetCtrlFaceOffset(((m_style & 0x200) ? 0xA5 : 0x54),
                                 dwDrawFlags,
                                 &offsetSize);
    ::OffsetRect(&rc, offsetSize.cx, offsetSize.cy);

    RECT rcImage, rcText;
    if (m_style & UIF_BUTTON_VERTICAL)
    {
        rcImage.left    = (rc.left + rc.right - cxContent) / 2;
        rcImage.top     = rc.top;
        rcImage.right   = rcImage.left + cxContent;
        rcImage.bottom  = rc.top + cyContent;
        rcText.left     = (rc.left + rc.right - cxText) / 2;
        rcText.top      = rc.bottom - cyText;
        rcText.right    = rcText.left + cxText;
        rcText.bottom   = rc.bottom;
    }
    else
    {
        rcImage.left    = rc.left;
        rcImage.top     = (rc.top + rc.bottom - cyContent) / 2;
        rcImage.bottom  = rcImage.top + cyContent;
        rcImage.right   = rc.left + cxContent;
        rcText.left     = rc.right - cxText;
        rcText.top      = (rc.top + rc.bottom - cyText) / 2;
        rcText.right    = rc.right;
        rcText.bottom   = rcText.top + cyText;
    }

    if (IsRTL())
        m_pScheme->m_bMirroring = TRUE;

    m_pScheme->DrawCtrlBkgd(hdcMem,
                            &rcBack,
                            ((m_style & 0x200) ? 0xA5 : 0x54),
                            dwDrawFlags);
    if (m_pszButtonText)
    {
        m_pScheme->DrawCtrlText(hdcMem, &rcText, m_pszButtonText, -1, dwDrawFlags,
                                !!(m_style & UIF_BUTTON_VERTICAL));
    }

    if (m_ButtonIcon.m_hIcon)
        m_pScheme->DrawCtrlIcon(hdcMem, &rcImage, m_ButtonIcon.m_hIcon, dwDrawFlags, &m_IconSize);
    else if (m_hbmButton1)
        m_pScheme->DrawCtrlBitmap(hdcMem, &rcImage, m_hbmButton1, m_hbmButton2, dwDrawFlags);

    if (IsRTL())
        m_pScheme->m_bMirroring = FALSE;

    m_pScheme->DrawCtrlEdge(hdcMem,
                            &rcBack,
                            ((m_style & 0x200) ? 0xA5 : 0x54),
                            dwDrawFlags);

    ::BitBlt(hDC, m_rc.left, m_rc.top, width, height, hdcMem, 0, 0, SRCCOPY);
    ::SelectObject(hdcMem, hFontOld);
    ::SelectObject(hdcMem, hbmOld);
    ::DeleteObject(hbmMem);
}

/////////////////////////////////////////////////////////////////////////////

inline
CUIFGripper::CUIFGripper(CUIFObject *pParent, LPCRECT prc, DWORD style)
    : CUIFObject(pParent, 0, prc, style)
{
    m_iStateId = 0;
    m_pszClassList = L"REBAR";
    if (m_style & UIF_GRIPPER_VERTICAL)
        m_iPartId = RP_GRIPPERVERT;
    else
        m_iPartId = RP_GRIPPER;
}

inline CUIFGripper::~CUIFGripper()
{
}

inline STDMETHODIMP_(void)
CUIFGripper::OnMouseMove(LONG x, LONG y)
{
    if (IsCapture())
    {
        POINT pt;
        ::GetCursorPos(&pt);
        m_pWindow->Move(pt.x - m_ptGripper.x, pt.y - m_ptGripper.y, -1, -1);
    }
}

inline STDMETHODIMP_(void)
CUIFGripper::OnLButtonDown(LONG x, LONG y)
{
    StartCapture();
    m_ptGripper.x = x;
    m_ptGripper.y = y;
    ::ScreenToClient(*m_pWindow, &m_ptGripper);
    RECT rc;
    ::GetWindowRect(*m_pWindow, &rc);
    m_ptGripper.x -= rc.left;
    m_ptGripper.y -= rc.top;
}

inline STDMETHODIMP_(void)
CUIFGripper::OnLButtonUp(LONG x, LONG y)
{
    if (IsCapture())
        EndCapture();
}

inline STDMETHODIMP_(BOOL)
CUIFGripper::OnPaintTheme(HDC hDC)
{
    if (FAILED(EnsureThemeData(*m_pWindow)))
        return FALSE;

    if (m_style & UIF_GRIPPER_VERTICAL)
    {
        m_rc.top += 2;
        m_rc.bottom -= 2;
    }
    else
    {
        m_rc.left += 2;
        m_rc.right -= 2;
    }

    if (FAILED(DrawThemeBackground(hDC, 1, &m_rc, 0)))
        return FALSE;

    return TRUE;
}

inline STDMETHODIMP_(void)
CUIFGripper::OnPaintNoTheme(HDC hDC)
{
    if (m_pScheme)
    {
        m_pScheme->DrawDragHandle(hDC, &m_rc, !!(m_style & UIF_GRIPPER_VERTICAL));
        return;
    }

    RECT rc;
    if (m_style & UIF_GRIPPER_VERTICAL)
        rc = { m_rc.left, m_rc.top + 1, m_rc.right, m_rc.top + 4 };
    else
        rc = { m_rc.left + 1, m_rc.top, m_rc.left + 4, m_rc.bottom };

    ::DrawEdge(hDC, &rc, BDR_RAISEDINNER, BF_RECT);
}

inline STDMETHODIMP_(BOOL)
CUIFGripper::OnSetCursor(UINT uMsg, LONG x, LONG y)
{
    HCURSOR hCursor = ::LoadCursor(NULL, IDC_SIZEALL);
    ::SetCursor(hCursor);
    return TRUE;
}

inline STDMETHODIMP_(void)
CUIFGripper::SetStyle(DWORD style)
{
    m_style = style;
    if (m_style & UIF_GRIPPER_VERTICAL)
        SetActiveTheme(L"REBAR", RP_GRIPPERVERT, 0);
    else
        SetActiveTheme(L"REBAR", RP_GRIPPER, 0);
}

/////////////////////////////////////////////////////////////////////////////

inline
CUIFToolbarMenuButton::CUIFToolbarMenuButton(
    CUIFToolbarButton *pParent,
    DWORD nObjectID,
    LPCRECT prc,
    DWORD style) : CUIFButton2(pParent, nObjectID, prc, style)
{
    m_pToolbarButton = pParent;

    HFONT hFont = ::CreateFont(8, 8, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, SYMBOL_CHARSET,
                               OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                               DEFAULT_PITCH | FF_DONTCARE, TEXT("Marlett"));
    SetFont(hFont);
    SetText(L"u"); // downward triangle
}

inline
CUIFToolbarMenuButton::~CUIFToolbarMenuButton()
{
    ::DeleteObject(m_hFont);
    SetFont(NULL);
}

inline STDMETHODIMP_(void)
CUIFToolbarMenuButton::OnLButtonUp(LONG x, LONG y)
{
    CUIFButton::OnLButtonUp(x, y);
    m_pToolbarButton->OnUnknownMouse2(x, y);
}

inline STDMETHODIMP_(BOOL)
CUIFToolbarMenuButton::OnSetCursor(UINT uMsg, LONG x, LONG y)
{
    m_pToolbarButton->OnSetCursor(uMsg, x, y);
    return FALSE;
}

/////////////////////////////////////////////////////////////////////////////

inline
CUIFToolbarButtonElement::CUIFToolbarButtonElement(
    CUIFToolbarButton *pParent,
    DWORD nObjectID,
    LPCRECT prc,
    DWORD style) : CUIFButton2(pParent, nObjectID, prc, style)
{
    m_pToolbarButton = pParent;
}

inline STDMETHODIMP_(LPCWSTR)
CUIFToolbarButtonElement::GetToolTip()
{
    if (m_pToolbarButton)
        return m_pToolbarButton->GetToolTip();
    return NULL;
}

inline STDMETHODIMP_(void)
CUIFToolbarButtonElement::OnLButtonUp(LONG x, LONG y)
{
    CUIFButton::OnLButtonUp(x, y);
    if ((m_pToolbarButton->m_dwToolbarButtonFlags & 0x30000) == 0x20000)
        m_pToolbarButton->OnUnknownMouse2(x, y);
    else
        m_pToolbarButton->OnUnknownMouse1(x, y);
}

inline STDMETHODIMP_(void)
CUIFToolbarButtonElement::OnRButtonUp(LONG x, LONG y)
{
    if ((m_pToolbarButton->m_dwToolbarButtonFlags & 0x30000) != 0x20000)
        m_pToolbarButton->OnUnknownMouse0();
}

/////////////////////////////////////////////////////////////////////////////

inline CUIFToolbarButton::CUIFToolbarButton(
    CUIFObject *pParent,
    DWORD nObjectID,
    LPCRECT prc,
    DWORD style,
    DWORD dwToolbarButtonFlags,
    LPCWSTR pszUnknownText) : CUIFObject(pParent, nObjectID, prc, style)
{
    m_dwToolbarButtonFlags = dwToolbarButtonFlags;
    m_pszUnknownText = pszUnknownText;
}

inline BOOL CUIFToolbarButton::Init()
{
    RECT rc1, rc2;
    rc1 = rc2 = m_rc;

    if ((m_dwToolbarButtonFlags & 0x30000) == 0x30000)
    {
        rc1.right -= 12;
        rc2.left = rc1.right + 1;
    }

    DWORD style = UIF_BUTTON_LARGE_ICON | UIF_BUTTON_V_ALIGN_MIDDLE | UIF_BUTTON_H_ALIGN_CENTER;
    if (m_dwToolbarButtonFlags & 0x2000)
        style |= 0x10;
    if (m_dwToolbarButtonFlags & 0x80000)
        style |= UIF_BUTTON_VERTICAL;
    m_pToolbarButtonElement = new(cicNoThrow) CUIFToolbarButtonElement(this, m_nObjectID, &rc1, style);
    if (!m_pToolbarButtonElement)
        return FALSE;

    m_pToolbarButtonElement->Initialize();
    AddUIObj(m_pToolbarButtonElement);

    if (!m_bEnable)
        m_pToolbarButtonElement->Enable(FALSE);

    if ((m_dwToolbarButtonFlags & 0x30000) == 0x30000)
    {
        style = UIF_BUTTON_LARGE_ICON | UIF_BUTTON_H_ALIGN_CENTER;
        if (m_dwToolbarButtonFlags & 0x80000)
            style |= UIF_BUTTON_VERTICAL;

        m_pToolbarMenuButton = new(cicNoThrow) CUIFToolbarMenuButton(this, 0, &rc2, style);
        if (!m_pToolbarMenuButton)
            return FALSE;

        m_pToolbarMenuButton->Initialize();
        AddUIObj(m_pToolbarMenuButton);

        if (!m_bEnable)
            m_pToolbarMenuButton->Enable(FALSE);
    }

    return TRUE;
}

inline HICON CUIFToolbarButton::GetIcon()
{
    return m_pToolbarButtonElement->m_ButtonIcon.m_hIcon;
}

inline void CUIFToolbarButton::SetIcon(HICON hIcon)
{
    m_pToolbarButtonElement->SetIcon(hIcon);
}

inline STDMETHODIMP_(void)
CUIFToolbarButton::ClearWndObj()
{
    if (m_pToolbarButtonElement)
        m_pToolbarButtonElement->ClearWndObj();
    if (m_pToolbarMenuButton)
        m_pToolbarMenuButton->ClearWndObj();

    CUIFObject::ClearWndObj();
}

inline STDMETHODIMP_(void)
CUIFToolbarButton::DetachWndObj()
{
    if (m_pToolbarButtonElement)
        m_pToolbarButtonElement->DetachWndObj();
    if (m_pToolbarMenuButton)
        m_pToolbarMenuButton->DetachWndObj();

    CUIFObject::DetachWndObj();
}

inline STDMETHODIMP_(void)
CUIFToolbarButton::Enable(BOOL bEnable)
{
    CUIFObject::Enable(bEnable);
    if (m_pToolbarButtonElement)
        m_pToolbarButtonElement->Enable(bEnable);
    if (m_pToolbarMenuButton)
        m_pToolbarMenuButton->Enable(bEnable);
}

inline STDMETHODIMP_(LPCWSTR)
CUIFToolbarButton::GetToolTip()
{
    return CUIFObject::GetToolTip();
}

inline STDMETHODIMP_(void)
CUIFToolbarButton::SetActiveTheme(LPCWSTR pszClassList, INT iPartId, INT iStateId)
{
    if (m_pToolbarButtonElement)
        m_pToolbarButtonElement->SetActiveTheme(pszClassList, iPartId, iStateId);
    if (m_pToolbarMenuButton)
        m_pToolbarMenuButton->SetActiveTheme(pszClassList, iPartId, iStateId);

    m_pszClassList = pszClassList;
    m_iPartId = iPartId;
    m_iStateId = iStateId;
}

inline STDMETHODIMP_(void)
CUIFToolbarButton::SetFont(HFONT hFont)
{
    m_pToolbarButtonElement->SetFont(hFont);
}

inline STDMETHODIMP_(void)
CUIFToolbarButton::SetRect(LPCRECT prc)
{
    CUIFObject::SetRect(prc);

    RECT rc1, rc2;
    rc1 = rc2 = m_rc;

    if ((m_dwToolbarButtonFlags & 0x30000) == 0x30000)
    {
        rc1.right -= 12;
        rc2.left = rc1.right + 1;
    }

    if (m_pToolbarButtonElement)
        m_pToolbarButtonElement->SetRect(&rc1);
    if (m_pToolbarMenuButton)
        m_pToolbarMenuButton->SetRect(&rc2);
}

inline STDMETHODIMP_(void)
CUIFToolbarButton::SetToolTip(LPCWSTR pszToolTip)
{
    CUIFObject::SetToolTip(pszToolTip);
    if (m_pToolbarButtonElement)
        m_pToolbarButtonElement->SetToolTip(pszToolTip);
    if (m_pToolbarMenuButton)
        m_pToolbarMenuButton->SetToolTip(pszToolTip);
}

/////////////////////////////////////////////////////////////////////////////

inline
CUIFWndFrame::CUIFWndFrame(
    CUIFObject *pParent,
    LPCRECT prc,
    DWORD style) : CUIFObject(pParent, 0, prc, style)
{
    m_iPartId = 7;
    m_iStateId = 0;
    m_pszClassList = L"WINDOW";
    m_dwHitTest = 0;
    m_cxFrame = m_cyFrame = 0;

    if (m_pScheme)
    {
        if ((m_style & 0xF) && (m_style & 0xF) <= 2)
        {
            m_cxFrame = m_pScheme->CxSizeFrame();
            m_cyFrame = m_pScheme->CySizeFrame();
        }
        else
        {
            m_cxFrame = m_pScheme->CxWndBorder();
            m_cyFrame = m_pScheme->CyWndBorder();
        }
    }

    m_cxMin = GetSystemMetrics(SM_CXMIN);
    m_cyMin = GetSystemMetrics(SM_CYMIN);
}

inline void CUIFWndFrame::GetFrameSize(LPSIZE pSize)
{
    pSize->cx = m_cxFrame;
    pSize->cy = m_cyFrame;
}

inline DWORD CUIFWndFrame::HitTest(LONG x, LONG y)
{
    DWORD dwFlags = 0;
    if ( m_rc.left <= x && x < m_rc.left + m_cxFrame)
        dwFlags |= 0x10;
    if (m_rc.top <= y && y < m_rc.top + m_cyFrame )
        dwFlags |= 0x20;
    if (m_rc.right - m_cxFrame <= x && x < m_rc.right)
        dwFlags |= 0x40;
    if (m_rc.bottom - m_cyFrame <= y && y < m_rc.bottom)
        dwFlags |= 0x80;
    return dwFlags;
}

inline STDMETHODIMP_(void)
CUIFWndFrame::OnMouseMove(LONG x, LONG y)
{
    if (!IsCapture())
        return;

    POINT Point;
    ::ClientToScreen(*m_pWindow, &Point);

    RECT rc = m_rcWnd;

    if (m_dwHitTest & 0x10)
        rc.left = Point.x + m_rcWnd.left - m_ptHit.x;

    if (m_dwHitTest & 0x20)
        rc.top = Point.y + m_rcWnd.top - m_ptHit.y;

    if (m_dwHitTest & 0x40)
    {
        rc.right = Point.x + m_rcWnd.right - m_ptHit.x;
        if (rc.right <= rc.left + m_cxMin)
            rc.right = rc.left + m_cxMin;
    }

    if (m_dwHitTest & 0x80)
    {
        rc.bottom = Point.y + m_rcWnd.bottom - m_ptHit.y;
        if (rc.bottom <= rc.top + m_cyMin)
            rc.bottom = rc.top + m_cyMin;
    }

    m_pWindow->Move(rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top);
}

inline STDMETHODIMP_(void)
CUIFWndFrame::OnLButtonDown(LONG x, LONG y)
{
    POINT Point = { x, y };
    DWORD hitTest = m_style & HitTest(x, y);
    if (!hitTest)
        return;

    ::ClientToScreen(*m_pWindow, &Point);
    m_ptHit = Point;
    m_pWindow = m_pWindow;
    m_dwHitTest = hitTest;
    ::GetWindowRect(*m_pWindow, &m_rcWnd);
    StartCapture();
}

inline STDMETHODIMP_(void)
CUIFWndFrame::OnLButtonUp(LONG x, LONG y)
{
    if (IsCapture())
        EndCapture();
}

inline STDMETHODIMP_(BOOL)
CUIFWndFrame::OnPaintTheme(HDC hDC)
{
    if (FAILED(EnsureThemeData(*m_pWindow)))
        return FALSE;

    RECT rc = m_rc;
    rc.right = m_cxFrame;
    if (FAILED(DrawThemeEdge(hDC, 0, &rc, 5, 1, NULL)))
        return FALSE;

    rc = m_rc;
    rc.left = rc.right - m_cxFrame;
    if (FAILED(DrawThemeEdge(hDC, 0, &rc, 10, 4, NULL)))
        return FALSE;

    rc = m_rc;
    rc.bottom = m_cyFrame;
    if (FAILED(DrawThemeEdge(hDC, 0, &rc, 5, 2, NULL)))
        return FALSE;

    rc = m_rc;
    rc.top = rc.bottom - m_cyFrame;
    if (FAILED(DrawThemeEdge(hDC, 0, &rc, 10, 8, NULL)))
        return FALSE;

    return TRUE;
}

inline STDMETHODIMP_(void)
CUIFWndFrame::OnPaintNoTheme(HDC hDC)
{
    if (!m_pScheme)
        return;

    DWORD type = 0;
    if ((m_style & 0xF) == 1)
        type = 1;
    else if ( (m_style & 0xF) == 2 )
        type = 2;

    m_pScheme->DrawWndFrame(hDC, &m_rc, type, m_cxFrame, m_cyFrame);
}

inline STDMETHODIMP_(BOOL)
CUIFWndFrame::OnSetCursor(UINT uMsg, LONG x, LONG y)
{
    DWORD dwHitTest = m_dwHitTest;
    if (!IsCapture())
        dwHitTest = m_style & HitTest(x, y);

    LPTSTR pszCursor = NULL;
    switch (dwHitTest)
    {
        case 0x30:
        case 0xC0:
            pszCursor = IDC_SIZENWSE;
            break;
        case 0x90:
        case 0x60:
            pszCursor = IDC_SIZENESW;
            break;
        case 0x10:
        case 0x40:
            pszCursor = IDC_SIZEWE;
            break;
        case 0x20:
        case 0x80:
            pszCursor = IDC_SIZENS;
            break;
        default:
            return FALSE;
    }

    HCURSOR hCursor = ::LoadCursor(NULL, pszCursor);
    ::SetCursor(hCursor);
    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////

inline
CUIFBalloonButton::CUIFBalloonButton(
    CUIFObject *pParent,
    DWORD nObjectID,
    LPCRECT prc,
    DWORD style) : CUIFButton(pParent, nObjectID, prc, style)
{
    m_nCommandID = 0;
}

inline STDMETHODIMP_(void)
CUIFBalloonButton::OnPaint(HDC hDC)
{
    RECT rc = m_rc;
    ::OffsetRect(&rc, -rc.left, -rc.top);

    HDC hMemDC = ::CreateCompatibleDC(hDC);
    HBITMAP hbmMem = ::CreateCompatibleBitmap(hDC, rc.right, rc.bottom);
    HGDIOBJ hbmOld = ::SelectObject(hMemDC, hbmMem);

    BOOL bPressed;
    COLORREF rgbShadow, rgbBorder;
    if (m_uButtonStatus == 1)
    {
        bPressed = TRUE;
        rgbShadow = ::GetSysColor(COLOR_BTNSHADOW);
        rgbBorder = ::GetSysColor(COLOR_BTNHIGHLIGHT);
    }
    else
    {
        bPressed = FALSE;
        if (m_uButtonStatus < 4)
        {
            rgbShadow = ::GetSysColor(COLOR_BTNHIGHLIGHT);
            rgbBorder = ::GetSysColor(COLOR_BTNSHADOW);
        }
        else
        {
            rgbShadow = ::GetSysColor(COLOR_INFOBK);
            rgbBorder = ::GetSysColor(COLOR_INFOBK);
        }
    }

    COLORREF rgbInfoBk = ::GetSysColor(COLOR_INFOBK);
    HBRUSH hbrBack = ::CreateSolidBrush(rgbInfoBk);
    ::FillRect(hMemDC, &rc, hbrBack);
    ::DeleteObject(hbrBack);

    DrawTextProc(hMemDC, &rc, bPressed);

    HBRUSH hNullBrush = (HBRUSH)::GetStockObject(NULL_BRUSH);
    HGDIOBJ hbrOld = ::SelectObject(hMemDC, hNullBrush);

    HPEN hPen = ::CreatePen(PS_SOLID, 0, rgbShadow);
    HGDIOBJ hPenOld = ::SelectObject(hMemDC, hPen);
    ::RoundRect(hMemDC, rc.left, rc.top, rc.right - 1, rc.bottom - 1, 6, 6);
    ::SelectObject(hMemDC, hPenOld);
    ::DeleteObject(hPen);

    hPen = ::CreatePen(PS_SOLID, 0, rgbBorder);
    hPenOld = ::SelectObject(hMemDC, hPen);
    ::RoundRect(hMemDC, rc.left + 1, rc.top + 1, rc.right, rc.bottom, 6, 6);
    ::SelectObject(hMemDC, hPenOld);
    ::DeleteObject(hPen);

    hPen = ::CreatePen(PS_SOLID, 0, ::GetSysColor(COLOR_BTNFACE));
    hPenOld = ::SelectObject(hMemDC, hPen);
    ::RoundRect(hMemDC, rc.left + 1, rc.top + 1, rc.right - 1, rc.bottom - 1, 6, 6);
    ::SelectObject(hMemDC, hPenOld);
    ::DeleteObject(hPen);

    ::SelectObject(hMemDC, hbrOld);
    ::BitBlt(hDC, m_rc.left, m_rc.top, m_rc.right - m_rc.left, m_rc.bottom - m_rc.top,
             hMemDC, rc.left, rc.top, SRCCOPY);
    ::SelectObject(hMemDC, hbmOld);
    ::DeleteObject(hbmMem);
    ::DeleteDC(hMemDC);
}

inline void
CUIFBalloonButton::DrawTextProc(HDC hDC, LPCRECT prc, BOOL bPressed)
{
    if (!m_pszButtonText)
        return;

    UINT uFlags = DT_SINGLELINE;

    if ((m_style & UIF_BUTTON_H_ALIGN_MASK) == UIF_BUTTON_H_ALIGN_CENTER)
        uFlags |= DT_CENTER;
    else if ((m_style & UIF_BUTTON_H_ALIGN_MASK) == UIF_BUTTON_H_ALIGN_RIGHT)
        uFlags |= DT_RIGHT;

    if ((m_style & UIF_BUTTON_V_ALIGN_MASK) == UIF_BUTTON_V_ALIGN_MIDDLE)
        uFlags |= DT_VCENTER;
    else if ((m_style & UIF_BUTTON_V_ALIGN_MASK) == UIF_BUTTON_V_ALIGN_BOTTOM)
        uFlags |= DT_BOTTOM;

    COLORREF rgbOldColor = ::SetTextColor(hDC, ::GetSysColor(COLOR_BTNTEXT));
    INT nOldBkMode = ::SetBkMode(hDC, TRANSPARENT);

    RECT rc = *prc;
    if (bPressed)
        ::OffsetRect(&rc, 1, 1);

    HGDIOBJ hFontOld = ::SelectObject(hDC, m_hFont);
    ::DrawTextW(hDC, m_pszButtonText, -1, &rc, uFlags);
    ::SelectObject(hDC, hFontOld);

    ::SetBkMode(hDC, nOldBkMode);
    ::SetTextColor(hDC, rgbOldColor);
}

/////////////////////////////////////////////////////////////////////////////

inline
CUIFBalloonWindow::CUIFBalloonWindow(HINSTANCE hInst, DWORD style) : CUIFWindow(hInst, style)
{
    m_dwUnknown6 = -1;
    m_nActionID = -1;
    m_hRgn = NULL;
    m_pszBalloonText = NULL;
    m_bHasBkColor = FALSE;
    m_bHasTextColor = FALSE;
    m_rgbBkColor = 0;
    m_rgbTextColor = 0;
    m_ptTarget.x = 0;
    m_ptTarget.y = 0;
    m_rcExclude.left = 0;
    m_rcExclude.right = 0;
    m_rcExclude.top = 0;
    m_rcExclude.bottom = 0;
    m_dwUnknown7 = 0;
    m_nBalloonType = 0;
    m_dwUnknown8[0] = 0;
    m_dwUnknown8[1] = 0;
    m_ptBalloon.x = 0;
    m_ptBalloon.y = 0;
    m_cButtons = 0;
    m_hwndNotif = NULL;
    m_uNotifMsg = 0;
    m_rcMargin.left = 8;
    m_rcMargin.top = 8;
    m_rcMargin.right = 8;
    m_rcMargin.bottom = 8;
}

inline
CUIFBalloonWindow::~CUIFBalloonWindow()
{
    if (m_pszBalloonText)
    {
        delete[] m_pszBalloonText;
        m_pszBalloonText = NULL;
    }
}

inline STDMETHODIMP_(void)
CUIFBalloonWindow::Initialize()
{
    CUIFWindow::Initialize();

    if ((m_style & UIF_BALLOON_WINDOW_TYPE_MASK) == UIF_BALLOON_WINDOW_OK)
    {
        AddButton(IDOK);
    }
    else if ((m_style & UIF_BALLOON_WINDOW_TYPE_MASK) == UIF_BALLOON_WINDOW_YESNO)
    {
        AddButton(IDYES);
        AddButton(IDNO);
    }
}

inline STDMETHODIMP_(LPCTSTR)
CUIFBalloonWindow::GetClassName()
{
    return TEXT("MSIME_PopupMessage");
}

inline STDMETHODIMP_(LPCTSTR)
CUIFBalloonWindow::GetWndTitle()
{
    return TEXT("MSIME_PopupMessage");
}

inline STDMETHODIMP_(void)
CUIFBalloonWindow::OnCreate(HWND hWnd)
{
    m_nActionID = -1;
    AdjustPos();
}

inline STDMETHODIMP_(void)
CUIFBalloonWindow::OnDestroy(HWND hWnd)
{
    SendNotification(m_nActionID);
    DoneWindowRegion();
}

inline STDMETHODIMP_(void)
CUIFBalloonWindow::OnKeyDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    CUIFBalloonButton *pButton = NULL;

    switch (wParam)
    {
        case VK_RETURN:
            pButton = (CUIFBalloonButton *)FindUIObject(0);
            break;
        case VK_ESCAPE:
            m_nActionID = -1;
            ::DestroyWindow(m_hWnd);
            return;
        case TEXT('Y'):
            pButton = FindButton(IDYES);
            break;
        case TEXT('N'):
            pButton = FindButton(IDNO);
            break;
    }

    if (!pButton)
        return;

    m_nActionID = pButton->m_nCommandID;
    ::DestroyWindow(m_hWnd);
}

inline STDMETHODIMP_(LRESULT)
CUIFBalloonWindow::OnObjectNotify(CUIFObject *pObject, WPARAM wParam, LPARAM lParam)
{
    CUIFBalloonButton *pButton = (CUIFBalloonButton *)pObject;
    m_nActionID = pButton->m_nCommandID;
    ::DestroyWindow(m_hWnd);
    return 0;
}

inline STDMETHODIMP_(void)
CUIFBalloonWindow::OnPaint(HDC hDC)
{
    RECT rc;
    GetRect(&rc);
    PaintFrameProc(hDC, &rc);

    switch (m_nBalloonType)
    {
        case 1:
            rc.top += 16;
            break;
        case 2:
            rc.right -= 16;
            break;
        case 3:
            rc.left += 16;
            break;
        default:
            rc.bottom -= 16;
            break;
    }

    RECT rcMargin;
    GetMargin(&rcMargin);

    rc.left += rcMargin.left;
    rc.top += rcMargin.top;
    rc.right -= rcMargin.right;
    rc.bottom -= rcMargin.bottom;

    PaintMessageProc(hDC, &rc, m_pszBalloonText);
}

inline void
CUIFBalloonWindow::AddButton(UINT nCommandId)
{
    RECT rc = { 0, 0, 0, 0 };
    if (!((IDOK <= nCommandId) && (nCommandId <= IDNO)))
        return;

    CUIFBalloonButton *pButton = new(cicNoThrow) CUIFBalloonButton(this, m_cButtons, &rc, 5);
    if (!pButton)
        return;

    pButton->Initialize();
    pButton->m_nCommandID = nCommandId;

    LPCWSTR pszText; // FIXME: Use resource strings
    switch (nCommandId)
    {
        case IDOK:
            pszText = L"OK";
            break;
        case IDCANCEL:
            pszText = L"Cancel";
            break;
        case IDABORT:
            pszText = L"&Abort";
            break;
        case IDRETRY:
            pszText = L"&Retry";
            break;
        case IDIGNORE:
            pszText = L"&Ignore";
            break;
        case IDYES:
            pszText = L"&Yes";
            break;
        default:
            pszText = L"&No";
            break;
    }

    pButton->SetText(pszText);

    AddUIObj(pButton);
    ++m_cButtons;
}

/// @unimplemented
inline void
CUIFBalloonWindow::AdjustPos()
{
    //FIXME
}

/// @unimplemented
inline HRGN
CUIFBalloonWindow::CreateRegion(LPCRECT prc)
{
    //FIXME
    return NULL;
}

inline void
CUIFBalloonWindow::DoneWindowRegion()
{
    if (m_hRgn)
    {
        ::SetWindowRgn(m_hWnd, NULL, TRUE);
        ::DeleteObject(m_hRgn);
        m_hRgn = NULL;
    }
}

inline CUIFBalloonButton *
CUIFBalloonWindow::FindButton(UINT nCommandID)
{
    for (UINT iButton = 0; iButton < m_cButtons; ++iButton)
    {
        CUIFBalloonButton *pButton = (CUIFBalloonButton *)FindUIObject(iButton);
        if (pButton && (pButton->m_nCommandID == nCommandID))
            return pButton;
    }
    return NULL;
}

inline CUIFObject *
CUIFBalloonWindow::FindUIObject(UINT nObjectID)
{
    for (size_t iItem = 0; iItem < m_ObjectArray.size(); ++iItem)
    {
        CUIFObject *pObject = m_ObjectArray[iItem];
        if (pObject->m_nObjectID == nObjectID)
            return pObject;
    }
    return NULL;
}

inline COLORREF
CUIFBalloonWindow::GetBalloonBkColor()
{
    if (m_bHasBkColor )
        return m_rgbBkColor;
    else
        return ::GetSysColor(COLOR_INFOBK);
}

inline COLORREF
CUIFBalloonWindow::GetBalloonTextColor()
{
    if (m_bHasTextColor)
        return m_rgbTextColor;
    else
        return ::GetSysColor(COLOR_INFOTEXT);
}

inline void
CUIFBalloonWindow::GetButtonSize(LPSIZE pSize)
{
    HDC hDisplayDC = ::CreateDC(TEXT("DISPLAY"), NULL, NULL, NULL);

    TEXTMETRIC tm;
    HGDIOBJ hFontOld = ::SelectObject(hDisplayDC, m_hFont);
    ::GetTextMetrics(hDisplayDC, &tm);
    ::SelectObject(hDisplayDC, hFontOld);
    ::DeleteDC(hDisplayDC);

    pSize->cx = 16 * tm.tmAveCharWidth;
    pSize->cy = tm.tmHeight + 10;
}

inline void
CUIFBalloonWindow::GetMargin(LPRECT prcMargin)
{
    if (prcMargin)
        *prcMargin = m_rcMargin;
}

inline void
CUIFBalloonWindow::SetExcludeRect(LPCRECT prcExclude)
{
    m_rcExclude = *prcExclude;
    AdjustPos();
}

inline void
CUIFBalloonWindow::SetTargetPos(POINT ptTarget)
{
    m_ptTarget = ptTarget;
    AdjustPos();
}

inline void
CUIFBalloonWindow::SetText(LPCWSTR pszText)
{
    if (m_pszBalloonText)
    {
        delete[] m_pszBalloonText;
        m_pszBalloonText = NULL;
    }

    if (pszText == NULL)
        pszText = L"";

    size_t cch = wcslen(pszText);
    m_pszBalloonText = new(cicNoThrow) WCHAR[cch + 1];
    if (m_pszBalloonText)
        lstrcpynW(m_pszBalloonText, pszText, cch + 1);

    AdjustPos();
}

inline void
CUIFBalloonWindow::InitWindowRegion()
{
    RECT rc;
    GetRect(&rc);
    m_hRgn = CreateRegion(&rc);
    if (m_hRgn)
        ::SetWindowRgn(m_hWnd, m_hRgn, TRUE);
}

inline void
CUIFBalloonWindow::LayoutObject()
{
    SIZE size;
    GetButtonSize(&size);

    RECT rc;
    GetRect(&rc);

    switch (m_nBalloonType)
    {
        case 1:
            rc.top += 16;
            break;
        case 2:
            rc.right -= 16;
            break;
        case 3:
            rc.left += 16;
            break;
        default:
            rc.bottom -= 16;
            break;
    }

    RECT rcMargin;
    GetMargin(&rcMargin);
    rc.left += rcMargin.left;
    rc.top += rcMargin.top;
    rc.right -= rcMargin.right;
    rc.bottom -= rcMargin.bottom;

    LONG xLeft = (rc.left + rc.right - size.cx * (((m_cButtons - 1) / 2) - m_cButtons)) / 2;
    for (UINT iButton = 0; iButton < m_cButtons; ++iButton)
    {
        CUIFObject *UIObject = FindUIObject(iButton);
        if (!UIObject)
            continue;

        rcMargin.left = xLeft + iButton * (size.cx * 3 / 2);
        rcMargin.top = rc.bottom - size.cy;
        rcMargin.right = rcMargin.left + size.cx;
        rcMargin.bottom = rc.bottom;

        UIObject->SetRect(&rcMargin);
        UIObject->Show(TRUE);
    }
}

inline void
CUIFBalloonWindow::PaintFrameProc(HDC hDC, LPCRECT prc)
{
    HRGN hRgn = CreateRegion(prc);
    HBRUSH hbrBack = ::CreateSolidBrush(GetBalloonBkColor());
    HBRUSH hbrFrame = ::CreateSolidBrush(::GetSysColor(COLOR_WINDOWFRAME));
    ::FillRgn(hDC, hRgn, hbrBack);
    ::FrameRgn(hDC, hRgn, hbrFrame, 1, 1);
    ::DeleteObject(hbrBack);
    ::DeleteObject(hbrFrame);
    ::DeleteObject(hRgn);
}

inline void
CUIFBalloonWindow::PaintMessageProc(HDC hDC, LPRECT prc, LPCWSTR pszText)
{
    HGDIOBJ hFontOld = ::SelectObject(hDC, m_hFont);
    COLORREF rgbOldColor = ::SetTextColor(hDC, GetBalloonTextColor());
    INT nOldBkMode = ::SetBkMode(hDC, TRANSPARENT);
    ::DrawTextW(hDC, pszText, -1, prc, DT_WORDBREAK);
    ::SelectObject(hDC, hFontOld);
    ::SetTextColor(hDC, rgbOldColor);
    ::SetBkMode(hDC, nOldBkMode);
}

inline void
CUIFBalloonWindow::SendNotification(WPARAM wParam)
{
    if (m_hwndNotif)
        ::PostMessage(m_hwndNotif, m_uNotifMsg, wParam, 0);
}
