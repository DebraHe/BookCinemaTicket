// DlgTab4.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "cinemaODBC.h"
#include "DlgTab4.h"
#include "afxdialogex.h"


// CDlgTab4 �Ի���

IMPLEMENT_DYNAMIC(CDlgTab4, CDialogEx)

CDlgTab4::CDlgTab4(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgTab4::IDD, pParent)
{

}

CDlgTab4::~CDlgTab4()
{
}

void CDlgTab4::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ORDERS, m_ListOrders);
}


BEGIN_MESSAGE_MAP(CDlgTab4, CDialogEx)
END_MESSAGE_MAP()


// CDlgTab4 ��Ϣ�������


BOOL CDlgTab4::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	CRect rc;
	m_ListOrders.GetWindowRect(&rc);

	m_ListOrders.InsertColumn(0,_T("������"),LVCFMT_CENTER,rc.Size().cx/4,0);
	m_ListOrders.InsertColumn(1,_T("��Ӱ��"),LVCFMT_CENTER,rc.Size().cx/4,1);
	m_ListOrders.InsertColumn(2,_T("ӰԺ��"),LVCFMT_CENTER,rc.Size().cx/4,2);
	m_ListOrders.InsertColumn(3,_T("�˻���"),LVCFMT_CENTER,rc.Size().cx/4,3);
	m_ListOrders.InsertColumn(4,_T("��ʼʱ��"),LVCFMT_CENTER,rc.Size().cx/4,3);
	m_ListOrders.InsertColumn(5,_T("����"),LVCFMT_CENTER,rc.Size().cx/4,3);
	m_ListOrders.InsertColumn(6,_T("��λ��"),LVCFMT_CENTER,rc.Size().cx/4,3);
	m_ListOrders.InsertColumn(7,_T("�۸�"),LVCFMT_CENTER,rc.Size().cx/4,3);
	m_ListOrders.InsertColumn(8,_T("��ַ"),LVCFMT_CENTER,rc.Size().cx/4,3);
	

	m_ListOrders.SetExtendedStyle(m_ListOrders.GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT
		|LVS_EX_HEADERDRAGDROP|LVS_EX_TWOCLICKACTIVATE|LVS_EX_FLATSB);

	
	//�����ݿ�film������ݲ��ֵ��뵽listcontrol��
	if(!m_db.IsOpen()&& !m_db.OpenEx(_T("DSN=bookingdns;UID=aa;PWD=123"),CDatabase::openReadOnly|CDatabase::noOdbcDialog))
	{
		MessageBox(L"���Ӵ���");
		return TRUE;
	}
	CRecordset m_set(&m_db);

	m_set.Open(CRecordset::forwardOnly,_T("select * from orders_search"),CRecordset::readOnly);
	CDBVariant var;
	m_ListOrders.DeleteAllItems();
	short nFields=m_set.GetODBCFieldCount();
	for(int i=0;!m_set.IsEOF();i++,m_set.MoveNext())
	{
		for(short index=0;index< nFields;index++)
		{
			m_set.GetFieldValue(index,var);
			if(index==0)
				m_ListOrders.InsertItem(i,VariantToCString(&var));
			else
				m_ListOrders.SetItemText(i,index,VariantToCString(&var));

		}
	}
	m_set.Close();
	m_db.Close();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

CString CDlgTab4::VariantToCString(CDBVariant*var)
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