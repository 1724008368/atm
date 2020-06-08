#include<iostream>
#include<fstream>
#include"BankAccount.h"
#include<conio.h>
#include<algorithm>
#include<map>
#include<iomanip>
#include <locale>
#include <windows.h>
#include <sstream> 
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
bool CheckAccountName(LinkList AccList, const std::string& InAccount, const std::string& InName);
void MapInitialization(LinkList AccList, std::map<std::string, int>& TemWrongPassword);
void QueryPrintDeposit(LinkList AccList, const std::string& InAccount);
void TakeInDeposit(LinkList AccList, const std::string& InAccount);
void TakeOutDeposit(LinkList AccList, const std::string& InAccount);
void GiveOtherDeposit(LinkList AccList, const std::string& InAccount);
void UserChangePassword(LinkList AccList, const std::string& InAccount);
void QueryFlowingWater(LinkList AccList, const std::string& InAccount);
void ReadFromFile1(DoubleLinkList AccList);
void ReadFromFile2(DoubleLinkList AccList);
void ReadFromFile3(DoubleLinkList AccList);
void SaveToFile1(LinkList AccList);
void SaveToFile2(LinkList AccList);
void SaveToFile3(LinkList AccList);
void AdministratorInterface(DoubleLinkList AccList);
void CreateUserAccount(DoubleLinkList AccList);
void DeleteUserAccount(LinkList AccList);
void ShowAllUsersInformation(LinkList AccList);
void UsersAccountDown(LinkList AccList);//排序算法均使用选择排序
void UsersAccountUp(LinkList AccList);
void UsersDepositDown(LinkList AccList);
void UsersDepositUp(LinkList AccList);
void UsersNameDown(LinkList AccList);
void UsersNameUp(LinkList AccList);
void FindUserInformation(LinkList AccList);
void ChangeUserInformation(LinkList AccList);
void SingleConditionSearch(LinkList AccList);
void GenderSearch(LinkList AccList);
void NameSearch(LinkList AccList);
void TelSearch(LinkList AccList);
void DepositSearch(LinkList AccList);
void SearchLowerThanDeposit(LinkList AccList, const double& AfferentDeposit);
void SearchUpperThanDeposit(LinkList AccList, const double& AfferentDeposit);
void FuzzySearch(LinkList AccList);
void SearchAsSurname(LinkList AccList);
void SearchAsKeyWord(LinkList AccList);
void SearchAsTelTopThree(LinkList AccList);
void SearchAsTelLastFour(LinkList AccList);
void StatisticalInformation(LinkList AccList);
void SeeUserBill(LinkList AccList);
void DepositInOutBill(LinkList AccList, const std::string& InAccount);
void DepositChangeBill(LinkList AccList, const std::string& InAccount);

int main()
{
	DoubleLinkList AccList = CreateList();
	ReadFromFile1(AccList);
	ReadFromFile2(AccList);
	ReadFromFile3(AccList);
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
void ReadFromFile1(DoubleLinkList AccList)
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
void ReadFromFile2(DoubleLinkList AccList)
{
	LinkList p = AccList.first->next;
	std::ifstream in("DepositChangeInformation.txt");
	while (p->next != nullptr) {
		(p->date).DepositChangeData.resize((p->date).NumDepositChange);
		for (int i = 0; i < (p->date).NumDepositChange; i++) {
			in >> (p->date).DepositChangeData[i].Money >> (p->date).DepositChangeData[i].CurrentDeposit >> (p->date).DepositChangeData[i].Time;
		}
		p = p->next;
	}
	in.close();
}
void ReadFromFile3(DoubleLinkList AccList)
{
	LinkList p = AccList.first->next;
	std::ifstream in("DepositInOutInformation.txt");
	while (p->next != nullptr) {
		(p->date).DepositInOutData.resize((p->date).NumDepositInOut);
		for (int i = 0; i < (p->date).NumDepositInOut; i++) {
			in >> (p->date).DepositInOutData[i].Money >> (p->date).DepositInOutData[i].CurrentDeposit >> (p->date).DepositInOutData[i].Time >> (p->date).DepositInOutData[i].OtherAccount;
		}
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
		std::cout << "请选择相应的按钮,按回车键结束\n" << "[1] 查询余额\n" << "[2] 存款\n" << "[3] 取款\n" << "[4] 转账\n" <<"[5] 修改密码\n"<<"[6] 查询流水\n"<< "[7] 退卡\n" << std::endl;
		int n;
		std::cin >> n;
		if (n == 1) {
			QueryPrintDeposit(AccList.first, TemAccount);
		}
		else if (n == 2) {
			TakeInDeposit(AccList.first, TemAccount);
			SaveToFile1(AccList.first);
			SaveToFile2(AccList.first);
			SaveToFile3(AccList.first);
		}
		else if (n == 3) {
			TakeOutDeposit(AccList.first, TemAccount);
			SaveToFile1(AccList.first);
			SaveToFile2(AccList.first);
			SaveToFile3(AccList.first);
		}
		else if (n == 4) {
			GiveOtherDeposit(AccList.first, TemAccount);
			SaveToFile1(AccList.first);
			SaveToFile2(AccList.first);
			SaveToFile3(AccList.first);
		}
		else if (n == 5) {
			UserChangePassword(AccList.first, TemAccount);
			SaveToFile1(AccList.first);
			SaveToFile2(AccList.first);
			SaveToFile3(AccList.first);
		}
		else if (n == 6) {
			QueryFlowingWater(AccList.first, TemAccount);
		}
		else if (n == 7) {
			Exit();
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

bool CheckAccountName(LinkList AccList, const std::string& InAccount, const std::string& InName)
{
	LinkList Temp = AccList->next;
	while (Temp->next != nullptr) {//未到达尾节点
		if ((Temp->date).GetMyAccount() == InAccount && (Temp->date).GetMyName() == InName)//找到了此账号同时密码正确
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
			(p->date).DepositChangeData.push_back(NumDepositChangeNode(money, (p->date).GetMyDeposit()));
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

	cout << "请输入转账人姓名" << endl;
	cin >> TurnOutName;
	if (CheckAccountName(AccList, TurnOutAccount, TurnOutName) == false) {
		cout << "账号和姓名不匹配" << endl;
		return;
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
			std::cout << "请输入转账金额(100整数倍),不多于5000" << std::endl;
			std::cin >> money;
			if (money % 100 || money <= 0 || money > 5000) {//判断取款金额是否合法
				cout << "转账金额有误,请重新输入" << endl;
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

			(p->date).DepositInOutData.push_back(NumDepositInOutNode(-money, (p->date).GetMyDeposit(), TurnOutAccount));
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

			(p->date).DepositInOutData.push_back(NumDepositInOutNode(money, (p->date).GetMyDeposit(), InAccount));
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
void SaveToFile1(LinkList AccList)
{
	std::ofstream Out("AccountInformation.txt");
	LinkList p = AccList->next;
	while (p->next != nullptr) {
		Out << p->date;
		p = p->next;
	}
	Out.close();
}

void SaveToFile2(LinkList AccList)
{
	LinkList p = AccList->next;
	std::ofstream out("DepositChangeInformation.txt");
	while (p->next != nullptr) {
		for (int i = 0; i < (p->date).NumDepositChange; i++) {
			out << (p->date).DepositChangeData[i].Money << " " << (p->date).DepositChangeData[i].CurrentDeposit << " " << (p->date).DepositChangeData[i].Time << endl;
		}
		p = p->next;
	}
	out.close();
}
void SaveToFile3(LinkList AccList)
{

	LinkList p = AccList->next;
	std::ofstream out("DepositInOutInformation.txt");
	while (p->next != nullptr) {

		for (int i = 0; i < (p->date).NumDepositInOut; i++) {
			out << (p->date).DepositInOutData[i].Money << " " << (p->date).DepositInOutData[i].CurrentDeposit << " " << (p->date).DepositInOutData[i].Time << " " << (p->date).DepositInOutData[i].OtherAccount << endl;
		}
		p = p->next;
	}
	out.close();
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
		cout << "[1] 创建用户账户\n" << "[2] 删除用户账户\n" << "[3] 查看全部用户信息\n" << "[4] 查找用户信息\n" << "[5] 修改用户信息\n" << "[6] 单条件查找\n"<<"[7] 模糊查找\n"<<"[8] 统计信息\n"<<"[9] 查看用户流水\n"<<"[10] 退出" << endl;
		cin >> n;
		if (n == 1) {
			CreateUserAccount(AccList);
			SaveToFile1(AccList.first);
			SaveToFile2(AccList.first);
			SaveToFile3(AccList.first);
		}
		else if (n == 2) {
			DeleteUserAccount(AccList.first);
			SaveToFile1(AccList.first);
			SaveToFile2(AccList.first);
			SaveToFile3(AccList.first);
		}
		else if (n == 3) {
			ShowAllUsersInformation(AccList.first);
		}
		else if (n == 4) {
			FindUserInformation(AccList.first);
		}
		else if (n == 5) {
			ChangeUserInformation(AccList.first);
			SaveToFile1(AccList.first);
			SaveToFile2(AccList.first);
			SaveToFile3(AccList.first);
		}
		else if (n == 6) {
			SingleConditionSearch(AccList.first);
		}
		else if (n == 7) {
			FuzzySearch(AccList.first);
		}
		else if (n == 8) {
			StatisticalInformation(AccList.first);
		}
		else if (n == 9) {
			SeeUserBill(AccList.first);
		}
		else if (n == 10) {
			Exit();
			return;
		}
	}
}
void CreateUserAccount(DoubleLinkList AccList)//传入的是头尾指针
{
	cout << "请依次输入 账号 密码 姓名 性别(01表示) 手机号" << endl;
	LinkList t = new ListNode;
	cin >> t->date;
	if (CheckAccount(AccList.first, (t->date).GetMyAccount()) == true) {
		cout << "该账号已存在,创建失败" << endl;
		delete t;
		return;
	}
	t->next = AccList.second;
	t->prev = AccList.second->prev;
	AccList.second->prev->next = t;
	AccList.second->prev = t;
	cout << "创建成功" << endl;
	
}
void DeleteUserAccount(LinkList AccList)
{
	
	string TemAccount = "";
	while (true) {
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
	if (BankAccount::NumBankAccount > 2) {
		cout << std::left << std::setw(15) << "账号" << std::left << std::setw(15) << "密码" << std::left << std::setw(15) << "姓名" << std::left << std::setw(15) << "性别" << std::left << std::setw(15) << "手机号" << std::left << std::setw(15) << "余额" << endl;
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
void FindUserInformation(LinkList AccList)
{
	string TemAccount = "";
	while (true) {
		cout << "请输入查找的账号" << endl;
		cin >> TemAccount;
		if (CheckAccount(AccList, TemAccount) == false) {
			cout << "账号不存在,请重新输入" << endl;
		}
		else {
			break;
		}
	}

	cout << std::left << std::setw(15) << "账号" << std::left << std::setw(15) << "密码" << std::left << std::setw(15) << "姓名" << std::left << std::setw(15) << "性别" << std::left << std::setw(15) << "手机号" << std::left << std::setw(15) << "余额" << endl;

	LinkList p = AccList->next;
	while (p->next!=nullptr) {
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

	int n;
	cout << "请选择修改的信息\n" << "[1] 密码\n" << "[2] 姓名\n" << "[3] 手机号\n" << "[4] 存款" << endl;
	cin >> n;
	if (n == 1) {
		cout << "请输入新密码" << endl;
		string TemPassword;
		cin >> TemPassword;
		(p->date).SetPassword(TemPassword);
		cout << "密码修改成功" << endl;
		SaveToFile1(AccList);
		SaveToFile2(AccList);
		SaveToFile3(AccList);

	}

	else if (n == 2) {

		cout << "请输入新姓名" << endl;
		string TemName;
		cin >> TemName;
		(p->date).SetName(TemName);
		cout << "姓名修改成功" << endl;
		SaveToFile1(AccList);
		SaveToFile2(AccList);
		SaveToFile3(AccList);
	}
	else if (n == 3) {
		cout << "请输入新手机号" << endl;
		long long TemTel;
		cin >> TemTel;
		(p->date).SetTel(TemTel);
		cout << "手机号修改成功" << endl;
		SaveToFile1(AccList);
		SaveToFile2(AccList);
		SaveToFile3(AccList);
	}
	else if (n == 4) {
		cout << "请输入修改的存款,负数表示存款减少" << endl;
		double t;
		cin >> t;
		if (t < 0 && (p->date).GetMyDeposit() + t < 0) {
			cout << "错误,存款不能为负数" << endl;
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
		SaveToFile1(AccList);
		SaveToFile2(AccList);
		SaveToFile3(AccList);

	}

}
void SingleConditionSearch(LinkList AccList)
{
	cout << "请选择条件" << endl;
	cout << "[1] 按性别查询\n" << "[2] 按姓名查询\n" << "[3] 按手机号查询\n" << "[4] 按存款查询"<< endl;
	int n;
	cin >> n;
	if (n == 1) {
		GenderSearch( AccList);
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
	if (n == 0||n==1) {
		bool IsFind = false;
		LinkList p = AccList->next;
		while (p->next != nullptr) {
			if ((p->date).GetMyGender() == n) {
				if (IsFind == false) {
					cout << std::left << std::setw(15) << "账号" << std::left << std::setw(15) << "密码" << std::left << std::setw(15) << "姓名" << std::left << std::setw(15) << "性别" << std::left << std::setw(15) << "手机号" << std::left << std::setw(15) << "余额" << endl;
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

	bool IsFind = false;
	LinkList p = AccList->next;
	while (p->next != nullptr) {
		if ((p->date).GetMyName() == TemName) {
			if (IsFind == false) {
				cout << std::left << std::setw(15) << "账号" << std::left << std::setw(15) << "密码" << std::left << std::setw(15) << "姓名" << std::left << std::setw(15) << "性别" << std::left << std::setw(15) << "手机号" << std::left << std::setw(15) << "余额" << endl;
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

	bool IsFind = false;
	LinkList p = AccList->next;
	while (p->next != nullptr) {
		if ((p->date).GetMyTel() == TemTel) {
			if (IsFind == false) {
				cout << std::left << std::setw(15) << "账号" << std::left << std::setw(15) << "密码" << std::left << std::setw(15) << "姓名" << std::left << std::setw(15) << "性别" << std::left << std::setw(15) << "手机号" << std::left << std::setw(15) << "余额" << endl;
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
	cout << "请选择查询方式\n" << "[1] 查询存款小于该值的用户\n" << "[2] 查询存款不小于该值的用户";
	int n;
	cin >> n;
	if (n == 1) {
		SearchLowerThanDeposit(AccList, k);
	}
}
void SearchLowerThanDeposit(LinkList AccList, const double& AfferentDeposit) {
	bool IsFind = false;
	LinkList p = AccList->next;
	while (p->next != nullptr) {
		if ((p->date).GetMyDeposit() < AfferentDeposit) {
			if (IsFind == false) {
				cout << std::left << std::setw(15) << "账号" << std::left << std::setw(15) << "密码" << std::left << std::setw(15) << "姓名" << std::left << std::setw(15) << "性别" << std::left << std::setw(15) << "手机号" << std::left << std::setw(15) << "余额" << endl;
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
				cout << std::left << std::setw(15) << "账号" << std::left << std::setw(15) << "密码" << std::left << std::setw(15) << "姓名" << std::left << std::setw(15) << "性别" << std::left << std::setw(15) << "手机号" << std::left << std::setw(15) << "余额" << endl;
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
	cout << "[1] 按姓氏查找(不支持复姓)\n" << "[2] 按姓名中关键字查询\n" << "[3] 按手机号前三位查询\n" << "[4] 按手机号后四位查询" << endl;
	int n;
	cin >> n;
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
		if (TemName.size() != 2) {
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
		if ((p->date).GetMyName().find(TemName)==0) {
			if (IsFind == false) {
				cout << std::left << std::setw(15) << "账号" << std::left << std::setw(15) << "密码" << std::left << std::setw(15) << "姓名" << std::left << std::setw(15) << "性别" << std::left << std::setw(15) << "手机号" << std::left << std::setw(15) << "余额" << endl;
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

	bool IsFind = false;
	LinkList p = AccList->next;
	while (p->next != nullptr) {
		if ((p->date).GetMyName().find(TemName)!=string::npos) {
			if (IsFind == false) {
				cout << std::left << std::setw(15) << "账号" << std::left << std::setw(15) << "密码" << std::left << std::setw(15) << "姓名" << std::left << std::setw(15) << "性别" << std::left << std::setw(15) << "手机号" << std::left << std::setw(15) << "余额" << endl;
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
		if ((p->date).GetMyTel()/100000000 == RealTel) {
			if (IsFind == false) {
				cout << std::left << std::setw(15) << "账号" << std::left << std::setw(15) << "密码" << std::left << std::setw(15) << "姓名" << std::left << std::setw(15) << "性别" << std::left << std::setw(15) << "手机号" << std::left << std::setw(15) << "余额" << endl;
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
		if ((p->date).GetMyTel()%10000== RealTel) {
			if (IsFind == false) {
				cout << std::left << std::setw(15) << "账号" << std::left << std::setw(15) << "密码" << std::left << std::setw(15) << "姓名" << std::left << std::setw(15) << "性别" << std::left << std::setw(15) << "手机号" << std::left << std::setw(15) << "余额" << endl;
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
	cout << "呐呐呐银行用户数: " << BankAccount::NumBankAccount - 2 << endl;
	double SumDeposit = 0;
	int Mr = 0, Mrs = 0;
	LinkList p = AccList->next;
	while (p->next != nullptr) {
		if ((p->date).GetMyGender() == 1) {
			Mr++;
		}
		else {
			Mrs++;
		}
		p = p->next;
	}

	cout << "男性 : " << Mr << " 位  " << "女性 : " << Mrs << " 位" << endl;

	p = AccList->next;
	while (p->next!=nullptr) {
		SumDeposit += (p->date).GetMyDeposit();
		p = p->next;
	}
	cout << "呐呐呐银行总存款数: " << std::fixed << std::setprecision(2) << SumDeposit << endl;

}

void UserChangePassword(LinkList AccList, const std::string& InAccount)
{
	string TemPassword="", NewPassword="",SureNewPassword="";
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

	if (CheckPassword(AccList, InAccount, TemPassword)==false) {
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
	
	if (SureNewPassword == NewPassword) {
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
void QueryFlowingWater(LinkList AccList, const std::string& InAccount)
{
	int n;
	cout << "请选择相应的按钮\n" << "[1] 存取款流水" << "[2] 转账流水" << endl;
	cin >> n;
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
			if ((p->date).NumDepositChange == 0) {
				cout << "无存取款流水信息" << endl;
			}
			else {
				cout << std::left << std::setw(15) << "行为" << std::left << std::setw(15) << "账号"  << std::left << std::setw(25) << "时间" << std::left << std::setw(15) << "存款变动" << std::left << std::setw(15) << "当前存款" << endl;
				for (auto& ans : (p->date).DepositChangeData) {
					cout << std::left << std::setw(15) << (ans.Money>0?"存款":"取款") << std::left << std::setw(15) << (p->date).GetMyAccount()  << std::left << std::setw(25) << ans.Time << std::left << std::setw(15) <<std::showpos<< ans.Money << std::noshowpos <<std::left << std::setw(15) <<std::fixed<<std::setprecision(2)<< ans.CurrentDeposit << endl;
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
				cout << std::left << std::setw(15) << "行为" << std::left << std::setw(15) << "转出账号" << std::left << std::setw(15) << "转入账号" << std::left << std::setw(25) << "时间" << std::left << std::setw(15) << "存款变动" << std::left << std::setw(15) << "当前存款" << endl;
				for (auto& ans : (p->date).DepositInOutData) {
					cout << std::left << std::setw(15) << (ans.Money > 0 ? "转入" : "转出") << std::left << std::setw(15) << (ans.Money > 0 ? ans.OtherAccount : (p->date).GetMyAccount())<<std::left << std::setw(15) << (ans.Money < 0 ? ans.OtherAccount : (p->date).GetMyAccount()) << std::left << std::setw(25) << ans.Time << std::left << std::setw(15) << std::showpos << ans.Money << std::noshowpos << std::left << std::setw(15) << std::fixed << std::setprecision(2) << ans.CurrentDeposit << endl;
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