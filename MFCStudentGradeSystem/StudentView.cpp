// StudentView.cpp: 实现文件
//

#include "pch.h"
#include "MFCStudentGradeSystem.h"
#include "StudentView.h"
#include "afxdialogex.h"
#include "TeacherSearch.h"


// StudentView 对话框

IMPLEMENT_DYNAMIC(StudentView, CDialogEx)

StudentView::StudentView(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_StudentMain, pParent)
{

}

StudentView::~StudentView()
{
}

void StudentView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);
}


BEGIN_MESSAGE_MAP(StudentView, CDialogEx)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON2, &StudentView::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &StudentView::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &StudentView::OnBnClickedButton4)
END_MESSAGE_MAP()


// StudentView 消息处理程序

//初始化界面
BOOL StudentView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	//m_List.InsertColumn(0, _T("编号"), 0, 100);		//控件插入列，表头的设置
	m_List.InsertColumn(0, _T("学号"), 0, 100);
	m_List.InsertColumn(1, _T("姓名"), 0, 100);
	m_List.InsertColumn(2, _T("c语言"), 0, 100);
	m_List.InsertColumn(3, _T("Java"), 0, 100);
	m_List.InsertColumn(4, _T("数据库"), 0, 100);
	m_List.InsertColumn(5, _T("平均成绩"), 0, 100);


	//连接数据库->从数据库中拿数据->关闭数据库->释放
	_ConnectionPtr m_pConnection;
	_CommandPtr m_pCommand;
	_RecordsetPtr m_pRecordset;		//结果集
	CString stSql;
	HRESULT hr = m_pConnection.CreateInstance("ADODB.Connection");
	if (SUCCEEDED(hr))
	{
		CString strConnection("Driver={sql server};server=.;database=Student;uid=sa;pwd=123456;");
		m_pConnection->Open((LPCTSTR)strConnection, "", "", adModeUnknown);
		m_pRecordset.CreateInstance("ADODB.Recordset");

		stSql.Format(_T("select * from StudentGrade") );
		m_pRecordset->Open((LPCTSTR)stSql, m_pConnection.GetInterfacePtr(), adOpenStatic, adLockOptimistic, adCmdText);
	}

	CString strColumn[6];		//字符串数组用来存储一行的4个内容
	int iRowIndex = 0;		//行下标初始化为0
	while (!m_pRecordset->adoEOF)		//结果集是否指向最后一行（BOF开始，EOF结束）
	{
		//strColumn[0] = m_pRecordset->GetCollect("id");		//从数据库拿id的值存在数组里
		//m_List.InsertItem(iRowIndex, strColumn[0]);		//插入新的行 数组中的值给m_List中行下表为0，列下标为0的格

		strColumn[0] = m_pRecordset->GetCollect("studentID");		//数组中的值给m_List中行下表为0，列下标为1的格
		m_List.InsertItem(iRowIndex, strColumn[0]);			//设置第2列 第3列...  _bstr_t：从ado取出来放在mfc中做转换

		strColumn[1] = m_pRecordset->GetCollect("studentName");
		m_List.SetItemText(iRowIndex, 1, (_bstr_t)strColumn[1]);

		strColumn[2] = m_pRecordset->GetCollect("cLanguade");
		m_List.SetItemText(iRowIndex, 2, (_bstr_t)strColumn[2]);

		strColumn[3] = m_pRecordset->GetCollect("javaLanguage");
		m_List.SetItemText(iRowIndex, 3, (_bstr_t)strColumn[3]);

		strColumn[4] = m_pRecordset->GetCollect("dateBase");
		m_List.SetItemText(iRowIndex, 4, (_bstr_t)strColumn[4]);

		strColumn[5] = m_pRecordset->GetCollect("gradeAverage");
		m_List.SetItemText(iRowIndex, 5, (_bstr_t)strColumn[5]);

		iRowIndex++;		//行下标＋1
		m_pRecordset->MoveNext();		//遍历下一行
	}
	m_pRecordset->Close();		//关闭
	m_pConnection->Close();
	m_pRecordset = NULL;		//释放清空

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void StudentView::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDialog* pdlg = (CDialog*)AfxGetMainWnd();
	pdlg->DestroyWindow();

	CDialogEx::OnClose();
}

//正序排序
void StudentView::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_List.DeleteAllItems();		//删除所有项目，清空，重新绑定数据

	_ConnectionPtr m_pConnection;
	_CommandPtr m_pCommand;
	_RecordsetPtr m_pRecordset;		//结果集
	CString stSql;
	HRESULT hr = m_pConnection.CreateInstance("ADODB.Connection");
	if (SUCCEEDED(hr))
	{
		//CString strConnection("Driver={sql server};server=127.0.0.1;database=ContributeDB;uid=sa;pwd=123456;");
		CString strConnection("Driver={sql server};server=.;database=Student;uid=sa;pwd=123456;");
		m_pConnection->Open((LPCTSTR)strConnection, "", "", adModeUnknown);
		m_pRecordset.CreateInstance("ADODB.Recordset");

		stSql.Format(_T("SELECT * FROM StudentGrade ORDER BY gradeAverage ASC"));
		m_pRecordset->Open((LPCTSTR)stSql, m_pConnection.GetInterfacePtr(), adOpenStatic, adLockOptimistic, adCmdText);
	}
	CString strColumn[6];		//字符串数组用来存储一行的4个内容
	int iRowIndex = 0;		//行下标初始化为0
	while (!m_pRecordset->adoEOF)		//结果集是否指向最后一行（BOF开始，EOF结束）
	{
		//strColumn[0] = m_pRecordset->GetCollect("id");		//从数据库拿id的值存在数组里
		//m_List.InsertItem(iRowIndex, strColumn[0]);		//插入新的行 数组中的值给m_List中行下表为0，列下标为0的格

		strColumn[0] = m_pRecordset->GetCollect("studentID");		//数组中的值给m_List中行下表为0，列下标为1的格
		m_List.InsertItem(iRowIndex, strColumn[0]);			//设置第2列 第3列...  _bstr_t：从ado取出来放在mfc中做转换

		strColumn[1] = m_pRecordset->GetCollect("studentName");
		m_List.SetItemText(iRowIndex, 1, (_bstr_t)strColumn[1]);

		strColumn[2] = m_pRecordset->GetCollect("cLanguade");
		m_List.SetItemText(iRowIndex, 2, (_bstr_t)strColumn[2]);

		strColumn[3] = m_pRecordset->GetCollect("javaLanguage");
		m_List.SetItemText(iRowIndex, 3, (_bstr_t)strColumn[3]);

		strColumn[4] = m_pRecordset->GetCollect("dateBase");
		m_List.SetItemText(iRowIndex, 4, (_bstr_t)strColumn[4]);

		strColumn[5] = m_pRecordset->GetCollect("gradeAverage");
		m_List.SetItemText(iRowIndex, 5, (_bstr_t)strColumn[5]);

		iRowIndex++;		//行下标＋1
		m_pRecordset->MoveNext();		//遍历下一行
	}
	m_pRecordset->Close();		//关闭
	m_pConnection->Close();
	m_pRecordset = NULL;		//释放清空

}

//倒序排序
void StudentView::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_List.DeleteAllItems();		//删除所有项目，清空，重新绑定数据

	_ConnectionPtr m_pConnection;
	_CommandPtr m_pCommand;
	_RecordsetPtr m_pRecordset;		//结果集
	CString stSql;
	HRESULT hr = m_pConnection.CreateInstance("ADODB.Connection");
	if (SUCCEEDED(hr))
	{
		//CString strConnection("Driver={sql server};server=127.0.0.1;database=ContributeDB;uid=sa;pwd=123456;");
		CString strConnection("Driver={sql server};server=.;database=Student;uid=sa;pwd=123456;");
		m_pConnection->Open((LPCTSTR)strConnection, "", "", adModeUnknown);
		m_pRecordset.CreateInstance("ADODB.Recordset");

		stSql.Format(_T("SELECT * FROM StudentGrade ORDER BY gradeAverage DeSC"));
		m_pRecordset->Open((LPCTSTR)stSql, m_pConnection.GetInterfacePtr(), adOpenStatic, adLockOptimistic, adCmdText);
	}
	CString strColumn[6];		//字符串数组用来存储一行的4个内容
	int iRowIndex = 0;		//行下标初始化为0
	while (!m_pRecordset->adoEOF)		//结果集是否指向最后一行（BOF开始，EOF结束）
	{
		//strColumn[0] = m_pRecordset->GetCollect("id");		//从数据库拿id的值存在数组里
		//m_List.InsertItem(iRowIndex, strColumn[0]);		//插入新的行 数组中的值给m_List中行下表为0，列下标为0的格

		strColumn[0] = m_pRecordset->GetCollect("studentID");		//数组中的值给m_List中行下表为0，列下标为1的格
		m_List.InsertItem(iRowIndex, strColumn[0]);			//设置第2列 第3列...  _bstr_t：从ado取出来放在mfc中做转换

		strColumn[1] = m_pRecordset->GetCollect("studentName");
		m_List.SetItemText(iRowIndex, 1, (_bstr_t)strColumn[1]);

		strColumn[2] = m_pRecordset->GetCollect("cLanguade");
		m_List.SetItemText(iRowIndex, 2, (_bstr_t)strColumn[2]);

		strColumn[3] = m_pRecordset->GetCollect("javaLanguage");
		m_List.SetItemText(iRowIndex, 3, (_bstr_t)strColumn[3]);

		strColumn[4] = m_pRecordset->GetCollect("dateBase");
		m_List.SetItemText(iRowIndex, 4, (_bstr_t)strColumn[4]);

		strColumn[5] = m_pRecordset->GetCollect("gradeAverage");
		m_List.SetItemText(iRowIndex, 5, (_bstr_t)strColumn[5]);

		iRowIndex++;		//行下标＋1
		m_pRecordset->MoveNext();		//遍历下一行
	}
	m_pRecordset->Close();		//关闭
	m_pConnection->Close();
	m_pRecordset = NULL;		//释放清空
}

//查询
void StudentView::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	TeacherSearch dlg;
	dlg.DoModal();
	int i = 0;
	_ConnectionPtr m_pConnection;
	_CommandPtr m_pCommand;
	_RecordsetPtr m_pRecordset;		//结果集
	CString stSql;
	HRESULT hr = m_pConnection.CreateInstance("ADODB.Connection");
	if (SUCCEEDED(hr))
	{
		//CString strConnection("Driver={sql server};server=127.0.0.1;database=ContributeDB;uid=sa;pwd=123456;");
		CString strConnection("Driver={sql server};server=.;database=Student;uid=sa;pwd=123456;");
		m_pConnection->Open((LPCTSTR)strConnection, "", "", adModeUnknown);
		m_pRecordset.CreateInstance("ADODB.Recordset");

		stSql.Format(_T("SELECT * FROM StudentGrade WHERE  studentID = '%s'"), dlg.sAccount);
		m_pRecordset->Open((LPCTSTR)stSql, m_pConnection.GetInterfacePtr(), adOpenStatic, adLockOptimistic, adCmdText);
	}
	CString strColumn[6];		//字符串数组用来存储一行的4个内容
	while (!m_pRecordset->adoEOF)		//结果集是否指向最后一行（BOF开始，EOF结束）
	{
		strColumn[0] = m_pRecordset->GetCollect("studentID");		//数组中的值给m_List中行下表为0，列下标为1的格
		strColumn[1] = m_pRecordset->GetCollect("studentName");
		strColumn[2] = m_pRecordset->GetCollect("cLanguade");
		strColumn[3] = m_pRecordset->GetCollect("javaLanguage");
		strColumn[4] = m_pRecordset->GetCollect("dateBase");
		strColumn[5] = m_pRecordset->GetCollect("gradeAverage");

		CString outcome = "学号\t姓名\tC语言\tJava\t数据库\t平均成绩\r\n"
			+ strColumn[0] + "\t" + strColumn[1] + "\t" + strColumn[2] + "\t" + strColumn[3] + "\t" + strColumn[4] + "\t" + strColumn[5];
		MessageBox(outcome, "学生成绩查询");
		i = i + 1;
		m_pRecordset->MoveNext();		//遍历下一行
	}
	if (i == 0)
	{
		MessageBox("所查信息不存在", "学生成绩查询");
	}
	m_pRecordset->Close();		//关闭
	m_pConnection->Close();
	m_pRecordset = NULL;		//释放清空
}


