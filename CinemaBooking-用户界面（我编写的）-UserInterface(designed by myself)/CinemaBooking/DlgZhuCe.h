#pragma once
#include "afxwin.h"
#include "afxdb.h"  //�������ݿ�

// CDlgZhuCe �Ի���

class CDlgZhuCe : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgZhuCe)

public:
	CDlgZhuCe(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgZhuCe();

// �Ի�������
	enum { IDD = IDD_ZhuCe };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedZhuceok();
	CString m_id;
	CString m_password;
	CString m_name;
	CString m_tele;
//����ӣ����ݿ�
private:
	CDatabase m_db;

};
