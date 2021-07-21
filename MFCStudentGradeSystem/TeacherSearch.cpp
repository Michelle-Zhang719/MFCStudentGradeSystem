// TeacherSearch.cpp: 实现文件
//

#include "pch.h"
#include "MFCStudentGradeSystem.h"
#include "TeacherSearch.h"
#include "afxdialogex.h"


// TeacherSearch 对话框

IMPLEMENT_DYNAMIC(TeacherSearch, CDialogEx)

TeacherSearch::TeacherSearch(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SearchGrade, pParent)
{

}

TeacherSearch::~TeacherSearch()
{
}

void TeacherSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TeacherSearch, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &TeacherSearch::OnBnClickedButton1)
END_MESSAGE_MAP()


// TeacherSearch 消息处理程序


void TeacherSearch::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItemText(IDC_EDIT1, sAccount);
	//GetDlgItemText(IDC_EDIT2, sName);
	EndDialog(0);
}
