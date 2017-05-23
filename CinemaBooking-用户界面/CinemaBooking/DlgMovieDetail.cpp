// DlgMovieDetail.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CinemaBooking.h"
#include "DlgMovieDetail.h"
#include "afxdialogex.h"


// CDlgMovieDetail �Ի���

IMPLEMENT_DYNAMIC(CDlgMovieDetail, CDialogEx)

CDlgMovieDetail::CDlgMovieDetail(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgMovieDetail::IDD, pParent)
{

}

CDlgMovieDetail::~CDlgMovieDetail()
{
}

void CDlgMovieDetail::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MovieDetail, m_MovieDetail);
	DDX_Control(pDX, IDC_BoxFname, m_BoxFname);

	if (!m_db.IsOpen() && !m_db.OpenEx(_T("DSN=bookingdns;UID=aa;PWD=123"),
		CDatabase::openReadOnly | CDatabase::noOdbcDialog))
	{
		MessageBox(L"���Ӵ���");
		return;
	}
	CRecordset m_set(&m_db);
	//Open�򿪼�¼����ִ��T-SQL��䣬��ȡ������Ϊֻ������
	CString sql;
	sql.Format(_T("select releasetime,nation,director,protagonist,type,duration,language,intro from Film where fname = '%s'"), fname);
	m_set.Open(CRecordset::forwardOnly, sql, CRecordset::readOnly);
	CString sreleasetime, snation, sdirector, sprotagonist, stype, sduration, slanguage, sintro;
	short index = 0;
	m_set.GetFieldValue(index, sreleasetime);//ȡ����һ���ֶε�ֵ 
	m_set.GetFieldValue(1, snation);//ȡ���ڶ���ֵ 
	m_set.GetFieldValue(2, sdirector);//ȡ��������ֵ	
	m_set.GetFieldValue(3, sprotagonist);//ȡ�����ĸ��ֶε�ֵ 
	m_set.GetFieldValue(4, stype);
	m_set.GetFieldValue(5, sduration);
	m_set.GetFieldValue(6, slanguage);
	m_set.GetFieldValue(7, sintro);

	GetDlgItem(IDC_BoxFname)->SetWindowText(fname);
	CString MovieDetail;
	MovieDetail.Format(_T("  ӰƬ����%s\n  ��ӳ���ڣ�%s\n  ���ң�%s\n  ���ݣ�%s\n  ���ݣ�%s\n  ���ͣ�%s\n  ʱ����%s\n  ���ԣ�%s\n  ��飺%s\n  "),
		fname, sreleasetime, snation, sdirector, sprotagonist, stype, sduration, slanguage, sintro);

	/*CFont font;

	font.CreateFont(0, // nHeight
	0, // nWidth
	0, // nEscapement
	0, // nOrientation
	FW_BOLD, // nWeight
	FALSE, // bItalic
	FALSE, // bUnderline
	0, // cStrikeOut
	ANSI_CHARSET, // nCharSet
	OUT_DEFAULT_PRECIS, // nOutPrecision
	CLIP_DEFAULT_PRECIS, // nClipPrecision
	DEFAULT_QUALITY, // nQuality
	DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily
	_T("Arial"));

	m_MovieDetail.SetFont(&font);

	font.DeleteObject();
	*/
	GetDlgItem(IDC_MovieDetail)->SetWindowText(MovieDetail);
	m_set.Close();
	m_db.Close();

	
}


BEGIN_MESSAGE_MAP(CDlgMovieDetail, CDialogEx)
	ON_BN_CLICKED(IDC_OUT, &CDlgMovieDetail::OnBnClickedOut)
END_MESSAGE_MAP()


// CDlgMovieDetail ��Ϣ�������


void CDlgMovieDetail::OnBnClickedOut()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}
