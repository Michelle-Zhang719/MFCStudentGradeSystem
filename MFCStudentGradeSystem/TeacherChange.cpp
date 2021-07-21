// TeacherChange.cpp: 实现文件
//

#include "pch.h"
#include "MFCStudentGradeSystem.h"
#include "TeacherChange.h"
#include "afxdialogex.h"


// TeacherChange 对话框

IMPLEMENT_DYNAMIC(TeacherChange, CDialogEx)

TeacherChange::TeacherChange(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ChangeGrade, pParent)
{

}

TeacherChange::~TeacherChange()
{
}

void TeacherChange::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_javaLanguage, mEditJavaL);
	DDX_Control(pDX, IDC_EDIT_UserName, mEditName);
	DDX_Control(pDX, IDC_EDIT_aver, mEditAver);
	DDX_Control(pDX, IDC_EDIT_cLanguage, mEditCL);
	DDX_Control(pDX, IDC_EDIT_date, mEditDate);
	DDX_Control(pDX, IDC_EDIT_stuID, mEditID);
}


BEGIN_MESSAGE_MAP(TeacherChange, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &TeacherChange::OnBnClickedButton1)
END_MESSAGE_MAP()


// TeacherChange 消息处理程序

void TeacherChange::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItemText(IDC_EDIT_stuID, sID);
	GetDlgItemText(IDC_EDIT_UserName, sName);
	GetDlgItemText(IDC_EDIT_cLanguage, sCL);
	GetDlgItemText(IDC_EDIT_javaLanguage, sJavaL);
	GetDlgItemText(IDC_EDIT_date, sDate);
	GetDlgItemText(IDC_EDIT_aver, sAver);

	_ConnectionPtr m_pConnection;		//数据库连接对象
	_CommandPtr m_pCommand;			//数据库命令对象
	HRESULT hresult = m_pConnection.CreateInstance("ADODB.Connection");		//创建Connection对象
	if (SUCCEEDED(hresult))
	{
		m_pCommand.CreateInstance("ADODB.Command");		//创建连接
		CString strConnection("Driver={sql server};server=.;database=Student;uid=sa;pwd=123456;");		//连接数据库
		m_pConnection->Open((LPCTSTR)strConnection, "", "", adModeUnknown);		//打卡数据库连接
		CString strSql;		//创建sql语句
		strSql.Format(_T("update StudentGrade set studentID='%s',studentName='%s',cLanguade='%s',javaLanguage='%s',dateBase='%s',gradeAverage='%s' where id='%s'"), sID, sName, sCL, sJavaL, sDate, sAver , id);		//插入全局变量数据
		m_pCommand->ActiveConnection = m_pConnection;
		m_pCommand->CommandText = (LPCTSTR)strSql;
		m_pCommand->Execute(NULL, NULL, adCmdUnknown);

		m_pCommand = NULL;		//清空
		m_pConnection->Close();
		m_pConnection = NULL;		//清空连接
	}
	EndDialog(0);		//关闭对话框
}


BOOL TeacherChange::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	mEditID.SetWindowText(sID);		//传值绑定
	mEditName.SetWindowText(sName);
	mEditCL.SetWindowText(sCL);
	mEditJavaL.SetWindowText(sJavaL);		//传值绑定
	mEditDate.SetWindowText(sDate);
	mEditAver.SetWindowText(sAver);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
