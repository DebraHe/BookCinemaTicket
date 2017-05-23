#pragma once
#include "afxcmn.h"
#include "afxdb.h"//new

// CDlgTab4 �Ի���

class CDlgTab4 : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgTab4)

public:
	CDlgTab4(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgTab4();

// �Ի�������
	enum { IDD = IDD_DLGTAB_ORDERS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	CDatabase m_db;//new
public:
	CListCtrl m_ListOrders;
	CString VariantToCString(CDBVariant*var);//new
	virtual BOOL OnInitDialog();
};
