// TeacherAdd.cpp: 实现文件
//

#include "pch.h"
#include "MFCStudentGradeSystem.h"
#include "TeacherAdd.h"
#include "afxdialogex.h"


// TeacherAdd 对话框

IMPLEMENT_DYNAMIC(TeacherAdd, CDialogEx)

TeacherAdd::TeacherAdd(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_AddGrade, pParent)
{

}

TeacherAdd::~TeacherAdd()
{
}

void TeacherAdd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TeacherAdd, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &TeacherAdd::OnBnClickedButton1)
END_MESSAGE_MAP()


// TeacherAdd 消息处理程序


void TeacherAdd::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItemText(IDC_EDIT_stuID, sStuID);
	GetDlgItemText(IDC_EDIT_cLanguage,sC);
	GetDlgItemText(IDC_EDIT_date, sDate);
	GetDlgItemText(IDC_EDIT_UserName, sStuName);
	GetDlgItemText(IDC_EDIT_javaLanguage, sJava);
	GetDlgItemText(IDC_EDIT_aver, sAver);
	EndDialog(0);
}
