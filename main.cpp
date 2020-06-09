//ͷ�ļ���include
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

//ʵ�ְ�����ƴ���Ƚ�
//����Ҳ���,������
#ifdef _MSC_VER
static const char* ZH_CN_LOCALE_STRING = "Chinese_china";
#else
static const char* ZH_CN_LOCALE_STRING = "zh_CN.utf8";
#endif
static const std::locale zh_CN_locale = std::locale(ZH_CN_LOCALE_STRING);
static const std::collate<char>& zh_CN_collate = std::use_facet<std::collate<char> >(zh_CN_locale);

//����Ա�˺�����
const std::string AdministratorAccount = "root";
const std::string AdministratorPassword = "root";

//��������
using ListNode = struct ListNode;
using LinkList = ListNode*;
using DoubleLinkList = std::pair<LinkList, LinkList>;

struct ListNode//˫������
{
	//������
	BankAccount date;
	//ָ����
	LinkList prev = nullptr;//������ʼ��
	LinkList next = nullptr;
};


//���õ�std�����ռ�ĳ�Ա������,ǰ��ûд,������Ĳ���дstd::��,��������Щ
using std::cin;
using std::cout;
using std::endl;
using std::string;
/************************ϵͳ������غ���****************************/

//��������
DoubleLinkList CreateList();

//��ӭ��
int Welcome();

//������
void Exit(DoubleLinkList AccList);

//���ļ������˻���Ϣ
void ReadFromFile1(DoubleLinkList AccList);

//���ļ������ȡ����Ϣ
void ReadFromFile2(DoubleLinkList AccList);

//���ļ�����ת����Ϣ
void ReadFromFile3(DoubleLinkList AccList);

//�����˻���Ϣ
void SaveToFile1(LinkList AccList);

//�����ȡ����Ϣ
void SaveToFile2(LinkList AccList);

//����
void SaveToFile3(LinkList AccList);

/************************ϵͳ������غ���****************************/

/************************�û�������غ���****************************/

//��ͨ�û���������
void UserInterface(DoubleLinkList AccList);

//�ж��˺��Ƿ����
bool CheckAccount(LinkList AccList, const std::string& InAccount);

//�ж������Ƿ���ȷ
bool CheckPassword(LinkList AccList, const std::string& InAccount, const std::string& InPassword);

//�ж��˺ź������Ƿ���Ӧ
bool CheckAccountName(LinkList AccList, const std::string& InAccount, const std::string& InName);

//��ʼ��map<string,int>ӳ��
void MapInitialization(LinkList AccList, std::map<std::string, int>& TemWrongPassword);

//��ѯ��������
void QueryPrintDeposit(LinkList AccList, const std::string& InAccount);

//������
void TakeInDeposit(LinkList AccList, const std::string& InAccount);

//ȡ�����
void TakeOutDeposit(LinkList AccList, const std::string& InAccount);

//ת�˲���
void GiveOtherDeposit(LinkList AccList, const std::string& InAccount);

//�û��޸�����
void UserChangePassword(LinkList AccList, const std::string& InAccount);

/************************�û�������غ���****************************/

/************************����Ա������غ���****************************/

//����Ա��������
void AdministratorInterface(DoubleLinkList AccList);

//��ѯ��ˮ
void QueryFlowingWater(LinkList AccList, const std::string& InAccount);

//�����û��˺�
void CreateUserAccount(DoubleLinkList AccList);

//ɾ���û��˺�
void DeleteUserAccount(LinkList AccList);

//չʾ�û���Ϣ
void ShowAllUsersInformation(LinkList AccList);

//���˺Ž�������(ѡ������)
void UsersAccountDown(LinkList AccList);

//���˺���������(ѡ������)
void UsersAccountUp(LinkList AccList);

//����������(ѡ������)
void UsersDepositDown(LinkList AccList);

//�������������(ѡ������)
void UsersDepositUp(LinkList AccList);

//������ȫƴ��������(ѡ������)
void UsersNameDown(LinkList AccList);

//������ȫƴ��������(ѡ������)
void UsersNameUp(LinkList AccList);

//�����û���Ϣ
void FindUserInformation(LinkList AccList);

//�޸��û���Ϣ
void ChangeUserInformation(LinkList AccList);

//����������
void SingleConditionSearch(LinkList AccList);

//���Ա�����û�
void GenderSearch(LinkList AccList);

//�����������û�
void NameSearch(LinkList AccList);

//���ֻ��Ų����û�
void TelSearch(LinkList AccList);

//���������û�
void DepositSearch(LinkList AccList);

//���Ҵ��С��ĳ�����û�
void SearchLowerThanDeposit(LinkList AccList, const double& AfferentDeposit);

//���Ҵ����ڵ���ĳ�����û�
void SearchUpperThanDeposit(LinkList AccList, const double& AfferentDeposit);

//ģ������
void FuzzySearch(LinkList AccList);

//�����ϲ����û�
void SearchAsSurname(LinkList AccList);

//�������ؼ��ʲ����û�
void SearchAsKeyWord(LinkList AccList);

//���ֻ���ǰ��λ�����û�
void SearchAsTelTopThree(LinkList AccList);

//���ֻ��ź���λ�����û�
void SearchAsTelLastFour(LinkList AccList);

//ͳ��������������Ϣ
void StatisticalInformation(LinkList AccList);

//�鿴�û��˵�
void SeeUserBill(LinkList AccList);

//�鿴��ȡ���˵�
void DepositInOutBill(LinkList AccList, const std::string& InAccount);

//�鿴ת���˵�
void DepositChangeBill(LinkList AccList, const std::string& InAccount);

/************************����Ա������غ���****************************/

//������
int main()
{
	DoubleLinkList AccList = CreateList();//��������
	ReadFromFile1(AccList);//��ʼ���ļ�
	ReadFromFile2(AccList);
	ReadFromFile3(AccList);
	while (int t = Welcome()) {//���������n������غ���
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

	//������ʱ�Ѿ���next��prev����ʼ��Ϊ��nullptr
	p->next = t;
	t->prev = p;
	return { p,t };//����һ��pair��������

}

void ReadFromFile1(DoubleLinkList AccList)
{
	LinkList p = AccList.second;
	std::ifstream in("AccountInformation.txt");//��ifstreamĬ�Ϸ�ʽ���ļ�

	if (!in.is_open())
		cout << "AccountInformation.txt�ļ���ʧ��" << endl;
	while (in.peek() != EOF) {//��peek������eof����ֹ�����һ������
		LinkList t = new ListNode;

		t->next = p;//˫������β�巨������
		t->prev = p->prev;
		p->prev->next = t;
		p->prev = t;

		in >> t->date;
	}
	in.close();//�ر�
}

void ReadFromFile2(DoubleLinkList AccList)
{
	LinkList p = AccList.first->next;
	std::ifstream in("DepositChangeInformation.txt");

	if (!in.is_open())
		cout << "DepositChangeInformation.txt�ļ���ʧ��" << endl;
	while (p->next != nullptr) {//���ζ���

		(p->date).DepositChangeData.resize((p->date).NumDepositChange);//����vector�Ĵ�С
		for (int i = 0; i < (p->date).NumDepositChange; i++) {//���ζ���ÿ��ת�˼�¼
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
		cout << "DepositInOutInformation.txt�ļ���ʧ��" << endl;
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
		cout << "AccountInformation.txt�ļ���ʧ��" << endl;
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
		cout << "DepositChangeInformation.txt�ļ���ʧ��" << endl;
	}
	while (p->next != nullptr) {
		for (int i = 0; i < (p->date).NumDepositChange; i++) {//�ǵ��ÿո�ͻس��ֿ�
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
		cout << "DepositInOutInformation.txt�ļ���ʧ��" << endl;
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
	std::cout << "��ӭʹ��������ATM������ϵͳ\n"
		<< "��ѡ����Ӧ�İ�ť,���س�������\n"
		<< "----------[1] �û���¼----------\n"
		<< "----------[2] ����Ա��¼--------\n"
		<< "----------[3] �˳�--------------"
		<< std::endl;
	int n;
	std::cin >> n;
	return n;
}

void Exit(DoubleLinkList AccList)
{
	LinkList p = AccList.first;
	LinkList t = p->next;
	while (p != nullptr) {//����ɾ��
		t = p->next;
		delete p;
		p = t;
	}

	std::cout << "----------��ӭ�´�ʹ��----------" << std::endl;
	exit(0);
}

void UserInterface(DoubleLinkList AccList)
{
	std::map<std::string, int> WrongPassword;//����һ����¼�˺�������������map
	MapInitialization(AccList.first, WrongPassword);//��ʼ��
	std::string TemAccount = "", TemPassword = "";

	while (true) {//������������˺�����,��Ȼ��ѭ��

		TemAccount = "", TemPassword = "";
		std::cout << "�������˺�" << std::endl;
		std::cin >> TemAccount;
		//std::cin.ignore();
		if (CheckAccount(AccList.first, TemAccount) == false) {
			system("cls");
			std::cout << "�˺Ŵ���,����������" << std::endl;
			continue;
		}
		if (WrongPassword[TemAccount] >= 3) {//������󳬹�����
			system("cls");
			std::cout << "���˺�������" << std::endl;
			continue;
		}

		system("cls");
		cout << "�˺���ȷ" << endl;
		std::cout << "����������,���δ����˺Ž�������" << std::endl;
		char ch;

		//_getch()��������,�ӿ���̨���һ���ַ�,����������,ͬʱwindowsƽ̨�µĻس��ı�ʾʱ'\r\n',����س�ʱch��ʾ���ַ�ʱ'\r',����ѭ��

		while (ch = _getch(), ch != '\r') {
			if (ch == '\b') {//���������Backspase��
				if (TemPassword.size()) {//��Ļ�����е�'*'�ַ������õ�ǰ����ĳ��ȱ�ʾ
					putchar('\b');//�˸�
					putchar(' ');//��ӡ�ո񸲸�ԭ'*'
					putchar('\b');//���˸�
				}
				if (TemPassword.size())
					TemPassword.erase(TemPassword.size() - 1, 1);//���µ�ǰ����

			}
			else {//��Ϊ������
				TemPassword = TemPassword + ch;//��������
				putchar('*');//��Ļ��ʾ*
			}
		}
		std::cout << std::endl;
		if (CheckPassword(AccList.first, TemAccount, TemPassword) == false) {//�ж������Ƿ���ȷ

			system("cls");
			std::cout << "�������,����������" << std::endl;
			WrongPassword[TemAccount] = WrongPassword[TemAccount] + 1;//������������������һ
			continue;
		}
		else {
			system("cls");
			std::cout << "������ȷ,��½�ɹ�" << std::endl;
			break;
		}
		//std::cout << TemAccount << std::endl << TemPassword << std::endl;
	}

	while (true) {//�˵�����
		std::cout << "��ѡ����Ӧ�İ�ť,���س�������\n" << "[1] ��ѯ���\n" << "[2] ���\n" << "[3] ȡ��\n" << "[4] ת��\n" << "[5] �޸�����\n" << "[6] ��ѯ��ˮ\n" << "[7] �˿�\n" << std::endl;
		int n;
		std::cin >> n;
		if (n == 1) {
			system("cls");
			QueryPrintDeposit(AccList.first, TemAccount);
			system("pause");
			system("cls");
		}
		else if (n == 2) {//��Ϣ�����ı�,�����ļ�
			system("cls");
			TakeInDeposit(AccList.first, TemAccount);
			SaveToFile1(AccList.first);
			SaveToFile2(AccList.first);
			SaveToFile3(AccList.first);
			system("pause");
			system("cls");

		}
		else if (n == 3) {//��Ϣ�����ı�,�����ļ�
			system("cls");
			TakeOutDeposit(AccList.first, TemAccount);
			SaveToFile1(AccList.first);
			SaveToFile2(AccList.first);
			SaveToFile3(AccList.first);
			system("pause");
			system("cls");


		}
		else if (n == 4) {//��Ϣ�����ı�,�����ļ�
			system("cls");
			GiveOtherDeposit(AccList.first, TemAccount);
			SaveToFile1(AccList.first);
			SaveToFile2(AccList.first);
			SaveToFile3(AccList.first);
			system("pause");
			system("cls");


		}
		else if (n == 5) {//��Ϣ�����ı�,�����ļ�
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
	while (Temp->next != nullptr) {//δ����β�ڵ�,���Բ���
		if ((Temp->date).GetMyAccount() == InAccount)//�ҵ��˴��˺�
			return true;
		Temp = Temp->next;
	}
	return false;
}
bool CheckPassword(LinkList AccList, const std::string& InAccount, const std::string& InPassword)
{
	LinkList Temp = AccList->next;
	while (Temp->next != nullptr) {//δ����β�ڵ�,���Բ���
		if ((Temp->date).GetMyAccount() == InAccount && (Temp->date).GetMyPassword() == InPassword)//�ҵ��˴��˺�ͬʱ������ȷ
			return true;
		Temp = Temp->next;
	}
	return false;
}

bool CheckAccountName(LinkList AccList, const std::string& InAccount, const std::string& InName)
{
	LinkList Temp = AccList->next;
	while (Temp->next != nullptr) {//δ����β�ڵ�,���Բ���
		if ((Temp->date).GetMyAccount() == InAccount && (Temp->date).GetMyName() == InName)//�ҵ��˴��˺�ͬʱ������ȷ
			return true;
		Temp = Temp->next;
	}
	return false;
}

void MapInitialization(LinkList AccList, std::map<std::string, int>& TemWrongPassword)//ʹ�������������޸�ʵ��
{
	LinkList p = AccList->next;
	while (p->next != nullptr) {//����
		TemWrongPassword.insert(std::make_pair((p->date).GetMyAccount(), 0));//ÿ����map�в���pair<�˺�,0>
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

		system("cls");
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
			//�޸ĸ��˺Ŵ�ȡ������
			(p->date).DepositChangeData.push_back(NumDepositChangeNode(money, (p->date).GetMyDeposit()));//vector�������
			(p->date).NumDepositChange++;//��ˮ������һ
			SYSTEMTIME sys;//windowsAPI��ȡʱ�䲢����ת��Ϊ�ַ�����ʽ
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
	system("cls");
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
	else if (n == 2) {//ɶ������

	}

}
void TakeOutDeposit(LinkList AccList, const std::string& InAccount)
{
	int n;
	int money = 0;
	std::cout << "��ѡ��ȡ����\n" << "[1] 100\t" << "[2] 200\n" << "[3] 500\t" << "[4] 1000\n" << "[5] 2000" << "[6] �������" << std::endl;
	std::cin >> n;

	system("cls");
	if (n == 1) money = 100;
	else if (n == 2) money = 200;
	else if (n == 3) money = 500;
	else if (n == 4) money = 1000;
	else if (n == 5) money = 2000;
	else if (n == 6) {
		while (true) {
			std::cout << "������ȡ����(100������),������5000" << std::endl;
			std::cin >> money;
			system("cls");
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
			if ((p->date).GetMyDeposit() < money) {//�ж�Ǯ������
				cout << "����" << endl;
				return;
			}
			(p->date).ModifyDeposit(-money);
			//�����޸Ĵ�ȡ������
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

	system("cls");
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
		system("cls");
		if (TurnOutAccount == InAccount) {//ת�˺Ϸ����ж�
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
	system("cls");
	if (CheckAccountName(AccList, TurnOutAccount, TurnOutName) == false) {//ת�˺Ϸ����ж�
		cout << "�˺ź�������ƥ��" << endl;
		return;
	}

	int n;
	int money = 0;
	std::cout << "��ѡ��ת�˽��\n" << "[1] 100\t\t" << "[2] 200\n" << "[3] 500\t\t" << "[4] 1000\n" << "[5] 2000\t" << "[6] �������" << std::endl;

	std::cin >> n;
	system("cls");
	if (n == 1) money = 100;
	else if (n == 2) money = 200;
	else if (n == 3) money = 500;
	else if (n == 4) money = 1000;
	else if (n == 5) money = 2000;
	else if (n == 6) {
		while (true) {
			std::cout << "������ת�˽��(100������),������5000" << std::endl;
			std::cin >> money;
			system("cls");
			if (money % 100 || money <= 0 || money > 5000) {//�ж�ȡ�����Ƿ�Ϸ�
				cout << "ת�˽������,����������" << endl;
			}
			else
				break;
		}
	}

	LinkList p = AccList->next;
	while (p->next != nullptr) {//�����Լ��˻��ۿ�
		if (InAccount == (p->date).GetMyAccount()) {
			if ((p->date).GetMyDeposit() < money) {//�жϴ�����
				cout << "����" << endl;
				return;
			}
			/*Ǯ��*/
			(p->date).ModifyDeposit(-money);

			(p->date).DepositInOutData.push_back(NumDepositInOutNode(-money, (p->date).GetMyDeposit(), TurnOutAccount));//�ϴ�ȡ���һ������,Ϊ���Ǽ�¼ת�˵���һ���˺�
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

			(p->date).DepositInOutData.push_back(NumDepositInOutNode(money, (p->date).GetMyDeposit(), InAccount));//��Ǯ�Ķ���Ҳ����ת������,��Ǯ��
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
	system("cls");
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

void UserChangePassword(LinkList AccList, const std::string& InAccount)
{
	string TemPassword = "", NewPassword = "", SureNewPassword = "";
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
	cout << endl;
	system("cls");

	if (CheckPassword(AccList, InAccount, TemPassword) == false) {
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
	cout << endl;

	system("cls");

	if (TemPassword == NewPassword) {
		cout << "�������ԭ������ͬ" << endl;
		return;
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
	cout << endl;

	system("cls");
	if (SureNewPassword == NewPassword) {//�����жϳɹ���ſ��Ը�
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

void AdministratorInterface(DoubleLinkList AccList)
{

	std::string TemAccount = "", TemPassword = "";
	while (true) {
		TemAccount = "", TemPassword = "";
		std::cout << "�������˺�" << std::endl;
		std::cin >> TemAccount;
		system("cls");
		//std::cin.ignore();
		if (TemAccount != AdministratorAccount) {
			std::cout << "�˺Ŵ���,����������" << std::endl;
			continue;
		}
		system("cls");
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
		system("cls");
		if (TemPassword != AdministratorPassword) {
			std::cout << "�������,����������" << std::endl;
		}
		else {
			std::cout << "������ȷ,��½�ɹ�" << std::endl;
			break;
		}
		//std::cout << TemAccount << std::endl << TemPassword << std::endl;
	}

	int n;
	while (true) {//����Ա�˵�����

		cout << "[1] �����û��˻�\n"
			<< "[2] ɾ���û��˻�\n"
			<< "[3] �鿴ȫ���û���Ϣ\n"
			<< "[4] �����û���Ϣ\n"
			<< "[5] �޸��û���Ϣ\n"
			<< "[6] ����������\n"
			<< "[7] ģ������\n"
			<< "[8] ͳ����Ϣ\n"
			<< "[9] �鿴�û���ˮ\n"
			<< "[10] �˳�"
			<< endl;
		cin >> n;
		if (n == 1) {//�û���Ϣ�ı�,�����ļ�

			system("cls");
			CreateUserAccount(AccList);
			SaveToFile1(AccList.first);
			SaveToFile2(AccList.first);
			SaveToFile3(AccList.first);
			system("pause");
			system("cls");
		}
		else if (n == 2) {//�û���Ϣ�ı�,�����ļ�
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
		else if (n == 5) {//�û���Ϣ�ı�,�����ļ�
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
void CreateUserAccount(DoubleLinkList AccList)//�������ͷβָ��
{
	cout << "���������� �˺� ���� ���� �Ա�(01��ʾ) �ֻ���" << endl;
	LinkList t = new ListNode;
	cin >> t->date;
	system("cls");

	if (CheckAccount(AccList.first, (t->date).GetMyAccount()) == true) {//���ж����˺��Ƿ��Ѿ�����
		cout << "���˺��Ѵ���,����ʧ��" << endl;
		delete t;
		return;
	}
	t->next = AccList.second;//˫������β��
	t->prev = AccList.second->prev;
	AccList.second->prev->next = t;
	AccList.second->prev = t;
	cout << "�����ɹ�" << endl;

}
void DeleteUserAccount(LinkList AccList)
{

	string TemAccount = "";
	while (true) {//�Ϸ����ж�
		cout << "������Ҫɾ�����˺�" << endl;
		cin >> TemAccount;
		system("cls");

		if (CheckAccount(AccList, TemAccount) == false) {
			cout << "�˺Ų�����,����������" << endl;
		}
		else {
			break;
		}
	}
	LinkList p = AccList->next;
	while (p->next != nullptr) {
		if ((p->date).GetMyAccount() == TemAccount) {//�ҵ�λ�ú��˳�
			break;
		}
		p = p->next;
	}
	p->prev->next = p->next;//˫�����ŵ�������
	p->next->prev = p->prev;
	delete p;//�ͷ��ڴ�
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
	system("cls");

	//��������,����ѡ������
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
	if (BankAccount::NumBankAccount > 2) {//Ҫ������Ϊ��
		cout << std::left << std::setw(15) << "�˺�"
			<< std::left << std::setw(15) << "����"
			<< std::left << std::setw(15) << "����"
			<< std::left << std::setw(15) << "�Ա�"
			<< std::left << std::setw(15) << "�ֻ���"
			<< std::left << std::setw(15) << "���"
			<< endl;
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
			if ((j->date).GetMyAccount() > (i->date).GetMyAccount()) {//ûɶ,��������������ôд��
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
			char* s1 = new char[30];//�����ڴ����������
			char* s2 = new char[30];
			//string��c_str�������ص��Ǹ���ʱָ��,�������ִ�к�ͻ��ɸ�Ұָ��,���Ե���strcpy�����Ƶ�ȷ����λ��
			strcpy(s1, (i->date).GetMyName().c_str());
			strcpy(s2, (j->date).GetMyName().c_str());
			if (zh_CN_collate.compare(s1, s1 + (i->date).GetMyName().size(), s2, s2 + (j->date).GetMyName().size()) < 0) {//����漰���ҵ�֪ʶä����,����Ӧ�ú�strcmp���
				std::swap(i->date, j->date);
			}
			delete[]s1;//�ͷ��ڴ�!!!
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
		cout << "������Ҫ���ҵ��˺�" << endl;
		cin >> TemAccount;
		system("cls");
		if (CheckAccount(AccList, TemAccount) == false) {
			cout << "�˺Ų�����,����������" << endl;
		}
		else {
			break;
		}
	}

	cout << std::left << std::setw(15) << "�˺�"
		<< std::left << std::setw(15) << "����"
		<< std::left << std::setw(15) << "����"
		<< std::left << std::setw(15) << "�Ա�"
		<< std::left << std::setw(15) << "�ֻ���"
		<< std::left << std::setw(15) << "���"
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
		cout << "��������Ҫ�޸ĵ��˺�" << endl;
		cin >> TemAccount;
		system("cls");

		if (CheckAccount(AccList, TemAccount) == false) {
			cout << "�˺Ų�����,����������" << endl;
		}
		else {
			break;
		}
	}

	LinkList p = AccList->next;
	while (p->next != nullptr) {
		if ((p->date).GetMyAccount() == TemAccount) {//�ҵ���ַ
			break;
		}
		p = p->next;
	}

	int n;
	cout << "��ѡ���޸ĵ���Ϣ\n"
		<< "[1] ����\n"
		<< "[2] ����\n"
		<< "[3] �ֻ���\n"
		<< "[4] ���"
		<< endl;
	cin >> n;
	if (n == 1) {//����Ա��������Ȼ���ü��ܴ���
		cout << "������������" << endl;
		string TemPassword;
		cin >> TemPassword;
		system("cls");
		if ((p->date).GetMyPassword() == TemPassword) {
			cout << "��������ԭ������ͬ,�޸�ʧ��" << endl;
			return;
		}

		(p->date).SetPassword(TemPassword);
		cout << "�����޸ĳɹ�" << endl;

	}

	else if (n == 2) {

		cout << "������������" << endl;
		string TemName;
		cin >> TemName;
		system("cls");

		if ((p->date).GetMyName() == TemName) {
			cout << "��������ԭ������ͬ,�޸�ʧ��" << endl;
			return;
		}

		(p->date).SetName(TemName);
		cout << "�����޸ĳɹ�" << endl;

	}
	else if (n == 3) {
		cout << "���������ֻ���" << endl;
		long long TemTel;
		cin >> TemTel;
		system("cls");

		if ((p->date).GetMyTel() == TemTel) {
			cout << "���ֻ�����ԭ�ֻ�����ͬ,�޸�ʧ��" << endl;
			return;
		}

		(p->date).SetTel(TemTel);
		cout << "�ֻ����޸ĳɹ�" << endl;

	}
	//�޸Ĳ���Ĭ��Ϊ��ȡ��,������ʾ���,������ʾȡ��
	else if (n == 4) {
		cout << "�������޸ĵĴ��,������ʾ������" << endl;
		double t;
		cin >> t;
		system("cls");
		if (t == 0) {
			cout << "���������Ϊһ������ֵ" << endl;
			return;
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


	}

}

void SingleConditionSearch(LinkList AccList)
{
	cout << "��ѡ������" << endl;
	cout << "[1] ���Ա��ѯ\n"
		<< "[2] ��������ѯ\n"
		<< "[3] ���ֻ��Ų�ѯ\n"
		<< "[4] ������ѯ"
		<< endl;
	int n;
	cin >> n;
	system("cls");

	//һ���˿��Կ��ܶ������п�,������п����԰�һ���ֻ���
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
	cout << "������Ҫ��ѯ���Ա�,1��ʾ����,0��ʾŮ��" << endl;
	int n;
	cin >> n;
	system("cls");

	if (n == 0 || n == 1) {//�������Ҫ��
		bool IsFind = false;//�ȼ���û�з���Ҫ����û�

		LinkList p = AccList->next;
		while (p->next != nullptr) {
			if ((p->date).GetMyGender() == n) {
				if (IsFind == false) {//����ǵ�һ���ҵ�,���������
					cout << std::left << std::setw(15) << "�˺�"
						<< std::left << std::setw(15) << "����"
						<< std::left << std::setw(15) << "����"
						<< std::left << std::setw(15) << "�Ա�"
						<< std::left << std::setw(15) << "�ֻ���"
						<< std::left << std::setw(15) << "���"
						<< endl;
				}

				cout << p->date;
				IsFind = true;//����IsFind
			}
			p = p->next;
		}
		if (IsFind == false) {//������һ����û�ҵ�
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
	system("cls");

	bool IsFind = false;
	LinkList p = AccList->next;
	while (p->next != nullptr) {
		if ((p->date).GetMyName() == TemName) {
			if (IsFind == false) {
				cout << std::left << std::setw(15) << "�˺�"
					<< std::left << std::setw(15) << "����"
					<< std::left << std::setw(15) << "����"
					<< std::left << std::setw(15) << "�Ա�"
					<< std::left << std::setw(15) << "�ֻ���"
					<< std::left << std::setw(15) << "���"
					<< endl;
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
	system("cls");

	bool IsFind = false;
	LinkList p = AccList->next;
	while (p->next != nullptr) {
		if ((p->date).GetMyTel() == TemTel) {
			if (IsFind == false) {
				cout << std::left << std::setw(15) << "�˺�"
					<< std::left << std::setw(15) << "����"
					<< std::left << std::setw(15) << "����"
					<< std::left << std::setw(15) << "�Ա�"
					<< std::left << std::setw(15) << "�ֻ���"
					<< std::left << std::setw(15) << "���"
					<< endl;
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
	system("cls");

	cout << "��ѡ���ѯ��ʽ\n"
		<< "[1] ��ѯ���С�ڸ�ֵ���û�\n"
		<< "[2] ��ѯ��С�ڸ�ֵ���û�";
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
				cout << std::left << std::setw(15) << "�˺�"
					<< std::left << std::setw(15) << "����"
					<< std::left << std::setw(15) << "����"
					<< std::left << std::setw(15) << "�Ա�"
					<< std::left << std::setw(15) << "�ֻ���"
					<< std::left << std::setw(15) << "���"
					<< endl;
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
				cout << std::left << std::setw(15) << "�˺�"
					<< std::left << std::setw(15) << "����"
					<< std::left << std::setw(15) << "����"
					<< std::left << std::setw(15) << "�Ա�"
					<< std::left << std::setw(15) << "�ֻ���"
					<< std::left << std::setw(15) << "���"
					<< endl;
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
	cout << "[1] �����ϲ���(��֧�ָ���)\n"
		<< "[2] �������йؼ��ֲ�ѯ\n"
		<< "[3] ���ֻ���ǰ��λ��ѯ\n"
		<< "[4] ���ֻ��ź���λ��ѯ" << endl;
	int n;
	cin >> n;
	system("cls");

	//������˼ά
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
		system("cls");

		if (TemName.size() != 2) {//һ�����ĺ���ռ�����ֽ�
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

		//string��find�������ص�һ���ҵ��Ǹ��Ӵ���λ�����ַ����±�,���û���ҵ�,����npos,����һ������,��ʾsize_t�����ֵ4294967295,��Ȼ����������±�0,��������ƥ������
		if ((p->date).GetMyName().find(TemName) == 0) {
			if (IsFind == false) {
				cout << std::left << std::setw(15) << "�˺�"
					<< std::left << std::setw(15) << "����"
					<< std::left << std::setw(15) << "����"
					<< std::left << std::setw(15) << "�Ա�"
					<< std::left << std::setw(15) << "�ֻ���"
					<< std::left << std::setw(15) << "���"
					<< endl;
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
	system("cls");

	bool IsFind = false;
	LinkList p = AccList->next;
	while (p->next != nullptr) {
		if ((p->date).GetMyName().find(TemName) != string::npos) {//������npos�����ҵ���
			if (IsFind == false) {
				cout << std::left << std::setw(15) << "�˺�"
					<< std::left << std::setw(15) << "����"
					<< std::left << std::setw(15) << "����"
					<< std::left << std::setw(15) << "�Ա�"
					<< std::left << std::setw(15) << "�ֻ���"
					<< std::left << std::setw(15) << "���"
					<< endl;
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
		system("cls");

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
		if ((p->date).GetMyTel() / 100000000 == RealTel) {//Ĭ���ֻ�����11λ��,ʹ��longlong�洢
			if (IsFind == false) {
				cout << std::left << std::setw(15) << "�˺�"
					<< std::left << std::setw(15) << "����"
					<< std::left << std::setw(15) << "����"
					<< std::left << std::setw(15) << "�Ա�"
					<< std::left << std::setw(15) << "�ֻ���"
					<< std::left << std::setw(15) << "���"
					<< endl;
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
		system("cls");

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
		if ((p->date).GetMyTel() % 10000 == RealTel) {//ȡ�ú���λ
			if (IsFind == false) {
				cout << std::left << std::setw(15) << "�˺�"
					<< std::left << std::setw(15) << "����"
					<< std::left << std::setw(15) << "����"
					<< std::left << std::setw(15) << "�Ա�"
					<< std::left << std::setw(15) << "�ֻ���"
					<< std::left << std::setw(15) << "���"
					<< endl;
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
	//��̬��Ա����ʹ��,��Ϊ����β���,������ʵ���û�����Ҫ��ȥ2
	cout << "�����������û���: " << BankAccount::NumBankAccount - 2 << endl;
	double SumDeposit = 0;
	int Mr = 0, Mrs = 0;
	LinkList p = AccList->next;
	while (p->next != nullptr) {//�ֱ�ͳ�����Ժ�Ů������,���ܽ�Ǯ
		if ((p->date).GetMyGender() == 1) {
			Mr++;
		}
		else {
			Mrs++;
		}
		SumDeposit += (p->date).GetMyDeposit();
		p = p->next;
	}

	cout << "���� : " << Mr << " λ  " << "Ů�� : " << Mrs << " λ" << endl;

	cout << "�����������ܴ����: " << std::fixed << std::setprecision(2) << SumDeposit << endl;

}


void QueryFlowingWater(LinkList AccList, const std::string& InAccount)
{
	int n;
	cout << "��ѡ����Ӧ�İ�ť\n" << "[1] ��ȡ����ˮ\t" << "[2] ת����ˮ" << endl;
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

			//�����ʱ�����ڱȽϳ�,��25��ȸ�ʽ�����
			if ((p->date).NumDepositChange == 0) {
				cout << "�޴�ȡ����ˮ��Ϣ" << endl;
			}
			else {
				cout << std::left << std::setw(15) << "��Ϊ"
					<< std::left << std::setw(15) << "�˺�"
					<< std::left << std::setw(25) << "ʱ��"
					<< std::left << std::setw(15) << "���䶯"
					<< std::left << std::setw(15) << "��ǰ���"
					<< endl;
				for (auto& ans : (p->date).DepositChangeData) {
					cout << std::left << std::setw(15) << (ans.Money > 0 ? "���" : "ȡ��")
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
				cout << "��ת����ˮ��Ϣ" << endl;
			}
			else {
				cout << std::left << std::setw(15) << "��Ϊ"
					<< std::left << std::setw(15) << "ת���˺�"
					<< std::left << std::setw(15) << "ת���˺�"
					<< std::left << std::setw(25) << "ʱ��"
					<< std::left << std::setw(15) << "���䶯"
					<< std::left << std::setw(15) << "��ǰ���"
					<< endl;
				for (auto& ans : (p->date).DepositInOutData) {
					cout << std::left << std::setw(15) << (ans.Money > 0 ? "ת��" : "ת��")
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
		cout << "������Ҫ�鿴���˺�" << endl;
		cin >> TemAccount;
		system("cls");

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