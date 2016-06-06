// Preview.cpp : CPreview の実装
#include "stdafx.h"
#include "Preview.h"

// CPreview


STDMETHODIMP CPreview::ShowFile(BSTR bstrFileName, int iSelectCount)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	pic.Clear();

	if (!pic.Load(T2CW(bstrFileName))) {
		FireViewChange();
		return E_FAIL;
	}

	FireViewChange();

	return S_OK;
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

	return E_FAIL;
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
	if (pic.IsValid()) {
		CRect rcMax = CRect(di.prcBounds->left, di.prcBounds->top, di.prcBounds->right, di.prcBounds->bottom);
		CRect rc = Fitrect::Fit(
			rcMax,
			CSize(pic.GetWidth(), pic.GetHeight())
		);
		pic.Draw(di.hdcDraw, rc, 0, true);
	}
	return S_OK;
}
