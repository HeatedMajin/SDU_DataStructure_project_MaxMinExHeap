
// StuManager2.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CStuManager2App: 
// �йش����ʵ�֣������ StuManager2.cpp
//

class CStuManager2App : public CWinApp
{
public:
	CStuManager2App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CStuManager2App theApp;