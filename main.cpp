//头文件的include
#include <iostream>
#include <fstream>
#include "BankAccount.h"
#include <conio.h>
#include <algorithm>
#include <map>
#include <iomanip>
#include <locale>
#include <windows.h>
#include <sstream> 

//实现按中文拼音比较
//这段我不懂,别问我
#ifdef _MSC_VER
static const char* ZH_CN_LOCALE_STRING = "Chinese_china";
#else
static const char* ZH_CN_LOCALE_STRING = "zh_CN.utf8";
#endif
static const std::locale zh_CN_locale = std::locale(ZH_CN_LOCALE_STRING);
static const std::collate<char>& zh_CN_collate = std::use_facet<std::collate<char> >(zh_CN_locale);

//管理员账号密码
const std::string AdministratorAccount = "root";
const std::string AdministratorPassword = "root";

//创建别名
using ListNode = struct ListNode;
using LinkList = ListNode*;
using DoubleLinkList = std::pair<LinkList, LinkList>;

struct ListNode//双向链表
{
	//数据域
	BankAccount date;
	//指针域
	LinkList prev = nullptr;//声明初始化
	LinkList next = nullptr;
};


//常用的std命名空间的成员的引入,前期没写,后来真的不想写std::了,加上了这些
using std::cin;
using std::cout;
using std::endl;
using std::string;
/************************系统操作相关函数****************************/

//创建链表
DoubleLinkList CreateList();

//欢迎语
int Welcome();

//结束语
void Exit(DoubleLinkList AccList);

//从文件读入账户信息
void ReadFromFile1(DoubleLinkList AccList);

//从文件读入存取款信息
void ReadFromFile2(DoubleLinkList AccList);

//从文件读入转账信息
void ReadFromFile3(DoubleLinkList AccList);

//保存账户信息
void SaveToFile1(LinkList AccList);

//保存存取款信息
void SaveToFile2(LinkList AccList);

//保存
void SaveToFile3(LinkList AccList);

/************************系统操作相关函数****************************/

/************************用户操作相关函数****************************/

//普通用户操作界面
void UserInterface(DoubleLinkList AccList);

//判断账号是否存在
bool CheckAccount(LinkList AccList, const std::string& InAccount);

//判断密码是否正确
bool CheckPassword(LinkList AccList, const std::string& InAccount, const std::string& InPassword);

//判断账号和密码是否照应
bool CheckAccountName(LinkList AccList, const std::string& InAccount, const std::string& InName);

//初始化map<string,int>映射
void MapInitialization(LinkList AccList, std::map<std::string, int>& TemWrongPassword);

//查询并输出余额
void QueryPrintDeposit(LinkList AccList, const std::string& InAccount);

//存款操作
void TakeInDeposit(LinkList AccList, const std::string& InAccount);

//取款操作
void TakeOutDeposit(LinkList AccList, const std::string& InAccount);

//转账操作
void GiveOtherDeposit(LinkList AccList, const std::string& InAccount);

//用户修改密码
void UserChangePassword(LinkList AccList, const std::string& InAccount);

/************************用户操作相关函数****************************/

/************************管理员操作相关函数****************************/

//管理员操作界面
void AdministratorInterface(DoubleLinkList AccList);

//查询流水
void QueryFlowingWater(LinkList AccList, const std::string& InAccount);

//创建用户账号
void CreateUserAccount(DoubleLinkList AccList);

//删除用户账号
void DeleteUserAccount(LinkList AccList);

//展示用户信息
void ShowAllUsersInformation(LinkList AccList);

//按账号降序排序(选择排序)
void UsersAccountDown(LinkList AccList);

//按账号升序排序(选择排序)
void UsersAccountUp(LinkList AccList);

//按存款降序排序(选择排序)
void UsersDepositDown(LinkList AccList);

//按存款升序排序(选择排序)
void UsersDepositUp(LinkList AccList);

//按姓名全拼降序排序(选择排序)
void UsersNameDown(LinkList AccList);

//按姓名全拼升序排序(选择排序)
void UsersNameUp(LinkList AccList);

//查找用户信息
void FindUserInformation(LinkList AccList);

//修改用户信息
void ChangeUserInformation(LinkList AccList);

//单条件查找
void SingleConditionSearch(LinkList AccList);

//按性别查找用户
void GenderSearch(LinkList AccList);

//按姓名查找用户
void NameSearch(LinkList AccList);

//按手机号查找用户
void TelSearch(LinkList AccList);

//按存款查找用户
void DepositSearch(LinkList AccList);

//查找存款小于某数的用户
void SearchLowerThanDeposit(LinkList AccList, const double& AfferentDeposit);

//查找存款大于等于某数的用户
void SearchUpperThanDeposit(LinkList AccList, const double& AfferentDeposit);

//模糊查找
void FuzzySearch(LinkList AccList);

//按姓氏查找用户
void SearchAsSurname(LinkList AccList);

//按姓名关键词查找用户
void SearchAsKeyWord(LinkList AccList);

//按手机号前三位查找用户
void SearchAsTelTopThree(LinkList AccList);

//按手机号后四位查找用户
void SearchAsTelLastFour(LinkList AccList);

//统计呐呐呐银行信息
void StatisticalInformation(LinkList AccList);

//查看用户账单
void SeeUserBill(LinkList AccList);

//查看存取款账单
void DepositInOutBill(LinkList AccList, const std::string& InAccount);

//查看转账账单
void DepositChangeBill(LinkList AccList, const std::string& InAccount);

/************************管理员操作相关函数****************************/

//主函数
int main()
{
	DoubleLinkList AccList = CreateList();//创建链表
	ReadFromFile1(AccList);//开始读文件
	ReadFromFile2(AccList);
	ReadFromFile3(AccList);
	while (int t = Welcome()) {//根据输入的n调用相关函数
		if (t == 3) {
			system("cls");
			Exit(AccList);
		}
		else if (t == 1) {
			system("cls");
			UserInterface(AccList);
		}
		else if (t == 2) {
			system("cls");
			AdministratorInterface(AccList);
		}
	}
}

DoubleLinkList CreateList()
{
	LinkList p = new ListNode;
	LinkList t = new ListNode;

	//在声明时已经把next和prev都初始化为了nullptr
	p->next = t;
	t->prev = p;
	return { p,t };//返回一个pair类型数据

}

void ReadFromFile1(DoubleLinkList AccList)
{
	LinkList p = AccList.second;
	std::ifstream in("AccountInformation.txt");//以ifstream默认方式打开文件

	if (!in.is_open())
		cout << "AccountInformation.txt文件打开失败" << endl;
	while (in.peek() != EOF) {//用peek而不是eof来防止多读入一个数据
		LinkList t = new ListNode;

		t->next = p;//双向链表尾插法插入结点
		t->prev = p->prev;
		p->prev->next = t;
		p->prev = t;

		in >> t->date;
	}
	in.close();//关闭
}

void ReadFromFile2(DoubleLinkList AccList)
{
	LinkList p = AccList.first->next;
	std::ifstream in("DepositChangeInformation.txt");

	if (!in.is_open())
		cout << "DepositChangeInformation.txt文件打开失败" << endl;
	while (p->next != nullptr) {//依次读入

		(p->date).DepositChangeData.resize((p->date).NumDepositChange);//设置vector的大小
		for (int i = 0; i < (p->date).NumDepositChange; i++) {//依次读入每条转账记录
			in >> (p->date).DepositChangeData[i].Money
				>> (p->date).DepositChangeData[i].CurrentDeposit
				>> (p->date).DepositChangeData[i].Time;
		}
		p = p->next;
	}
	in.close();
}

void ReadFromFile3(DoubleLinkList AccList)
{
	LinkList p = AccList.first->next;
	std::ifstream in("DepositInOutInformation.txt");

	if (!in.is_open())
		cout << "DepositInOutInformation.txt文件打开失败" << endl;
	while (p->next != nullptr) {
		(p->date).DepositInOutData.resize((p->date).NumDepositInOut);
		for (int i = 0; i < (p->date).NumDepositInOut; i++) {
			in >> (p->date).DepositInOutData[i].Money
				>> (p->date).DepositInOutData[i].CurrentDeposit
				>> (p->date).DepositInOutData[i].Time
				>> (p->date).DepositInOutData[i].OtherAccount;
		}
		p = p->next;
	}
	in.close();
}

void SaveToFile1(LinkList AccList)
{
	std::ofstream out("AccountInformation.txt");
	if (!out.is_open()) {
		cout << "AccountInformation.txt文件打开失败" << endl;
	}
	LinkList p = AccList->next;
	while (p->next != nullptr) {
		out << p->date;
		p = p->next;
	}
	out.close();
}

void SaveToFile2(LinkList AccList)
{
	LinkList p = AccList->next;
	std::ofstream out("DepositChangeInformation.txt");
	if (!out.is_open()) {
		cout << "DepositChangeInformation.txt文件打开失败" << endl;
	}
	while (p->next != nullptr) {
		for (int i = 0; i < (p->date).NumDepositChange; i++) {//记得用空格和回车分开
			out << (p->date).DepositChangeData[i].Money << " "
				<< (p->date).DepositChangeData[i].CurrentDeposit << " "
				<< (p->date).DepositChangeData[i].Time
				<< endl;
		}
		p = p->next;
	}
	out.close();
}
void SaveToFile3(LinkList AccList)
{

	LinkList p = AccList->next;
	std::ofstream out("DepositInOutInformation.txt");
	if (!out.is_open()) {
		cout << "DepositInOutInformation.txt文件打开失败" << endl;
	}
	while (p->next != nullptr) {

		for (int i = 0; i < (p->date).NumDepositInOut; i++) {
			out << (p->date).DepositInOutData[i].Money << " "
				<< (p->date).DepositInOutData[i].CurrentDeposit << " "
				<< (p->date).DepositInOutData[i].Time << " "
				<< (p->date).DepositInOutData[i].OtherAccount
				<< endl;
		}
		p = p->next;
	}
	out.close();
}

int Welcome()
{
	std::cout << "欢迎使用呐呐呐ATM机管理系统\n"
		<< "请选择相应的按钮,按回车键结束\n"
		<< "----------[1] 用户登录----------\n"
		<< "----------[2] 管理员登录--------\n"
		<< "----------[3] 退出--------------"
		<< std::endl;
	int n;
	std::cin >> n;
	return n;
}

void Exit(DoubleLinkList AccList)
{
	LinkList p = AccList.first;
	LinkList t = p->next;
	while (p != nullptr) {//依次删除
		t = p->next;
		delete p;
		p = t;
	}

	std::cout << "----------欢迎下次使用----------" << std::endl;
	exit(0);
}

void UserInterface(DoubleLinkList AccList)
{
	std::map<std::string, int> WrongPassword;//建立一个记录账号密码错误次数的map
	MapInitialization(AccList.first, WrongPassword);//初始化
	std::string TemAccount = "", TemPassword = "";

	while (true) {//这里必须得输对账号密码,不然死循环

		TemAccount = "", TemPassword = "";
		std::cout << "请输入账号" << std::endl;
		std::cin >> TemAccount;
		//std::cin.ignore();
		if (CheckAccount(AccList.first, TemAccount) == false) {
			system("cls");
			std::cout << "账号错误,请重新输入" << std::endl;
			continue;
		}
		if (WrongPassword[TemAccount] >= 3) {//密码错误超过三次
			system("cls");
			std::cout << "该账号已锁定" << std::endl;
			continue;
		}

		system("cls");
		cout << "账号正确" << endl;
		std::cout << "请输入密码,三次错误账号将被锁定" << std::endl;
		char ch;

		//_getch()函数作用,从控制台获得一个字符,但并不回显,同时windows平台下的回车的表示时'\r\n',输入回车时ch表示的字符时'\r',结束循环

		while (ch = _getch(), ch != '\r') {
			if (ch == '\b') {//如果按下了Backspase键
				if (TemPassword.size()) {//屏幕上现有的'*'字符可以用当前密码的长度表示
					putchar('\b');//退格
					putchar(' ');//打印空格覆盖原'*'
					putchar('\b');//再退格
				}
				if (TemPassword.size())
					TemPassword.erase(TemPassword.size() - 1, 1);//更新当前密码

			}
			else {//若为其他键
				TemPassword = TemPassword + ch;//更新密码
				putchar('*');//屏幕显示*
			}
		}
		std::cout << std::endl;
		if (CheckPassword(AccList.first, TemAccount, TemPassword) == false) {//判断密码是否正确

			system("cls");
			std::cout << "密码错误,请重新输入" << std::endl;
			WrongPassword[TemAccount] = WrongPassword[TemAccount] + 1;//已输入错误密码次数加一
			continue;
		}
		else {
			system("cls");
			std::cout << "密码正确,登陆成功" << std::endl;
			break;
		}
		//std::cout << TemAccount << std::endl << TemPassword << std::endl;
	}

	while (true) {//菜单界面
		std::cout << "请选择相应的按钮,按回车键结束\n" << "[1] 查询余额\n" << "[2] 存款\n" << "[3] 取款\n" << "[4] 转账\n" << "[5] 修改密码\n" << "[6] 查询流水\n" << "[7] 退卡\n" << std::endl;
		int n;
		std::cin >> n;
		if (n == 1) {
			system("cls");
			QueryPrintDeposit(AccList.first, TemAccount);
			system("pause");
			system("cls");
		}
		else if (n == 2) {//信息发生改变,保存文件
			system("cls");
			TakeInDeposit(AccList.first, TemAccount);
			SaveToFile1(AccList.first);
			SaveToFile2(AccList.first);
			SaveToFile3(AccList.first);
			system("pause");
			system("cls");

		}
		else if (n == 3) {//信息发生改变,保存文件
			system("cls");
			TakeOutDeposit(AccList.first, TemAccount);
			SaveToFile1(AccList.first);
			SaveToFile2(AccList.first);
			SaveToFile3(AccList.first);
			system("pause");
			system("cls");


		}
		else if (n == 4) {//信息发生改变,保存文件
			system("cls");
			GiveOtherDeposit(AccList.first, TemAccount);
			SaveToFile1(AccList.first);
			SaveToFile2(AccList.first);
			SaveToFile3(AccList.first);
			system("pause");
			system("cls");


		}
		else if (n == 5) {//信息发生改变,保存文件
			system("cls");
			UserChangePassword(AccList.first, TemAccount);
			SaveToFile1(AccList.first);
			SaveToFile2(AccList.first);
			SaveToFile3(AccList.first);
			system("pause");
			system("cls");

		}
		else if (n == 6) {
			system("cls");
			QueryFlowingWater(AccList.first, TemAccount);
			system("pause");
			system("cls");

		}
		else if (n == 7) {
			system("cls");
			Exit(AccList);
			return;
		}
		else {
			system("cls");
		}
	}

}
bool CheckAccount(LinkList AccList, const std::string& InAccount)
{
	LinkList Temp = AccList->next;
	while (Temp->next != nullptr) {//未到达尾节点,线性查找
		if ((Temp->date).GetMyAccount() == InAccount)//找到了此账号
			return true;
		Temp = Temp->next;
	}
	return false;
}
bool CheckPassword(LinkList AccList, const std::string& InAccount, const std::string& InPassword)
{
	LinkList Temp = AccList->next;
	while (Temp->next != nullptr) {//未到达尾节点,线性查找
		if ((Temp->date).GetMyAccount() == InAccount && (Temp->date).GetMyPassword() == InPassword)//找到了此账号同时密码正确
			return true;
		Temp = Temp->next;
	}
	return false;
}

bool CheckAccountName(LinkList AccList, const std::string& InAccount, const std::string& InName)
{
	LinkList Temp = AccList->next;
	while (Temp->next != nullptr) {//未到达尾节点,线性查找
		if ((Temp->date).GetMyAccount() == InAccount && (Temp->date).GetMyName() == InName)//找到了此账号同时密码正确
			return true;
		Temp = Temp->next;
	}
	return false;
}

void MapInitialization(LinkList AccList, std::map<std::string, int>& TemWrongPassword)//使用引用类型以修改实参
{
	LinkList p = AccList->next;
	while (p->next != nullptr) {//遍历
		TemWrongPassword.insert(std::make_pair((p->date).GetMyAccount(), 0));//每次向map中插入pair<账号,0>
		p = p->next;
	}
}
void QueryPrintDeposit(LinkList AccList, const std::string& InAccount)
{
	LinkList p = AccList->next;
	while (p->next != nullptr) {
		if (InAccount == (p->date).GetMyAccount()) {
			std::cout << "余额为 " << std::fixed << std::setprecision(2) << (p->date).GetMyDeposit() << std::endl;
			break;
		}
		p = p->next;

	}
}
void TakeInDeposit(LinkList AccList, const std::string& InAccount)
{
	int money;
	while (true) {

		system("cls");
		std::cout << "请输入存款金额(100整数倍),不多于5000" << std::endl;
		std::cin >> money;
		if (money % 100 || money <= 0 || money > 5000) {//判断存款金额是否合法
			cout << "存款金额有误,请重新输入" << endl;
		}
		else
			break;
	}

	LinkList p = AccList->next;
	while (p->next != nullptr) {
		if (InAccount == (p->date).GetMyAccount()) {
			(p->date).ModifyDeposit(money);
			//修改该账号存取款数据
			(p->date).DepositChangeData.push_back(NumDepositChangeNode(money, (p->date).GetMyDeposit()));//vector添加数据
			(p->date).NumDepositChange++;//流水项数加一
			SYSTEMTIME sys;//windowsAPI获取时间并将其转化为字符串格式
			GetLocalTime(&sys);
			char TemTime[100];
			sprintf(TemTime, "%4d/%02d/%02d/%02d:%02d:%02d", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond);
			(p->date).DepositChangeData[(p->date).NumDepositChange - 1].Time = TemTime;
			break;

		}
		p = p->next;

	}
	//SaveToFile(AccList);
	std::cout << "是否打印凭条\t\t[1]是\t[2]否" << std::endl;
	int n;
	std::cin >> n;
	system("cls");
	if (n == 1) {//使用print格式控制符输出较优
		SYSTEMTIME sys;//windowsAPI获取时间
		GetLocalTime(&sys);
		printf("\n----------------------------------------\n");
		printf("|               存款凭条               |\n");
		printf("|--------------------------------------|\n");
		printf("|                                      |\n");
		printf("|存款账号:%-29s|\n", InAccount.c_str());
		printf("|存款金额:%-29d|\n", money);
		printf("|存款时间:%4d/%02d/%02d %02d:%02d:%02d          |\n", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond);
		printf("|                                      |\n");
		printf("----------------------------------------\n\n");
		printf("凭条打印完成\n");
	}
	else if (n == 2) {//啥都不做

	}

}
void TakeOutDeposit(LinkList AccList, const std::string& InAccount)
{
	int n;
	int money = 0;
	std::cout << "请选择取款金额\n" << "[1] 100\t" << "[2] 200\n" << "[3] 500\t" << "[4] 1000\n" << "[5] 2000" << "[6] 其他金额" << std::endl;
	std::cin >> n;

	system("cls");
	if (n == 1) money = 100;
	else if (n == 2) money = 200;
	else if (n == 3) money = 500;
	else if (n == 4) money = 1000;
	else if (n == 5) money = 2000;
	else if (n == 6) {
		while (true) {
			std::cout << "请输入取款金额(100整数倍),不多于5000" << std::endl;
			std::cin >> money;
			system("cls");
			if (money % 100 || money <= 0 || money > 5000) {//判断取款金额是否合法
				cout << "取款金额有误,请重新输入" << endl;
			}
			else
				break;
		}
	}

	LinkList p = AccList->next;
	while (p->next != nullptr) {
		if (InAccount == (p->date).GetMyAccount()) {
			if ((p->date).GetMyDeposit() < money) {//判断钱够不够
				cout << "余额不足" << endl;
				return;
			}
			(p->date).ModifyDeposit(-money);
			//继续修改存取款数据
			(p->date).DepositChangeData.push_back(NumDepositChangeNode(-money, (p->date).GetMyDeposit()));
			(p->date).NumDepositChange++;
			SYSTEMTIME sys;//windowsAPI获取时间
			GetLocalTime(&sys);
			char TemTime[100];
			sprintf(TemTime, "%4d/%02d/%02d/%02d:%02d:%02d", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond);
			(p->date).DepositChangeData[(p->date).NumDepositChange - 1].Time = TemTime;
			break;
		}
		p = p->next;

	}

	//SaveToFile(AccList);

	cout << "是否打印凭条\t\t[1]是\t[2]否" << endl;
	cin >> n;

	system("cls");
	if (n == 1) {//使用print格式控制符输出较优
		SYSTEMTIME sys;//windowsAPI获取时间
		GetLocalTime(&sys);
		printf("\n----------------------------------------\n");
		printf("|               取款凭条               |\n");
		printf("|--------------------------------------|\n");
		printf("|                                      |\n");
		printf("|取款账号:%-29s|\n", InAccount.c_str());
		printf("|取款金额:%-29d|\n", money);
		printf("|取款时间:%4d/%02d/%02d %02d:%02d:%02d          |\n", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond);
		printf("|                                      |\n");
		printf("----------------------------------------\n\n");
		printf("凭条打印完成\n");
	}
	else if (n == 2) {

	}
}
void GiveOtherDeposit(LinkList AccList, const std::string& InAccount)
{
	string TurnOutAccount = "", TurnOutName = "";
	while (true) {

		cout << "请输入转账账号" << endl;
		cin >> TurnOutAccount;
		system("cls");
		if (TurnOutAccount == InAccount) {//转账合法性判断
			cout << "不能向自己转账,请重新输入" << endl;
			continue;
		}
		if (CheckAccount(AccList, TurnOutAccount) == false) {//没找到
			cout << "查无此账号,请重新输入" << endl;
		}
		else {
			break;
		}
	}

	cout << "请输入转账人姓名" << endl;
	cin >> TurnOutName;
	system("cls");
	if (CheckAccountName(AccList, TurnOutAccount, TurnOutName) == false) {//转账合法性判断
		cout << "账号和姓名不匹配" << endl;
		return;
	}

	int n;
	int money = 0;
	std::cout << "请选择转账金额\n" << "[1] 100\t\t" << "[2] 200\n" << "[3] 500\t\t" << "[4] 1000\n" << "[5] 2000\t" << "[6] 其他金额" << std::endl;

	std::cin >> n;
	system("cls");
	if (n == 1) money = 100;
	else if (n == 2) money = 200;
	else if (n == 3) money = 500;
	else if (n == 4) money = 1000;
	else if (n == 5) money = 2000;
	else if (n == 6) {
		while (true) {
			std::cout << "请输入转账金额(100整数倍),不多于5000" << std::endl;
			std::cin >> money;
			system("cls");
			if (money % 100 || money <= 0 || money > 5000) {//判断取款金额是否合法
				cout << "转账金额有误,请重新输入" << endl;
			}
			else
				break;
		}
	}

	LinkList p = AccList->next;
	while (p->next != nullptr) {//先在自己账户扣款
		if (InAccount == (p->date).GetMyAccount()) {
			if ((p->date).GetMyDeposit() < money) {//判断存款够不够
				cout << "余额不足" << endl;
				return;
			}
			/*钱够*/
			(p->date).ModifyDeposit(-money);

			(p->date).DepositInOutData.push_back(NumDepositInOutNode(-money, (p->date).GetMyDeposit(), TurnOutAccount));//较存取款多一个参数,为的是记录转账的另一个账号
			(p->date).NumDepositInOut++;
			SYSTEMTIME sys;//windowsAPI获取时间
			GetLocalTime(&sys);
			char TemTime[100];
			sprintf(TemTime, "%4d/%02d/%02d/%02d:%02d:%02d", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond);
			(p->date).DepositInOutData[(p->date).NumDepositInOut - 1].Time = TemTime;

			break;
		}
		p = p->next;

	}

	p = AccList->next;
	while (p->next != nullptr) {
		if (TurnOutAccount == (p->date).GetMyAccount()) {
			(p->date).ModifyDeposit(money);

			(p->date).DepositInOutData.push_back(NumDepositInOutNode(money, (p->date).GetMyDeposit(), InAccount));//收钱的对象也得有转账数据,加钱了
			(p->date).NumDepositInOut++;
			SYSTEMTIME sys;//windowsAPI获取时间
			GetLocalTime(&sys);
			char TemTime[100];
			sprintf(TemTime, "%4d/%02d/%02d/%02d:%02d:%02d", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond);
			(p->date).DepositInOutData[(p->date).NumDepositInOut - 1].Time = TemTime;

			break;
		}
		p = p->next;
	}

	//SaveToFile(AccList);

	cout << "是否打印凭条\t\t[1]是\t[2]否" << endl;
	cin >> n;
	system("cls");
	if (n == 1) {//使用print格式控制符输出较优
		SYSTEMTIME sys;//windowsAPI获取时间
		GetLocalTime(&sys);
		printf("\n----------------------------------------\n");
		printf("|               转账凭条               |\n");
		printf("|--------------------------------------|\n");
		printf("|                                      |\n");
		printf("|转出账号:%-29s|\n", InAccount.c_str());
		printf("|转入账号:%-29s|\n", TurnOutAccount.c_str());
		printf("|转账金额:%-29d|\n", money);
		printf("|转账时间:%4d/%02d/%02d %02d:%02d:%02d          |\n", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond);
		printf("|                                      |\n");
		printf("----------------------------------------\n\n");
		printf("凭条打印完成\n");
	}
	else if (n == 2) {

	}


}

void UserChangePassword(LinkList AccList, const std::string& InAccount)
{
	string TemPassword = "", NewPassword = "", SureNewPassword = "";
	cout << "请输入原密码" << endl;

	char ch;
	while (ch = _getch(), ch != '\r') {
		if (ch == '\b') {
			if (TemPassword.size()) {
				putchar('\b');
				putchar(' ');
				putchar('\b');
			}
			if (TemPassword.size())
				TemPassword.erase(TemPassword.size() - 1, 1);

		}
		else {
			TemPassword = TemPassword + ch;
			putchar('*');
		}

	}
	cout << endl;
	system("cls");

	if (CheckPassword(AccList, InAccount, TemPassword) == false) {
		cout << "密码错误" << endl;
		return;
	}

	cout << "请输入新密码" << endl;
	while (ch = _getch(), ch != '\r') {
		if (ch == '\b') {
			if (NewPassword.size()) {
				putchar('\b');
				putchar(' ');
				putchar('\b');
			}
			if (NewPassword.size())
				NewPassword.erase(NewPassword.size() - 1, 1);

		}
		else {
			NewPassword = NewPassword + ch;
			putchar('*');
		}
	}
	cout << endl;

	system("cls");

	if (TemPassword == NewPassword) {
		cout << "新密码和原密码相同" << endl;
		return;
	}

	cout << "请再次输入新密码" << endl;

	while (ch = _getch(), ch != '\r') {
		if (ch == '\b') {
			if (SureNewPassword.size()) {
				putchar('\b');
				putchar(' ');
				putchar('\b');
			}
			if (SureNewPassword.size())
				SureNewPassword.erase(SureNewPassword.size() - 1, 1);

		}
		else {
			SureNewPassword = SureNewPassword + ch;
			putchar('*');
		}
	}
	cout << endl;

	system("cls");
	if (SureNewPassword == NewPassword) {//二次判断成功后才可以改
		LinkList p = AccList->next;
		while (p->next != nullptr) {
			if ((p->date).GetMyAccount() == InAccount) {
				(p->date).SetPassword(NewPassword);
				cout << "密码修改成功" << endl;
				return;
			}
			p = p->next;
		}
	}
	else {
		cout << "两次输入密码不一致" << endl;
		return;
	}
}

void AdministratorInterface(DoubleLinkList AccList)
{

	std::string TemAccount = "", TemPassword = "";
	while (true) {
		TemAccount = "", TemPassword = "";
		std::cout << "请输入账号" << std::endl;
		std::cin >> TemAccount;
		system("cls");
		//std::cin.ignore();
		if (TemAccount != AdministratorAccount) {
			std::cout << "账号错误,请重新输入" << std::endl;
			continue;
		}
		system("cls");
		std::cout << "请输入密码" << std::endl;

		char ch;
		while (ch = _getch(), ch != '\r') {
			if (ch == '\b') {
				if (TemPassword.size()) {
					putchar('\b');
					putchar(' ');
					putchar('\b');
				}
				if (TemPassword.size())
					TemPassword.erase(TemPassword.size() - 1, 1);

			}
			else {
				TemPassword = TemPassword + ch;
				putchar('*');
			}
		}
		std::cout << std::endl;
		system("cls");
		if (TemPassword != AdministratorPassword) {
			std::cout << "密码错误,请重新输入" << std::endl;
		}
		else {
			std::cout << "密码正确,登陆成功" << std::endl;
			break;
		}
		//std::cout << TemAccount << std::endl << TemPassword << std::endl;
	}

	int n;
	while (true) {//管理员菜单界面

		cout << "[1] 创建用户账户\n"
			<< "[2] 删除用户账户\n"
			<< "[3] 查看全部用户信息\n"
			<< "[4] 查找用户信息\n"
			<< "[5] 修改用户信息\n"
			<< "[6] 单条件查找\n"
			<< "[7] 模糊查找\n"
			<< "[8] 统计信息\n"
			<< "[9] 查看用户流水\n"
			<< "[10] 退出"
			<< endl;
		cin >> n;
		if (n == 1) {//用户信息改变,保存文件

			system("cls");
			CreateUserAccount(AccList);
			SaveToFile1(AccList.first);
			SaveToFile2(AccList.first);
			SaveToFile3(AccList.first);
			system("pause");
			system("cls");
		}
		else if (n == 2) {//用户信息改变,保存文件
			system("cls");
			DeleteUserAccount(AccList.first);
			SaveToFile1(AccList.first);
			SaveToFile2(AccList.first);
			SaveToFile3(AccList.first);
			system("pause");

			system("cls");
		}
		else if (n == 3) {
			system("cls");
			ShowAllUsersInformation(AccList.first);
			system("pause");

			system("cls");
		}
		else if (n == 4) {
			system("cls");
			FindUserInformation(AccList.first);
			system("pause");

			system("cls");
		}
		else if (n == 5) {//用户信息改变,保存文件
			system("cls");
			ChangeUserInformation(AccList.first);
			SaveToFile1(AccList.first);
			SaveToFile2(AccList.first);
			SaveToFile3(AccList.first);
			system("pause");

			system("cls");
		}
		else if (n == 6) {
			system("cls");
			SingleConditionSearch(AccList.first);
			system("pause");

			system("cls");
		}
		else if (n == 7) {
			system("cls");
			FuzzySearch(AccList.first);
			system("pause");

			system("cls");
		}
		else if (n == 8) {
			system("cls");

			StatisticalInformation(AccList.first);
			system("pause");

			system("cls");

		}
		else if (n == 9) {
			system("cls");

			SeeUserBill(AccList.first);
			system("pause");

			system("cls");

		}
		else if (n == 10) {
			system("cls");

			Exit(AccList);
			return;
		}
		else {
			system("cls");
		}
	}
}
void CreateUserAccount(DoubleLinkList AccList)//传入的是头尾指针
{
	cout << "请依次输入 账号 密码 姓名 性别(01表示) 手机号" << endl;
	LinkList t = new ListNode;
	cin >> t->date;
	system("cls");

	if (CheckAccount(AccList.first, (t->date).GetMyAccount()) == true) {//先判断这账号是否已经存在
		cout << "该账号已存在,创建失败" << endl;
		delete t;
		return;
	}
	t->next = AccList.second;//双向链表尾插
	t->prev = AccList.second->prev;
	AccList.second->prev->next = t;
	AccList.second->prev = t;
	cout << "创建成功" << endl;

}
void DeleteUserAccount(LinkList AccList)
{

	string TemAccount = "";
	while (true) {//合法性判断
		cout << "请输入要删除的账号" << endl;
		cin >> TemAccount;
		system("cls");

		if (CheckAccount(AccList, TemAccount) == false) {
			cout << "账号不存在,请重新输入" << endl;
		}
		else {
			break;
		}
	}
	LinkList p = AccList->next;
	while (p->next != nullptr) {
		if ((p->date).GetMyAccount() == TemAccount) {//找到位置后退出
			break;
		}
		p = p->next;
	}
	p->prev->next = p->next;//双链表优点体现了
	p->next->prev = p->prev;
	delete p;//释放内存
	cout << "账号: " << TemAccount << " 已删除" << endl;

}
void ShowAllUsersInformation(LinkList AccList)
{
	int n;
	cout << "请选择您需要的展示方式" << endl;
	cout << "[1] 按账号降序排序" << endl;
	cout << "[2] 按账号升序排序" << endl;
	cout << "[3] 按存款降序排序" << endl;
	cout << "[4] 按存款升序排序" << endl;
	cout << "[5] 按姓名降序排序" << endl;
	cout << "[6] 按姓名升序排序" << endl;
	cin >> n;
	system("cls");

	//各种排序,都是选择排序
	if (n == 1) {
		UsersAccountDown(AccList);
	}
	else if (n == 2) {
		UsersAccountUp(AccList);
	}
	else if (n == 3) {
		UsersDepositDown(AccList);
	}
	else if (n == 4) {
		UsersDepositUp(AccList);
	}
	else if (n == 5) {
		UsersNameDown(AccList);
	}
	else if (n == 6) {
		UsersNameUp(AccList);
	}

	LinkList p = AccList->next;
	if (BankAccount::NumBankAccount > 2) {//要是链表不为空
		cout << std::left << std::setw(15) << "账号"
			<< std::left << std::setw(15) << "密码"
			<< std::left << std::setw(15) << "姓名"
			<< std::left << std::setw(15) << "性别"
			<< std::left << std::setw(15) << "手机号"
			<< std::left << std::setw(15) << "余额"
			<< endl;
	}
	else if (BankAccount::NumBankAccount == 2) {
		cout << "无用户信息" << endl;
	}
	while (p->next != nullptr) {
		cout << p->date;
		p = p->next;
	}

}
void UsersAccountDown(LinkList AccList)
{
	LinkList i = nullptr;
	LinkList j = nullptr;
	for (i = AccList->next; i->next != nullptr; i = i->next) {
		for (j = i->next; j->next != nullptr; j = j->next) {
			if ((j->date).GetMyAccount() > (i->date).GetMyAccount()) {//没啥,六个函数都是这么写的
				std::swap(i->date, j->date);
			}

		}
	}
}
void UsersAccountUp(LinkList AccList)
{
	LinkList i = nullptr;
	LinkList j = nullptr;
	for (i = AccList->next; i->next != nullptr; i = i->next) {
		for (j = i->next; j->next != nullptr; j = j->next) {
			if ((j->date).GetMyAccount() < (i->date).GetMyAccount()) {
				std::swap(i->date, j->date);
			}

		}
	}
}
void UsersDepositDown(LinkList AccList)
{
	LinkList i = nullptr;
	LinkList j = nullptr;
	for (i = AccList->next; i->next != nullptr; i = i->next) {
		for (j = i->next; j->next != nullptr; j = j->next) {
			if ((j->date).GetMyDeposit() > (i->date).GetMyDeposit()) {
				std::swap(i->date, j->date);
			}

		}
	}
}
void UsersDepositUp(LinkList AccList)
{
	LinkList i = nullptr;
	LinkList j = nullptr;
	for (i = AccList->next; i->next != nullptr; i = i->next) {
		for (j = i->next; j->next != nullptr; j = j->next) {
			if ((j->date).GetMyDeposit() < (i->date).GetMyDeposit()) {
				std::swap(i->date, j->date);
			}

		}
	}
}
void UsersNameDown(LinkList AccList)
{
	LinkList i = nullptr;
	LinkList j = nullptr;
	for (i = AccList->next; i->next != nullptr; i = i->next) {
		for (j = i->next; j->next != nullptr; j = j->next) {
			char* s1 = new char[30];//申请内存来存放姓名
			char* s2 = new char[30];
			//string的c_str方法返回的是个临时指针,这条语句执行后就会变成个野指针,所以得用strcpy来复制到确定的位置
			strcpy(s1, (i->date).GetMyName().c_str());
			strcpy(s2, (j->date).GetMyName().c_str());
			if (zh_CN_collate.compare(s1, s1 + (i->date).GetMyName().size(), s2, s2 + (j->date).GetMyName().size()) < 0) {//这就涉及到我的知识盲区了,不过应该和strcmp差不多
				std::swap(i->date, j->date);
			}
			delete[]s1;//释放内存!!!
			delete[]s2;
		}
	}
}
void UsersNameUp(LinkList AccList)
{
	LinkList i = nullptr;
	LinkList j = nullptr;
	for (i = AccList->next; i->next != nullptr; i = i->next) {
		for (j = i->next; j->next != nullptr; j = j->next) {
			char* s1 = new char[30];
			char* s2 = new char[30];
			strcpy(s1, (i->date).GetMyName().c_str());
			strcpy(s2, (j->date).GetMyName().c_str());
			if (zh_CN_collate.compare(s1, s1 + (i->date).GetMyName().size(), s2, s2 + (j->date).GetMyName().size()) > 0) {
				std::swap(i->date, j->date);
			}
			delete[]s1;
			delete[]s2;
		}
	}
}
void FindUserInformation(LinkList AccList)
{
	string TemAccount = "";
	while (true) {
		cout << "请输入要查找的账号" << endl;
		cin >> TemAccount;
		system("cls");
		if (CheckAccount(AccList, TemAccount) == false) {
			cout << "账号不存在,请重新输入" << endl;
		}
		else {
			break;
		}
	}

	cout << std::left << std::setw(15) << "账号"
		<< std::left << std::setw(15) << "密码"
		<< std::left << std::setw(15) << "姓名"
		<< std::left << std::setw(15) << "性别"
		<< std::left << std::setw(15) << "手机号"
		<< std::left << std::setw(15) << "余额"
		<< endl;

	LinkList p = AccList->next;
	while (p->next != nullptr) {
		if ((p->date).GetMyAccount() == TemAccount) {
			cout << p->date;
			break;
		}
		p = p->next;
	}
}

void ChangeUserInformation(LinkList AccList)
{
	string TemAccount = "";

	while (true) {
		cout << "请输入需要修改的账号" << endl;
		cin >> TemAccount;
		system("cls");

		if (CheckAccount(AccList, TemAccount) == false) {
			cout << "账号不存在,请重新输入" << endl;
		}
		else {
			break;
		}
	}

	LinkList p = AccList->next;
	while (p->next != nullptr) {
		if ((p->date).GetMyAccount() == TemAccount) {//找到地址
			break;
		}
		p = p->next;
	}

	int n;
	cout << "请选择修改的信息\n"
		<< "[1] 密码\n"
		<< "[2] 姓名\n"
		<< "[3] 手机号\n"
		<< "[4] 存款"
		<< endl;
	cin >> n;
	if (n == 1) {//管理员改密码自然不用加密处理
		cout << "请输入新密码" << endl;
		string TemPassword;
		cin >> TemPassword;
		system("cls");
		if ((p->date).GetMyPassword() == TemPassword) {
			cout << "新密码与原密码相同,修改失败" << endl;
			return;
		}

		(p->date).SetPassword(TemPassword);
		cout << "密码修改成功" << endl;

	}

	else if (n == 2) {

		cout << "请输入新姓名" << endl;
		string TemName;
		cin >> TemName;
		system("cls");

		if ((p->date).GetMyName() == TemName) {
			cout << "新姓名与原姓名相同,修改失败" << endl;
			return;
		}

		(p->date).SetName(TemName);
		cout << "姓名修改成功" << endl;

	}
	else if (n == 3) {
		cout << "请输入新手机号" << endl;
		long long TemTel;
		cin >> TemTel;
		system("cls");

		if ((p->date).GetMyTel() == TemTel) {
			cout << "新手机号与原手机号相同,修改失败" << endl;
			return;
		}

		(p->date).SetTel(TemTel);
		cout << "手机号修改成功" << endl;

	}
	//修改操作默认为存取款,正数表示存款,负数表示取款
	else if (n == 4) {
		cout << "请输入修改的存款,负数表示存款减少" << endl;
		double t;
		cin >> t;
		system("cls");
		if (t == 0) {
			cout << "存款变更必须为一个非零值" << endl;
			return;
		}
		else {
			(p->date).ModifyDeposit(t);
			(p->date).DepositChangeData.push_back(NumDepositChangeNode(t, (p->date).GetMyDeposit()));
			(p->date).NumDepositChange++;
			SYSTEMTIME sys;//windowsAPI获取时间
			GetLocalTime(&sys);
			char TemTime[100];
			sprintf(TemTime, "%4d/%02d/%02d/%02d:%02d:%02d", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond);
			(p->date).DepositChangeData[(p->date).NumDepositChange - 1].Time = TemTime;

			cout << "存款修改成功" << endl;
		}


	}

}

void SingleConditionSearch(LinkList AccList)
{
	cout << "请选择条件" << endl;
	cout << "[1] 按性别查询\n"
		<< "[2] 按姓名查询\n"
		<< "[3] 按手机号查询\n"
		<< "[4] 按存款查询"
		<< endl;
	int n;
	cin >> n;
	system("cls");

	//一个人可以开很多张银行卡,多个银行卡可以绑定一个手机号
	if (n == 1) {
		GenderSearch(AccList);
	}
	else if (n == 2) {
		NameSearch(AccList);
	}
	else if (n == 3) {
		TelSearch(AccList);
	}
	else if (n == 4) {
		DepositSearch(AccList);
	}
}

void GenderSearch(LinkList AccList)
{
	cout << "请输入要查询的性别,1表示男性,0表示女性" << endl;
	int n;
	cin >> n;
	system("cls");

	if (n == 0 || n == 1) {//输入符合要求
		bool IsFind = false;//先假设没有符合要求的用户

		LinkList p = AccList->next;
		while (p->next != nullptr) {
			if ((p->date).GetMyGender() == n) {
				if (IsFind == false) {//如果是第一次找到,输出属性栏
					cout << std::left << std::setw(15) << "账号"
						<< std::left << std::setw(15) << "密码"
						<< std::left << std::setw(15) << "姓名"
						<< std::left << std::setw(15) << "性别"
						<< std::left << std::setw(15) << "手机号"
						<< std::left << std::setw(15) << "余额"
						<< endl;
				}

				cout << p->date;
				IsFind = true;//更新IsFind
			}
			p = p->next;
		}
		if (IsFind == false) {//如果真的一个都没找到
			cout << "未找到相关数据" << endl;
		}
	}
	else {
		cout << "输入有误" << endl;
		return;
	}

}
void NameSearch(LinkList AccList)
{
	cout << "请输入要查询的姓名" << endl;
	string TemName;
	cin >> TemName;
	system("cls");

	bool IsFind = false;
	LinkList p = AccList->next;
	while (p->next != nullptr) {
		if ((p->date).GetMyName() == TemName) {
			if (IsFind == false) {
				cout << std::left << std::setw(15) << "账号"
					<< std::left << std::setw(15) << "密码"
					<< std::left << std::setw(15) << "姓名"
					<< std::left << std::setw(15) << "性别"
					<< std::left << std::setw(15) << "手机号"
					<< std::left << std::setw(15) << "余额"
					<< endl;
			}
			cout << p->date;
			IsFind = true;
		}
		p = p->next;
	}
	if (IsFind == false) {
		cout << "未找到相关数据" << endl;
	}
}
void TelSearch(LinkList AccList)
{
	cout << "请输入要查询的电话号" << endl;
	long long TemTel;
	cin >> TemTel;
	system("cls");

	bool IsFind = false;
	LinkList p = AccList->next;
	while (p->next != nullptr) {
		if ((p->date).GetMyTel() == TemTel) {
			if (IsFind == false) {
				cout << std::left << std::setw(15) << "账号"
					<< std::left << std::setw(15) << "密码"
					<< std::left << std::setw(15) << "姓名"
					<< std::left << std::setw(15) << "性别"
					<< std::left << std::setw(15) << "手机号"
					<< std::left << std::setw(15) << "余额"
					<< endl;
			}
			cout << p->date;
			IsFind = true;
		}
		p = p->next;
	}
	if (IsFind == false) {
		cout << "未找到相关数据" << endl;
	}
}
void DepositSearch(LinkList AccList)
{
	cout << "请输入存款分界点" << endl;
	double k;
	cin >> k;
	system("cls");

	cout << "请选择查询方式\n"
		<< "[1] 查询存款小于该值的用户\n"
		<< "[2] 查询存款不小于该值的用户";
	int n;
	cin >> n;
	system("cls");

	if (n == 1) {
		SearchLowerThanDeposit(AccList, k);
	}
	else if (n == 2) {
		SearchUpperThanDeposit(AccList, k);
	}
}

void SearchLowerThanDeposit(LinkList AccList, const double& AfferentDeposit) {
	bool IsFind = false;
	LinkList p = AccList->next;
	while (p->next != nullptr) {
		if ((p->date).GetMyDeposit() < AfferentDeposit) {

			if (IsFind == false) {
				cout << std::left << std::setw(15) << "账号"
					<< std::left << std::setw(15) << "密码"
					<< std::left << std::setw(15) << "姓名"
					<< std::left << std::setw(15) << "性别"
					<< std::left << std::setw(15) << "手机号"
					<< std::left << std::setw(15) << "余额"
					<< endl;
			}

			cout << p->date;
			IsFind = true;
		}
		p = p->next;
	}
	if (IsFind == false) {
		cout << "未找到相关数据" << endl;
	}
}

void SearchUpperThanDeposit(LinkList AccList, const double& AfferentDeposit)
{
	bool IsFind = false;
	LinkList p = AccList->next;
	while (p->next != nullptr) {
		if ((p->date).GetMyDeposit() >= AfferentDeposit) {
			if (IsFind == false) {
				cout << std::left << std::setw(15) << "账号"
					<< std::left << std::setw(15) << "密码"
					<< std::left << std::setw(15) << "姓名"
					<< std::left << std::setw(15) << "性别"
					<< std::left << std::setw(15) << "手机号"
					<< std::left << std::setw(15) << "余额"
					<< endl;
			}
			cout << p->date;
			IsFind = true;
		}
		p = p->next;
	}
	if (IsFind == false) {
		cout << "未找到相关数据" << endl;
	}
}

void FuzzySearch(LinkList AccList)
{
	cout << "请选择模糊查找模式" << endl;
	cout << "[1] 按姓氏查找(不支持复姓)\n"
		<< "[2] 按姓名中关键字查询\n"
		<< "[3] 按手机号前三位查询\n"
		<< "[4] 按手机号后四位查询" << endl;
	int n;
	cin >> n;
	system("cls");

	//正常人思维
	if (n == 1) {
		SearchAsSurname(AccList);
	}
	else if (n == 2) {
		SearchAsKeyWord(AccList);
	}
	else if (n == 3) {
		SearchAsTelTopThree(AccList);
	}
	else if (n == 4) {
		SearchAsTelLastFour(AccList);
	}
}

void SearchAsSurname(LinkList AccList)
{
	string TemName = "";
	while (true) {
		cout << "请输入姓氏,复姓请输入姓氏第一个字" << endl;
		cin >> TemName;
		system("cls");

		if (TemName.size() != 2) {//一个中文汉字占两个字节
			cout << "输入不合法,请重新输入" << endl;
		}
		else {
			cout << "输入成功" << endl;
			break;
		}
	}

	bool IsFind = false;
	LinkList p = AccList->next;
	while (p->next != nullptr) {

		//string的find方法返回第一次找到那个子串的位置首字符的下标,如果没有找到,返回npos,这是一个常量,表示size_t的最大值4294967295,显然如果返回了下标0,代表姓氏匹配上了
		if ((p->date).GetMyName().find(TemName) == 0) {
			if (IsFind == false) {
				cout << std::left << std::setw(15) << "账号"
					<< std::left << std::setw(15) << "密码"
					<< std::left << std::setw(15) << "姓名"
					<< std::left << std::setw(15) << "性别"
					<< std::left << std::setw(15) << "手机号"
					<< std::left << std::setw(15) << "余额"
					<< endl;
			}
			cout << p->date;
			IsFind = true;
		}
		p = p->next;
	}
	if (IsFind == false) {
		cout << "未找到相关数据" << endl;
	}

}

void SearchAsKeyWord(LinkList AccList)
{
	string TemName = "";
	cout << "请输入要查找的姓名关键字" << endl;
	cin >> TemName;
	system("cls");

	bool IsFind = false;
	LinkList p = AccList->next;
	while (p->next != nullptr) {
		if ((p->date).GetMyName().find(TemName) != string::npos) {//不等于npos代表找到了
			if (IsFind == false) {
				cout << std::left << std::setw(15) << "账号"
					<< std::left << std::setw(15) << "密码"
					<< std::left << std::setw(15) << "姓名"
					<< std::left << std::setw(15) << "性别"
					<< std::left << std::setw(15) << "手机号"
					<< std::left << std::setw(15) << "余额"
					<< endl;
			}
			cout << p->date;
			IsFind = true;
		}
		p = p->next;
	}
	if (IsFind == false) {
		cout << "未找到相关数据" << endl;
	}
}

void SearchAsTelTopThree(LinkList AccList)
{
	string TemTel = "";
	while (true) {
		cout << "请输入要查找的手机号前三位" << endl;
		cin >> TemTel;
		system("cls");

		if (TemTel.size() != 3) {
			cout << "输入不合法,请重新输入" << endl;
			continue;
		}
		else {
			cout << "输入成功" << endl;
			break;
		}

	}

	std::stringstream stream;//string转换为long long
	long long RealTel;
	stream << TemTel;
	stream >> RealTel;

	bool IsFind = false;
	LinkList p = AccList->next;
	while (p->next != nullptr) {
		if ((p->date).GetMyTel() / 100000000 == RealTel) {//默认手机号是11位的,使用longlong存储
			if (IsFind == false) {
				cout << std::left << std::setw(15) << "账号"
					<< std::left << std::setw(15) << "密码"
					<< std::left << std::setw(15) << "姓名"
					<< std::left << std::setw(15) << "性别"
					<< std::left << std::setw(15) << "手机号"
					<< std::left << std::setw(15) << "余额"
					<< endl;
			}
			cout << p->date;
			IsFind = true;
		}
		p = p->next;
	}
	if (IsFind == false) {
		cout << "未找到相关数据" << endl;
	}
}

void SearchAsTelLastFour(LinkList AccList)
{
	string TemTel = "";
	while (true) {
		cout << "请输入要查找的手机号后四位" << endl;
		cin >> TemTel;
		system("cls");

		if (TemTel.size() != 4) {
			cout << "输入不合法,请重新输入" << endl;
			continue;
		}
		else {
			cout << "输入成功" << endl;
			break;
		}

	}

	std::stringstream stream;//string转换为long long
	long long RealTel;
	stream << TemTel;
	stream >> RealTel;

	bool IsFind = false;
	LinkList p = AccList->next;
	while (p->next != nullptr) {
		if ((p->date).GetMyTel() % 10000 == RealTel) {//取得后四位
			if (IsFind == false) {
				cout << std::left << std::setw(15) << "账号"
					<< std::left << std::setw(15) << "密码"
					<< std::left << std::setw(15) << "姓名"
					<< std::left << std::setw(15) << "性别"
					<< std::left << std::setw(15) << "手机号"
					<< std::left << std::setw(15) << "余额"
					<< endl;
			}
			cout << p->date;
			IsFind = true;
		}
		p = p->next;
	}
	if (IsFind == false) {
		cout << "未找到相关数据" << endl;
	}
}
void StatisticalInformation(LinkList AccList)
{
	//静态成员变量使用,因为有首尾结点,所以真实的用户数需要减去2
	cout << "呐呐呐银行用户数: " << BankAccount::NumBankAccount - 2 << endl;
	double SumDeposit = 0;
	int Mr = 0, Mrs = 0;
	LinkList p = AccList->next;
	while (p->next != nullptr) {//分别统计男性和女性人数,和总金钱
		if ((p->date).GetMyGender() == 1) {
			Mr++;
		}
		else {
			Mrs++;
		}
		SumDeposit += (p->date).GetMyDeposit();
		p = p->next;
	}

	cout << "男性 : " << Mr << " 位  " << "女性 : " << Mrs << " 位" << endl;

	cout << "呐呐呐银行总存款数: " << std::fixed << std::setprecision(2) << SumDeposit << endl;

}


void QueryFlowingWater(LinkList AccList, const std::string& InAccount)
{
	int n;
	cout << "请选择相应的按钮\n" << "[1] 存取款流水\t" << "[2] 转账流水" << endl;
	cin >> n;
	system("cls");

	if (n == 1) {
		DepositInOutBill(AccList, InAccount);
	}
	if (n == 2) {
		DepositChangeBill(AccList, InAccount);
	}
}

void DepositInOutBill(LinkList AccList, const std::string& InAccount)
{
	LinkList p = AccList->next;
	while (p->next != nullptr) {
		if ((p->date).GetMyAccount() == InAccount) {

			//这里的时间由于比较长,按25宽度格式化输出
			if ((p->date).NumDepositChange == 0) {
				cout << "无存取款流水信息" << endl;
			}
			else {
				cout << std::left << std::setw(15) << "行为"
					<< std::left << std::setw(15) << "账号"
					<< std::left << std::setw(25) << "时间"
					<< std::left << std::setw(15) << "存款变动"
					<< std::left << std::setw(15) << "当前存款"
					<< endl;
				for (auto& ans : (p->date).DepositChangeData) {
					cout << std::left << std::setw(15) << (ans.Money > 0 ? "存款" : "取款")
						<< std::left << std::setw(15) << (p->date).GetMyAccount()
						<< std::left << std::setw(25) << ans.Time
						<< std::left << std::setw(15) << std::showpos << ans.Money
						<< std::noshowpos << std::left << std::setw(15) << std::fixed << std::setprecision(2) << ans.CurrentDeposit << endl;
				}
			}

		}
		p = p->next;
	}
	cout << endl;
}

void DepositChangeBill(LinkList AccList, const std::string& InAccount)
{
	LinkList p = AccList->next;
	while (p->next != nullptr) {
		if ((p->date).GetMyAccount() == InAccount) {
			if ((p->date).NumDepositInOut == 0) {
				cout << "无转账流水信息" << endl;
			}
			else {
				cout << std::left << std::setw(15) << "行为"
					<< std::left << std::setw(15) << "转出账号"
					<< std::left << std::setw(15) << "转入账号"
					<< std::left << std::setw(25) << "时间"
					<< std::left << std::setw(15) << "存款变动"
					<< std::left << std::setw(15) << "当前存款"
					<< endl;
				for (auto& ans : (p->date).DepositInOutData) {
					cout << std::left << std::setw(15) << (ans.Money > 0 ? "转入" : "转出")
						<< std::left << std::setw(15) << (ans.Money > 0 ? ans.OtherAccount : (p->date).GetMyAccount())
						<< std::left << std::setw(15) << (ans.Money < 0 ? ans.OtherAccount : (p->date).GetMyAccount())
						<< std::left << std::setw(25) << ans.Time
						<< std::left << std::setw(15) << std::showpos << ans.Money
						<< std::noshowpos << std::left << std::setw(15) << std::fixed << std::setprecision(2) << ans.CurrentDeposit << endl;
				}
			}

		}
		p = p->next;
	}
	cout << endl;
}

void SeeUserBill(LinkList AccList)
{
	string TemAccount = "";
	while (true) {
		cout << "请输入要查看的账号" << endl;
		cin >> TemAccount;
		system("cls");

		if (CheckAccount(AccList, TemAccount) == false) {
			cout << "账号不存在,请重新输入" << endl;
		}
		else {
			break;
		}
	}

	DepositInOutBill(AccList, TemAccount);
	DepositChangeBill(AccList, TemAccount);

}