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
/*ʵ�ְ�����ƴ���Ƚ�*/

#ifdef _MSC_VER
static const char* ZH_CN_LOCALE_STRING = "Chinese_china";
#else
static const char* ZH_CN_LOCALE_STRING = "zh_CN.utf8";
#endif
static const std::locale zh_CN_locale = std::locale(ZH_CN_LOCALE_STRING);
static const std::collate<char>& zh_CN_collate = std::use_facet<std::collate<char> >(zh_CN_locale);

/******************/

//����Ա�˺�����
std::string AdministratorAccount = "root";
std::string AdministratorPassword = "root";

using ListNode = struct ListNode;
using LinkList = ListNode*;
using DoubleLinkList = std::pair<LinkList, LinkList>;

struct ListNode//˫������
{
	//������
	BankAccount date;
	//ָ����
	LinkList prev = nullptr;//ͷ�ڵ�
	LinkList next = nullptr;//β�ڵ�
};


/*����ʹ�õ�һЩstd�ռ��еĶ���*/
using std::cin;
using std::cout;
using std::endl;
using std::string;

DoubleLinkList CreateList();//��������
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
void UsersAccountDown(LinkList AccList);//�����㷨��ʹ��ѡ������
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
	std::cout << "��ӭʹ��������ATM������ϵͳ\n" << "��ѡ����Ӧ�İ�ť,���س�������\n" << "[1]�û���¼\n" << "[2]����Ա��¼\n" << "[3]�˳�" << std::endl;
	int n;
	std::cin >> n;
	return n;
}
void Exit()
{
	std::cout << "��ӭ�´�ʹ��" << std::endl;

	exit(0);
}
void UserInterface(DoubleLinkList AccList)
{
	std::map<std::string, int> WrongPassword;
	MapInitialization(AccList.first, WrongPassword);
	std::string TemAccount = "", TemPassword = "";

	while (true) {

		TemAccount = "", TemPassword = "";
		std::cout << "�������˺�" << std::endl;
		std::cin >> TemAccount;
		std::cin.ignore();
		if (CheckAccount(AccList.first,TemAccount) == false) {
			std::cout << "�˺Ŵ���,����������" << std::endl;
			continue;
		}
		if (WrongPassword[TemAccount] >= 3) {//������󳬹�����
			std::cout << "���˺�������" << std::endl;
			continue;
		}
		std::cout << "����������,���δ����˺Ž�������" << std::endl;
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
			std::cout << "�������,����������" << std::endl;
			WrongPassword[TemAccount] = WrongPassword[TemAccount] + 1;
			continue;
		}
		else {
			std::cout << "������ȷ,��½�ɹ�" << std::endl;
			break;
		}
		//std::cout << TemAccount << std::endl << TemPassword << std::endl;
	}
	
	while (true) {
		std::cout << "��ѡ����Ӧ�İ�ť,���س�������\n" << "[1] ��ѯ���\n" << "[2] ���\n" << "[3] ȡ��\n" << "[4] ת��\n" <<"[5] �޸�����\n"<<"[6] ��ѯ��ˮ\n"<< "[7] �˿�\n" << std::endl;
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
	while (Temp->next != nullptr) {//δ����β�ڵ�
		if ((Temp->date).GetMyAccount() == InAccount)//�ҵ��˴��˺�
			return true;
		Temp = Temp->next;
	}
	return false;
}
bool CheckPassword(LinkList AccList, const std::string& InAccount, const std::string& InPassword)
{
	LinkList Temp = AccList->next;
	while (Temp->next != nullptr) {//δ����β�ڵ�
		if ((Temp->date).GetMyAccount() == InAccount && (Temp->date).GetMyPassword() == InPassword)//�ҵ��˴��˺�ͬʱ������ȷ
			return true;
		Temp = Temp->next;
	}
	return false;
}

bool CheckAccountName(LinkList AccList, const std::string& InAccount, const std::string& InName)
{
	LinkList Temp = AccList->next;
	while (Temp->next != nullptr) {//δ����β�ڵ�
		if ((Temp->date).GetMyAccount() == InAccount && (Temp->date).GetMyName() == InName)//�ҵ��˴��˺�ͬʱ������ȷ
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
			std::cout << "���Ϊ " << std::fixed << std::setprecision(2) << (p->date).GetMyDeposit() << std::endl;
			break;
		}
		p = p->next;

	}
}
void TakeInDeposit(LinkList AccList, const std::string& InAccount)
{
	int money;
	while (true) {
		std::cout << "����������(100������),������5000" << std::endl;
		std::cin >> money;
		if (money % 100 || money <= 0 || money > 5000) {//�жϴ�����Ƿ�Ϸ�
			cout << "���������,����������" << endl;
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
			SYSTEMTIME sys;//windowsAPI��ȡʱ��
			GetLocalTime(&sys);
			char TemTime[100];
			sprintf(TemTime, "%4d/%02d/%02d/%02d:%02d:%02d", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond);
			(p->date).DepositChangeData[(p->date).NumDepositChange - 1].Time = TemTime;
			break;
		}
		p = p->next;

	}
	//SaveToFile(AccList);
	std::cout << "�Ƿ��ӡƾ��\t\t[1]��\t[2]��" << std::endl;
	int n;
	std::cin >> n;
	if (n == 1) {//ʹ��print��ʽ���Ʒ��������
		SYSTEMTIME sys;//windowsAPI��ȡʱ��
		GetLocalTime(&sys);
		printf("\n----------------------------------------\n");
		printf("|               ���ƾ��               |\n");
		printf("|--------------------------------------|\n");
		printf("|                                      |\n");
		printf("|����˺�:%-29s|\n", InAccount.c_str());
		printf("|�����:%-29d|\n", money);
		printf("|���ʱ��:%4d/%02d/%02d %02d:%02d:%02d          |\n", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond);
		printf("|                                      |\n");
		printf("----------------------------------------\n\n");
		printf("ƾ����ӡ���\n");
	}
	else if (n == 2) {

	}

}
void TakeOutDeposit(LinkList AccList, const std::string& InAccount)
{
	int n;
	int money=0;
	std::cout << "��ѡ��ȡ����\n" << "[1] 100\t" << "[2] 200\n"<<"[3] 500\t" << "[4] 1000\n" << "[5] 2000" << "[6] �������" << std::endl;
	std::cin >> n;
	if (n == 1) money = 100;
	else if (n == 2) money = 200;
	else if (n == 3) money = 500;
	else if (n == 4) money = 1000;
	else if (n == 5) money = 2000;
	else if (n == 6) {
		while (true) {
			std::cout << "������ȡ����(100������),������5000" << std::endl;
			std::cin >> money;
			if (money % 100 || money <= 0 || money > 5000) {//�ж�ȡ�����Ƿ�Ϸ�
				cout << "ȡ��������,����������" << endl;
			}
			else
				break;
		}
	}

	LinkList p = AccList->next;
	while (p->next != nullptr) {
		if (InAccount == (p->date).GetMyAccount()) {
			if ((p->date).GetMyDeposit() < money) {
				cout << "����" << endl;
				return;
			}
			(p->date).ModifyDeposit(-money);
			(p->date).DepositChangeData.push_back(NumDepositChangeNode(-money, (p->date).GetMyDeposit()));
			(p->date).NumDepositChange++;
			SYSTEMTIME sys;//windowsAPI��ȡʱ��
			GetLocalTime(&sys);
			char TemTime[100];
			sprintf(TemTime, "%4d/%02d/%02d/%02d:%02d:%02d", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond);
			(p->date).DepositChangeData[(p->date).NumDepositChange - 1].Time = TemTime;
			break;
		}
		p = p->next;

	}

	//SaveToFile(AccList);

	cout << "�Ƿ��ӡƾ��\t\t[1]��\t[2]��" << endl;
	cin >> n;
	if (n == 1) {//ʹ��print��ʽ���Ʒ��������
		SYSTEMTIME sys;//windowsAPI��ȡʱ��
		GetLocalTime(&sys);
		printf("\n----------------------------------------\n");
		printf("|               ȡ��ƾ��               |\n");
		printf("|--------------------------------------|\n");
		printf("|                                      |\n");
		printf("|ȡ���˺�:%-29s|\n", InAccount.c_str());
		printf("|ȡ����:%-29d|\n", money);
		printf("|ȡ��ʱ��:%4d/%02d/%02d %02d:%02d:%02d          |\n", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond);
		printf("|                                      |\n");
		printf("----------------------------------------\n\n");
		printf("ƾ����ӡ���\n");
	}
	else if (n == 2) {

	}
}
void GiveOtherDeposit(LinkList AccList, const std::string& InAccount)
{
	string TurnOutAccount = "", TurnOutName = "";
	while (true) {

		cout << "������ת���˺�" << endl;
		cin >> TurnOutAccount;
		if (TurnOutAccount == InAccount) {
			cout << "�������Լ�ת��,����������" << endl;
			continue;
		}
		if (CheckAccount(AccList, TurnOutAccount) == false) {//û�ҵ�
			cout << "���޴��˺�,����������" << endl;
		}
		else {
			break;
		}
	}

	cout << "������ת��������" << endl;
	cin >> TurnOutName;
	if (CheckAccountName(AccList, TurnOutAccount, TurnOutName) == false) {
		cout << "�˺ź�������ƥ��" << endl;
		return;
	}



	int n;
	int money = 0;
	std::cout << "��ѡ��ת�˽��\n" << "[1] 100\t" << "[2] 200\n" << "[3] 500\t" << "[4] 1000\n" << "[5] 2000" << "[6] �������" << std::endl;

	std::cin >> n;
	if (n == 1) money = 100;
	else if (n == 2) money = 200;
	else if (n == 3) money = 500;
	else if (n == 4) money = 1000;
	else if (n == 5) money = 2000;
	else if (n == 6) {
		while (true) {
			std::cout << "������ת�˽��(100������),������5000" << std::endl;
			std::cin >> money;
			if (money % 100 || money <= 0 || money > 5000) {//�ж�ȡ�����Ƿ�Ϸ�
				cout << "ת�˽������,����������" << endl;
			}
			else
				break;
		}
	}

	LinkList p = AccList->next;
	while (p->next != nullptr) {
		if (InAccount == (p->date).GetMyAccount()) {
			if ((p->date).GetMyDeposit() < money) {
				cout << "����" << endl;
				return;
			}
			/*Ǯ��*/
			(p->date).ModifyDeposit(-money);

			(p->date).DepositInOutData.push_back(NumDepositInOutNode(-money, (p->date).GetMyDeposit(), TurnOutAccount));
			(p->date).NumDepositInOut++;
			SYSTEMTIME sys;//windowsAPI��ȡʱ��
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
			SYSTEMTIME sys;//windowsAPI��ȡʱ��
			GetLocalTime(&sys);
			char TemTime[100];
			sprintf(TemTime, "%4d/%02d/%02d/%02d:%02d:%02d", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond);
			(p->date).DepositInOutData[(p->date).NumDepositInOut - 1].Time = TemTime;

			break;
		}
		p = p->next;
	}

	//SaveToFile(AccList);

	cout << "�Ƿ��ӡƾ��\t\t[1]��\t[2]��" << endl;
	cin >> n;
	if (n == 1) {//ʹ��print��ʽ���Ʒ��������
		SYSTEMTIME sys;//windowsAPI��ȡʱ��
		GetLocalTime(&sys);
		printf("\n----------------------------------------\n");
		printf("|               ת��ƾ��               |\n");
		printf("|--------------------------------------|\n");
		printf("|                                      |\n");
		printf("|ת���˺�:%-29s|\n", InAccount.c_str());
		printf("|ת���˺�:%-29s|\n", TurnOutAccount.c_str());
		printf("|ת�˽��:%-29d|\n", money);
		printf("|ת��ʱ��:%4d/%02d/%02d %02d:%02d:%02d          |\n", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond);
		printf("|                                      |\n");
		printf("----------------------------------------\n\n");
		printf("ƾ����ӡ���\n");
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
		std::cout << "�������˺�" << std::endl;
		std::cin >> TemAccount;
		std::cin.ignore();
		if (TemAccount!= AdministratorAccount) {
			std::cout << "�˺Ŵ���,����������" << std::endl;
			continue;
		}
		std::cout << "����������" << std::endl;

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
			std::cout << "�������,����������" << std::endl;
		}
		else {
			std::cout << "������ȷ,��½�ɹ�" << std::endl;
			break;
		}
		//std::cout << TemAccount << std::endl << TemPassword << std::endl;
	}

	int n;
	while (true) {
		cout << "[1] �����û��˻�\n" << "[2] ɾ���û��˻�\n" << "[3] �鿴ȫ���û���Ϣ\n" << "[4] �����û���Ϣ\n" << "[5] �޸��û���Ϣ\n" << "[6] ����������\n"<<"[7] ģ������\n"<<"[8] ͳ����Ϣ\n"<<"[9] �鿴�û���ˮ\n"<<"[10] �˳�" << endl;
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
void CreateUserAccount(DoubleLinkList AccList)//�������ͷβָ��
{
	cout << "���������� �˺� ���� ���� �Ա�(01��ʾ) �ֻ���" << endl;
	LinkList t = new ListNode;
	cin >> t->date;
	if (CheckAccount(AccList.first, (t->date).GetMyAccount()) == true) {
		cout << "���˺��Ѵ���,����ʧ��" << endl;
		delete t;
		return;
	}
	t->next = AccList.second;
	t->prev = AccList.second->prev;
	AccList.second->prev->next = t;
	AccList.second->prev = t;
	cout << "�����ɹ�" << endl;
	
}
void DeleteUserAccount(LinkList AccList)
{
	
	string TemAccount = "";
	while (true) {
		cout << "������Ҫɾ�����˺�" << endl;
		cin >> TemAccount;
		if (CheckAccount(AccList, TemAccount) == false) {
			cout << "�˺Ų�����,����������" << endl;
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
	cout << "�˺�: " << TemAccount << " ��ɾ��" << endl;

}
void ShowAllUsersInformation(LinkList AccList)
{
	int n;
	cout << "��ѡ������Ҫ��չʾ��ʽ" << endl;
	cout << "[1] ���˺Ž�������" << endl;
	cout << "[2] ���˺���������" << endl;
	cout << "[3] ����������" << endl;
	cout << "[4] �������������" << endl;
	cout << "[5] ��������������" << endl;
	cout << "[6] ��������������" << endl;
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
		cout << std::left << std::setw(15) << "�˺�" << std::left << std::setw(15) << "����" << std::left << std::setw(15) << "����" << std::left << std::setw(15) << "�Ա�" << std::left << std::setw(15) << "�ֻ���" << std::left << std::setw(15) << "���" << endl;
	}
	else if (BankAccount::NumBankAccount == 2) {
		cout << "���û���Ϣ" << endl;
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
		cout << "��������ҵ��˺�" << endl;
		cin >> TemAccount;
		if (CheckAccount(AccList, TemAccount) == false) {
			cout << "�˺Ų�����,����������" << endl;
		}
		else {
			break;
		}
	}

	cout << std::left << std::setw(15) << "�˺�" << std::left << std::setw(15) << "����" << std::left << std::setw(15) << "����" << std::left << std::setw(15) << "�Ա�" << std::left << std::setw(15) << "�ֻ���" << std::left << std::setw(15) << "���" << endl;

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
		cout << "��������Ҫ�޸ĵ��˺�" << endl;
		cin >> TemAccount;
		if (CheckAccount(AccList, TemAccount) == false) {
			cout << "�˺Ų�����,����������" << endl;
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
	cout << "��ѡ���޸ĵ���Ϣ\n" << "[1] ����\n" << "[2] ����\n" << "[3] �ֻ���\n" << "[4] ���" << endl;
	cin >> n;
	if (n == 1) {
		cout << "������������" << endl;
		string TemPassword;
		cin >> TemPassword;
		(p->date).SetPassword(TemPassword);
		cout << "�����޸ĳɹ�" << endl;
		SaveToFile1(AccList);
		SaveToFile2(AccList);
		SaveToFile3(AccList);

	}

	else if (n == 2) {

		cout << "������������" << endl;
		string TemName;
		cin >> TemName;
		(p->date).SetName(TemName);
		cout << "�����޸ĳɹ�" << endl;
		SaveToFile1(AccList);
		SaveToFile2(AccList);
		SaveToFile3(AccList);
	}
	else if (n == 3) {
		cout << "���������ֻ���" << endl;
		long long TemTel;
		cin >> TemTel;
		(p->date).SetTel(TemTel);
		cout << "�ֻ����޸ĳɹ�" << endl;
		SaveToFile1(AccList);
		SaveToFile2(AccList);
		SaveToFile3(AccList);
	}
	else if (n == 4) {
		cout << "�������޸ĵĴ��,������ʾ������" << endl;
		double t;
		cin >> t;
		if (t < 0 && (p->date).GetMyDeposit() + t < 0) {
			cout << "����,����Ϊ����" << endl;
		}
		else {
			(p->date).ModifyDeposit(t);
			(p->date).DepositChangeData.push_back(NumDepositChangeNode(t, (p->date).GetMyDeposit()));
			(p->date).NumDepositChange++;
			SYSTEMTIME sys;//windowsAPI��ȡʱ��
			GetLocalTime(&sys);
			char TemTime[100];
			sprintf(TemTime, "%4d/%02d/%02d/%02d:%02d:%02d", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond);
			(p->date).DepositChangeData[(p->date).NumDepositChange - 1].Time = TemTime;

			cout << "����޸ĳɹ�" << endl;
		}
		SaveToFile1(AccList);
		SaveToFile2(AccList);
		SaveToFile3(AccList);

	}

}
void SingleConditionSearch(LinkList AccList)
{
	cout << "��ѡ������" << endl;
	cout << "[1] ���Ա��ѯ\n" << "[2] ��������ѯ\n" << "[3] ���ֻ��Ų�ѯ\n" << "[4] ������ѯ"<< endl;
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
	cout << "������Ҫ��ѯ���Ա�,1��ʾ����,0��ʾŮ��" << endl;
	int n;
	cin >> n;
	if (n == 0||n==1) {
		bool IsFind = false;
		LinkList p = AccList->next;
		while (p->next != nullptr) {
			if ((p->date).GetMyGender() == n) {
				if (IsFind == false) {
					cout << std::left << std::setw(15) << "�˺�" << std::left << std::setw(15) << "����" << std::left << std::setw(15) << "����" << std::left << std::setw(15) << "�Ա�" << std::left << std::setw(15) << "�ֻ���" << std::left << std::setw(15) << "���" << endl;
				}
				cout << p->date;
				IsFind = true;
			}
			p = p->next;
		}
		if (IsFind == false) {
			cout << "δ�ҵ��������" << endl;
		}
	}
	else {
		cout << "��������" << endl;
		return;
	}
	
}
void NameSearch(LinkList AccList)
{
	cout << "������Ҫ��ѯ������" << endl;
	string TemName;
	cin >> TemName;

	bool IsFind = false;
	LinkList p = AccList->next;
	while (p->next != nullptr) {
		if ((p->date).GetMyName() == TemName) {
			if (IsFind == false) {
				cout << std::left << std::setw(15) << "�˺�" << std::left << std::setw(15) << "����" << std::left << std::setw(15) << "����" << std::left << std::setw(15) << "�Ա�" << std::left << std::setw(15) << "�ֻ���" << std::left << std::setw(15) << "���" << endl;
			}
			cout << p->date;
			IsFind = true;
		}
		p = p->next;
	}
	if (IsFind == false) {
		cout << "δ�ҵ��������" << endl;
	}
}
void TelSearch(LinkList AccList)
{
	cout << "������Ҫ��ѯ�ĵ绰��" << endl;
	long long TemTel;
	cin >> TemTel;

	bool IsFind = false;
	LinkList p = AccList->next;
	while (p->next != nullptr) {
		if ((p->date).GetMyTel() == TemTel) {
			if (IsFind == false) {
				cout << std::left << std::setw(15) << "�˺�" << std::left << std::setw(15) << "����" << std::left << std::setw(15) << "����" << std::left << std::setw(15) << "�Ա�" << std::left << std::setw(15) << "�ֻ���" << std::left << std::setw(15) << "���" << endl;
			}
			cout << p->date;
			IsFind = true;
		}
		p = p->next;
	}
	if (IsFind == false) {
		cout << "δ�ҵ��������" << endl;
	}
}
void DepositSearch(LinkList AccList)
{
	cout << "��������ֽ��" << endl;
	double k;
	cin >> k;
	cout << "��ѡ���ѯ��ʽ\n" << "[1] ��ѯ���С�ڸ�ֵ���û�\n" << "[2] ��ѯ��С�ڸ�ֵ���û�";
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
				cout << std::left << std::setw(15) << "�˺�" << std::left << std::setw(15) << "����" << std::left << std::setw(15) << "����" << std::left << std::setw(15) << "�Ա�" << std::left << std::setw(15) << "�ֻ���" << std::left << std::setw(15) << "���" << endl;
			}
			cout << p->date;
			IsFind = true;
		}
		p = p->next;
	}
	if (IsFind == false) {
		cout << "δ�ҵ��������" << endl;
	}
}
void SearchUpperThanDeposit(LinkList AccList, const double& AfferentDeposit)
{
	bool IsFind = false;
	LinkList p = AccList->next;
	while (p->next != nullptr) {
		if ((p->date).GetMyDeposit() >= AfferentDeposit) {
			if (IsFind == false) {
				cout << std::left << std::setw(15) << "�˺�" << std::left << std::setw(15) << "����" << std::left << std::setw(15) << "����" << std::left << std::setw(15) << "�Ա�" << std::left << std::setw(15) << "�ֻ���" << std::left << std::setw(15) << "���" << endl;
			}
			cout << p->date;
			IsFind = true;
		}
		p = p->next;
	}
	if (IsFind == false) {
		cout << "δ�ҵ��������" << endl;
	}
}

void FuzzySearch(LinkList AccList)
{
	cout << "��ѡ��ģ������ģʽ" << endl;
	cout << "[1] �����ϲ���(��֧�ָ���)\n" << "[2] �������йؼ��ֲ�ѯ\n" << "[3] ���ֻ���ǰ��λ��ѯ\n" << "[4] ���ֻ��ź���λ��ѯ" << endl;
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
		cout << "����������,�������������ϵ�һ����" << endl;
		cin >> TemName;
		if (TemName.size() != 2) {
			cout << "���벻�Ϸ�,����������" << endl;
		}
		else {
			cout << "����ɹ�" << endl;
			break;
		}
	}

	bool IsFind = false;
	LinkList p = AccList->next;
	while (p->next != nullptr) {
		if ((p->date).GetMyName().find(TemName)==0) {
			if (IsFind == false) {
				cout << std::left << std::setw(15) << "�˺�" << std::left << std::setw(15) << "����" << std::left << std::setw(15) << "����" << std::left << std::setw(15) << "�Ա�" << std::left << std::setw(15) << "�ֻ���" << std::left << std::setw(15) << "���" << endl;
			}
			cout << p->date;
			IsFind = true;
		}
		p = p->next;
	}
	if (IsFind == false) {
		cout << "δ�ҵ��������" << endl;
	}

}

void SearchAsKeyWord(LinkList AccList)
{
	string TemName = "";
	cout << "������Ҫ���ҵ������ؼ���" << endl;
	cin >> TemName;

	bool IsFind = false;
	LinkList p = AccList->next;
	while (p->next != nullptr) {
		if ((p->date).GetMyName().find(TemName)!=string::npos) {
			if (IsFind == false) {
				cout << std::left << std::setw(15) << "�˺�" << std::left << std::setw(15) << "����" << std::left << std::setw(15) << "����" << std::left << std::setw(15) << "�Ա�" << std::left << std::setw(15) << "�ֻ���" << std::left << std::setw(15) << "���" << endl;
			}
			cout << p->date;
			IsFind = true;
		}
		p = p->next;
	}
	if (IsFind == false) {
		cout << "δ�ҵ��������" << endl;
	}
}

void SearchAsTelTopThree(LinkList AccList)
{
	string TemTel = "";
	while (true) {
		cout << "������Ҫ���ҵ��ֻ���ǰ��λ" << endl;
		cin >> TemTel;
		if (TemTel.size() != 3) {
			cout << "���벻�Ϸ�,����������" << endl;
			continue;
		}
		else {
			cout << "����ɹ�" << endl;
			break;
		}

	}
	
	std::stringstream stream;//stringת��Ϊlong long
	long long RealTel;
	stream << TemTel;
	stream >> RealTel;


	bool IsFind = false;
	LinkList p = AccList->next;
	while (p->next != nullptr) {
		if ((p->date).GetMyTel()/100000000 == RealTel) {
			if (IsFind == false) {
				cout << std::left << std::setw(15) << "�˺�" << std::left << std::setw(15) << "����" << std::left << std::setw(15) << "����" << std::left << std::setw(15) << "�Ա�" << std::left << std::setw(15) << "�ֻ���" << std::left << std::setw(15) << "���" << endl;
			}
			cout << p->date;
			IsFind = true;
		}
		p = p->next;
	}
	if (IsFind == false) {
		cout << "δ�ҵ��������" << endl;
	}
}

void SearchAsTelLastFour(LinkList AccList)
{
	string TemTel = "";
	while (true) {
		cout << "������Ҫ���ҵ��ֻ��ź���λ" << endl;
		cin >> TemTel;
		if (TemTel.size() != 4) {
			cout << "���벻�Ϸ�,����������" << endl;
			continue;
		}
		else {
			cout << "����ɹ�" << endl;
			break;
		}

	}

	std::stringstream stream;//stringת��Ϊlong long
	long long RealTel;
	stream << TemTel;
	stream >> RealTel;


	bool IsFind = false;
	LinkList p = AccList->next;
	while (p->next != nullptr) {
		if ((p->date).GetMyTel()%10000== RealTel) {
			if (IsFind == false) {
				cout << std::left << std::setw(15) << "�˺�" << std::left << std::setw(15) << "����" << std::left << std::setw(15) << "����" << std::left << std::setw(15) << "�Ա�" << std::left << std::setw(15) << "�ֻ���" << std::left << std::setw(15) << "���" << endl;
			}
			cout << p->date;
			IsFind = true;
		}
		p = p->next;
	}
	if (IsFind == false) {
		cout << "δ�ҵ��������" << endl;
	}
}
void StatisticalInformation(LinkList AccList)
{
	cout << "�����������û���: " << BankAccount::NumBankAccount - 2 << endl;
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

	cout << "���� : " << Mr << " λ  " << "Ů�� : " << Mrs << " λ" << endl;

	p = AccList->next;
	while (p->next!=nullptr) {
		SumDeposit += (p->date).GetMyDeposit();
		p = p->next;
	}
	cout << "�����������ܴ����: " << std::fixed << std::setprecision(2) << SumDeposit << endl;

}

void UserChangePassword(LinkList AccList, const std::string& InAccount)
{
	string TemPassword="", NewPassword="",SureNewPassword="";
	cout << "������ԭ����" << endl;

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
		cout << "�������" << endl;
		return;
	}
	
	cout << "������������" << endl;
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

	cout << "���ٴ�����������" << endl;

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
				cout << "�����޸ĳɹ�" << endl;
				return;
			}
			p = p->next;
		}
	}
	else {
		cout << "�����������벻һ��" << endl;
		return;
	}
}
void QueryFlowingWater(LinkList AccList, const std::string& InAccount)
{
	int n;
	cout << "��ѡ����Ӧ�İ�ť\n" << "[1] ��ȡ����ˮ" << "[2] ת����ˮ" << endl;
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
				cout << "�޴�ȡ����ˮ��Ϣ" << endl;
			}
			else {
				cout << std::left << std::setw(15) << "��Ϊ" << std::left << std::setw(15) << "�˺�"  << std::left << std::setw(25) << "ʱ��" << std::left << std::setw(15) << "���䶯" << std::left << std::setw(15) << "��ǰ���" << endl;
				for (auto& ans : (p->date).DepositChangeData) {
					cout << std::left << std::setw(15) << (ans.Money>0?"���":"ȡ��") << std::left << std::setw(15) << (p->date).GetMyAccount()  << std::left << std::setw(25) << ans.Time << std::left << std::setw(15) <<std::showpos<< ans.Money << std::noshowpos <<std::left << std::setw(15) <<std::fixed<<std::setprecision(2)<< ans.CurrentDeposit << endl;
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
				cout << "��ת����ˮ��Ϣ" << endl;
			}
			else {
				cout << std::left << std::setw(15) << "��Ϊ" << std::left << std::setw(15) << "ת���˺�" << std::left << std::setw(15) << "ת���˺�" << std::left << std::setw(25) << "ʱ��" << std::left << std::setw(15) << "���䶯" << std::left << std::setw(15) << "��ǰ���" << endl;
				for (auto& ans : (p->date).DepositInOutData) {
					cout << std::left << std::setw(15) << (ans.Money > 0 ? "ת��" : "ת��") << std::left << std::setw(15) << (ans.Money > 0 ? ans.OtherAccount : (p->date).GetMyAccount())<<std::left << std::setw(15) << (ans.Money < 0 ? ans.OtherAccount : (p->date).GetMyAccount()) << std::left << std::setw(25) << ans.Time << std::left << std::setw(15) << std::showpos << ans.Money << std::noshowpos << std::left << std::setw(15) << std::fixed << std::setprecision(2) << ans.CurrentDeposit << endl;
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
		cout << "������Ҫ�鿴���˺�" << endl;
		cin >> TemAccount;
		if (CheckAccount(AccList, TemAccount) == false) {
			cout << "�˺Ų�����,����������" << endl;
		}
		else {
			break;
		}
	}

	DepositInOutBill(AccList, TemAccount);
	DepositChangeBill(AccList, TemAccount);

}