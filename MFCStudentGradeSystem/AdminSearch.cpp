// AdminSearch.cpp: 实现文件
//

#include "pch.h"
#include "MFCStudentGradeSystem.h"
#include "AdminSearch.h"
#include "afxdialogex.h"


// AdminSearch 对话框

IMPLEMENT_DYNAMIC(AdminSearch, CDialogEx)

AdminSearch::AdminSearch(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG4, pParent)
{

}

AdminSearch::~AdminSearch()
{
}

void AdminSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(AdminSearch, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_okSearch, &AdminSearch::OnBnClickedButtonoksearch)
END_MESSAGE_MAP()


// AdminSearch 消息处理程序


void AdminSearch::OnBnClickedButtonoksearch()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItemText(IDC_EDIT_account, sAccount);
	EndDialog(0);
}
