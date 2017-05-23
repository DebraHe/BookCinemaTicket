#pragma once
#include "afxdb.h"  //�������ݿ�
#include "colorbutton.h"
#include "afxwin.h"

// CDlgBookTicket �Ի���

class CDlgBookTicket : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgBookTicket)

public:
	CDlgBookTicket(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgBookTicket();

// �Ի�������
	enum { IDD = IDD_BookTicket };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	//����ӣ����ݿ�
private:
	CDatabase m_db;
public:
	CString fname;
	colorbutton	m_d4;
	colorbutton	m_d3;
	colorbutton	m_d2;
	colorbutton	m_d1;
	colorbutton	m_c4;
	colorbutton	m_c3;
	colorbutton	m_c2;
	colorbutton	m_c1;
	colorbutton	m_b4;
	colorbutton	m_b3;
	colorbutton	m_b2;
	colorbutton	m_b1;
	colorbutton	m_a4;
	colorbutton	m_a3;
	colorbutton	m_a2;
	colorbutton	m_a1;
	afx_msg void OnBnClickedButtona1();
	afx_msg void OnBnClickedButtona2();
	afx_msg void OnBnClickedButtona3();
	afx_msg void OnBnClickedButtona4();
	afx_msg void OnBnClickedButtonb1();
	afx_msg void OnBnClickedButtonb2();
	afx_msg void OnBnClickedButtonb3();
	afx_msg void OnBnClickedButtonb4();
	afx_msg void OnBnClickedButtonc1();
	afx_msg void OnBnClickedButtonc2();
	afx_msg void OnBnClickedButtonc3();
	afx_msg void OnBnClickedButtonc4();
	afx_msg void OnBnClickedButtond1();
	afx_msg void OnBnClickedButtond2();
	afx_msg void OnBnClickedButtond3();
	afx_msg void OnBnClickedButtond4();
	CComboBox m_Theatre;
	CComboBox m_starttime;
	CString id,tname, starttime,sid;
	afx_msg void OnCbnSelchangeComboTheatre();
	afx_msg void OnCbnSelchangeComboStarttime();
	void UpdateSeatnum(); //������λ��ȫ��Ϊ��
	void AddOrders(CString seat);//��������λ
	afx_msg void OnBnClickedOut();
	void SeatTrue();
};
