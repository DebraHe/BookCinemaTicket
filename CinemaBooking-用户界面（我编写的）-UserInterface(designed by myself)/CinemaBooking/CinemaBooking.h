
// CinemaBooking.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCinemaBookingApp: 
// �йش����ʵ�֣������ CinemaBooking.cpp
//

class CCinemaBookingApp : public CWinApp
{
public:
	CCinemaBookingApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCinemaBookingApp theApp;