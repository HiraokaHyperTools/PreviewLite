// dllmain.cpp : DllMain �̎����ł��B

#include "stdafx.h"
#include "resource.h"
#include "PreviewLite_i.h"
#include "dllmain.h"

CPreviewLiteModule _AtlModule;

class CPreviewLiteApp : public CWinApp
{
public:

// �I�[�o�[���C�h
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CPreviewLiteApp, CWinApp)
END_MESSAGE_MAP()

CPreviewLiteApp theApp;

BOOL CPreviewLiteApp::InitInstance()
{
	return CWinApp::InitInstance();
}

int CPreviewLiteApp::ExitInstance()
{
	return CWinApp::ExitInstance();
}
