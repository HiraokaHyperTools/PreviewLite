// Preview.h : CPreview �̐錾
#pragma once
#include "resource.h"       // ���C�� �V���{��
#include <atlctl.h>
#include "PreviewLite_i.h"
#include "_IPreviewEvents_CP.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "DCOM �̊��S�T�|�[�g���܂�ł��Ȃ� Windows Mobile �v���b�g�t�H�[���̂悤�� Windows CE �v���b�g�t�H�[���ł́A�P��X���b�h COM �I�u�W�F�N�g�͐������T�|�[�g����Ă��܂���BATL ���P��X���b�h COM �I�u�W�F�N�g�̍쐬���T�|�[�g���邱�ƁA����т��̒P��X���b�h COM �I�u�W�F�N�g�̎����̎g�p�������邱�Ƃ���������ɂ́A_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ���`���Ă��������B���g�p�� rgs �t�@�C���̃X���b�h ���f���� 'Free' �ɐݒ肳��Ă���ADCOM Windows CE �ȊO�̃v���b�g�t�H�[���ŃT�|�[�g�����B��̃X���b�h ���f���Ɛݒ肳��Ă��܂����B"
#endif

using namespace ATL;



// CPreview
class ATL_NO_VTABLE CPreview :
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<IPreview2, &IID_IPreview2, &LIBID_PreviewLiteLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IOleControlImpl<CPreview>,
	public IOleObjectImpl<CPreview>,
	public IOleInPlaceActiveObjectImpl<CPreview>,
	public IViewObjectExImpl<CPreview>,
	public IOleInPlaceObjectWindowlessImpl<CPreview>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CPreview>,
	public CProxy_IPreviewEvents<CPreview>,
	public IQuickActivateImpl<CPreview>,
	public IProvideClassInfo2Impl<&CLSID_Preview, &__uuidof(_IPreviewEvents), &LIBID_PreviewLiteLib>,
	public CComCoClass<CPreview, &CLSID_Preview>,
	public CComControl<CPreview>
{
public:
#pragma warning(push)
#pragma warning(disable: 4355) // 'this' : �x�[�X �����o�[�������q���X�g�Ŏg�p����܂����B


	CPreview()
	{

	}

#pragma warning(pop)

	CxImage pic;
	int printable;

	DECLARE_OLEMISC_STATUS(0
		|OLEMISC_RECOMPOSEONRESIZE
		|OLEMISC_CANTLINKINSIDE
		|OLEMISC_INSIDEOUT
		|OLEMISC_ACTIVATEWHENVISIBLE
		|OLEMISC_SETCLIENTSITEFIRST
		)

		DECLARE_REGISTRY_RESOURCEID(IDR_PREVIEW)


	BEGIN_COM_MAP(CPreview)
		COM_INTERFACE_ENTRY(IPreview)
		COM_INTERFACE_ENTRY(IPreview2)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(IViewObjectEx)
		COM_INTERFACE_ENTRY(IViewObject2)
		COM_INTERFACE_ENTRY(IViewObject)
		COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
		COM_INTERFACE_ENTRY(IOleInPlaceObject)
		COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObjectWindowless)
		COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
		COM_INTERFACE_ENTRY(IOleControl)
		COM_INTERFACE_ENTRY(IOleObject)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY(IConnectionPointContainer)
		COM_INTERFACE_ENTRY(IQuickActivate)
		COM_INTERFACE_ENTRY(IProvideClassInfo)
		COM_INTERFACE_ENTRY(IProvideClassInfo2)
	END_COM_MAP()

	BEGIN_PROP_MAP(CPreview)
		PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
		PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
		// �G���g���̗�
		// PROP_ENTRY_TYPE("�v���p�e�B��", dispid, clsid, vtType)
		// PROP_PAGE(CLSID_StockColorPage)
	END_PROP_MAP()

	BEGIN_CONNECTION_POINT_MAP(CPreview)
		CONNECTION_POINT_ENTRY(__uuidof(_IPreviewEvents))
	END_CONNECTION_POINT_MAP()

	BEGIN_MSG_MAP(CPreview)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_SETFOCUS, OnSetFocus)
		//MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
		CHAIN_MSG_MAP(CComControl<CPreview>)
		ALT_MSG_MAP(1)
		// �X�[�p�[�N���X Static �̃��b�Z�[�W �}�b�v �G���g���ɒu�������܂��B
	END_MSG_MAP()
	// �n���h���[ �v���g�^�C�v:
	//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnSetFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lRes = CComControl<CPreview>::OnSetFocus(uMsg, wParam, lParam, bHandled);
		return lRes;
	}

	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		return 0;
	}

	// http://microsoft.public.vc.atl.narkive.com/t9sSahd4/atl-activex-control-flicker
	LRESULT OnEraseBkgnd(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		bHandled = TRUE;
		return 0;
	}

	STDMETHOD(SetObjectRects)(LPCRECT prcPos, LPCRECT prcClip)
	{
		IOleInPlaceObjectWindowlessImpl<CPreview>::SetObjectRects(prcPos, prcClip);
		int cx, cy;
		cx = prcPos->right - prcPos->left;
		cy = prcPos->bottom - prcPos->top;
		return S_OK;
	}

	// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
	{
		static const IID* const arr[] =
		{
			&IID_IPreview,
		};

		for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
		{
			if (InlineIsEqualGUID(*arr[i], riid))
				return S_OK;
		}
		return S_FALSE;
	}

	// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

	// IPreview

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		printable = 0;
		return S_OK;
	}

	void FinalRelease()
	{

	}

	class Fitrect {
	public:
		static CRect Fit(CRect rcMax, CSize rcBox) {
			if (rcMax.Height() == 0 || rcBox.cy == 0)
				return rcMax;
			float frMax = rcMax.Width() / (float)rcMax.Height();
			float frBox = rcBox.cx / (float)rcBox.cy;
			float centerx = ((float)rcMax.left + rcMax.right) / 2;
			float centery = ((float)rcMax.top + rcMax.bottom) / 2;
			if (frMax >= frBox) {
				// �c��
				float v = float(rcBox.cx) * rcMax.Height() / rcBox.cy / 2;
				return CRect(
					int(centerx - v),
					int(rcMax.top),
					int(centerx + v),
					int(rcMax.bottom)
				);
			}
			else {
				// ����
				float v = float(rcBox.cy) * rcMax.Width() / rcBox.cx / 2;
				return CRect(
					int(rcMax.left),
					int(centery - v),
					int(rcMax.right),
					int(centery + v)
				);
			}
		}
	};

	virtual HRESULT OnDraw(
		ATL_DRAWINFO& di
	);

	STDMETHOD(ShowFile)(BSTR bstrFileName, int iSelectCount);
	STDMETHOD(get_printable)(LONG* pVal);
	STDMETHOD(put_printable)(LONG newVal);
	STDMETHOD(get_cxImage)(LONG* pVal);
	STDMETHOD(get_cyImage)(LONG* pVal);
	STDMETHOD(Show)(VARIANT var);

	STDMETHOD(Zoom)(int iSelectCount);
	STDMETHOD(BestFit)(void);
	STDMETHOD(ActualSize)(void);
	STDMETHOD(SlideShow)(void);
};

OBJECT_ENTRY_AUTO(__uuidof(Preview), CPreview)
