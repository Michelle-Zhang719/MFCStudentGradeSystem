// TeacherView.cpp: 实现文件
//

#include "pch.h"
#include "MFCStudentGradeSystem.h"
#include "TeacherView.h"
#include "afxdialogex.h"
#include "TeacherAdd.h"
#include "TeacherChange.h"
#include "TeacherSearch.h"


// TeacherView 对话框

IMPLEMENT_DYNAMIC(TeacherView, CDialogEx)

TeacherView::TeacherView(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_GradeMain, pParent)
{

}

TeacherView::~TeacherView()
{
}

void TeacherView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);
}


BEGIN_MESSAGE_MAP(TeacherView, CDialogEx)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_allSelect, &TeacherView::OnBnClickedButtonallselect)
	ON_BN_CLICKED(IDC_BUTTON_backSelect, &TeacherView::OnBnClickedButtonbackselect)
	ON_BN_CLICKED(IDC_BUTTON_txtOut, &TeacherView::OnBnClickedButtontxtout)
	ON_BN_CLICKED(IDC_BUTTON_delete, &TeacherView::OnBnClickedButtondelete)
	ON_BN_CLICKED(IDC_BUTTON_add, &TeacherView::OnBnClickedButtonadd)
	ON_BN_CLICKED(IDC_BUTTON_change, &TeacherView::OnBnClickedButtonchange)
	ON_BN_CLICKED(IDC_BUTTON_check, &TeacherView::OnBnClickedButtoncheck)
	ON_BN_CLICKED(IDC_BUTTON1, &TeacherView::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &TeacherView::OnBnClickedButton2)
END_MESSAGE_MAP()


// TeacherView 消息处理程序


void TeacherView::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDialog* pdlg = (CDialog*)AfxGetMainWnd();
	pdlg->DestroyWindow();

	CDialogEx::OnClose();
}

//初始化老师界面，显示学生成绩
BOOL TeacherView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES);		//选择样式 行全选|复选框

	m_List.InsertColumn(0, _T("编号"), 0, 100);		//控件插入列，表头的设置
	m_List.InsertColumn(1, _T("学号"), 0, 100);
	m_List.InsertColumn(2, _T("姓名"), 0, 100);
	m_List.InsertColumn(3, _T("c语言"), 0, 100);
	m_List.InsertColumn(4, _T("Java"), 0, 100);
	m_List.InsertColumn(5, _T("数据库"), 0, 100);
	m_List.InsertColumn(6, _T("平均成绩"), 0, 100);


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

		stSql.Format(_T("SELECT * FROM StudentGrade"));
		m_pRecordset->Open((LPCTSTR)stSql, m_pConnection.GetInterfacePtr(), adOpenStatic, adLockOptimistic, adCmdText);
	}

	CString strColumn[7];		//字符串数组用来存储一行的4个内容
	int iRowIndex = 0;		//行下标初始化为0
	while (!m_pRecordset->adoEOF)		//结果集是否指向最后一行（BOF开始，EOF结束）
	{
		strColumn[0] = m_pRecordset->GetCollect("id");		//从数据库拿id的值存在数组里
		m_List.InsertItem(iRowIndex, strColumn[0]);		//插入新的行 数组中的值给m_List中行下表为0，列下标为0的格

		strColumn[1] = m_pRecordset->GetCollect("studentID");		//数组中的值给m_List中行下表为0，列下标为1的格
		m_List.SetItemText(iRowIndex, 1, (_bstr_t)strColumn[1]);		//设置第2列 第3列...  _bstr_t：从ado取出来放在mfc中做转换

		strColumn[2] = m_pRecordset->GetCollect("studentName");
		m_List.SetItemText(iRowIndex, 2, (_bstr_t)strColumn[2]);

		strColumn[3] = m_pRecordset->GetCollect("cLanguade");
		m_List.SetItemText(iRowIndex, 3, (_bstr_t)strColumn[3]);

		strColumn[4] = m_pRecordset->GetCollect("javaLanguage");
		m_List.SetItemText(iRowIndex, 4, (_bstr_t)strColumn[4]);

		strColumn[5] = m_pRecordset->GetCollect("dateBase");
		m_List.SetItemText(iRowIndex, 5, (_bstr_t)strColumn[5]);

		strColumn[6] = m_pRecordset->GetCollect("gradeAverage");
		m_List.SetItemText(iRowIndex, 6, (_bstr_t)strColumn[6]);

		iRowIndex++;		//行下标＋1
		m_pRecordset->MoveNext();		//遍历下一行
	}
	m_pRecordset->Close();		//关闭
	m_pConnection->Close();
	m_pRecordset = NULL;		//释放清空

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

//全选
void TeacherView::OnBnClickedButtonallselect()
{
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 0; i < m_List.GetItemCount(); i++)
	{
		m_List.SetCheck(i, TRUE);		//TRUE选中
	}
}

//反选
void TeacherView::OnBnClickedButtonbackselect()
{
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 0; i < m_List.GetItemCount(); i++)
	{
		m_List.SetCheck(i, !m_List.GetCheck(i));
	}
}

//导出学生成绩
void TeacherView::OnBnClickedButtontxtout()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog fDlg(FALSE, ".txt", "StudentGrade", OFN_OVERWRITEPROMPT, "数据文件(*.txt)|*.txt|所有文件(*.*)|*.*||", NULL);
	if (fDlg.DoModal() == IDOK) {
		CString cs, list;
		CStdioFile file(fDlg.GetPathName(), CFile::modeWrite | CFile::modeCreate);
		
		list = "编号\t学号\t姓名\tC语言\tJava\t数据库\t平均成绩\n";
		file.WriteString(list);
		for (int i = 0; i < m_List.GetItemCount(); i++) {
			//获取每一行条目的文本
			cs = m_List.GetItemText(i, 0) + "\t";
			cs += m_List.GetItemText(i, 1) + "\t";
			cs += m_List.GetItemText(i, 2) + "\t";
			cs += m_List.GetItemText(i, 3) + "\t";
			cs += m_List.GetItemText(i, 4) + "\t";
			cs += m_List.GetItemText(i, 5) + "\t";
			cs += m_List.GetItemText(i, 6) + "\n";
			file.WriteString(cs);
		}
		file.Close();
	}
}

//删除学生成绩
void TeacherView::OnBnClickedButtondelete()
{
	// TODO: 在此添加控件通知处理程序代码
	CString sDelId("");		//存放删除id，赋初值为空

	int flag = 0;
	for (int i = 0; i < m_List.GetItemCount(); i++)		//被选中数量不能为0
	{
		if (m_List.GetCheck(i))
		{
			flag++;
		}
	}
	if (flag == 0)
	{
		MessageBox(_T("请选择一组数据删除"));
		return;
	}


	for (int i = 0; i < m_List.GetItemCount(); i++)
	{
		if (m_List.GetCheck(i))		//若被选中
		{
			sDelId += _T(",") + m_List.GetItemText(i, 0);		//追加删除
		}
	}
	sDelId = sDelId.Right(sDelId.GetLength() - 1);		//删除最前面的逗号

	//同插入对数据库的操作
	_ConnectionPtr m_pConnection;		//数据库连接对象
	_CommandPtr m_pCommand;			//数据库命令对象
	HRESULT hresult = m_pConnection.CreateInstance("ADODB.Connection");		//创建Connection对象
	if (SUCCEEDED(hresult))
	{
		m_pCommand.CreateInstance("ADODB.Command");		//创建连接
		CString strConnection("Driver={sql server};server=.;database=Student;uid=sa;pwd=123456;");		//连接数据库
		m_pConnection->Open((LPCTSTR)strConnection, "", "", adModeUnknown);		//打卡数据库连接
		CString strSql;		//创建sql语句
		strSql.Format(_T("delete from StudentGrade where id in(%s)"), sDelId);		
		m_pCommand->ActiveConnection = m_pConnection;
		m_pCommand->CommandText = (LPCTSTR)strSql;

		m_pCommand->Execute(NULL, NULL, adCmdUnknown);

		m_pCommand = NULL;		//清空


		m_List.DeleteAllItems();

		//————————————实现重新绑定———————————————————
		_RecordsetPtr m_pRecordset;		//结果集
		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pRecordset->Open(("SELECT * FROM StudentGrade"), m_pConnection.GetInterfacePtr(), adOpenStatic, adLockOptimistic, adCmdText);
		CString strColumn[7];		//字符串数组用来存储一行的4个内容
		int iRowIndex = 0;		//行下标初始化为0
		while (!m_pRecordset->adoEOF)		//结果集是否指向最后一行（BOF开始，EOF结束）
		{
			strColumn[0] = m_pRecordset->GetCollect("id");		//从数据库拿id的值存在数组里
			m_List.InsertItem(iRowIndex, strColumn[0]);		//插入新的行 数组中的值给m_List中行下表为0，列下标为0的格

			strColumn[1] = m_pRecordset->GetCollect("studentID");		//数组中的值给m_List中行下表为0，列下标为1的格
			m_List.SetItemText(iRowIndex, 1, (_bstr_t)strColumn[1]);		//设置第2列 第3列...  _bstr_t：从ado取出来放在mfc中做转换

			strColumn[2] = m_pRecordset->GetCollect("studentName");
			m_List.SetItemText(iRowIndex, 2, (_bstr_t)strColumn[2]);

			strColumn[3] = m_pRecordset->GetCollect("cLanguade");
			m_List.SetItemText(iRowIndex, 3, (_bstr_t)strColumn[3]);

			strColumn[4] = m_pRecordset->GetCollect("javaLanguage");
			m_List.SetItemText(iRowIndex, 4, (_bstr_t)strColumn[4]);

			strColumn[5] = m_pRecordset->GetCollect("dateBase");
			m_List.SetItemText(iRowIndex, 5, (_bstr_t)strColumn[5]);

			strColumn[6] = m_pRecordset->GetCollect("gradeAverage");
			m_List.SetItemText(iRowIndex, 6, (_bstr_t)strColumn[6]);

			iRowIndex++;		//行下标＋1
			m_pRecordset->MoveNext();		//遍历下一行
		}
		m_pRecordset->Close();		//关闭
		m_pConnection->Close();
		m_pRecordset = NULL;		//释放清空
		m_pConnection = NULL;		//清空连接
	}
}

//添加学生成绩
void TeacherView::OnBnClickedButtonadd()
{
	// TODO: 在此添加控件通知处理程序代码
	TeacherAdd dlg;
	dlg.DoModal();		//弹出新增窗口

	for (int i = 0; i < m_List.GetItemCount(); i++)
	{
		CString temp_sStuID = m_List.GetItemText(i, 1);
		CString temp_sStuName = m_List.GetItemText(i, 2);
		CString temp_sC = m_List.GetItemText(i, 3);
		CString temp_sJava = m_List.GetItemText(i, 4);
		CString temp_sDate = m_List.GetItemText(i, 5);
		CString temp_sAver = m_List.GetItemText(i, 6);

		if (temp_sStuID.CompareNoCase(dlg.sStuID) == 0 )
		{
			MessageBox(_T("该学生成绩已存在"));
			return;
		}
	}

	m_List.DeleteAllItems();		//删除所有项目，清空，重新绑定数据

	//————————————————实现插入————————————
	_ConnectionPtr m_pConnection;		//数据库连接对象
	_CommandPtr m_pCommand;			//数据库命令对象
	HRESULT hresult = m_pConnection.CreateInstance("ADODB.Connection");		//创建Connection对象
	if (SUCCEEDED(hresult))
	{
		m_pCommand.CreateInstance("ADODB.Command");		//创建连接
		CString strConnection("Driver={sql server};server=.;database=Student;uid=sa;pwd=123456;");	//连接数据库
		m_pConnection->Open((LPCTSTR)strConnection, "", "", adModeUnknown);		//打卡数据库连接
		CString strSql;		//创建sql语句
		strSql.Format(_T("insert into StudentGrade(  studentID, studentName, cLanguade,javaLanguage,dateBase,gradeAverage)values ('%s','%s','%s','%s', '%s', '%s')"),
			dlg.sStuID, dlg.sStuName, dlg.sC, dlg.sJava, dlg.sDate, dlg.sAver);		//插入全局变量数据

		m_pCommand->ActiveConnection = m_pConnection;
		m_pCommand->CommandText =( (LPCTSTR)strSql);
		m_pCommand->Execute(NULL, NULL, adCmdUnknown);
		m_pCommand = NULL;		//清空



		//————————————实现重新绑定———————————————————
		_RecordsetPtr m_pRecordset;		//结果集
		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pRecordset->Open(("SELECT * FROM StudentGrade"), m_pConnection.GetInterfacePtr(), adOpenStatic, adLockOptimistic, adCmdText);
		CString strColumn[7];		//字符串数组用来存储一行的4个内容
		int iRowIndex = 0;		//行下标初始化为0
		while (!m_pRecordset->adoEOF)		//结果集是否指向最后一行（BOF开始，EOF结束）
		{
			strColumn[0] = m_pRecordset->GetCollect("id");		//从数据库拿id的值存在数组里
			m_List.InsertItem(iRowIndex, strColumn[0]);		//插入新的行 数组中的值给m_List中行下表为0，列下标为0的格

			strColumn[1] = m_pRecordset->GetCollect("studentID");		//数组中的值给m_List中行下表为0，列下标为1的格
			m_List.SetItemText(iRowIndex, 1, (_bstr_t)strColumn[1]);		//设置第2列 第3列...  _bstr_t：从ado取出来放在mfc中做转换

			strColumn[2] = m_pRecordset->GetCollect("studentName");
			m_List.SetItemText(iRowIndex, 2, (_bstr_t)strColumn[2]);

			strColumn[3] = m_pRecordset->GetCollect("cLanguade");
			m_List.SetItemText(iRowIndex, 3, (_bstr_t)strColumn[3]);

			strColumn[4] = m_pRecordset->GetCollect("javaLanguage");
			m_List.SetItemText(iRowIndex, 4, (_bstr_t)strColumn[4]);

			strColumn[5] = m_pRecordset->GetCollect("dateBase");
			m_List.SetItemText(iRowIndex, 5, (_bstr_t)strColumn[5]);

			strColumn[6] = m_pRecordset->GetCollect("gradeAverage");
			m_List.SetItemText(iRowIndex, 6, (_bstr_t)strColumn[6]);

			iRowIndex++;		//行下标＋1
			m_pRecordset->MoveNext();		//遍历下一行
		}
		m_pRecordset->Close();		//关闭
		m_pConnection->Close();
		m_pRecordset = NULL;		//释放清空
		m_pConnection = NULL;		//清空连接

	}
}

//修改学生成绩
void TeacherView::OnBnClickedButtonchange()
{
	// TODO: 在此添加控件通知处理程序代码
	TeacherChange dlg;

	int flag = 0;
	for (int i = 0; i < m_List.GetItemCount(); i++)		//只能有一组被选中
	{
		if (m_List.GetCheck(i))
		{
			flag++;
		}
	}
	if (flag != 1)
	{
		MessageBox(_T("请选择一组数据修改"));
		return;
	}

	for (int i = 0; i < m_List.GetItemCount(); i++)
	{
		if (m_List.GetCheck(i))		//真的被选中,从文本框像全局变量传数据
		{
			dlg.id = m_List.GetItemText(i, 0);		//第i行第0列
			dlg.sID = m_List.GetItemText(i, 1);
			dlg.sName = m_List.GetItemText(i, 2);
			dlg.sCL = m_List.GetItemText(i, 3);
			dlg.sJavaL = m_List.GetItemText(i, 4);
			dlg.sDate = m_List.GetItemText(i, 5);
			dlg.sAver = m_List.GetItemText(i, 6);
		}
	}
	dlg.DoModal();		//可弹窗
	m_List.DeleteAllItems();

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


		//stSql.Format(_T("SELECT * FROM Employee where LoginName = '%s' and LoginPassword = '%s'"), strUserName, strUserPwd);
		stSql.Format(_T("SELECT * FROM StudentGrade"));
		m_pRecordset->Open((LPCTSTR)stSql, m_pConnection.GetInterfacePtr(), adOpenStatic, adLockOptimistic, adCmdText);
	}

	CString strColumn[7];		//字符串数组用来存储一行的4个内容
	int iRowIndex = 0;		//行下标初始化为0
	while (!m_pRecordset->adoEOF)		//结果集是否指向最后一行（BOF开始，EOF结束）
	{
		strColumn[0] = m_pRecordset->GetCollect("id");		//从数据库拿id的值存在数组里
		m_List.InsertItem(iRowIndex, strColumn[0]);		//插入新的行 数组中的值给m_List中行下表为0，列下标为0的格

		strColumn[1] = m_pRecordset->GetCollect("studentID");		//数组中的值给m_List中行下表为0，列下标为1的格
		m_List.SetItemText(iRowIndex, 1, (_bstr_t)strColumn[1]);		//设置第2列 第3列...  _bstr_t：从ado取出来放在mfc中做转换

		strColumn[2] = m_pRecordset->GetCollect("studentName");
		m_List.SetItemText(iRowIndex, 2, (_bstr_t)strColumn[2]);

		strColumn[3] = m_pRecordset->GetCollect("cLanguade");
		m_List.SetItemText(iRowIndex, 3, (_bstr_t)strColumn[3]);

		strColumn[4] = m_pRecordset->GetCollect("javaLanguage");
		m_List.SetItemText(iRowIndex, 4, (_bstr_t)strColumn[4]);

		strColumn[5] = m_pRecordset->GetCollect("dateBase");
		m_List.SetItemText(iRowIndex, 5, (_bstr_t)strColumn[5]);

		strColumn[6] = m_pRecordset->GetCollect("gradeAverage");
		m_List.SetItemText(iRowIndex, 6, (_bstr_t)strColumn[6]);

		iRowIndex++;		//行下标＋1
		m_pRecordset->MoveNext();		//遍历下一行
	}
	m_pRecordset->Close();		//关闭
	m_pConnection->Close();
	m_pRecordset = NULL;		//释放清空
}

//查询学生成绩
void TeacherView::OnBnClickedButtoncheck()
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

		stSql.Format(_T("SELECT * FROM StudentGrade WHERE  studentID = '%s' "), dlg.sAccount);
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

//正序排序
void TeacherView::OnBnClickedButton1()
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
	CString strColumn[7];		//字符串数组用来存储一行的4个内容
	int iRowIndex = 0;		//行下标初始化为0
	while (!m_pRecordset->adoEOF)		//结果集是否指向最后一行（BOF开始，EOF结束）
	{
		strColumn[0] = m_pRecordset->GetCollect("id");		//从数据库拿id的值存在数组里
		m_List.InsertItem(iRowIndex, strColumn[0]);		//插入新的行 数组中的值给m_List中行下表为0，列下标为0的格

		strColumn[1] = m_pRecordset->GetCollect("studentID");		//数组中的值给m_List中行下表为0，列下标为1的格
		m_List.SetItemText(iRowIndex, 1, (_bstr_t)strColumn[1]);		//设置第2列 第3列...  _bstr_t：从ado取出来放在mfc中做转换

		strColumn[2] = m_pRecordset->GetCollect("studentName");
		m_List.SetItemText(iRowIndex, 2, (_bstr_t)strColumn[2]);

		strColumn[3] = m_pRecordset->GetCollect("cLanguade");
		m_List.SetItemText(iRowIndex, 3, (_bstr_t)strColumn[3]);

		strColumn[4] = m_pRecordset->GetCollect("javaLanguage");
		m_List.SetItemText(iRowIndex, 4, (_bstr_t)strColumn[4]);

		strColumn[5] = m_pRecordset->GetCollect("dateBase");
		m_List.SetItemText(iRowIndex, 5, (_bstr_t)strColumn[5]);

		strColumn[6] = m_pRecordset->GetCollect("gradeAverage");
		m_List.SetItemText(iRowIndex, 6, (_bstr_t)strColumn[6]);

		iRowIndex++;		//行下标＋1
		m_pRecordset->MoveNext();		//遍历下一行
	}
	m_pRecordset->Close();		//关闭
	m_pConnection->Close();
	m_pRecordset = NULL;		//释放清空



}

//倒序排序
void TeacherView::OnBnClickedButton2()
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
	CString strColumn[7];		//字符串数组用来存储一行的4个内容
	int iRowIndex = 0;		//行下标初始化为0
	while (!m_pRecordset->adoEOF)		//结果集是否指向最后一行（BOF开始，EOF结束）
	{
		strColumn[0] = m_pRecordset->GetCollect("id");		//从数据库拿id的值存在数组里
		m_List.InsertItem(iRowIndex, strColumn[0]);		//插入新的行 数组中的值给m_List中行下表为0，列下标为0的格

		strColumn[1] = m_pRecordset->GetCollect("studentID");		//数组中的值给m_List中行下表为0，列下标为1的格
		m_List.SetItemText(iRowIndex, 1, (_bstr_t)strColumn[1]);		//设置第2列 第3列...  _bstr_t：从ado取出来放在mfc中做转换

		strColumn[2] = m_pRecordset->GetCollect("studentName");
		m_List.SetItemText(iRowIndex, 2, (_bstr_t)strColumn[2]);

		strColumn[3] = m_pRecordset->GetCollect("cLanguade");
		m_List.SetItemText(iRowIndex, 3, (_bstr_t)strColumn[3]);

		strColumn[4] = m_pRecordset->GetCollect("javaLanguage");
		m_List.SetItemText(iRowIndex, 4, (_bstr_t)strColumn[4]);

		strColumn[5] = m_pRecordset->GetCollect("dateBase");
		m_List.SetItemText(iRowIndex, 5, (_bstr_t)strColumn[5]);

		strColumn[6] = m_pRecordset->GetCollect("gradeAverage");
		m_List.SetItemText(iRowIndex, 6, (_bstr_t)strColumn[6]);

		iRowIndex++;		//行下标＋1
		m_pRecordset->MoveNext();		//遍历下一行
	}
	m_pRecordset->Close();		//关闭
	m_pConnection->Close();
	m_pRecordset = NULL;		//释放清空


}
