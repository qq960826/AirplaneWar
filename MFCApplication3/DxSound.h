// DxSound.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������
#include "DSBuffer.h"



// CDxSoundApp:
// �йش����ʵ�֣������ DxSound.cpp
//

class CDxSoundApp : public CWinApp
{
public:
	CDxSoundApp();
	CString app_path;

// ��д
public:
	virtual BOOL InitInstance();
private:
	BOOL InitializeDirectSound();
// ʵ��

	DECLARE_MESSAGE_MAP()
};

//extern CMFCApplication3Doc theApp;
