#pragma once
#include "afxdb.h"  //�������ݿ�
#include "afxwin.h"

// CDlgMovieDetail �Ի���

class CDlgMovieDetail : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgMovieDetail)

public:
	CDlgMovieDetail(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgMovieDetail();

// �Ի�������
	enum { IDD = IDD_MovieDetail };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	//����ӣ����ݿ�
private:
	CDatabase m_db;
public:
	CString fname;
	afx_msg void OnBnClickedOut();
	CStatic m_MovieDetail;
	CStatic m_BoxFname;
};
