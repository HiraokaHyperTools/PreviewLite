// Preview.cpp : CPreview の実装
#include "stdafx.h"
#include "Preview.h"

// CPreview


STDMETHODIMP CPreview::ShowFile(BSTR bstrFileName, int iSelectCount)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	pic.Clear();
	status.Empty();

	if (wcslen(bstrFileName) < 1) {
		status = "プレビューは空です。";
		FireViewChange();
		return S_OK;
	}

	bool f = pic.Load(T2CW(bstrFileName));
	if (!f) {
		status.Format(L"表示できません %s", bstrFileName);
	}
	FireViewChange();

	return f ? S_OK : S_FALSE;
}


STDMETHODIMP CPreview::get_printable(LONG* pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	*pVal = printable;

	return S_OK;
}


STDMETHODIMP CPreview::put_printable(LONG newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	printable = newVal;

	return S_OK;
}


STDMETHODIMP CPreview::get_cxImage(LONG* pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	*pVal = pic.GetWidth();

	return S_OK;
}


STDMETHODIMP CPreview::get_cyImage(LONG* pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	*pVal = pic.GetHeight();

	return S_OK;
}


STDMETHODIMP CPreview::Show(VARIANT var)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (var.vt == VT_BSTR) {
		return ShowFile(var.bstrVal, 0);
	}

	return S_FALSE;
}


STDMETHODIMP CPreview::Zoom(int iSelectCount)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: ここに実装コードを追加してください。

	return S_FALSE;
}


STDMETHODIMP CPreview::BestFit()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: ここに実装コードを追加してください。

	return S_FALSE;
}


STDMETHODIMP CPreview::ActualSize()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: ここに実装コードを追加してください。

	return S_FALSE;
}


STDMETHODIMP CPreview::SlideShow()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: ここに実装コードを追加してください。

	return S_FALSE;
}

HRESULT CPreview::OnDraw(
	ATL_DRAWINFO& di
) {
	CRect rcMax = CRect(di.prcBounds->left, di.prcBounds->top, di.prcBounds->right, di.prcBounds->bottom);
	FillRect(di.hdcDraw, rcMax, (HBRUSH)GetStockObject(WHITE_BRUSH));

	if (pic.IsValid()) {
		CRect rc = Fitrect::Fit(
			rcMax,
			CSize(pic.GetWidth(), pic.GetHeight())
		);
		pic.Draw(di.hdcDraw, rc, 0, true);
	}
	else {
		SetBkColor(di.hdcDraw, RGB(255, 255, 255));
		SetTextColor(di.hdcDraw, RGB(0, 0, 0));
		DrawText(di.hdcDraw, status, status.GetLength(), rcMax, DT_LEFT|DT_TOP);
	}
	return S_OK;
}
