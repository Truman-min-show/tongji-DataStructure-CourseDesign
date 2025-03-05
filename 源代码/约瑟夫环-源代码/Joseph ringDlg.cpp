﻿




#include "stdafx.h"
#include "Joseph ring.h"
#include "Joseph ringDlg.h"
#include "afxdialogex.h"
#include <cmath>
#include <string>
#include <fstream>
#include<ctime>
using namespace std;


using namespace std;
const double PI = acos(-1.0);
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);   

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CJosephringDlg 对话框



CJosephringDlg::CJosephringDlg(CWnd* pParent )
	: CDialogEx(IDD_JOSEPHRING_DIALOG, pParent)
	, m_people_all(10)
	, m_people_start(1)
	, m_people_peroid(rand()%6+1)
	, interval(750)
	, m_number2(0)
	, m_number(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CJosephringDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_people_all);
	DDX_Text(pDX, IDC_EDIT3, m_people_start);
	DDX_Text(pDX, IDC_EDIT4, interval);
	
	DDX_Control(pDX, IDC_LIST3, m_code);
	DDX_Control(pDX, IDC_LIST2, m_result);
	DDX_Control(pDX, IDC_PICTURE, m_picture);
	DDX_Control(pDX, IDC_PROGRESS1, m_progress);
}

BEGIN_MESSAGE_MAP(CJosephringDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CJosephringDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CJosephringDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &CJosephringDlg::OnBnClickedButton2)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CJosephringDlg 消息处理程序

BOOL CJosephringDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	
	SetIcon(m_hIcon, TRUE);			
	SetIcon(m_hIcon, FALSE);		


	GotoDlgCtrl(GetDlgItem(IDC_EDIT2));

	CRect rect;
	m_result.GetClientRect(rect);
	m_result.InsertColumn(0, _T("输出"), LVCFMT_CENTER, rect.Width());
	m_result.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	m_code.InsertColumn(0, _T("代码"), LVCFMT_CENTER, rect.Width());
	m_code.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	/*int pos = 0;
	CString cstr("void Joseph(int n, int m, int k)");
	m_code.InsertItem(pos++, cstr);*/
	

	ifstream file("code.txt");
	string str;
	int pos = 0;
	while (getline(file, str))
	{
		CString cstr(str.c_str());
		m_code.InsertItem(pos++, cstr);
	}
	m_progress.SetRange(0, 100);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CJosephringDlg::OnSysCommand(UINT nID, LPARAM lParam)
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



void CJosephringDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);

		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;


		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDC *pDC = m_picture.GetDC();
		CRect rect;
		m_picture.GetClientRect(rect);
		pDC->FillRect(rect, &CBrush(RGB(0, 255, 255)));
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CJosephringDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CJosephringDlg::OnBnClickedButton1()
{
	
	UpdateData(TRUE);
	CDC *pDC = m_picture.GetDC();
	CRect rect;
	m_picture.GetClientRect(rect);
	for (int i = 1; i<=m_people_all; ++i)
		died_num[i] = 0;
	pDC->FillRect(&rect, &CBrush(RGB(0, 250, 250)));
	if (!Invalid())
	{
		OnBnClickedButton3();
		MessageBox(_T("不合法的约瑟夫环或刷新时间"));
		return;
	}
	Build_Josephus_ring();
	MessageBox(_T("约瑟夫环构建成功"));
	for (int i = 1; i <= m_people_all; ++i)
		died_num[i] = 0;
	UpdateData(FALSE);
}

bool CJosephringDlg::Invalid()
{
	
	bool flag = true;
	flag &= m_people_all >= 2 && m_people_all <= 100;
	flag &= m_people_start >= 1 && m_people_start <= m_people_all;
	flag &= interval >= 50&&interval<=1500;
	return flag;
}

void CJosephringDlg::Build_Josephus_ring()
{
	
	Init_Josephus_ring();
	Create_Josephus_ring();
}

void CJosephringDlg::Joseph_ring_code_selectiom(int x)
{
	
	m_code.SetItemState(m_code.GetSelectionMark(), 0, LVIS_SELECTED);
	m_code.SetFocus();
	int colume = 2;
	if (colume == 3)colume = 0;
	m_code.SetItemState(x, LVIS_SELECTED, LVIS_SELECTED);
}
void CJosephringDlg::Init_Josephus_ring()
{
	
	for (int i = 1; i <= m_people_all; ++i)
		died[i] = 0;
}

void CJosephringDlg::Create_Josephus_ring()
{
	
	CDC *pDC = m_picture.GetDC();
	CRect rect;
	m_picture.GetClientRect(rect);
	CBrush brush1(RGB(255, 255, 0));
	pDC->SelectObject(brush1);
	pDC->Ellipse(rect);

	double angle = 360.0 / m_people_all;
	double l = 90 + angle / 2.0;
	double r = 90 - angle / 2.0;
	double mid;
	for (int i = 1; i <= m_people_all; ++i)
	{
		mid = (l + r) / 2.0;
		//double xxx = 450 + 435 * cos(mid * PI / 180);
	    //double yyy = 460 - 435 * sin(mid * PI / 180);
		double xxx = rect.Width() / 2 * 0.98 + (rect.Width() / 2 * 0.93) * cos(mid * PI / 180);
		double yyy = rect.Height() / 2 * 0.98 - (rect.Height() / 2 * 0.93) * sin(mid * PI / 180);
		Draw_Joseph_ring(xxx,  yyy, died[i]);
		l = r;
		r -= angle;
	}
}

void CJosephringDlg::Renew_Josephus_ring()
{
	double angle = 360.0 / m_people_all;
	int i=m_cur_pos;
	double mid = 90 - (i - 1) * angle;
	//double xxx = 450 + 435 * cos(mid * PI / 180);
	//double yyy = 460 - 435 * sin(mid * PI / 180);
	CRect rect;
	m_picture.GetClientRect(rect);
	double xxx = rect.Width() / 2*0.98 + (rect.Width() / 2 *0.93) * cos(mid * PI / 180);
	double yyy = rect.Height() / 2 * 0.98 - (rect.Height() / 2 * 0.93) * sin(mid * PI / 180);
	Draw_Joseph_ring(xxx, yyy, died[i]);

	while (1) {
		if (i == 1)
			i = m_people_all;
		else
			i--;
		if (died[i] != 2)
			break;
	}
	mid = 90 - (i - 1) * angle;
	xxx = rect.Width() / 2 * 0.98 + (rect.Width() / 2 * 0.93) * cos(mid * PI / 180);
	yyy = rect.Height() / 2 * 0.98 - (rect.Height() / 2 * 0.93) * sin(mid * PI / 180);
	Draw_Joseph_ring(xxx, yyy, died[i]);
}

void CJosephringDlg::Draw_Joseph_ring(double x, double y, int state)
{
	
	CDC *pDC = m_picture.GetDC();
	CRect rect, rect_background;
	m_picture.GetClientRect(rect_background);
	rect = new CRect((int)x, (int)y, (int)x + rect_background.Width() / 45, (int)y + rect_background.Height() / 45);
	CPen pen(PS_DASH, 2, RGB(255, 0, 0));
	CBrush brush;
	switch (state)
	{
	case 0:
		brush.CreateSolidBrush(RGB(0, 255, 0));
		break;
	case 1:
		brush.CreateSolidBrush(RGB(0, 255, 0));
		break;
	case 2:
		brush.CreateSolidBrush(RGB(255, 0, 0));
		break;
	case 3:
		brush.CreateSolidBrush(RGB(255, 0, 0));
		break;
	}
	pDC->SelectObject(brush);
	if (state & 1)
		pDC->SelectObject(pen);
	pDC->Ellipse(rect);
}

void CJosephringDlg::OnTimer(UINT_PTR nIDEvent)
{
	
	UpdateData(TRUE);
	if (nIDEvent == 0)
	{
		Joseph_ring_code_selectiom(6);
		bool finded = 0;
		while (!finded)
		{
			--m_cnt;
			--m_period;
			if (died[m_cur_pos] == 2)
			{
				++m_cnt;
				++m_period;
			}
			else
			{
				finded = 1;
				//m_number = m_people_peroid - m_period;
				//m_number2 = m_cur_pos;
				if (m_period == 0)
				{
					++m_death;
					CString str, tmp;
					str = "(";
					tmp.Format(_T("%d"), m_death);
					str += tmp;
					str += ")骰子摇出";
					tmp.Format(_T("%d"), m_people_peroid);
					str += tmp;
					str += "，淘汰";
					tmp.Format(_T("%d"), m_cur_pos);
					str += tmp;
					str += "号玩家";
					
					m_result.InsertItem(m_death - 1, str);

					died[m_cur_pos] = 2;
					m_people_peroid = rand()%6+ 1;
					m_period = m_people_peroid;
					Joseph_ring_code_selectiom(13);
					m_progress.SetPos(100.0 * m_death / (m_people_all - 1));

					died_num[m_cur_pos] = m_death;
				}
				++died[m_cur_pos];
				if ( m_death == 24 && died[m_cur_pos] == 1 || m_death==25 &&died[m_cur_pos] == 3||m_death == 23 && died[m_cur_pos] == 1 )
					Create_Josephus_ring();
				else
					Renew_Josephus_ring();
				--died[m_cur_pos];
			}
			m_cur_pos = m_cur_pos % m_people_all + 1;
		}
		if (m_death == m_people_all - 1)
		{
			KillTimer(0);
			CString str, tmp;
			str = "胜者是：";
			int survivor;
			for (int i = 1; i <= m_people_all; ++i)
			{
				if (died[i] == 0)
					survivor = i;
			}
			tmp.Format(_T("%d"), survivor);
			str += tmp;
			str += "号玩家";
			m_result.InsertItem(m_death, str);
			MessageBox(_T("已经找到了胜者！"));
			Joseph_ring_code_selectiom(20);
		}
	}
	UpdateData(FALSE);
	CDialogEx::OnTimer(nIDEvent);
}

void CJosephringDlg::OnBnClickedButton3()
{
	
	UpdateData(TRUE);
	KillTimer(0);
	m_people_all = 10;
	m_people_start = 1;
	m_people_peroid = rand()%6+1;
	interval = 750;
	m_number = 0;
	m_number2 = 0;
	m_progress.SetPos(0);
	m_result.DeleteAllItems();
	for (int i = 1; i <= m_people_all; ++i)
		died_num[i] = 0;
	CDC *pDC = m_picture.GetDC();
	CRect rect;
	m_picture.GetClientRect(rect);
	pDC->FillRect(rect, &CBrush(RGB(255, 255, 0)));
	GotoDlgCtrl(GetDlgItem(IDC_PICTURE));
	UpdateData(FALSE);
}


void CJosephringDlg::OnBnClickedButton2()
{
	
	int cnt = 0;
	srand(time(NULL));
	for (int i = 1; i <= m_people_all; ++i)
	{
		if (died[i] == 0)
			++cnt;
		died_num[i] = 0;
	}
	if (cnt != m_people_all || !Invalid())
	{
		MessageBox(_T("请先输入游戏数据"));
		return;
	}
	//m_cnt = (m_people_all - 1) * m_people_peroid;
	m_people_peroid = rand() % 6 + 1;
	m_cur_pos = m_people_start;
	m_period = m_people_peroid;
	
	Joseph_ring_code_selectiom(3);
	m_death = 0;
	m_result.DeleteAllItems();
	m_number = 0;
	m_number2 = 0;
	SetTimer(0, interval, NULL);
}



