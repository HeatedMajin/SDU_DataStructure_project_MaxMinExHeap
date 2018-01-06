
// StuManagerDlg.h : 头文件
//

#pragma once


// CStuManagerDlg 对话框
class CStuManagerDlg : public CDialogEx
{
// 构造
public:
	CStuManagerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_STUMANAGER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	//自己的函数
	void init(CString str = _T("stu.txt"));
	void setItem();
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnClose();
	afx_msg void OnBnClickedFind();
	afx_msg void OnBnClickedFindInverse();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnBnClickedGetMax();
	afx_msg void OnBnClickedGetMin();
	afx_msg void OnBnClickedDelMax();
	afx_msg void OnBnClickedDelMin();
};
