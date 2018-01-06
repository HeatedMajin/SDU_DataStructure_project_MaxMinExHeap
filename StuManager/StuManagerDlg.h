
// StuManagerDlg.h : ͷ�ļ�
//

#pragma once


// CStuManagerDlg �Ի���
class CStuManagerDlg : public CDialogEx
{
// ����
public:
	CStuManagerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_STUMANAGER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	//�Լ��ĺ���
	void init(CString str = _T("stu.txt"));
	void setItem();
	// ���ɵ���Ϣӳ�亯��
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
