
// ControleMovingDevicesDlg.h: 头文件
//

#pragma once


// CControleMovingDevicesDlg 对话框
class CControleMovingDevicesDlg : public CDialogEx
{
// 构造
public:
	CControleMovingDevicesDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONTROLEMOVINGDEVICES_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	TCHAR DosPath[MAX_PATH];
	CString check();
	CString panfu;
	CString m_rongliang;
	CString m_keshiyong;
	CString m_yiyongrongliang;
	CString m_copyfile;
	CString m_copycontent;
	CString m_delete;
	CString m_panfu;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton6();
};
