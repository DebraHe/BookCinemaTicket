// DlgZhuCe.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CinemaBooking.h"
#include "DlgZhuCe.h"
#include "afxdialogex.h"


// CDlgZhuCe �Ի���

IMPLEMENT_DYNAMIC(CDlgZhuCe, CDialogEx)

CDlgZhuCe::CDlgZhuCe(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgZhuCe::IDD, pParent)
{
	m_id = _T("");
	m_password = _T("");
	m_name = _T("");
	m_tele = _T("");
}

CDlgZhuCe::~CDlgZhuCe()
{
}

void CDlgZhuCe::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_id, m_id);
	DDX_Text(pDX, IDC_password, m_password);
	DDX_Text(pDX, IDC_name, m_name);
	DDX_Text(pDX, IDC_tele, m_tele);
}


BEGIN_MESSAGE_MAP(CDlgZhuCe, CDialogEx)
	ON_BN_CLICKED(IDC_ZhuCeOK, &CDlgZhuCe::OnBnClickedZhuceok)
END_MESSAGE_MAP()


// CDlgZhuCe ��Ϣ�������


void CDlgZhuCe::OnBnClickedZhuceok()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	
	/*CRecordset m_set(&m_db);
	//Open�򿪼�¼����ִ��T-SQL��䣬��ȡ������Ϊֻ������
	m_set.Open(CRecordset::forwardOnly, _T("select * from Account"), CRecordset::readOnly);
	CDBVariant var;
	*/
	UpdateData(TRUE);
	if (m_id.IsEmpty() || m_password.IsEmpty() || m_name.IsEmpty() || m_tele.IsEmpty())
	{
		MessageBox(L"ע�������Ϣ������Ϊ�գ�ע��ʧ�ܣ�");
	}
	else
	{
		//�������ݿ⣬������Դ��IsOpen�жϵ�ǰ�Ƿ���һ�����ӣ�
		//CDatabase::openReadOnly ��ʾ��ֻ����ʽ������Դ��
		//CDatabase::noOdbcDialog ��ʾ����ʾODBC���ӶԻ���
		if (!m_db.IsOpen() && !m_db.OpenEx(_T("DSN=bookingdns;UID=aa;PWD=123"),
			CDatabase::openReadOnly | CDatabase::noOdbcDialog))
		{
			MessageBox(L"���Ӵ���");
			return;
		}
		try
		{			
			CString sql;
			sql.Format(_T("insert into Account(id,password,name,tele) values('%s','%s','%s','%s')"), m_id, m_password, m_name, m_tele);
			m_db.ExecuteSQL(LPCTSTR(sql));
		}
		catch (CDBException *pe)
		{
			//pe->ReportError();
			MessageBox(_T("���˺��ѱ�ע�ᣡ ������˻�����"),_T("ע��"),MB_OK);
			pe->Delete();
		}
		m_db.Close();
	}
	CDialogEx::OnOK();
}
