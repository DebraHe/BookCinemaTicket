
// cinemaODBCDlg.h : ͷ�ļ�
//

#pragma once
#include "DlgTab1.h"
#include "DlgTab2.h"
#include "DlgTab3.h"
#include "DlgTab4.h"
#include "DlgTab5.h"
#include "afxdb.h"//new


// CcinemaODBCDlg �Ի���
class CcinemaODBCDlg : public CDialogEx
{
// ����
public:
	CcinemaODBCDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CINEMAODBC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_tab;

	CDlgTab1 m_tab1;
	CDlgTab2 m_tab2;
	CDlgTab3 m_tab3;
	CDlgTab4 m_tab4;
	CDlgTab5 m_tab5;

	afx_msg void OnBnClickedButtonAddfilm();
	afx_msg void OnBnClickedButtonAddcinema();
	afx_msg void OnBnClickedButtonAddschedule();
	afx_msg void OnSelchangeTabUser(NMHDR *pNMHDR, LRESULT *pResult);
};
