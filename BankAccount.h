#pragma once
#include "BaseUser.h"
class BankAccount :
	public BaseUser
{
private://��Ա����
	int MyGender;
	long long MyTel;
	double MyDeposit;
public:
	static int NumBankAccount;
public://��Ա����

	/***���캯����ʼ����Ա����***/
	BankAccount(const std::string AfferentAccount ="", const  std::string AfferentPassword = "", const  std::string AfferentName = "", int AfferentGender=0, long long AfferentTel=0, double AfferentDeposit = 0);

	/***���ƹ��캯����ʼ����Ա����***/
	BankAccount(const BankAccount& OtherBankAccount);

	/***��������***/
	~BankAccount();

	/***��ó�Ա����MyGenderֵ***/
	int GetMyGender();

	/***��ó�Ա����MyTelֵ***/
	long long GetMyTel();

	/***��ó�Ա����MyDepositֵ***/
	double GetMyDeposit();

	/***�޸����***/
	void ModifyDeposit(double tem);

	/***���õ绰***/
	void SetTel(long long AfferentTel);

	/***ת��***/
	void Transfer(BankAccount& OtherBankAccount, double tem);

	/***cin����***/
	/***��˳������˺����������Ա�(01��ʾ)�ֻ���***/
	friend std::istream& operator>>(std::istream& i, BankAccount& tem);

	/***ifstream����***/
	/***��˳����ļ������˺����������Ա�(01��ʾ)�ֻ��Ŵ��***/
	friend std::ifstream& operator>>(std::ifstream& i, BankAccount& tem);

	/***ofstreamд��***/
	/***��˳�����ļ�д���˺����������Ա�(01��ʾ)�ֻ��Ŵ��***/
	friend std::ofstream& operator<<(std::ofstream& o, BankAccount& tem);
};


