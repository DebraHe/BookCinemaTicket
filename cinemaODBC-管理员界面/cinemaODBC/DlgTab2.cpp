// DlgTab2.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "cinemaODBC.h"
#include "DlgTab2.h"
#include "afxdialogex.h"


// CDlgTab2 �Ի���

IMPLEMENT_DYNAMIC(CDlgTab2, CDialogEx)

CDlgTab2::CDlgTab2(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgTab2::IDD, pParent)
{

	m_EditTid = _T("");
	m_EditTname = _T("");
	m_EditAddress = _T("");
}

CDlgTab2::~CDlgTab2()
{
}

void CDlgTab2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CINEMA, m_ListCinema);

	

	DDX_Text(pDX, IDC_EDIT_TID, m_EditTid);
	DDV_MaxChars(pDX, m_EditTid, 50);
	DDX_Text(pDX, IDC_EDIT_TNAME, m_EditTname);
	DDV_MaxChars(pDX, m_EditTname, 50);
	DDX_Text(pDX, IDC_EDIT_ADDR, m_EditAddress);
	DDV_MaxChars(pDX, m_EditAddress, 100);
}

BOOL CDlgTab2::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect rc;
	m_ListCinema.GetWindowRect(&rc);

	m_ListCinema.InsertColumn(0,_T("ӰԺ���"),LVCFMT_CENTER,rc.Size().cx/4,0);
	m_ListCinema.InsertColumn(1,_T("ӰԺ��"),LVCFMT_CENTER,rc.Size().cx/4,1);
	m_ListCinema.InsertColumn(2,_T("��ϸ��ַ"),LVCFMT_CENTER,rc.Size().cx/4,2);


	m_ListCinema.SetExtendedStyle(m_ListCinema.GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT
		|LVS_EX_HEADERDRAGDROP|LVS_EX_TWOCLICKACTIVATE|LVS_EX_FLATSB);


	//�����ݿ�film������ݲ��ֵ��뵽listcontrol��
	if(!m_db.IsOpen()&& !m_db.OpenEx(_T("DSN=bookingdns;UID=aa;PWD=123"),CDatabase::openReadOnly|CDatabase::noOdbcDialog))
	{
		MessageBox(L"���Ӵ���");
		return TRUE;
	}
	CRecordset m_set(&m_db);

	m_set.Open(CRecordset::forwardOnly,_T("select * from Theatre"),CRecordset::readOnly);
	CDBVariant var;
	m_ListCinema.DeleteAllItems();
	short nFields=m_set.GetODBCFieldCount();
	for(int i=0;!m_set.IsEOF();i++,m_set.MoveNext())
	{
		for(short index=0;index< nFields;index++)
		{
			m_set.GetFieldValue(index,var);
			if(index==0)
				m_ListCinema.InsertItem(i,VariantToCString(&var));
			else
				m_ListCinema.SetItemText(i,index,VariantToCString(&var));

		}
	}
	m_set.Close();
	m_db.Close();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


CString CDlgTab2::VariantToCString(CDBVariant*var)
{
	CString str_conv;  //���ת���������
	if (!var)
	{
		str_conv = "NULL Var Parameter";
		return str_conv;
	}
	switch (var->m_dwType)
	{
	case DBVT_SHORT:
		str_conv.Format(L"%d", (int)var->m_iVal);
		break;
	case DBVT_LONG:
		str_conv.Format(L"%d", var->m_lVal);
		break;
	case DBVT_SINGLE:
		str_conv.Format(L"%10.6f", (double)var->m_fltVal);
		break;
	case DBVT_DOUBLE:
		str_conv.Format(L"%10.6f", var->m_dblVal);
		break;
	case DBVT_BOOL:
		str_conv = (var->m_boolVal == 0) ? L"FALSE" : L"TURE";
		break;
	case DBVT_STRING:
		str_conv = var->m_pstring->GetBuffer();
		break;
	case DBVT_ASTRING:
		str_conv = var->m_pstringA->GetBuffer();
		break;
	case DBVT_WSTRING:
		str_conv = var->m_pstringW->GetBuffer();
		break;
	case DBVT_DATE:
		str_conv.Format(L"%d-%d-%d", (var->m_pdate)->year, (var->m_pdate)->month, (var->m_pdate)->day);
		break;
	default:
		str_conv.Format(L"UnKnown type %d\n", var->m_dwType);
		TRACE(L"UnKnown type %d\n", var->m_dwType);

	}
	return str_conv;

}

BEGIN_MESSAGE_MAP(CDlgTab2, CDialogEx)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_CINEMA, &CDlgTab2::OnLvnItemchangedListCinema)
	ON_BN_CLICKED(IDC_BUTTON_SAVECINEMA, &CDlgTab2::OnBnClickedButtonSavecinema)
	ON_BN_CLICKED(IDC_BUTTON_DELECINEMA, &CDlgTab2::OnBnClickedButtonDelecinema)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_CINEMA, &CDlgTab2::OnNMDblclkListCinema)
	ON_BN_CLICKED(IDC_BUTTON_ALTERCINEMA, &CDlgTab2::OnBnClickedButtonAltercinema)
END_MESSAGE_MAP()


// CDlgTab2 ��Ϣ�������


void CDlgTab2::OnLvnItemchangedListCinema(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


void CDlgTab2::OnBnClickedButtonSavecinema()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if( m_EditTid.IsEmpty()||m_EditTname.IsEmpty()||m_EditAddress.IsEmpty())
	{
       MessageBox(_T("������������Ϣ"),_T("ע��"),MB_OK);
	}
	else
	{
		//�������ݿ⣬������Դ��IsOpen�жϵ�ǰ�Ƿ���һ�����ӣ�
		//CDatabase::openReadOnly ��ʾ��ֻ����ʽ������Դ��
		//CDatabase::noOdbcDialog ��ʾ����ʾODBC���ӶԻ���
		if (!m_db.IsOpen() && !m_db.OpenEx(_T("DSN=bookingdns;UID=aa;PWD=123"),CDatabase::openReadOnly | CDatabase::noOdbcDialog))
		{
			MessageBox(L"���Ӵ���");
			return;
		}
		try
		{
			
			CString sql;
			sql.Format(_T("insert into Theatre(tid,tname,address) values('%s','%s','%s')"), m_EditTid, m_EditTname,m_EditAddress);
			m_db.ExecuteSQL(LPCTSTR(sql));
		}
		catch (CDBException *pe)
		{
			//pe->ReportError();
			MessageBox(_T("��ӰԺ�Ѵ��ڣ������"),_T("ע��"),MB_OK);
			pe->Delete();
		}
		m_db.Close();
		//�����ݿ�film������ݲ��ֵ��뵽listcontrol��
		
	if(!m_db.IsOpen()&& !m_db.OpenEx(_T("DSN=bookingdns;UID=aa;PWD=123"),CDatabase::openReadOnly|CDatabase::noOdbcDialog))
	{
		MessageBox(L"���Ӵ���");
		return;
	}
	CRecordset m_set(&m_db);

	m_set.Open(CRecordset::forwardOnly,_T("select * from Theatre"),CRecordset::readOnly);
	CDBVariant var;
	m_ListCinema.DeleteAllItems();
	short nFields=m_set.GetODBCFieldCount();
	for(int i=0;!m_set.IsEOF();i++,m_set.MoveNext())
	{
		for(short index=0;index< nFields;index++)
		{
			m_set.GetFieldValue(index,var);
			if(index==0)
				m_ListCinema.InsertItem(i,VariantToCString(&var));
			else
				m_ListCinema.SetItemText(i,index,VariantToCString(&var));

		}
	}
	m_set.Close();
	m_db.Close();
	
	}
}


void CDlgTab2::OnBnClickedButtonDelecinema()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	POSITION pos=m_ListCinema.GetFirstSelectedItemPosition();
	if(pos==NULL)
	{
		MessageBox(_T("��ѡ��һ����¼��"),_T("ע��"),MB_OK);//TRACE(_T("û����Ϣ��ѡ��"));
	}
	else
	{
		while(pos)
		{
			int index_item=m_ListCinema.GetNextSelectedItem(pos);
			TRACE(_T("item%d was selected!\n"),index_item);
			CString Bno=m_ListCinema.GetItemText(index_item,0);
			if(!m_db.IsOpen()&&!m_db.OpenEx(_T("DSN=bookingdns;UID=aa;PWD=123"),CDatabase::openReadOnly|CDatabase::noOdbcDialog))
			{
				MessageBox(L"���Ӵ���");
				return;
			}
			try
			{
				CString del;
				del.Format(_T("delete from Theatre where tid='%s'"),Bno);
				m_db.ExecuteSQL(del);
			}
			catch(CDBException*pe)
			{
				pe->ReportError();
				pe->Delete();
			}
			m_db.Close();
			m_ListCinema.DeleteItem(index_item);
		}
	}
}


void CDlgTab2::OnNMDblclkListCinema(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	CString tid,tname,addr;
	int i = m_ListCinema.GetSelectionMark();
	tid=m_ListCinema.GetItemText(i,0);
	tname=m_ListCinema.GetItemText(i,1);
	addr=m_ListCinema.GetItemText(i,2);

	m_EditTid=tid;
	m_EditTname=tname;
	m_EditAddress=addr;
    UpdateData(FALSE);



}


void CDlgTab2::OnBnClickedButtonAltercinema()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if( m_EditTid.IsEmpty()||m_EditTname.IsEmpty()||m_EditAddress.IsEmpty())
	{
       MessageBox(_T("������������Ϣ"),_T("ע��"),MB_OK);
	}
	else
	{
		//�������ݿ⣬������Դ��IsOpen�жϵ�ǰ�Ƿ���һ�����ӣ�
		//CDatabase::openReadOnly ��ʾ��ֻ����ʽ������Դ��
		//CDatabase::noOdbcDialog ��ʾ����ʾODBC���ӶԻ���
		if (!m_db.IsOpen() && !m_db.OpenEx(_T("DSN=bookingdns;UID=aa;PWD=123"),CDatabase::openReadOnly | CDatabase::noOdbcDialog))
		{
			MessageBox(L"���Ӵ���");
			return;
		}
		try
		{
			
			CString sql;
			sql.Format(_T("update Theatre set tname='%s', address='%s'where tid='%s'"), m_EditTname, m_EditAddress, m_EditTid);
			m_db.ExecuteSQL(LPCTSTR(sql));
		}
		catch (CDBException *pe)
		{
			
			//pe->ReportError();
			MessageBox(_T("��ӰԺ�Ѵ��ڣ������"),_T("ע��"),MB_OK);
			pe->Delete();
		}
		m_db.Close();
		//�����ݿ�film������ݲ��ֵ��뵽listcontrol��
		
	if(!m_db.IsOpen()&& !m_db.OpenEx(_T("DSN=bookingdns;UID=aa;PWD=123"),CDatabase::openReadOnly|CDatabase::noOdbcDialog))
	{
		MessageBox(L"���Ӵ���");
		return;
	}
	CRecordset m_set(&m_db);

	m_set.Open(CRecordset::forwardOnly,_T("select * from Theatre"),CRecordset::readOnly);
	CDBVariant var;
	m_ListCinema.DeleteAllItems();
	short nFields=m_set.GetODBCFieldCount();
	for(int i=0;!m_set.IsEOF();i++,m_set.MoveNext())
	{
		for(short index=0;index< nFields;index++)
		{
			m_set.GetFieldValue(index,var);
			if(index==0)
				m_ListCinema.InsertItem(i,VariantToCString(&var));
			else
				m_ListCinema.SetItemText(i,index,VariantToCString(&var));

		}
	}
	m_set.Close();
	m_db.Close();
	
	}
}



