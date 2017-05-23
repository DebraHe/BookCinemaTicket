
// CinemaBookingDlg.h : ͷ�ļ�
//
#include "DlgShowing.h"   
#include "DlgWillShow.h"
#include "DlgMyOrder.h"
#include "DlgMovieDetail.h"
#include "DlgBookTicket.h"
#include "DlgUserLogin.h"

#include "TraButton.h"  //͸����ť

#pragma once


// CCinemaBookingDlg �Ի���
class CCinemaBookingDlg : public CDialogEx
{
// ����
public:
	CCinemaBookingDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CINEMABOOKING_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	//�½�������ǩҳ
	CDlgShowing *m_DlgShowing;
	CDlgWillShow *m_DlgWillShow;
	afx_msg void OnBnClickedShowing();
	afx_msg void OnBnClickedWillshow();
	//����һ��ҳ�棬��ʾ�ҵĶ���
	afx_msg void OnBnClickedMyorder();
public:
	//͸����ť
	CTraButton m_btn1;
	CTraButton m_btn2;
	CTraButton m_btn3;
	CTraButton m_btn4;

	
	afx_msg void OnBnClickedOutlogin();
	
	CString m_StaticID;
public:
	CString ID; //����һ��ȫ�ֱ�����Ϊ�˻���
};
