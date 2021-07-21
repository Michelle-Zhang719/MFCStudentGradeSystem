
// MFCStudentGradeSystemDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCStudentGradeSystem.h"
#include "MFCStudentGradeSystemDlg.h"
#include "afxdialogex.h"
#include "AdminView.h"
#include "Debug/msado15.tlh"
#include "TeacherView.h"
#include "StudentView.h"

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


// CMFCStudentGradeSystemDlg 对话框



CMFCStudentGradeSystemDlg::CMFCStudentGradeSystemDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCSTUDENTGRADESYSTEM_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCStudentGradeSystemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	
}

BEGIN_MESSAGE_MAP(CMFCStudentGradeSystemDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_adminLogin, &CMFCStudentGradeSystemDlg::OnBnClickedButtonadminlogin)
	ON_BN_CLICKED(IDC_BUTTON_teacherLogin, &CMFCStudentGradeSystemDlg::OnBnClickedButtonteacherlogin)
	ON_BN_CLICKED(IDC_BUTTON_studentlogin, &CMFCStudentGradeSystemDlg::OnBnClickedButtonstudentlogin)
END_MESSAGE_MAP()


// CMFCStudentGradeSystemDlg 消息处理程序

BOOL CMFCStudentGradeSystemDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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

void CMFCStudentGradeSystemDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCStudentGradeSystemDlg::OnPaint()
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
HCURSOR CMFCStudentGradeSystemDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//管理员登陆
void CMFCStudentGradeSystemDlg::OnBnClickedButtonadminlogin()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strUserName, strUserPwd;		//存储用户名和用户密码的两个字符串

	GetDlgItemText(IDC_EDIT_UserName, strUserName);		//从文本框读数据放到字符串中
	GetDlgItemText(IDC_EDIT_UserPwd, strUserPwd);
	

	CString strValidationInfo(" ");		//验证信息，同意判断用户名和密码不能为空
	if (strUserName == " ")
	{
		strValidationInfo = _T("用户名不可为空，请输入\n");
	}
	if (strUserPwd == " ")
	{
		strValidationInfo += _T("密码不可为空，请输入\n");	//追加提示信息
	}
	if (strValidationInfo != " ")
	{
		AfxMessageBox(strValidationInfo);		//弹窗
		return;
	}

	_ConnectionPtr m_pConnection;
	_CommandPtr m_pCommand;
	_RecordsetPtr m_pRecordset;
	CString stSql;
	HRESULT hr = m_pConnection.CreateInstance("ADODB.Connection");
	if (SUCCEEDED(hr))
	{
		//CString strConnection("Driver={sql server};server=127.0.0.1;database=ContributeDB;uid=sa;pwd=123456;");
		CString strConnection("Driver={sql server};server=.;database=Student;uid=sa;pwd=123456;");
		m_pConnection->Open((LPCTSTR)strConnection, "", "", adModeUnknown);
		m_pRecordset.CreateInstance("ADODB.Recordset");

		//stSql.Format(_T("SELECT * FROM Employee where LoginName = '%s' and LoginPassword = '%s'"), strUserName, strUserPwd);
		stSql.Format(_T("select * From Users where UserLogin = '%s' and UserPwd = '%s' and note = '管理员'"), strUserName, strUserPwd);
		m_pRecordset->Open((LPCTSTR)stSql, m_pConnection.GetInterfacePtr(), adOpenStatic, adLockOptimistic, adCmdText);

		if (!m_pRecordset->adoBOF)
		{
			//用户名密码正确，有数据，表示数据库里有该用户，说明该用户身份合法，允许继续使用
			ShowWindow(SW_HIDE);		//隐藏当前窗体
			AdminView  mainSys;
			mainSys.DoModal();		//弹窗
		}
		else
		{
			//身份不合法，请重新输入正确的用户名和密码
			::MessageBox(NULL, _T("用户名或密码不正确，请确认"), _T("登录信息有误"), MB_OK);
			return;
		}

	}
	
}


//教师登录
void CMFCStudentGradeSystemDlg::OnBnClickedButtonteacherlogin()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strUserName, strUserPwd;		//存储用户名和用户密码的两个字符串

	GetDlgItemText(IDC_EDIT_UserName, strUserName);		//从文本框读数据放到字符串中
	GetDlgItemText(IDC_EDIT_UserPwd, strUserPwd);

	CString strValidationInfo(" ");		//验证信息，同意判断用户名和密码不能为空
	if (strUserName == " ")
	{
		strValidationInfo = _T("用户名不可为空，请输入\n");
	}
	if (strUserPwd == " ")
	{
		strValidationInfo += _T("密码不可为空，请输入\n");	//追加提示信息
	}
	if (strValidationInfo != " ")
	{
		AfxMessageBox(strValidationInfo);		//弹窗
		return;
	}

	_ConnectionPtr m_pConnection;
	_CommandPtr m_pCommand;
	_RecordsetPtr m_pRecordset;
	CString stSql;
	HRESULT hr = m_pConnection.CreateInstance("ADODB.Connection");
	if (SUCCEEDED(hr))
	{
		//CString strConnection("Driver={sql server};server=127.0.0.1;database=ContributeDB;uid=sa;pwd=123456;");
		CString strConnection("Driver={sql server};server=.;database=Student;uid=sa;pwd=123456;");
		m_pConnection->Open((LPCTSTR)strConnection, "", "", adModeUnknown);
		m_pRecordset.CreateInstance("ADODB.Recordset");

		//stSql.Format(_T("SELECT * FROM Employee where LoginName = '%s' and LoginPassword = '%s'"), strUserName, strUserPwd);
		stSql.Format(_T("select * From Users where UserLogin = '%s' and UserPwd = '%s' and note = '老师'"), strUserName, strUserPwd);
		m_pRecordset->Open((LPCTSTR)stSql, m_pConnection.GetInterfacePtr(), adOpenStatic, adLockOptimistic, adCmdText);

		if (!m_pRecordset->adoBOF)
		{
			//用户名密码正确，有数据，表示数据库里有该用户，说明该用户身份合法，允许继续使用
			ShowWindow(SW_HIDE);
			TeacherView mainSys;
			mainSys.DoModal();
		}
		else
		{
			//身份不合法，请重新输入正确的用户名和密码
			::MessageBox(NULL, _T("用户名或密码不正确，请确认"), _T("登录信息有误"), MB_OK);
			return;
		}

	}
}

//学生登录
void CMFCStudentGradeSystemDlg::OnBnClickedButtonstudentlogin()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strUserName, strUserPwd;		//存储用户名和用户密码的两个字符串

	GetDlgItemText(IDC_EDIT_UserName, strUserName);		//从文本框读数据放到字符串中
	GetDlgItemText(IDC_EDIT_UserPwd, strUserPwd);

	CString strValidationInfo(" ");		//验证信息，同意判断用户名和密码不能为空
	if (strUserName == " ")
	{
		strValidationInfo = _T("用户名不可为空，请输入\n");
	}
	if (strUserPwd == " ")
	{
		strValidationInfo += _T("密码不可为空，请输入\n");	//追加提示信息
	}
	if (strValidationInfo != " ")
	{
		AfxMessageBox(strValidationInfo);		//弹窗
		return;
	}

	_ConnectionPtr m_pConnection;
	_CommandPtr m_pCommand;
	_RecordsetPtr m_pRecordset;
	CString stSql;
	HRESULT hr = m_pConnection.CreateInstance("ADODB.Connection");
	if (SUCCEEDED(hr))
	{
		//CString strConnection("Driver={sql server};server=127.0.0.1;database=ContributeDB;uid=sa;pwd=123456;");
		CString strConnection("Driver={sql server};server=.;database=Student;uid=sa;pwd=123456;");
		m_pConnection->Open((LPCTSTR)strConnection, "", "", adModeUnknown);
		m_pRecordset.CreateInstance("ADODB.Recordset");

		//stSql.Format(_T("SELECT * FROM Employee where LoginName = '%s' and LoginPassword = '%s'"), strUserName, strUserPwd);
		stSql.Format(_T("select * From Users where UserLogin = '%s' and UserPwd = '%s' and note = '学生'"), strUserName, strUserPwd);
		m_pRecordset->Open((LPCTSTR)stSql, m_pConnection.GetInterfacePtr(), adOpenStatic, adLockOptimistic, adCmdText);

		if (!m_pRecordset->adoBOF)
		{
			//用户名密码正确，有数据，表示数据库里有该用户，说明该用户身份合法，允许继续使用
			ShowWindow(SW_HIDE);
			StudentView mainSys;
			mainSys.DoModal();
		}
		else
		{
			//身份不合法，请重新输入正确的用户名和密码
			::MessageBox(NULL, _T("用户名或密码不正确，请确认"), _T("登录信息有误"), MB_OK);
			return;
		}

	}
}
