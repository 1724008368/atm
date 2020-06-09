#include "BankAccount.h"

//静态成员变量初始化
int BankAccount::NumBankAccount = 0;

/*******构造函数开始*******/
BankAccount::BankAccount(const std::string AfferentAccount, const  std::string AfferentPassword , const  std::string AfferentName , int AfferentGender , long long AfferentTel , double AfferentDeposit ) :BaseUser(AfferentAccount, AfferentPassword, AfferentName),MyGender(AfferentGender),MyTel(AfferentTel),MyDeposit(AfferentDeposit)
{
	NumBankAccount++;
}
/*******构造函数结束*******/

/*******复制构造函数开始*******/
BankAccount::BankAccount(const BankAccount& OtherBankAccount):BaseUser(OtherBankAccount), MyGender(OtherBankAccount.MyGender), MyTel(OtherBankAccount.MyTel), MyDeposit(OtherBankAccount.MyDeposit)
{
	NumBankAccount++;
}
/*******复制构造函数结束*******/

/*******析构函数开始*******/
BankAccount::~BankAccount()
{
	NumBankAccount--;
}
/*******析构函数结束*******/

/*******GetMyGender函数开始*******/
int BankAccount::GetMyGender()
{
	return MyGender;
}
/*******GetMyGender函数结束*******/

/*******GetMyTel函数开始*******/
long long BankAccount::GetMyTel()
{
	return MyTel;
}
/*******GetMyTel函数结束*******/

/*******GetMyDeposit函数开始*******/
double BankAccount::GetMyDeposit()
{
	return MyDeposit;
}
/*******GetMyDeposit函数结束*******/

/*******ModifyDeposit函数开始*******/
void BankAccount::ModifyDeposit(double tem)
{
	MyDeposit += tem;
}
/*******ModifyDeposit函数结束*******/

/*******SetTel函数开始*******/
void BankAccount::SetTel(long long AfferentTel)
{
	MyTel = AfferentTel;
}
/*******SetTel函数结束*******/

/*******Transfer函数开始*******/
void BankAccount::Transfer(BankAccount& OtherBankAccount, double tem)
{
	OtherBankAccount.ModifyDeposit(tem);
	this->ModifyDeposit(-tem);
}
/*******Transfer函数结束*******/

/*******cin读入函数开始*******/
std::istream& operator>>(std::istream& i, BankAccount& tem)
{
	i >> tem.MyAccount >> tem.MyPassword >> tem.MyName >> tem.MyGender >> tem.MyTel;
	i.ignore();
	return i;
}
/*******cin读入函数结束*******/

/*******ifstream读入开始*******/
std::ifstream& operator>>(std::ifstream& i, BankAccount& tem)
{
	i >> tem.MyAccount >> tem.MyPassword >> tem.MyName >> tem.MyGender >> tem.MyTel >> tem.MyDeposit>> tem.NumDepositChange>> tem.NumDepositInOut;
	i.ignore();
	return i;
}
/*******ifstream读入结束*******/

/*******ofstream写入开始*******/
std::ofstream& operator<<(std::ofstream& o, BankAccount& tem)
{
	o << tem.MyAccount << " "
		<< tem.MyPassword << " "
		<< tem.MyName << " " 
		<< tem.MyGender << " "
		<< tem.MyTel << " " 
		<< tem.MyDeposit <<" "
		<<tem.NumDepositChange << " " 
		<< tem.NumDepositInOut << 
		std::endl;
	return o;
}
/*******ofstream写入结束*******/

/*******cout输出开始*******/
std::ostream& operator<<(std::ostream& o, BankAccount& tem)
{
	o << std::left << std::setw(15) << tem.MyAccount
		<< std::left << std::setw(15) << tem.MyPassword
		<< std::left << std::setw(15) << tem.MyName 
		<< std::left << std::setw(15) << ((tem.MyGender==1)?"男":"女")
		<< std::left << std::setw(15) << tem.MyTel
		<< std::left << std::fixed<<std::setprecision(2)<<std::setw(15) << tem.MyDeposit 
		<< std::endl;
	return o;
}
/*******cout输出结束*******/

/*******存取款信息结构构造函数开始*******/
NumDepositChangeNode::NumDepositChangeNode(double TheMoney, double TheCurrentDeposit):Money(TheMoney), CurrentDeposit(TheCurrentDeposit)
{

}
/*******存取款信息结构构造函数结束*******/

/*******转账信息结构构造函数开始*******/
NumDepositInOutNode::NumDepositInOutNode(double TheMoney, double TheCurrentDeposit, std::string TheOtherAccount) :Money(TheMoney), CurrentDeposit(TheCurrentDeposit), OtherAccount(TheOtherAccount)
{

}
/*******存取款信息结构构造函数结束*******/