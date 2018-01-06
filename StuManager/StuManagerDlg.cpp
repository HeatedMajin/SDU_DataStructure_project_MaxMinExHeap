
// StuManagerDlg.cpp : ʵ���ļ�
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
int tcount;//��β�������ڼ���
int hcount = 1;//��ͷ�����ڼ���
// CStuManagerDlg �Ի���

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


//�����ļ��е�����
void CStuManagerDlg::init(CString str){
	setlocale(LC_CTYPE, "chs");
	CStdioFile file;
	if (!file.Open(str, CFile::modeRead)){
		return;
	}
	CListCtrl *list = (CListCtrl*)GetDlgItem(IDC_LIST);
	//�б����,���ȶ������
	list->DeleteAllItems();
	queue = new BiPrioQueue<stu>();

	//��ȡ�ļ�
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

	//�ı䰴ť������
	CButton* button = (CButton*)GetDlgItem(IDC_FIND);
	str.Format(_T("ɾ����%d��(���ɼ�)"), 1);
	button->SetWindowTextW(str);
	//button->SetWindowTextW(_T("ɾ�����Ԫ��"));
	
	button = (CButton*)GetDlgItem(IDC_FIND_INVERSE);
	str.Format(_T("ɾ����%d��(��С�ɼ�)"), tcount);
	button->SetWindowTextW(str);
	//button->SetWindowTextW(_T("ɾ����СԪ��"));
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

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

	list->InsertColumn(0, _T("ѧ��"), 0, 100);
	list->InsertColumn(1, _T("����"), 0, 100);
	list->InsertColumn(2, _T("����"), 0, 50);
	list->InsertColumn(3, _T("�Ա�"), 0, 50);
	list->InsertColumn(4, _T("�ɼ�"), 0, 50);
	list->InsertColumn(5, _T("����"), 0,200);
	//��Ӹ��ӵ���ʽ
	list->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	//��ȡ�ļ���ԭ�е�����
	init();
	setItem();
	


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CStuManagerDlg::OnPaint()
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

//ϵͳ�رնԻ���
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

//ȡ��߳ɼ�
void CStuManagerDlg::OnBnClickedGetMax()
{
	try{
		stu*  s = &(queue->getMax());
		CString str;
		str.Format(_T("��߳ɼ�:\r\nѧ��:%s;����:%s;����:%s;�Ա�:%s;�ɼ�:%d;����:%s"), s->stu_no, s->name, s->age, s->gender, s->grade, s->other);
		AfxMessageBox(str);
	}
	catch (...){
		AfxMessageBox(_T("�Ѳ�ѯ���"));
	}
}

//ȡ��ͳɼ�
void CStuManagerDlg::OnBnClickedGetMin()
{
	try{
		stu*  s = &(queue->getMin());
		CString str;
		str.Format(_T("��ͳɼ�:\r\nѧ��:%s;����:%s;����:%s;�Ա�:%s;�ɼ�:%d;����:%s"), s->stu_no, s->name, s->age, s->gender, s->grade, s->other);
		AfxMessageBox(str);
	}catch (...){
		AfxMessageBox(_T("�Ѳ�ѯ���"));
	}
}

//ɾ����߳ɼ�
void CStuManagerDlg::OnBnClickedDelMax()
{
	try{
		stu*  s = &(queue->deQueue_max());
		CString str;
		str.Format(_T("��%d��:\r\nѧ��:%s;����:%s;����:%s;�Ա�:%s;�ɼ�:%d;����:%s"), hcount, s->stu_no, s->name, s->age, s->gender, s->grade, s->other);
		AfxMessageBox(str);

		//ɾ��list�����һ��
		CListCtrl *list = (CListCtrl*)GetDlgItem(IDC_LIST);
		list->DeleteItem(hcount);

		//�ı䰴ť������

		++hcount;
		if (hcount > tcount){
			CButton* ifind = (CButton*)GetDlgItem(IDC_FIND_INVERSE);
			ifind->SetWindowTextW(_T("��ɾ�����"));
			ifind->EnableWindow(false);

			CButton* button = (CButton*)GetDlgItem(IDC_FIND);
			button->SetWindowTextW(_T("��ɾ�����"));
			button->EnableWindow(false);
		}
		else{
			CButton* button = (CButton*)GetDlgItem(IDC_FIND);
			str.Format(_T("ɾ����%d��"), hcount);
			button->SetWindowTextW(str);
		}
		setItem();
	}
	catch (...){
		AfxMessageBox(_T("��ɾ�����"));
	}
}

//ɾ����ͳɼ�
void CStuManagerDlg::OnBnClickedDelMin()
{
	try{
		stu*  s = &(queue->deQueue_min());
		CString str;
		str.Format(_T("��%d��:\r\nѧ��:%s;����:%s;����:%s;�Ա�:%s;�ɼ�:%d;����:%s"), tcount, s->stu_no, s->name, s->age, s->gender, s->grade, s->other);
		AfxMessageBox(str);


		//ɾ��list�����һ��
		CListCtrl *list = (CListCtrl*)GetDlgItem(IDC_LIST);
		list->DeleteItem(tcount);


		//�ı䰴ť������
		--tcount;

		if (hcount > tcount){
			CButton* ifind = (CButton*)GetDlgItem(IDC_FIND_INVERSE);
			ifind->SetWindowTextW(_T("��ɾ�����"));
			ifind->EnableWindow(false);

			CButton* button = (CButton*)GetDlgItem(IDC_FIND);
			button->SetWindowTextW(_T("��ɾ�����"));
			button->EnableWindow(false);
		}
		else{
			CButton* button = (CButton*)GetDlgItem(IDC_FIND_INVERSE);
			str.Format(_T("ɾ����%d��"), tcount);
			button->SetWindowTextW(str);
		}
		setItem();

	}
	catch (...){
		AfxMessageBox(_T("��ɾ�����"));
	}
}
