
// StuManagerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "StuManager.h"
#include "StuManagerDlg.h"
#include "afxdialogex.h"
#include <cstdio>
#include <string>
#include <locale.h>
#include "BiPrioqueue.h"
#include "student.h"
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


BiPrioQueue<stu> *queue ;
int tcount;//从尾部上数第几个
int hcount = 1;//从头上数第几个
// CStuManagerDlg 对话框

CStuManagerDlg::CStuManagerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CStuManagerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CStuManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CStuManagerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CStuManagerDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CStuManagerDlg::OnBnClickedCancel)
	ON_WM_CLOSE()
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_GET_MAX, &CStuManagerDlg::OnBnClickedGetMax)
	ON_BN_CLICKED(IDC_GET_MIN, &CStuManagerDlg::OnBnClickedGetMin)
	ON_BN_CLICKED(IDC_DEL_MAX, &CStuManagerDlg::OnBnClickedDelMax)
	ON_BN_CLICKED(IDC_DEL_MIN, &CStuManagerDlg::OnBnClickedDelMin)
END_MESSAGE_MAP()


//加载文件中的数据
void CStuManagerDlg::init(CString str){
	setlocale(LC_CTYPE, "chs");
	CStdioFile file;
	if (!file.Open(str, CFile::modeRead)){
		return;
	}
	CListCtrl *list = (CListCtrl*)GetDlgItem(IDC_LIST);
	//列表清空,优先队列清空
	list->DeleteAllItems();
	queue = new BiPrioQueue<stu>();

	//读取文件
	CString line;
	int column = 0;
	stu *s;
	while (file.ReadString(line) && line.GetLength() != 0){
		if (line == _T("*|")){
			s = new stu();
			column = 0;
			continue;
		}
		switch (column){
		case 0:
			s->stu_no = line;
			break;
		case 1:
			s->name = line;
			break;
		case 2:
			s->age = line;
			break;
		case 3:
			s->gender = line;
			break;
		case 4:
			s->grade =  _wtoi(line);
			break;
		case 5:
			s->other = line;
			queue->inQueue(*s);
			break;
		}
		column++;
	}

	file.Close();

	hcount = 1;
	tcount = queue->GetCurSize();

	//改变按钮的文字
	CButton* button = (CButton*)GetDlgItem(IDC_FIND);
	str.Format(_T("删除第%d名(最大成绩)"), 1);
	button->SetWindowTextW(str);
	//button->SetWindowTextW(_T("删除最大元素"));
	
	button = (CButton*)GetDlgItem(IDC_FIND_INVERSE);
	str.Format(_T("删除第%d名(最小成绩)"), tcount);
	button->SetWindowTextW(str);
	//button->SetWindowTextW(_T("删除最小元素"));
}

void CStuManagerDlg::setItem(){
	CListCtrl *list = (CListCtrl*)GetDlgItem(IDC_LIST);
	list->DeleteAllItems();
	if (queue->isEmpty()){
		return;
	}
	stu* all = queue->GetAll();
	int row = -1;
	for (int i = 2; i < queue->GetCurSize()+2; i++)
	{
		list->InsertItem(++row, _T(""));
		list->SetItemText(row, 0, all[i].stu_no);
		list->SetItemText(row, 1, all[i].name);
		list->SetItemText(row, 2, all[i].age);
		list->SetItemText(row, 3, all[i].gender);
		CString str;
		str.Format(_T("%d"), all[i].grade);
		list->SetItemText(row, 4, str);
		list->SetItemText(row, 5, all[i].other);
	}
}

BOOL CStuManagerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	//center
	int cx = GetSystemMetrics(SM_CXFULLSCREEN);
	int cy = GetSystemMetrics(SM_CYFULLSCREEN);

	LPRECT rect = new RECT();
	GetWindowRect(rect);

	int width = rect->right - rect->left;
	int height = rect->bottom - rect->top;

	MoveWindow((cx - width) / 2, (cy - height) / 2, width, height);


	// add title
	CListCtrl *list = (CListCtrl*)GetDlgItem(IDC_LIST);

	list->InsertColumn(0, _T("学号"), 0, 100);
	list->InsertColumn(1, _T("姓名"), 0, 100);
	list->InsertColumn(2, _T("年龄"), 0, 50);
	list->InsertColumn(3, _T("性别"), 0, 50);
	list->InsertColumn(4, _T("成绩"), 0, 50);
	list->InsertColumn(5, _T("其他"), 0,200);
	//添加附加的样式
	list->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	//读取文件中原有的数据
	init();
	setItem();
	


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CStuManagerDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CStuManagerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CStuManagerDlg::OnBnClickedOk()
{
	
}


void CStuManagerDlg::OnBnClickedCancel()
{
}

//系统关闭对话框
void CStuManagerDlg::OnClose()
{
	EndDialog(IDCANCEL);
}


void CStuManagerDlg::OnDropFiles(HDROP hDropInfo)
{
	TCHAR tchar[100];
	DragQueryFile(hDropInfo, 0, tchar, sizeof(tchar));
	CString str;
	for (int i = 0; i < 100; ++i){
		if (tchar[i]==_T('\0')){
			str += tchar[i];
			break;
		}
		str += tchar[i];
	}

	init(str);
	setItem();
}

//取最高成绩
void CStuManagerDlg::OnBnClickedGetMax()
{
	try{
		stu*  s = &(queue->getMax());
		CString str;
		str.Format(_T("最高成绩:\r\n学号:%s;姓名:%s;年龄:%s;性别:%s;成绩:%d;其他:%s"), s->stu_no, s->name, s->age, s->gender, s->grade, s->other);
		AfxMessageBox(str);
	}
	catch (...){
		AfxMessageBox(_T("已查询完毕"));
	}
}

//取最低成绩
void CStuManagerDlg::OnBnClickedGetMin()
{
	try{
		stu*  s = &(queue->getMin());
		CString str;
		str.Format(_T("最低成绩:\r\n学号:%s;姓名:%s;年龄:%s;性别:%s;成绩:%d;其他:%s"), s->stu_no, s->name, s->age, s->gender, s->grade, s->other);
		AfxMessageBox(str);
	}catch (...){
		AfxMessageBox(_T("已查询完毕"));
	}
}

//删除最高成绩
void CStuManagerDlg::OnBnClickedDelMax()
{
	try{
		stu*  s = &(queue->deQueue_max());
		CString str;
		str.Format(_T("第%d名:\r\n学号:%s;姓名:%s;年龄:%s;性别:%s;成绩:%d;其他:%s"), hcount, s->stu_no, s->name, s->age, s->gender, s->grade, s->other);
		AfxMessageBox(str);

		//删掉list中最大一行
		CListCtrl *list = (CListCtrl*)GetDlgItem(IDC_LIST);
		list->DeleteItem(hcount);

		//改变按钮的文字

		++hcount;
		if (hcount > tcount){
			CButton* ifind = (CButton*)GetDlgItem(IDC_FIND_INVERSE);
			ifind->SetWindowTextW(_T("已删除完毕"));
			ifind->EnableWindow(false);

			CButton* button = (CButton*)GetDlgItem(IDC_FIND);
			button->SetWindowTextW(_T("已删除完毕"));
			button->EnableWindow(false);
		}
		else{
			CButton* button = (CButton*)GetDlgItem(IDC_FIND);
			str.Format(_T("删除第%d名"), hcount);
			button->SetWindowTextW(str);
		}
		setItem();
	}
	catch (...){
		AfxMessageBox(_T("已删除完毕"));
	}
}

//删除最低成绩
void CStuManagerDlg::OnBnClickedDelMin()
{
	try{
		stu*  s = &(queue->deQueue_min());
		CString str;
		str.Format(_T("第%d名:\r\n学号:%s;姓名:%s;年龄:%s;性别:%s;成绩:%d;其他:%s"), tcount, s->stu_no, s->name, s->age, s->gender, s->grade, s->other);
		AfxMessageBox(str);


		//删掉list中最大一行
		CListCtrl *list = (CListCtrl*)GetDlgItem(IDC_LIST);
		list->DeleteItem(tcount);


		//改变按钮的文字
		--tcount;

		if (hcount > tcount){
			CButton* ifind = (CButton*)GetDlgItem(IDC_FIND_INVERSE);
			ifind->SetWindowTextW(_T("已删除完毕"));
			ifind->EnableWindow(false);

			CButton* button = (CButton*)GetDlgItem(IDC_FIND);
			button->SetWindowTextW(_T("已删除完毕"));
			button->EnableWindow(false);
		}
		else{
			CButton* button = (CButton*)GetDlgItem(IDC_FIND_INVERSE);
			str.Format(_T("删除第%d名"), tcount);
			button->SetWindowTextW(str);
		}
		setItem();

	}
	catch (...){
		AfxMessageBox(_T("已删除完毕"));
	}
}
