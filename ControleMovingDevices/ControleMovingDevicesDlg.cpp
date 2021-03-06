
// ControleMovingDevicesDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "ControleMovingDevices.h"
#include "ControleMovingDevicesDlg.h"
#include "afxdialogex.h"
#include<shellapi.h>
#include <process.h>
#include<tchar.h>
#include<ShlObj.h>
#include <tlhelp32.h> 
#define ArraySize(ptr)    (sizeof(ptr) / sizeof(ptr[0]))
#pragma comment(lib,"shell32.lib")
#include<iostream>
using namespace std;
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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


// CControleMovingDevicesDlg 对话框



CControleMovingDevicesDlg::CControleMovingDevicesDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CONTROLEMOVINGDEVICES_DIALOG, pParent)
	, m_rongliang(_T(""))
	, m_keshiyong(_T(""))
	, m_yiyongrongliang(_T(""))
	, m_copyfile(_T(""))
	, m_copycontent(_T(""))
	, m_delete(_T(""))
	, m_panfu(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CControleMovingDevicesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_MAX, m_rongliang);
	DDX_Text(pDX, IDC_STATIC_AVALIABLE, m_keshiyong);
	DDX_Text(pDX, IDC_STATIC_CONSUME, m_yiyongrongliang);
	DDX_Text(pDX, IDC_EDIT4__COPYFILE, m_copyfile);
	DDX_Text(pDX, IDC_EDIT1_COPYCONTENT, m_copycontent);
	DDX_Text(pDX, IDC_EDIT2_DELETE, m_delete);
	DDX_Text(pDX, IDC_STATIC_PAN, m_panfu);
}

BEGIN_MESSAGE_MAP(CControleMovingDevicesDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CControleMovingDevicesDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CControleMovingDevicesDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CControleMovingDevicesDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CControleMovingDevicesDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON2, &CControleMovingDevicesDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON6, &CControleMovingDevicesDlg::OnBnClickedButton6)
END_MESSAGE_MAP()


// CControleMovingDevicesDlg 消息处理程序
CString CControleMovingDevicesDlg::check() {

	int DSLength = GetLogicalDriveStrings(0, NULL);

	//通过GetLogicalDriveStrings()函数获取所有驱动器字符串信息长度。

	char* DStr = new char[DSLength];//用获取的长度在堆区创建一个c风格的字符串数组

	GetLogicalDriveStrings(DSLength, (LPTSTR)DStr);

	//通过GetLogicalDriveStrings将字符串信息复制到堆区数组中,其中保存了所有驱动器的信息。


	

	CString a;
	int DType;

	int si = 0;


	for (int i = 0; i < DSLength / 4; ++i)
		//为了显示每个驱动器的状态，则通过循环输出实现，由于DStr内部保存的数据是A:\NULLB:\NULLC:\NULL，这样的信息，所以DSLength/4可以获得具体大循环范围
	{
		char dir[3] = { DStr[si],':','\\' };

		DType = GetDriveType(DStr + i * 4);

		//GetDriveType函数，可以获取驱动器类型，参数为驱动器的根目录


		if (DType == DRIVE_REMOVABLE)

		{
			a = dir[0];
			DWORD64 qwFreeBytes, qwFreeBytesToCaller, qwTotalBytes;
			BOOL bResult = GetDiskFreeSpaceEx(TEXT(a+":"),
				(PULARGE_INTEGER)&qwFreeBytesToCaller,
				(PULARGE_INTEGER)&qwTotalBytes,
				(PULARGE_INTEGER)&qwFreeBytes);
			if (bResult)
			{
				m_rongliang.Format(_T("%d"), qwTotalBytes/1024/1024/1024);
				m_rongliang += "GB";
				m_keshiyong.Format(_T("%d"), qwFreeBytes / 1024 / 1024);
				m_keshiyong += "MB";
				m_yiyongrongliang.Format(_T("%d"), (qwTotalBytes - qwFreeBytes) / 1024 / 1024);
				m_yiyongrongliang += "MB";
			}
				
			return a;
		}

		si += 4;
	}
	return "无U盘";
}
BOOL CControleMovingDevicesDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	panfu = check();
	m_panfu = panfu;
	UpdateData(false);
	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}


void CControleMovingDevicesDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。
BOOL HideVolume(LPCTSTR lpDriveLetter, LPCTSTR lpDevice, BOOL bAddMountPoint)
{
	BOOL bRet = FALSE;
	TCHAR szDriveLetterAndSlash[4] = { 0 };
	TCHAR szDriveLetter[3] = { 0 };
	TCHAR szUniqueVolumeName[MAX_PATH] = { 0 };
	// 	if(lpDriveLetter && lpDevice)
	// 	{
	szDriveLetter[0] = lpDriveLetter[0];
	szDriveLetter[1] = TEXT(':');
	szDriveLetter[2] = TEXT('\0');

	szDriveLetterAndSlash[0] = lpDriveLetter[0];
	szDriveLetterAndSlash[1] = TEXT(':');
	szDriveLetterAndSlash[2] = TEXT('\\');
	szDriveLetterAndSlash[3] = TEXT('\0');
	/*	}*/
	if (bAddMountPoint)
	{
		//Try to Attach lpDevice to lpDriveLetter
		bRet = DefineDosDevice(DDD_RAW_TARGET_PATH, szDriveLetter,
			lpDevice);

		if (bRet)
		{
			if (!GetVolumeNameForVolumeMountPoint(szDriveLetterAndSlash,
				szUniqueVolumeName,
				MAX_PATH))
			{
				//Can't Find Attached lpDevice 's VolumeName
				szUniqueVolumeName[0] = '\0';
			}

			bRet = DefineDosDevice(
				DDD_RAW_TARGET_PATH | DDD_REMOVE_DEFINITION |
				DDD_EXACT_MATCH_ON_REMOVE, szDriveLetter,
				lpDevice);

			if (!bRet)
				return bRet;

			bRet = SetVolumeMountPoint(szDriveLetterAndSlash,
				szUniqueVolumeName);
		}
	}
	else
	{
		bRet = DeleteVolumeMountPoint(szDriveLetterAndSlash);
	}
	return bRet;

}
void CControleMovingDevicesDlg::OnPaint()
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
HCURSOR CControleMovingDevicesDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CControleMovingDevicesDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	QueryDosDevice(_T(panfu+":"), DosPath, MAX_PATH);
	HideVolume(_T(panfu+"://"), NULL, FALSE);
}


void CControleMovingDevicesDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	CString begin = m_copyfile;
	int wei = 0;
	for (int  i = 0; i < begin.GetLength(); i++)
	{
		if (begin[i]=='\\')
		{
			wei = i;
		}
	}
	CString name;
	for (int i = wei; i <begin.GetLength(); i++)
	{
		name += begin[i];
	}
	CString end = panfu + ":" + "\\" + name;
	if (CopyFile(begin, end, FALSE) == 0)
	{
		MessageBox("复制失败");
	}
	else
	{
		MessageBox("复制成功");
	}
}

void CControleMovingDevicesDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	SHFILEOPSTRUCT fop;
	fop.wFunc = FO_COPY;
	CString begin = m_copycontent;
	begin += '\0';
	fop.pFrom =begin;
	CString name;

	int wei = 0;
	for (int i = 0; i <m_copycontent.GetLength(); i++)
	{
		if (m_copycontent[i] == '\\')
		{
			wei = i;
		}
	}
	for (int i = wei; i < begin.GetLength(); i++)
	{
		name += begin[i];
	}
	CString end = panfu + ":\\"+name+'\0';
	fop.pTo =end;
	if (SHFileOperation(&fop) == 0)
	{
		MessageBox("复制成功");
	}
	else
	{
		MessageBox("复制失败");
	}
	
}


void CControleMovingDevicesDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	//本方法为删除函数
	UpdateData(true);
	SHFILEOPSTRUCT dele;
	dele.fFlags = FOF_NOCONFIRMATION;

	dele.hNameMappings = NULL;

	dele.hwnd = NULL;

	dele.lpszProgressTitle = NULL;
	dele.wFunc = FO_DELETE;
	string a = m_delete;
	dele.pFrom = a.c_str();
	dele.pTo = NULL;
	if (SHFileOperation(&dele) == 0)
	{
		MessageBox("删除成功");
	}
	else
	{
		MessageBox("删除失败");
	}
}
/*
	卸载U盘
*/

void CControleMovingDevicesDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	HideVolume(_T("F://"), DosPath, TRUE);
}
BOOL FindProcessPid(LPCSTR ProcessName, DWORD& dwPid)
{
	HANDLE hProcessSnap;
	PROCESSENTRY32 pe32;

	// Take a snapshot of all processes in the system.
	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		return(FALSE);
	}

	pe32.dwSize = sizeof(PROCESSENTRY32);

	if (!Process32First(hProcessSnap, &pe32))
	{
		CloseHandle(hProcessSnap);          // clean the snapshot object
		return(FALSE);
	}

	BOOL    bRet = FALSE;
	do
	{
		if (!strcmp(ProcessName, pe32.szExeFile))
		{
			dwPid = pe32.th32ProcessID;
			bRet = TRUE;
			break;
		}

	} while (Process32Next(hProcessSnap, &pe32));

	CloseHandle(hProcessSnap);
	return bRet;
}

void CControleMovingDevicesDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	LPCSTR ListApps[]{
		"ControleMovingDevices.exe"
	};
	// StopMyService();
	DWORD dwPid = 0;

	for (int i = 0; i < ArraySize(ListApps); i++)
	{
		if (FindProcessPid(ListApps[i], dwPid))
		{
			CString a;
			a.Format(_T("%d"), dwPid);;
			MessageBox("PID:"+a);
		}
	}
}
