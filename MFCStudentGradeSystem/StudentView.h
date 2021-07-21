#pragma once


// StudentView 对话框

class StudentView : public CDialogEx
{
	DECLARE_DYNAMIC(StudentView)

public:
	StudentView(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~StudentView();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_StudentMain };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	CListCtrl m_List;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
};
