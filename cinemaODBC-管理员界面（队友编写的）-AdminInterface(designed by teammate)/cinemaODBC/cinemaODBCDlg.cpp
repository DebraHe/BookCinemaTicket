
// cinemaODBCDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "cinemaODBC.h"
#include "cinemaODBCDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CcinemaODBCDlg �Ի���




CcinemaODBCDlg::CcinemaODBCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CcinemaODBCDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CcinemaODBCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_CONTROL, m_tab);
}

BEGIN_MESSAGE_MAP(CcinemaODBCDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_CONTROL, &CcinemaODBCDlg::OnSelchangeTabUser)
END_MESSAGE_MAP()


// CcinemaODBCDlg ��Ϣ�������

BOOL CcinemaODBCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������


	CRect tabRect;

	m_tab.InsertItem(0, _T("��Ӱ"));//�����һ����ǩ
	m_tab.InsertItem(1, _T("ӰԺ"));//����ڶ�����ǩ
	m_tab.InsertItem(2, _T("��Ƭ"));//����ڶ�����ǩ
	m_tab.InsertItem(3, _T("����"));//����ڶ�����ǩ
	m_tab.InsertItem(4, _T("�˻�"));//����ڶ�����ǩ

	m_tab1.Create(IDD_DLGTAB_FILM, &m_tab);//������һ����ǩҳ
	m_tab2.Create(IDD_DLGTAB_CINEMA, &m_tab);//������һ����ǩҳ
	m_tab3.Create(IDD_DLGTAB_SCHEDULE, &m_tab);//������һ����ǩҳ
	m_tab4.Create(IDD_DLGTAB_ORDERS, &m_tab);//������һ����ǩҳ
	m_tab5.Create(IDD_DLGTAB_ACCOUNT, &m_tab);//������һ����ǩҳ

	m_tab.GetClientRect(&tabRect);//��ȡ��ǩ�ؼ�������

	//����tabRect��ֵ�������ĸ��Ƿ�Χ�ʺ������ǩҳ
	tabRect.left += 1;
	tabRect.right -= 1;
	tabRect.top += 25;
	tabRect.bottom -= 1;

	//���ݵ����õ�tabRect������m_tab1��m_tab2��2����ǩҳ�����ѵ�һ����ǩҳ����Ϊ��ʾ���ɵڶ�������Ϊ����
	m_tab1.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
	m_tab2.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	m_tab3.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	m_tab4.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	m_tab5.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CcinemaODBCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CcinemaODBCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CcinemaODBCDlg::OnSelchangeTabUser(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	CRect tabRect;

	m_tab.GetClientRect(&tabRect);//��ȡ��ǩ�ؼ�������

	//����tabRect��ֵ�������ĸ��Ƿ�Χ�ʺ������ǩҳ
	tabRect.left += 1;
	tabRect.right -= 1;
	tabRect.top += 25;
	tabRect.bottom -= 1;

	switch(m_tab.GetCurSel())
	{
		//��ʾ��һҳ�����صڶ�ҳ
	case 0:
		m_tab1.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		m_tab2.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		m_tab3.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		m_tab4.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		m_tab5.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		
		break;

	case 1:
		m_tab1.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		m_tab2.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		m_tab3.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		m_tab4.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		m_tab5.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		break;

    case 2:
		m_tab1.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		m_tab2.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		m_tab3.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		m_tab4.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		m_tab5.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		//ShellExecute(NULL,_T("open"),_T("d:\\1.txt "),NULL,NULL,SW_SHOWNORMAL);

		break;
    case 3:
		m_tab1.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		m_tab2.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		m_tab3.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		m_tab4.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		m_tab5.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);

		break;
    case 4:
		m_tab1.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		m_tab2.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		m_tab3.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		m_tab4.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		m_tab5.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);

		break;
	default :
		break;
	}

}

void CcinemaODBCDlg::OnBnClickedButtonAddfilm()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CcinemaODBCDlg::OnBnClickedButtonAddcinema()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CcinemaODBCDlg::OnBnClickedButtonAddschedule()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
