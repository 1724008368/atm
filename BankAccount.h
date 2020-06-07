#pragma once
#include "BaseUser.h"
class BankAccount :
	public BaseUser
{
private://成员变量
	int MyGender;
	long long MyTel;
	double MyDeposit;
public:
	static int NumBankAccount;
public://成员函数

	/***构造函数初始化成员变量***/
	BankAccount(const std::string AfferentAccount ="", const  std::string AfferentPassword = "", const  std::string AfferentName = "", int AfferentGender=0, long long AfferentTel=0, double AfferentDeposit = 0);

	/***复制构造函数初始化成员变量***/
	BankAccount(const BankAccount& OtherBankAccount);

	/***析构函数***/
	~BankAccount();

	/***获得成员变量MyGender值***/
	int GetMyGender();

	/***获得成员变量MyTel值***/
	long long GetMyTel();

	/***获得成员变量MyDeposit值***/
	double GetMyDeposit();

	/***修改余额***/
	void ModifyDeposit(double tem);

	/***设置电话***/
	void SetTel(long long AfferentTel);

	/***转账***/
	void Transfer(BankAccount& OtherBankAccount, double tem);

	/***cin读入***/
	/***按顺序读入账号密码姓名性别(01表示)手机号***/
	friend std::istream& operator>>(std::istream& i, BankAccount& tem);

	/***ifstream读入***/
	/***按顺序从文件读入账号密码姓名性别(01表示)手机号存款***/
	friend std::ifstream& operator>>(std::ifstream& i, BankAccount& tem);

	/***ofstream写入***/
	/***按顺序向文件写入账号密码姓名性别(01表示)手机号存款***/
	friend std::ofstream& operator<<(std::ofstream& o, BankAccount& tem);
};


