#include<iostream>
#include<fstream>
#include"BankAccount.h"
#include<conio.h>
#include<algorithm>
#include<map>
#include<iomanip>
#include <locale>
#include <windows.h>
/*实现按中文拼音比较*/

#ifdef _MSC_VER
static const char* ZH_CN_LOCALE_STRING = "Chinese_china";
#else
static const char* ZH_CN_LOCALE_STRING = "zh_CN.utf8";
#endif
static const std::locale zh_CN_locale = std::locale(ZH_CN_LOCALE_STRING);
static const std::collate<char>& zh_CN_collate = std::use_facet<std::collate<char> >(zh_CN_locale);

/******************/

//管理员账号密码
std::string AdministratorAccount = "root";
std::string AdministratorPassword = "root";

using ListNode = struct ListNode;
using LinkList = ListNode*;
using DoubleLinkList = std::pair<LinkList, LinkList>;

struct ListNode//双向链表
{
	//数据域
	BankAccount date;
	//指针域
	LinkList prev = nullptr;//头节点
	LinkList next = nullptr;//尾节点
};


/*大量使用的一些std空间中的东西*/
using std::cin;
using std::cout;
using std::endl;
using std::string;

DoubleLinkList CreateList();//创建链表
int Welcome();
void Exit();
void UserInterface(DoubleLinkList AccList);
bool CheckAccount(LinkList AccList, const std::string& InAccount);
bool CheckPassword(LinkList AccList, const std::string& InAccount, const std::string& InPassword);
void MapInitialization(LinkList AccList, std::map<std::string, int>& TemWrongPassword);
void QueryPrintDeposit(LinkList AccList, const std::string& InAccount);
void TakeInDeposit(LinkList AccList, const std::string& InAccount);
void TakeOutDeposit(LinkList AccList, const std::string& InAccount);
void GiveOtherDeposit(LinkList AccList, const std::string& InAccount);
void ReadFromFile(DoubleLinkList AccList);
void SaveToFile(LinkList AccList);
void AdministratorInterface(DoubleLinkList AccList);
void CreateUserAccount(LinkList AccList);
void DeleteUserAccount(LinkList AccList);
void ShowAllUsersInformation(LinkList AccList);
void UsersAccountDown(LinkList AccList);//排序算法均使用选择排序
void UsersAccountUp(LinkList AccList);
void UsersDepositDown(LinkList AccList);
void UsersDepositUp(LinkList AccList);
void UsersNameDown(LinkList AccList);
void UsersNameUp(LinkList AccList);
int main()
{
	DoubleLinkList AccList = CreateList();
	ReadFromFile(AccList);
	while (int t = Welcome()) {
		if (t == 3) {
			Exit();
		}
		else if (t == 1) {
			UserInterface(AccList);
		}
		else if (t == 2) {
			AdministratorInterface(AccList);
		}
	}
}
DoubleLinkList CreateList()
{
	LinkList p = new ListNode;
	LinkList t = new ListNode;
	p->next = t;
	t->prev = p;
	return { p,t };
}
void ReadFromFile(DoubleLinkList AccList)
{
	LinkList p = AccList.first;
	std::ifstream in("AccountInformation.txt");
	if (!in.is_open())
		cout << "sb";
	while (in.peek()!=EOF) {
		LinkList t = new ListNode;
		t->prev = p;
		t->next = p->next;
		p->next->prev = t;
		p->next = t;
		
		in >> t->date;
		p = p->next;
	}
	in.close();
}
int Welcome()
{
	std::cout << "欢迎使用呐呐呐ATM机管理系统\n" << "请选择相应的按钮,按回车键结束\n" << "[1]用户登录\n" << "[2]管理员登录\n" << "[3]退出" << std::endl;
	int n;
	std::cin >> n;
	return n;
}
void Exit()
{
	std::cout << "欢迎下次使用" << std::endl;

	exit(0);
}
void UserInterface(DoubleLinkList AccList)
{
	std::map<std::string, int> WrongPassword;
	MapInitialization(AccList.first, WrongPassword);
	std::string TemAccount = "", TemPassword = "";

	while (true) {

		TemAccount = "", TemPassword = "";
		std::cout << "请输入账号" << std::endl;
		std::cin >> TemAccount;
		std::cin.ignore();
		if (CheckAccount(AccList.first,TemAccount) == false) {
			std::cout << "账号错误,请重新输入" << std::endl;
			continue;
		}
		if (WrongPassword[TemAccount] >= 3) {//密码错误超过三次
			std::cout << "该账号已锁定" << std::endl;
			continue;
		}
		std::cout << "请输入密码,三次错误账号将被锁定" << std::endl;
		char ch;
		while (ch = _getch(), ch != '\r')
		{
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
		if (CheckPassword(AccList.first, TemAccount, TemPassword) == false) {
			std::cout << "密码错误,请重新输入" << std::endl;
			WrongPassword[TemAccount] = WrongPassword[TemAccount] + 1;
			continue;
		}
		else {
			std::cout << "密码正确,登陆成功" << std::endl;
			break;
		}
		//std::cout << TemAccount << std::endl << TemPassword << std::endl;
	}
	
	while (true) {
		std::cout << "请选择相应的按钮,按回车键结束\n" << "[1]查询余额\n" << "[2]存款\n" << "[3]取款\n" << "[4]转账\n" << "[5]退卡\n" << std::endl;
		int n;
		std::cin >> n;
		if (n == 1) {
			QueryPrintDeposit(AccList.first, TemAccount);
		}
		else if (n == 2) {
			TakeInDeposit(AccList.first, TemAccount);
		}
		else if (n == 3) {
			TakeOutDeposit(AccList.first, TemAccount);
		}
		else if (n == 4) {
			GiveOtherDeposit(AccList.first, TemAccount);
		}
		else if (n == 5) {
			return;
		}
	}


}
bool CheckAccount(LinkList AccList, const std::string& InAccount)
{
	LinkList Temp = AccList->next;
	while (Temp->next != nullptr) {//未到达尾节点
		if ((Temp->date).GetMyAccount() == InAccount)//找到了此账号
			return true;
		Temp = Temp->next;
	}
	return false;
}
bool CheckPassword(LinkList AccList, const std::string& InAccount, const std::string& InPassword)
{
	LinkList Temp = AccList->next;
	while (Temp->next != nullptr) {//未到达尾节点
		if ((Temp->date).GetMyAccount() == InAccount && (Temp->date).GetMyPassword() == InPassword)//找到了此账号同时密码正确
			return true;
		Temp = Temp->next;
	}
	return false;
}
void MapInitialization(LinkList AccList, std::map<std::string, int>& TemWrongPassword)
{
	LinkList p = AccList->next;
	while (p->next != nullptr) {
		TemWrongPassword.insert(std::make_pair((p->date).GetMyAccount(), 0));
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
			break;
		}
		p = p->next;

	}
	SaveToFile(AccList);
	std::cout << "是否打印凭条\t\t[1]是\t[2]否" << std::endl;
	int n;
	std::cin >> n;
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
	else if (n == 2) {

	}

}
void TakeOutDeposit(LinkList AccList, const std::string& InAccount)
{
	int n;
	int money=0;
	std::cout << "请选择取款金额\n" << "[1] 100\t" << "[2] 200\n"<<"[3] 500\t" << "[4] 1000\n" << "[5] 2000" << "[6] 其他金额" << std::endl;
	std::cin >> n;
	if (n == 1) money = 100;
	else if (n == 2) money = 200;
	else if (n == 3) money = 500;
	else if (n == 4) money = 1000;
	else if (n == 5) money = 2000;
	else if (n == 6) {
		while (true) {
			std::cout << "请输入取款金额(100整数倍),不多于5000" << std::endl;
			std::cin >> money;
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
			if ((p->date).GetMyDeposit() < money) {
				cout << "余额不足" << endl;
				return;
			}
			(p->date).ModifyDeposit(-money);
			
			break;
		}
		p = p->next;

	}

	SaveToFile(AccList);

	cout << "是否打印凭条\t\t[1]是\t[2]否" << endl;
	cin >> n;
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
	string TurnOutAccount = "";
	while (true) {

		cout << "请输入转账账号" << endl;
		cin >> TurnOutAccount;
		if (TurnOutAccount == InAccount) {
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

	int n;
	int money = 0;
	std::cout << "请选择转账金额\n" << "[1] 100\t" << "[2] 200\n" << "[3] 500\t" << "[4] 1000\n" << "[5] 2000" << "[6] 其他金额" << std::endl;

	std::cin >> n;
	if (n == 1) money = 100;
	else if (n == 2) money = 200;
	else if (n == 3) money = 500;
	else if (n == 4) money = 1000;
	else if (n == 5) money = 2000;
	else if (n == 6) {
		while (true) {
			std::cout << "请输入取款金额(100整数倍),不多于5000" << std::endl;
			std::cin >> money;
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
			if ((p->date).GetMyDeposit() < money) {
				cout << "余额不足" << endl;
				return;
			}
			/*钱够*/
			(p->date).ModifyDeposit(-money);
			break;
		}
		p = p->next;

	}

	p = AccList->next;
	while (p->next != nullptr) {
		if (TurnOutAccount == (p->date).GetMyAccount()) {
			(p->date).ModifyDeposit(money);
			break;
		}
		p = p->next;
	}

	SaveToFile(AccList);

	cout << "是否打印凭条\t\t[1]是\t[2]否" << endl;
	cin >> n;
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
void SaveToFile(LinkList AccList)
{
	std::ofstream Out("AccountInformation.txt");
	LinkList p = AccList->next;
	while (p->next != nullptr) {
		Out << p->date;
		p = p->next;
	}
	Out.close();
}
void AdministratorInterface(DoubleLinkList AccList)
{

	std::string TemAccount = "", TemPassword = "";
	while (true) {
		TemAccount = "", TemPassword = "";
		std::cout << "请输入账号" << std::endl;
		std::cin >> TemAccount;
		std::cin.ignore();
		if (TemAccount!= AdministratorAccount) {
			std::cout << "账号错误,请重新输入" << std::endl;
			continue;
		}
		std::cout << "请输入密码" << std::endl;

		char ch;
		while (ch = _getch(), ch != '\r')
		{
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
		if (TemPassword!= AdministratorPassword) {
			std::cout << "密码错误,请重新输入" << std::endl;
		}
		else {
			std::cout << "密码正确,登陆成功" << std::endl;
			break;
		}
		//std::cout << TemAccount << std::endl << TemPassword << std::endl;
	}

	int n;
	while (true) {
		cout << "[1] 创建用户账户\n" << "[2] 删除用户账户\n" << "[3] 查看全部用户信息\n" << "[4] 查找用户信息\n" << "[5] 修改用户信息\n" << "[6] 退出" << endl;
		cin >> n;
		if (n == 1) {
			CreateUserAccount(AccList.second);
		}
		else if (n == 2) {
			DeleteUserAccount(AccList.first);
		}
		else if (n == 3) {
			ShowAllUsersInformation(AccList.first);
		}
		else if (n == 4) {

		}
		else if (n == 5) {

		}
		else if (n == 6) {

		}
	}
}
void CreateUserAccount(LinkList AccList)//这波插入的是尾节点
{
	cout << "请依次输入 账号 密码 姓名 性别(01表示) 手机号 存款" << endl;
	LinkList t = new ListNode;
	cin >> t->date;
	t->next = AccList;
	t->prev = AccList->prev;
	AccList->prev->next = t;
	AccList->prev = t;
	cout << "创建成功" << endl;
}
void DeleteUserAccount(LinkList AccList)
{
	
	string TemAccount = "";
	while (true)
	{
		cout << "请输入要删除的账号" << endl;
		cin >> TemAccount;
		if (CheckAccount(AccList, TemAccount) == false) {
			cout << "账号不存在,请重新输入" << endl;
		}
		else {
			break;
		}
	}
	LinkList p = AccList->next;
	while (p->next != nullptr) {
		if ((p->date).GetMyAccount() == TemAccount) {
			break;
		}
		p = p->next;
	}
	p->prev->next = p->next;
	p->next->prev = p->prev;
	delete p;
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
	cout << std::left << std::setw(15) << "账号" << std::left << std::setw(15) << "密码" << std::left << std::setw(15) << "姓名" << std::left << std::setw(15) << "性别" << std::left << std::setw(15) << "手机号" << std::left << std::setw(15) << "余额" << endl;
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
			if ((j->date).GetMyAccount() > (i->date).GetMyAccount()) {
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
			char* s1 = new char[30];
			char* s2 = new char[30];
			strcpy(s1, (i->date).GetMyName().c_str());
			strcpy(s2, (j->date).GetMyName().c_str());
			if (zh_CN_collate.compare(s1,s1+ (i->date).GetMyName().size(), s2, s2 + (j->date).GetMyName().size())<0) {
				std::swap(i->date, j->date);
			}
			delete[]s1;
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