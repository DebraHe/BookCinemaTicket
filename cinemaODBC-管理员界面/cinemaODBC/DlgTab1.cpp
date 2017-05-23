// DlgTab1.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "cinemaODBC.h"
#include "DlgTab1.h"
#include "afxdialogex.h"


// CDlgTab1 �Ի���

IMPLEMENT_DYNAMIC(CDlgTab1, CDialogEx)

CDlgTab1::CDlgTab1(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgTab1::IDD, pParent)
{

	m_EditFid = _T("");
	m_EditFname = _T("");
	m_EditDirector = _T("");
	m_EditProtagonist = _T("");
	m_EditType = _T("");
	m_EditReleasetime = _T("");
	m_EditDuration = _T("");
	m_EditNation = _T("");
	m_EditIntro = _T("");
	m_EditLanguage = _T("");
}

CDlgTab1::~CDlgTab1()
{
}

void CDlgTab1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_FILM, m_ListFilm);



	DDX_Text(pDX, IDC_EDIT_FID, m_EditFid);
	DDV_MaxChars(pDX, m_EditFid, 50);
	DDX_Text(pDX, IDC_EDIT_FNAME, m_EditFname);
	DDV_MaxChars(pDX, m_EditFname, 50);
	DDX_Text(pDX, IDC_EDIT_DIRECTOR, m_EditDirector);
	DDV_MaxChars(pDX, m_EditDirector, 50);
	DDX_Text(pDX, IDC_EDIT_PROTAGONIST, m_EditProtagonist);
	DDV_MaxChars(pDX, m_EditProtagonist, 50);
	DDX_Text(pDX, IDC_EDIT_TYPE, m_EditType);
	DDV_MaxChars(pDX, m_EditType, 50);
	DDX_Text(pDX, IDC_EDIT_RELEASETIME, m_EditReleasetime);
	DDV_MaxChars(pDX, m_EditReleasetime, 50);
	DDX_Text(pDX, IDC_EDIT_DURATION, m_EditDuration);
	DDV_MaxChars(pDX, m_EditDuration, 50);
	DDX_Text(pDX, IDC_EDIT_NATION, m_EditNation);
	DDV_MaxChars(pDX, m_EditNation, 50);
	DDX_Text(pDX, IDC_EDIT_INTRO, m_EditIntro);
	DDV_MaxChars(pDX, m_EditIntro, 200);
	DDX_Text(pDX, IDC_EDIT_LANGUAGE, m_EditLanguage);
	DDV_MaxChars(pDX, m_EditLanguage, 50);
}

BEGIN_MESSAGE_MAP(CDlgTab1, CDialogEx)
	
	ON_BN_CLICKED(IDC_BUTTON_SAVEFILM, &CDlgTab1::OnBnClickedButtonSavefilm)
	ON_BN_CLICKED(IDC_BUTTON_DELEFILM, &CDlgTab1::OnBnClickedButtonDelefilm)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_FILM, &CDlgTab1::OnNMDblclkListFilm)
	ON_BN_CLICKED(IDC_BUTTON_ALTERFILM, &CDlgTab1::OnBnClickedButtonAlterfilm)
	ON_WM_TIMER()
END_MESSAGE_MAP()


BOOL CDlgTab1::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect rc;
	m_ListFilm.GetWindowRect(&rc);

	m_ListFilm.InsertColumn(0,_T("��Ӱ���"),LVCFMT_CENTER,rc.Size().cx/4,0);
	m_ListFilm.InsertColumn(1,_T("��Ӱ��"),LVCFMT_CENTER,rc.Size().cx/4,1);
	m_ListFilm.InsertColumn(2,_T("��ӳʱ��"),LVCFMT_CENTER,rc.Size().cx/4,2);
	m_ListFilm.InsertColumn(3,_T("����"),LVCFMT_CENTER,rc.Size().cx/4,3);
	m_ListFilm.InsertColumn(4,_T("����"),LVCFMT_CENTER,rc.Size().cx/4,4);
	m_ListFilm.InsertColumn(5,_T("����"),LVCFMT_CENTER,rc.Size().cx/4,5);
	m_ListFilm.InsertColumn(6,_T("����"),LVCFMT_CENTER,rc.Size().cx/4,6);
	m_ListFilm.InsertColumn(7,_T("ʱ��"),LVCFMT_CENTER,rc.Size().cx/4,7);
	m_ListFilm.InsertColumn(8,_T("���"),LVCFMT_CENTER,rc.Size().cx/4,8);
	m_ListFilm.InsertColumn(9,_T("����"),LVCFMT_CENTER,rc.Size().cx/4,9);


	m_ListFilm.SetExtendedStyle(m_ListFilm.GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT
		|LVS_EX_HEADERDRAGDROP|LVS_EX_TWOCLICKACTIVATE|LVS_EX_FLATSB);

	
	//�����ݿ�film������ݲ��ֵ��뵽listcontrol��
	UpdateData(TRUE);
	if(!m_db.IsOpen()&& !m_db.OpenEx(_T("DSN=bookingdns;UID=aa;PWD=123"),CDatabase::openReadOnly|CDatabase::noOdbcDialog))
	{
		MessageBox(L"���Ӵ���");
		return TRUE;
	}
	CRecordset m_set(&m_db);

	m_set.Open(CRecordset::forwardOnly,_T("select * from Film"),CRecordset::readOnly);
	CDBVariant var;
	m_ListFilm.DeleteAllItems();
	short nFields=m_set.GetODBCFieldCount();
	for(int i=0;!m_set.IsEOF();i++,m_set.MoveNext())
	{
		for(short index=0;index< nFields;index++)
		{
			m_set.GetFieldValue(index,var);
			if(index==0)
				m_ListFilm.InsertItem(i,VariantToCString(&var));
			else
				m_ListFilm.SetItemText(i,index,VariantToCString(&var));

		}
	}
	m_set.Close();
	m_db.Close();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

CString CDlgTab1::VariantToCString(CDBVariant*var)
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



// CDlgTab1 ��Ϣ�������


void CDlgTab1::OnBnClickedButtonOpen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	
}

//�����ݿ�����µ���Ϣ
void CDlgTab1::OnBnClickedButtonSavefilm()
{
	UpdateData(TRUE);
	//�ж�editcontrol��õ���Ϣ��д�Ƿ�����
	if( m_EditFid.IsEmpty()||m_EditFname.IsEmpty()||m_EditDirector.IsEmpty()||m_EditProtagonist.IsEmpty()||m_EditType.IsEmpty()
		||m_EditReleasetime.IsEmpty()||m_EditDuration.IsEmpty()||m_EditNation.IsEmpty()||m_EditIntro.IsEmpty()||m_EditLanguage.IsEmpty())
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
			sql.Format(_T("insert into Film(fid,fname,releasetime,nation,director,protagonist,type,duration,intro,language) values('%s','%s','%s','%s','%s','%s','%s','%s','%s','%s')"),
				       m_EditFid, m_EditFname, m_EditReleasetime, m_EditNation,m_EditDirector,m_EditProtagonist,m_EditType,m_EditDuration,m_EditIntro,m_EditLanguage);//ִ�в���һ�е�TSQL
			m_db.ExecuteSQL(LPCTSTR(sql));
		}
		catch (CDBException *pe)
		{
			//pe->ReportError();
			MessageBox(_T("�õ�Ӱ�Ѵ��ڻ��Ӱ��û�а�ָ����ʽ���룬�����"),_T("ע��"),MB_OK);
			pe->Delete();
		}
		m_db.Close();

		//�����ݿ�film����������µ��뵽listcontrol��
	if(!m_db.IsOpen()&& !m_db.OpenEx(_T("DSN=bookingdns;UID=aa;PWD=123"),CDatabase::openReadOnly|CDatabase::noOdbcDialog))
	{
		MessageBox(L"���Ӵ���");
		return;
	}
	CRecordset m_set(&m_db);

	m_set.Open(CRecordset::forwardOnly,_T("select * from Film"),CRecordset::readOnly);
	CDBVariant var;
	m_ListFilm.DeleteAllItems();
	short nFields=m_set.GetODBCFieldCount();
	for(int i=0;!m_set.IsEOF();i++,m_set.MoveNext())
	{
		for(short index=0;index< nFields;index++)
		{
			m_set.GetFieldValue(index,var);
			if(index==0)
				m_ListFilm.InsertItem(i,VariantToCString(&var));
			else
				m_ListFilm.SetItemText(i,index,VariantToCString(&var));

		}
	}
	m_set.Close();
	m_db.Close();
	
	}
	
}

//ɾ��ѡ�е���Ϣ
void CDlgTab1::OnBnClickedButtonDelefilm()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	POSITION pos=m_ListFilm.GetFirstSelectedItemPosition();//��ȡ��ǰѡ���е�λ������
	if(pos==NULL)
	{
		MessageBox(_T("��ѡ��һ����¼��"),_T("ע��"),MB_OK);//�ж��Ƿ�ѡ��������һ��
	}
	else
	{
		while(pos)
		{
			int index_item=m_ListFilm.GetNextSelectedItem(pos);
			TRACE(_T("item%d was selected!\n"),index_item);
			CString Bno=m_ListFilm.GetItemText(index_item,0);//��ȡѡ���еĵ�һ�е�����
			//�����ݿ�ɾ�����ݿ��ж�Ӧ�ĸ���
			if(!m_db.IsOpen()&&!m_db.OpenEx(_T("DSN=bookingdns;UID=aa;PWD=123"),CDatabase::openReadOnly|CDatabase::noOdbcDialog))
			{
				MessageBox(L"���Ӵ���");
				return;
			}
			try
			{
				CString del;
				del.Format(_T("delete from Film where fid='%s'"),Bno);//ִ��ɾ��������TSQL
				m_db.ExecuteSQL(del);
			}
			catch(CDBException*pe)
			{
				pe->ReportError();
				pe->Delete();
			}
			m_db.Close();
			m_ListFilm.DeleteItem(index_item);
		}
	}

}

//˫���б��е�һ���Ϣ���뵽editcontrol
void CDlgTab1::OnNMDblclkListFilm(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	//UpdateData(TRUE);

	CString fid,fname,releasetime,nation,director,protagonist,type,duration,intro,language;
	int i = m_ListFilm.GetSelectionMark();//��ȡѡ�е���

	fid=m_ListFilm.GetItemText(i,0);//��ȡѡ���еĸ��в���������
	fname=m_ListFilm.GetItemText(i,1);
	releasetime=m_ListFilm.GetItemText(i,2);
	nation=m_ListFilm.GetItemText(i,3);
	director=m_ListFilm.GetItemText(i,4);
	protagonist=m_ListFilm.GetItemText(i,5);
	type=m_ListFilm.GetItemText(i,6);
	duration=m_ListFilm.GetItemText(i,7);
	intro=m_ListFilm.GetItemText(i,8);
	language=m_ListFilm.GetItemText(i,9);

	m_EditFid=fid;                //������ֵ��������editcontrol
	m_EditFname=fname;
	m_EditReleasetime=releasetime;
	m_EditNation=nation;
	m_EditDirector=director;
	m_EditProtagonist=protagonist;
	m_EditType=type;
	m_EditDuration=duration;
	m_EditIntro=intro;
	m_EditLanguage=language;

	UpdateData(FALSE);
   
}

//���¸��±����޸Ĺ�����Ϣ
void CDlgTab1::OnBnClickedButtonAlterfilm()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	//���жϴ���Ĳ����Ƿ�Ϊ��
	if( m_EditFid.IsEmpty()||m_EditFname.IsEmpty()||m_EditDirector.IsEmpty()||m_EditProtagonist.IsEmpty()||m_EditType.IsEmpty()
		||m_EditReleasetime.IsEmpty()||m_EditDuration.IsEmpty()||m_EditNation.IsEmpty()||m_EditIntro.IsEmpty()||m_EditLanguage.IsEmpty())
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
			sql.Format(_T("update Film set fname='%s', releasetime='%s', nation='%s',director='%s', protagonist='%s', type='%s', duration='%s',intro='%s',language='%s'where fid='%s'"),
				       m_EditFname, m_EditReleasetime, m_EditNation,m_EditDirector,m_EditProtagonist,m_EditType,m_EditDuration,m_EditIntro,m_EditLanguage, m_EditFid);//ִ�и��µ�TSQL���
			m_db.ExecuteSQL(LPCTSTR(sql));
		}
		catch (CDBException *pe)
		{
			//pe->ReportError();
			MessageBox(_T("�õ�Ӱ�Ѵ��ڻ��Ӱ��û�а�ָ����ʽ�������"),_T("ע��"),MB_OK);
			pe->Delete();
		}
		m_db.Close();

	//�����ݿ�film������ݷ����µ��뵽listcontrol��
	if(!m_db.IsOpen()&& !m_db.OpenEx(_T("DSN=bookingdns;UID=aa;PWD=123"),CDatabase::openReadOnly|CDatabase::noOdbcDialog))
	{
		MessageBox(L"���Ӵ���");
		return;
	}
	CRecordset m_set(&m_db);

	m_set.Open(CRecordset::forwardOnly,_T("select * from Film"),CRecordset::readOnly);
	CDBVariant var;
	m_ListFilm.DeleteAllItems();
	short nFields=m_set.GetODBCFieldCount();
	for(int i=0;!m_set.IsEOF();i++,m_set.MoveNext())
	{
		for(short index=0;index< nFields;index++)
		{
			m_set.GetFieldValue(index,var);
			if(index==0)
				m_ListFilm.InsertItem(i,VariantToCString(&var));
			else
				m_ListFilm.SetItemText(i,index,VariantToCString(&var));

		}
	}
	m_set.Close();
	m_db.Close();
	
	}
	
}

