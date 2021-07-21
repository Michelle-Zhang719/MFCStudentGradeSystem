// AdminUpdate.cpp: 实现文件
//

#include "pch.h"
#include "MFCStudentGradeSystem.h"
#include "AdminUpdate.h"
#include "afxdialogex.h"


// AdminUpdate 对话框

IMPLEMENT_DYNAMIC(AdminUpdate, CDialogEx)

AdminUpdate::AdminUpdate(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent)
{

}

AdminUpdate::~AdminUpdate()
{
}

void AdminUpdate::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_accountNote, m_EditNote);
	DDX_Control(pDX, IDC_EDIT_account, m_EditAccount);
	DDX_Control(pDX, IDC_EDIT_accountPwd, m_EditAccountPwd);
}


BEGIN_MESSAGE_MAP(AdminUpdate, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_addSave, &AdminUpdate::OnBnClickedButtonaddsave)
END_MESSAGE_MAP()


// AdminUpdate 消息处理程序



void AdminUpdate::OnBnClickedButtonaddsave()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItemText(IDC_EDIT_accountNote, sNote);
	GetDlgItemText(IDC_EDIT_account, sAccount);
	GetDlgItemText(IDC_EDIT_accountPwd, sAccountPwd);

	_ConnectionPtr m_pConnection;		//数据库连接对象
	_CommandPtr m_pCommand;			//数据库命令对象
	HRESULT hresult = m_pConnection.CreateInstance("ADODB.Connection");		//创建Connection对象
	if (SUCCEEDED(hresult))
	{
		m_pCommand.CreateInstance("ADODB.Command");		//创建连接
		CString strConnection("Driver={sql server};server=.;database=Student;uid=sa;pwd=123456;");		//连接数据库
		m_pConnection->Open((LPCTSTR)strConnection, "", "", adModeUnknown);		//打卡数据库连接
		CString strSql;		//创建sql语句
		strSql.Format(_T("update Users set UserLogin='%s',UserPwd='%s',note='%s' where id='%s'"), sAccount, sAccountPwd, sNote, id);		//插入全局变量数据
		m_pCommand->ActiveConnection = m_pConnection;
		m_pCommand->CommandText = (LPCTSTR)strSql;
		m_pCommand->Execute(NULL, NULL, adCmdUnknown);

		m_pCommand = NULL;		//清空
		m_pConnection->Close();
		m_pConnection = NULL;		//清空连接
	}
	EndDialog(0);		//关闭对话框
}


BOOL AdminUpdate::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	m_EditAccount.SetWindowText(sAccount );		//传值绑定
	m_EditAccountPwd.SetWindowText(sAccountPwd);
	m_EditNote.SetWindowText(sNote);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
