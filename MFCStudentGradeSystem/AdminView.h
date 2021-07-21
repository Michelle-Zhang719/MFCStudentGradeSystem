#pragma once


// AdminView 对话框

class AdminView : public CDialogEx
{
	DECLARE_DYNAMIC(AdminView)

public:
	AdminView(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~AdminView();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	CListCtrl m_List;
	afx_msg void OnBnClickedButtonallselect();
	afx_msg void OnBnClickedButtonbackselect();
	afx_msg void OnBnClickedButtonadd();
	afx_msg void OnBnClickedButtontxtout();
	afx_msg void OnBnClickedButtondelete();
	afx_msg void OnBnClickedButtonchange();
	afx_msg void OnBnClickedButtoncheck();
};
