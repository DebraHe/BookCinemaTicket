
// cinemaODBC.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CcinemaODBCApp:
// �йش����ʵ�֣������ cinemaODBC.cpp
//

class CcinemaODBCApp : public CWinApp
{
public:
	CcinemaODBCApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CcinemaODBCApp theApp;