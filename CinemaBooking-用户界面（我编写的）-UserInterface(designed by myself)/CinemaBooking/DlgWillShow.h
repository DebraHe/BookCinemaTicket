#pragma once
#include "afxcmn.h"
#include "afxdb.h"  //�������ݿ�
#include "DlgMovieDetail.h"
// CDlgWillShow �Ի���

class CDlgWillShow : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgWillShow)

public:
	CDlgWillShow(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgWillShow();

// �Ի�������
	enum { IDD = IDD_WillShow };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListWillShow;
	//����ӣ����ݿ�
private:
	CDatabase m_db;
public:
	CString VariantToCString(CDBVariant* var);
	afx_msg void OnBnClickedMoviedetail();
	CString Fname;  //ѡ�е�ӰƬ��
};
