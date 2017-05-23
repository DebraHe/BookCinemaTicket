// DlgTab3.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "cinemaODBC.h"
#include "DlgTab3.h"
#include "afxdialogex.h"


// CDlgTab3 �Ի���

IMPLEMENT_DYNAMIC(CDlgTab3, CDialogEx)

CDlgTab3::CDlgTab3(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgTab3::IDD, pParent)
{

	//  m_ComFid = _T("");
	//  m_ComTid = _T("");
	//  m_ComPrice = _T("");
	//  m_ComNum = _T("");
	m_EditStart = _T("");
	m_EditEnd = _T("");
	m_EditSid = _T("");
	m_EditPrice = _T("");
	m_EditNum = _T("");
}

CDlgTab3::~CDlgTab3()
{
}

void CDlgTab3::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SCHEDULE, m_ListSchedule);
	//  DDX_CBString(pDX, IDC_COMBO_FID, m_ComFid);
	//  DDV_MaxChars(pDX, m_ComFid, 50);
	//  DDX_CBString(pDX, IDC_COMBO_TID, m_ComTid);
	//  DDV_MaxChars(pDX, m_ComTid, 50);
	//  DDX_CBString(pDX, IDC_COMBO_PRICE, m_ComPrice);
	//  DDV_MaxChars(pDX, m_ComPrice, 50);
	//  DDX_CBString(pDX, IDC_COMBO_NUM, m_ComNum);
	//  DDV_MaxChars(pDX, m_ComNum, 50);
	DDX_Text(pDX, IDC_EDIT_STARTTIME, m_EditStart);
	DDV_MaxChars(pDX, m_EditStart, 50);
	DDX_Text(pDX, IDC_EDIT_ENDTIME, m_EditEnd);
	DDV_MaxChars(pDX, m_EditEnd, 50);
	DDX_Text(pDX, IDC_EDIT_SID, m_EditSid);
	DDV_MaxChars(pDX, m_EditSid, 50);

	DDX_Control(pDX, IDC_COMBO_TID, m_ComTid);
	DDX_Control(pDX, IDC_COMBO_FID, m_ComFid);
	//  DDX_Control(pDX, IDC_COMBO_NUM, m_ComNum);
	//  DDX_Control(pDX, IDC_COMBO_PRICE, m_ComPrice);
	DDX_Text(pDX, IDC_EDIT_PRICE, m_EditPrice);
	DDV_MaxChars(pDX, m_EditPrice, 50);
	DDX_Text(pDX, IDC_EDIT_NUM, m_EditNum);
	DDV_MaxChars(pDX, m_EditNum, 50);
}

BOOL CDlgTab3::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect rc;
	m_ListSchedule.GetWindowRect(&rc);

	m_ListSchedule.InsertColumn(0,_T("��Ƭ��"),LVCFMT_CENTER,rc.Size().cx/4,0);
	m_ListSchedule.InsertColumn(1,_T("��Ӱ��"),LVCFMT_CENTER,rc.Size().cx/4,1);
	m_ListSchedule.InsertColumn(2,_T("ӰԺ��"),LVCFMT_CENTER,rc.Size().cx/4,2);
	m_ListSchedule.InsertColumn(3,_T("��ʼʱ��"),LVCFMT_CENTER,rc.Size().cx/4,3);
	m_ListSchedule.InsertColumn(4,_T("����ʱ��"),LVCFMT_CENTER,rc.Size().cx/4,4);
	m_ListSchedule.InsertColumn(5,_T("����"),LVCFMT_CENTER,rc.Size().cx/4,5);
	m_ListSchedule.InsertColumn(6,_T("Ʊ��"),LVCFMT_CENTER,rc.Size().cx/4,6);


	m_ListSchedule.SetExtendedStyle(m_ListSchedule.GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT
		|LVS_EX_HEADERDRAGDROP|LVS_EX_TWOCLICKACTIVATE|LVS_EX_FLATSB);

	//�����ݿ�film������ݲ��ֵ��뵽listcontrol��
	if(!m_db.IsOpen()&& !m_db.OpenEx(_T("DSN=bookingdns;UID=aa;PWD=123"),CDatabase::openReadOnly|CDatabase::noOdbcDialog))
	{
		MessageBox(L"���Ӵ���");
		return TRUE;
	}
	CRecordset m_set(&m_db);

	m_set.Open(CRecordset::forwardOnly,_T("select * from Schedule"),CRecordset::readOnly);
	CDBVariant var;
	m_ListSchedule.DeleteAllItems();
	short nFields=m_set.GetODBCFieldCount();//��ȡ��������
	for(int i=0;!m_set.IsEOF();i++,m_set.MoveNext())//�ж��Ƿ����һ��
	{
		for(short index=0;index< nFields;index++)   //����
		{
			m_set.GetFieldValue(index,var);
			if(index==0)
				m_ListSchedule.InsertItem(i,VariantToCString(&var));
			else
				m_ListSchedule.SetItemText(i,index,VariantToCString(&var));

		}
	}

	m_set.Close();
	m_db.Close();

	if(!m_db.IsOpen()&& !m_db.OpenEx(_T("DSN=bookingdns;UID=aa;PWD=123"),CDatabase::openReadOnly|CDatabase::noOdbcDialog))
	{
		MessageBox(L"���Ӵ���");
		return TRUE;
	}

	CRecordset m_set1(&m_db);
	m_set1.Open(CRecordset::forwardOnly,_T("select fid from Film"),CRecordset::readOnly);
	CString comstr1;
	for (int i = 0; !m_set1.IsEOF(); i++, m_set1.MoveNext())
	{
		short m=0;
		m_set1.GetFieldValue(m,comstr1);
		m_ComFid.AddString(comstr1);
	}
	m_set1.Close();

	CRecordset m_set2(&m_db);
	m_set2.Open(CRecordset::forwardOnly,_T("select tid from Theatre"),CRecordset::readOnly);
	CString comstr2;
	for (int i = 0; !m_set2.IsEOF(); i++, m_set2.MoveNext())
	{
		short m=0;
		m_set2.GetFieldValue(m,comstr2);
		m_ComTid.AddString(comstr2);
	}
	m_set2.Close();

	

	m_db.Close();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


CString CDlgTab3::VariantToCString(CDBVariant*var)
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
		str_conv.Format(L"%20.8f", (double)var->m_fltVal);
		break;
	case DBVT_DOUBLE:
		str_conv.Format(L"%20.8f", var->m_dblVal);
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


BEGIN_MESSAGE_MAP(CDlgTab3, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_DELESCHEDULE, &CDlgTab3::OnBnClickedButtonDeleschedule)
	ON_BN_CLICKED(IDC_BUTTON_ADDSCHEDULE, &CDlgTab3::OnBnClickedButtonAddschedule)
	ON_BN_CLICKED(IDC_BUTTON_ALTERSCHEDULE, &CDlgTab3::OnBnClickedButtonAlterschedule)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_SCHEDULE, &CDlgTab3::OnNMDblclkListSchedule)
	ON_EN_CHANGE(IDC_EDIT_ENDTIME, &CDlgTab3::OnEnChangeEditEndtime)
END_MESSAGE_MAP()


// CDlgTab3 ��Ϣ�������


void CDlgTab3::OnBnClickedButtonDeleschedule()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	POSITION pos=m_ListSchedule.GetFirstSelectedItemPosition();
	if(pos==NULL)
	{
		MessageBox(_T("��ѡ��һ����¼��"),_T("ע��"),MB_OK);//TRACE(_T("û����Ϣ��ѡ��"));
	}
	else
	{
		while(pos)
		{
			int index_item=m_ListSchedule.GetNextSelectedItem(pos);
			TRACE(_T("item%d was selected!\n"),index_item);
			CString Bno=m_ListSchedule.GetItemText(index_item,0);
			if(!m_db.IsOpen()&&!m_db.OpenEx(_T("DSN=bookingdns;UID=aa;PWD=123"),CDatabase::openReadOnly|CDatabase::noOdbcDialog))
			{
				MessageBox(L"���Ӵ���");
				return;
			}
			try
			{
				CString del;
				del.Format(_T("delete from Schedule where sid='%s'"),Bno);
				m_db.ExecuteSQL(del);
			}
			catch(CDBException*pe)
			{
				pe->ReportError();
				pe->Delete();
			}
			m_db.Close();
			m_ListSchedule.DeleteItem(index_item);
		}
	}


}


void CDlgTab3::OnBnClickedButtonAddschedule()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	int Indexfid,Indextid;
	Indexfid = m_ComFid.GetCurSel();
	Indextid = m_ComTid.GetCurSel();
    CString strFid,strTid;
	if(Indexfid!=-1)
	{
		m_ComFid.GetLBText( Indexfid, strFid);
	}
	if(Indextid!=-1)
	{
		m_ComTid.GetLBText( Indextid, strTid);
	}
    

	
	
	UpdateData(TRUE);
	if( m_EditSid.IsEmpty()||m_EditStart.IsEmpty()||m_EditEnd.IsEmpty()||strFid.IsEmpty()||strTid.IsEmpty()||m_EditPrice.IsEmpty()||m_EditNum.IsEmpty())
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
			sql.Format(_T("insert into Schedule(sid,fid,tid,starttime,endtime,hallnum,price) values('%s','%s','%s','%s','%s','%s','%s')"), m_EditSid, strFid,strTid,m_EditStart,m_EditEnd,m_EditNum,m_EditPrice);
			m_db.ExecuteSQL(LPCTSTR(sql));
		}
		catch (CDBException *pe)
		{
			//pe->ReportError();
			MessageBox(_T("����Ƭ���Ѵ��ڣ������"),_T("ע��"),MB_OK);
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

	m_set.Open(CRecordset::forwardOnly,_T("select * from Schedule"),CRecordset::readOnly);
	CDBVariant var;
	m_ListSchedule.DeleteAllItems();
	short nFields=m_set.GetODBCFieldCount();
	for(int i=0;!m_set.IsEOF();i++,m_set.MoveNext())
	{
		for(short index=0;index< nFields;index++)
		{
			m_set.GetFieldValue(index,var);
			if(index==0)
				m_ListSchedule.InsertItem(i,VariantToCString(&var));
			else
				m_ListSchedule.SetItemText(i,index,VariantToCString(&var));

		}
	}
	m_set.Close();
	m_db.Close();
	
	}
	
}


void CDlgTab3::OnBnClickedButtonAlterschedule()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	/*
	int Indexfid = m_ComFid.GetCurSel();
    CString strFid;
	if(!Indexfid)
	{
       m_ComFid.GetLBText( Indexfid, strFid);
	}
	else
	{
		Indexfid=m_ComFid.GetCount ();
		m_ComFid.GetLBText( Indexfid, strFid);
	}

	int Indextid = m_ComTid.GetCurSel();
    CString strTid;
	if(!Indextid )
	{
        m_ComTid.GetLBText( Indextid, strTid);
	}
	else
	{
		Indextid=m_ComTid.GetCount ();
		m_ComTid.GetLBText( Indextid, strTid);
	}
	*/

	int Indexfid,Indextid;
	Indexfid = m_ComFid.GetCurSel();
	Indextid = m_ComTid.GetCurSel();
    CString strFid,strTid;
	if(Indexfid!=-1)
	{
		m_ComFid.GetLBText( Indexfid, strFid);
	}
	if(Indextid!=-1)
	{
		m_ComTid.GetLBText( Indextid, strTid);
	}
    
	UpdateData(TRUE);
	if( m_EditSid.IsEmpty()||strFid.IsEmpty()||strTid.IsEmpty()||m_EditStart.IsEmpty()||m_EditEnd.IsEmpty()||m_EditPrice.IsEmpty()||m_EditNum.IsEmpty())
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
			sql.Format(_T("update Schedule set fid='%s',tid='%s',starttime='%s',endtime='%s',hallnum='%s',price='%s' where sid='%s'"),strFid,strTid,m_EditStart,m_EditEnd,m_EditNum,m_EditPrice,m_EditSid);
			m_db.ExecuteSQL(LPCTSTR(sql));
		}
		catch (CDBException *pe)
		{
			//pe->ReportError();
			MessageBox(_T("����Ƭ���Ѵ��ڣ������"),_T("ע��"),MB_OK);
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

	m_set.Open(CRecordset::forwardOnly,_T("select * from Schedule"),CRecordset::readOnly);
	CDBVariant var;
	m_ListSchedule.DeleteAllItems();
	short nFields=m_set.GetODBCFieldCount();
	for(int i=0;!m_set.IsEOF();i++,m_set.MoveNext())
	{
		for(short index=0;index< nFields;index++)
		{
			m_set.GetFieldValue(index,var);
			if(index==0)
				m_ListSchedule.InsertItem(i,VariantToCString(&var));
			else
				m_ListSchedule.SetItemText(i,index,VariantToCString(&var));

		}
	}
	m_set.Close();
	m_db.Close();
	
	}
	
}


void CDlgTab3::OnNMDblclkListSchedule(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	CString sid,fid,tid,starttime,endtime,number,price;
	int i = m_ListSchedule.GetSelectionMark();
	sid=m_ListSchedule.GetItemText(i,0);
	fid=m_ListSchedule.GetItemText(i,1);
	tid=m_ListSchedule.GetItemText(i,2);
	starttime=m_ListSchedule.GetItemText(i,3);
	endtime=m_ListSchedule.GetItemText(i,4);
	number=m_ListSchedule.GetItemText(i,5);
	price=m_ListSchedule.GetItemText(i,6);

	int count_fid=m_ComFid.GetCount ();//��ȡ��ǰ�б����������1
	m_ComFid.InsertString(count_fid, fid );//�����һ�в���ѡ��ֵfid
	m_ComFid.SetCurSel(count_fid);  //��ʾ���һ��

	int count_tid=m_ComTid.GetCount ();//��ȡ��ǰ�б����������1
	m_ComTid.InsertString(count_tid, tid );//�����һ�в���ѡ��ֵfid
	m_ComTid.SetCurSel(count_tid);  //��ʾ���һ��

	m_EditSid=sid;
	m_EditStart=starttime;
	m_EditEnd=endtime;
	m_EditNum=number;
	m_EditPrice=price;

    UpdateData(FALSE);

}




void CDlgTab3::OnEnChangeEditEndtime()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
