// DlgUserLogin.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CinemaBooking.h"
#include "DlgUserLogin.h"
#include "afxdialogex.h"


// CDlgUserLogin �Ի���

IMPLEMENT_DYNAMIC(CDlgUserLogin, CDialogEx)

CDlgUserLogin::CDlgUserLogin(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgUserLogin::IDD, pParent)
	, m_ID(_T(""))
	, m_PassWord(_T(""))
{

}

CDlgUserLogin::~CDlgUserLogin()
{
}

void CDlgUserLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_Name, m_ID);
	DDX_Text(pDX, IDC_EDIT_PassWord, m_PassWord);
}


BEGIN_MESSAGE_MAP(CDlgUserLogin, CDialogEx)
	ON_BN_CLICKED(IDC_DengLu, &CDlgUserLogin::OnBnClickedDenglu)
	ON_BN_CLICKED(IDC_ZhuCe, &CDlgUserLogin::OnBnClickedZhuce)
	ON_BN_CLICKED(IDC_OUT, &CDlgUserLogin::OnBnClickedOut)
END_MESSAGE_MAP()


// CDlgUserLogin ��Ϣ�������
BOOL CDlgUserLogin::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN&&pMsg->wParam == VK_RETURN)
		return TRUE;
	if (pMsg->message == WM_KEYDOWN&&pMsg->wParam == VK_ESCAPE)
		return TRUE;
	return CDialog::PreTranslateMessage(pMsg);
}


void CDlgUserLogin::OnBnClickedDenglu()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//�������ݿ⣬������Դ��IsOpen�жϵ�ǰ�Ƿ���һ�����ӣ�
	//CDatabase::openReadOnly ��ʾ��ֻ����ʽ������Դ��
	//CDatabase::noOdbcDialog ��ʾ����ʾODBC���ӶԻ���
	if (!m_db.IsOpen() && !m_db.OpenEx(_T("DSN=bookingdns;UID=aa;PWD=123"),
		CDatabase::openReadOnly | CDatabase::noOdbcDialog))
	{
		MessageBox(L"���Ӵ���");
		return;
	}
	CRecordset m_set(&m_db);
	//Open�򿪼�¼����ִ��T-SQL��䣬��ȡ������Ϊֻ������
	m_set.Open(CRecordset::forwardOnly, _T("select * from Account"), CRecordset::readOnly);
	if (!m_set.IsEOF())
	{
		while (!m_set.IsEOF())
		{
			UpdateData(TRUE);
			CString sID, sPassWord;
			short index = 0;
			m_set.GetFieldValue(index, sID);//ȡ����һ���ֶε�ֵ���ŵ�sID�� 
			m_set.GetFieldValue(1, sPassWord);//ȡ���ڶ���ֵ�ŵ�sPassWord�� 
			if ((_tcscmp(sID, m_ID) == 0) && (_tcscmp(sPassWord, m_PassWord) == 0))
			{
				//MessageBox(L"��½�ɹ�");
				CDialogEx::OnOK();
				return;
			}
			m_set.MoveNext();
		}
		MessageBox(L"��¼ʧ�ܣ��û��������ڻ����������");
		return;
	}
	m_set.Close();
	m_db.Close();

	
}


void CDlgUserLogin::OnBnClickedZhuce()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDlgZhuCe m_DlgZhuCe;
	m_DlgZhuCe.DoModal();
}


void CDlgUserLogin::OnBnClickedOut()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	exit(0);
}
