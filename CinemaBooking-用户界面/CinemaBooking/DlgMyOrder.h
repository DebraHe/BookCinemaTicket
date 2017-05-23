#pragma once
#include "afxcmn.h"
#include "afxdb.h"  //�������ݿ�

// CDlgMyOrder �Ի���

class CDlgMyOrder : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgMyOrder)

public:
	CDlgMyOrder(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgMyOrder();

// �Ի�������
	enum { IDD = IDD_MyOrder };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListOrderInfo;
	//����ӣ����ݿ�
private:
	CDatabase m_db;
public:
	CString VariantToCString(CDBVariant* var);
	CString orderID;
	afx_msg void OnBnClickedOut();
};
