// DlgMyOrder.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CinemaBooking.h"
#include "DlgMyOrder.h"
#include "afxdialogex.h"


// CDlgMyOrder �Ի���

IMPLEMENT_DYNAMIC(CDlgMyOrder, CDialogEx)

CDlgMyOrder::CDlgMyOrder(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgMyOrder::IDD, pParent)
{

}

CDlgMyOrder::~CDlgMyOrder()
{
}
CString CDlgMyOrder::VariantToCString(CDBVariant*var)
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
void CDlgMyOrder::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OrderInfo, m_ListOrderInfo);


	CRect rc;
	m_ListOrderInfo.GetWindowRect(&rc);
	m_ListOrderInfo.InsertColumn(0, _T("������"), LVCFMT_CENTER, rc.Size().cx / 8, 0);
	m_ListOrderInfo.InsertColumn(1, _T("��Ӱ��"), LVCFMT_CENTER, rc.Size().cx / 4, 1);
	m_ListOrderInfo.InsertColumn(2, _T("ӰԺ��"), LVCFMT_CENTER, rc.Size().cx / 4, 2);
	m_ListOrderInfo.InsertColumn(3, _T("��ʼʱ��"), LVCFMT_CENTER, rc.Size().cx / 4, 3);
	m_ListOrderInfo.InsertColumn(4, _T("��λ��"), LVCFMT_CENTER, rc.Size().cx / 8, 4);
	m_ListOrderInfo.InsertColumn(5, _T("Ʊ��"), LVCFMT_CENTER, rc.Size().cx / 8, 5);
	m_ListOrderInfo.InsertColumn(6, _T("ӰԺ��ַ"), LVCFMT_CENTER, rc.Size().cx / 2, 6);

	m_ListOrderInfo.SetExtendedStyle(m_ListOrderInfo.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT
		| LVS_EX_HEADERDRAGDROP | LVS_EX_TWOCLICKACTIVATE | LVS_EX_FLATSB);

	
	//�����ݿ�film������ݲ��ֵ��뵽listcontrol��
	if (!m_db.IsOpen() && !m_db.OpenEx(_T("DSN=bookingdns;UID=aa;PWD=123"),
		CDatabase::openReadOnly | CDatabase::noOdbcDialog))
	{
		MessageBox(L"���Ӵ���");
		return;
	}
	CRecordset m_set(&m_db);
	CString sql;
	sql.Format(_T("select oid,fname,tname,starttime,seatnum,price,address from Film, Orders, Schedule, Theatre where Orders.id = '%s' and Schedule.sid = Orders.sid and Film.fid = Schedule.fid and Theatre.tid = Schedule.tid"), orderID);
	m_set.Open(CRecordset::forwardOnly, sql, CRecordset::readOnly);
	CDBVariant var;
	m_ListOrderInfo.DeleteAllItems();
	short nFields = m_set.GetODBCFieldCount();
	for (int i = 0; !m_set.IsEOF(); i++, m_set.MoveNext())
	{
		for (short index = 0; index < nFields; index++)
		{
			m_set.GetFieldValue(index, var);
			if (index == 0)
				m_ListOrderInfo.InsertItem(i, VariantToCString(&var));
			else
				m_ListOrderInfo.SetItemText(i, index, VariantToCString(&var));
		}
	}
	m_set.Close();
	m_db.Close();
	
}


BEGIN_MESSAGE_MAP(CDlgMyOrder, CDialogEx)
	ON_BN_CLICKED(IDC_OUT, &CDlgMyOrder::OnBnClickedOut)
END_MESSAGE_MAP()


// CDlgMyOrder ��Ϣ�������


void CDlgMyOrder::OnBnClickedOut()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}
