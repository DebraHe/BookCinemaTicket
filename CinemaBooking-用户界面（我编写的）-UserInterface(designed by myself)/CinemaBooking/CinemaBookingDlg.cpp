
// CinemaBookingDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CinemaBooking.h"
#include "CinemaBookingDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCinemaBookingDlg �Ի���



CCinemaBookingDlg::CCinemaBookingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCinemaBookingDlg::IDD, pParent)
	, m_StaticID(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_DlgShowing = NULL;
	m_DlgWillShow = NULL;
}

void CCinemaBookingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Showing, m_btn1);
	DDX_Control(pDX, IDC_WillShow, m_btn2);
	DDX_Control(pDX, IDC_MyOrder, m_btn3);
	DDX_Control(pDX, IDC_OutLogin, m_btn4);

	DDX_Text(pDX, IDC_STATIC_ID, m_StaticID);
}

BEGIN_MESSAGE_MAP(CCinemaBookingDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_Showing, &CCinemaBookingDlg::OnBnClickedShowing)
	ON_BN_CLICKED(IDC_WillShow, &CCinemaBookingDlg::OnBnClickedWillshow)
	ON_BN_CLICKED(IDC_MyOrder, &CCinemaBookingDlg::OnBnClickedMyorder)
	ON_BN_CLICKED(IDC_OutLogin, &CCinemaBookingDlg::OnBnClickedOutlogin)
END_MESSAGE_MAP()


// CCinemaBookingDlg ��Ϣ�������

BOOL CCinemaBookingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	
	//�Ƚ����û���¼ע�����
	CDlgUserLogin m_DlgUserLogin;
	m_DlgUserLogin.DoModal();
	
	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	//��ֵ����ǰ�û�
	//CDlgUserLogin m_DlgUserLogin;
	ID=m_DlgUserLogin.m_ID;
	GetDlgItem(IDC_STATIC_ID)->SetWindowText(ID);

	//�����Ӵ���
	CStatic *pFrame = (CStatic *)GetDlgItem(IDC_MAIN_FRAME);
	RECT rect;
	pFrame->GetClientRect(&rect);
	rect.left += 2;
	rect.top += 2;
	rect.right -= 2;
	rect.bottom -= 2;

	m_DlgShowing = new CDlgShowing;
	//�����˻���
	m_DlgShowing->Id = ID;

	m_DlgShowing->Create(IDD_Showing, pFrame);
	m_DlgShowing->MoveWindow(&rect);
	m_DlgShowing->ShowWindow(SW_SHOW);

	m_DlgWillShow = new CDlgWillShow;
	m_DlgWillShow->Create(IDD_WillShow, pFrame);
	m_DlgWillShow->MoveWindow(&rect);
	m_DlgWillShow->ShowWindow(SW_HIDE);
	//�����Ӵ������

	//͸����ť
	m_btn1.Load(IDB_PNG1, 244);
	m_btn2.Load(IDB_PNG1, 244);
	m_btn3.Load(IDB_PNG1, 244);
	m_btn4.Load(IDB_PNG1, 244);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CCinemaBookingDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCinemaBookingDlg::OnPaint()
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
HCURSOR CCinemaBookingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCinemaBookingDlg::OnBnClickedShowing()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_DlgShowing->ShowWindow(SW_SHOW);
	m_DlgWillShow->ShowWindow(SW_HIDE);
}


void CCinemaBookingDlg::OnBnClickedWillshow()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_DlgWillShow->ShowWindow(SW_SHOW);
	m_DlgShowing->ShowWindow(SW_HIDE);
}


void CCinemaBookingDlg::OnBnClickedMyorder()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDlgMyOrder m_DlgMyOrder;
	//�����˻���
	m_DlgMyOrder.orderID = ID;
	m_DlgMyOrder.DoModal();
	
}

void CCinemaBookingDlg::OnBnClickedOutlogin()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	//�����˳���

	//�õ���ǰ�����·��
	TCHAR strPath[MAX_PATH];
	GetModuleFileName(NULL, strPath, 100);

	//�����ػ����̣��������½��̳ɹ�����WM_QUIT��Ϣ����ԭ���Ľ��̣�
	STARTUPINFO startInfo;
	PROCESS_INFORMATION processInfo;
	ZeroMemory(&startInfo, sizeof(STARTUPINFO));
	startInfo.cb = sizeof(STARTUPINFO);
	if (CreateProcess(NULL, (LPTSTR)(LPCTSTR)strPath, NULL, NULL, FALSE, 0, NULL, NULL, &startInfo, &processInfo))
	{
		CloseHandle(processInfo.hProcess);
		CloseHandle(processInfo.hThread);
		PostQuitMessage(WM_CLOSE);
	}

}
