#pragma once


// AdminUpdate 对话框

class AdminUpdate : public CDialogEx
{
	DECLARE_DYNAMIC(AdminUpdate)

public:
	AdminUpdate(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~AdminUpdate();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString sAccount, sAccountPwd, sNote,id;
	CEdit m_EditNote;
	CEdit m_EditAccount;
	CEdit m_EditAccountPwd;
	afx_msg void OnBnClickedButtonaddsave();
	virtual BOOL OnInitDialog();
};
