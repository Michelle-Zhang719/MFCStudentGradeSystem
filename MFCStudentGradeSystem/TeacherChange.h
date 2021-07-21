#pragma once


// TeacherChange 对话框

class TeacherChange : public CDialogEx
{
	DECLARE_DYNAMIC(TeacherChange)

public:
	TeacherChange(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~TeacherChange();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ChangeGrade };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString sID, sName, sJavaL, sDate, sAver, sCL, id;
	CEdit mEditJavaL;
	CEdit mEditName;
	CEdit mEditAver;
	CEdit mEditCL;
	CEdit mEditDate;
	CEdit mEditID;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
};
