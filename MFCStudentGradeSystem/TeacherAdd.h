#pragma once


// TeacherAdd 对话框

class TeacherAdd : public CDialogEx
{
	DECLARE_DYNAMIC(TeacherAdd)

public:
	TeacherAdd(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~TeacherAdd();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_AddGrade };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString sStuID, sStuName, sC, sJava, sDate, sAver;
	afx_msg void OnBnClickedButton1();
};
