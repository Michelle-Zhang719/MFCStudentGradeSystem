#pragma once


// CEditStuGraSys 对话框

class CEditStuGraSys : public CDialogEx
{
	DECLARE_DYNAMIC(CEditStuGraSys)

public:
	CEditStuGraSys(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CEditStuGraSys();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	CString sAccount, sAccountPwd, sNote;
	afx_msg void OnBnClickedButtonaddsave();
};
