#pragma once


// CDlgUserLogin �Ի���
#include "DlgZhuCe.h"
#include "afxdb.h"  //�������ݿ�

class CDlgUserLogin : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgUserLogin)

public:
	CDlgUserLogin(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgUserLogin();

// �Ի�������
	enum { IDD = IDD_UserLogin };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedDenglu();
	afx_msg void OnBnClickedZhuce();
	CString m_ID;
	CString m_PassWord;
	//����ӣ����ݿ�
private:
	CDatabase m_db;
	BOOL PreTranslateMessage(MSG* pMsg);
public:
	afx_msg void OnBnClickedOut();
};
