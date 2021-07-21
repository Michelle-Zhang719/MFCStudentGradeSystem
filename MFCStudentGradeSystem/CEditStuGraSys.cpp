// CEditStuGraSys.cpp: 实现文件
//

#include "pch.h"
#include "MFCStudentGradeSystem.h"
#include "CEditStuGraSys.h"
#include "afxdialogex.h"


// CEditStuGraSys 对话框

IMPLEMENT_DYNAMIC(CEditStuGraSys, CDialogEx)

CEditStuGraSys::CEditStuGraSys(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

CEditStuGraSys::~CEditStuGraSys()
{
}

void CEditStuGraSys::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CEditStuGraSys, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_addSave, &CEditStuGraSys::OnBnClickedButtonaddsave)
END_MESSAGE_MAP()


// CEditStuGraSys 消息处理程序


void CEditStuGraSys::OnBnClickedButtonaddsave()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItemText(IDC_EDIT_account, sAccount);
	GetDlgItemText(IDC_EDIT_accountPwd, sAccountPwd);
	GetDlgItemText(IDC_EDIT_accountNote, sNote);
	EndDialog(0);

}
