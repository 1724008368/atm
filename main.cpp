#include<iostream>
#include<fstream>
#include"BankAccount.h"
#include<conio.h>
#include<algorithm>
#include<map>
#include<iomanip>
#include <windows.h>
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
		std::cout << "��ѡ����Ӧ�İ�ť,���س�������\n" << "[1]��ѯ���\n" << "[2]���\n" << "[3]ȡ��\n" << "[4]ת��\n" << "[5]�˿�\n" << std::endl;
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
			break;
		}
		p = p->next;

	}
	SaveToFile(AccList);
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
			
			break;
		}
		p = p->next;

	}

	SaveToFile(AccList);

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
	string TurnOutAccount = "";
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
			/*Ǯ��*/
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
		std::cout << "�������˺�" << std::endl;
		std::cin >> TemAccount;
		std::cin.ignore();
		if (TemAccount!= AdministratorAccount) {
			std::cout << "�˺Ŵ���,����������" << std::endl;
			continue;
		}
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
			std::cout << "�������,����������" << std::endl;
		}
		else {
			std::cout << "������ȷ,��½�ɹ�" << std::endl;
			break;
		}
		//std::cout << TemAccount << std::endl << TemPassword << std::endl;
	}
	cout << "[1] �����û��˻�\n" << "[2] ɾ���û��˻�\n" << "[3] �鿴ȫ���û���Ϣ\n" << "[4] �����û���Ϣ\n" << "[5] �޸��û���Ϣ\n" << "[6] �˳�" << endl;
	int n;
	while (cin>>n) {
		if (n == 1) {
			CreateUserAccount(AccList.second);
		}
		else if (n == 2) {
			DeleteUserAccount(AccList.first);
		}
		else if (n == 3) {

		}
		else if (n == 4) {

		}
		else if (n == 5) {

		}
		else if (n == 6) {

		}
	}
}
void CreateUserAccount(LinkList AccList)//�Ⲩ�������β�ڵ�
{
	cout << "���������� �˺� ���� ���� �Ա�(01��ʾ) �ֻ��� ���" << endl;
	LinkList t = new ListNode;
	cin >> t->date;
	t->next = AccList;
	t->prev = AccList->prev;
	AccList->prev->next = t;
	AccList->prev = t;
	cout << "�����ɹ�" << endl;
}
void DeleteUserAccount(LinkList AccList)
{
	cout << "������Ҫɾ�����˺�" << endl;
}