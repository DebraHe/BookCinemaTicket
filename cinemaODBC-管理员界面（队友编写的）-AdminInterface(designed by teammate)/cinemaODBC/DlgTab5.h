#pragma once
#include "afxcmn.h"
#include "afxdb.h"//new

// CDlgTab5 �Ի���

class CDlgTab5 : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgTab5)

public:
	CDlgTab5(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgTab5();

// �Ի�������
	enum { IDD = IDD_DLGTAB_ACCOUNT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	CDatabase m_db;//new
public:
	virtual BOOL OnInitDialog();
	CString VariantToCString(CDBVariant*var);//new
	CListCtrl m_ListAccount;
};
