#pragma once
#include "afxcmn.h"
#include "afxdb.h"//new

// CDlgTab1 �Ի���

class CDlgTab1 : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgTab1)

public:
	CDlgTab1(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgTab1();

// �Ի�������
	enum { IDD = IDD_DLGTAB_FILM };


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	CDatabase m_db;//new

public:
	CListCtrl m_ListFilm;
	CString VariantToCString(CDBVariant*var);//new
	afx_msg void OnBnClickedButtonOpen();
	
	
	afx_msg void OnBnClickedButtonSavefilm();
	CString m_EditFid;
	CString m_EditFname;
	CString m_EditDirector;
	CString m_EditProtagonist;
	CString m_EditType;
	CString m_EditReleasetime;
	CString m_EditDuration;
	CString m_EditNation;
	CString m_EditIntro;
	afx_msg void OnBnClickedButtonDelefilm();
	afx_msg void OnNMDblclkListFilm(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonAlterfilm();
	virtual BOOL OnInitDialog();
	CString m_EditLanguage;
};
