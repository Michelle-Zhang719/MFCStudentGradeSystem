﻿#pragma once


// AdminSearch 对话框

class AdminSearch : public CDialogEx
{
	DECLARE_DYNAMIC(AdminSearch)

public:
	AdminSearch(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~AdminSearch();
	CString sAccount;


// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonoksearch();
};
