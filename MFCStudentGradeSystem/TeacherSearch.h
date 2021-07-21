#pragma once


// TeacherSearch 对话框

class TeacherSearch : public CDialogEx
{
	DECLARE_DYNAMIC(TeacherSearch)

public:
	TeacherSearch(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~TeacherSearch();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SearchGrade };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString sAccount, sName;		//用来接收文本框的值

	afx_msg void OnBnClickedButton1();
};
