#pragma once
#include "afxcmn.h"
#include "afxdb.h"  //�������ݿ�
#include "DlgMovieDetail.h"
#include "DlgBookTicket.h"

// CDlgShowing �Ի���

class CDlgShowing : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgShowing)

public:
	CDlgShowing(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgShowing();

// �Ի�������
	enum { IDD = IDD_Showing };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListShowing;
	//����ӣ����ݿ�
private:
	CDatabase m_db;
public:
	CString VariantToCString(CDBVariant* var);
	afx_msg void OnBnClickedMoviedetail();
	CString Fname,Id;  //ѡ�е�ӰƬ��
	afx_msg void OnBnClickedBookticket();
};
