// dllmain.h : モジュール クラスの宣言です。

class CPreviewLiteModule : public ATL::CAtlDllModuleT< CPreviewLiteModule >
{
public :
	DECLARE_LIBID(LIBID_PreviewLiteLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_PREVIEWLITE, "{5A025858-ABAD-4FC5-B8FD-1625CC0C6665}")
};

extern class CPreviewLiteModule _AtlModule;
