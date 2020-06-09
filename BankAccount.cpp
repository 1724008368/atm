#include "BankAccount.h"

//��̬��Ա������ʼ��
int BankAccount::NumBankAccount = 0;

/*******���캯����ʼ*******/
BankAccount::BankAccount(const std::string AfferentAccount, const  std::string AfferentPassword , const  std::string AfferentName , int AfferentGender , long long AfferentTel , double AfferentDeposit ) :BaseUser(AfferentAccount, AfferentPassword, AfferentName),MyGender(AfferentGender),MyTel(AfferentTel),MyDeposit(AfferentDeposit)
{
	NumBankAccount++;
}
/*******���캯������*******/

/*******���ƹ��캯����ʼ*******/
BankAccount::BankAccount(const BankAccount& OtherBankAccount):BaseUser(OtherBankAccount), MyGender(OtherBankAccount.MyGender), MyTel(OtherBankAccount.MyTel), MyDeposit(OtherBankAccount.MyDeposit)
{
	NumBankAccount++;
}
/*******���ƹ��캯������*******/

/*******����������ʼ*******/
BankAccount::~BankAccount()
{
	NumBankAccount--;
}
/*******������������*******/

/*******GetMyGender������ʼ*******/
int BankAccount::GetMyGender()
{
	return MyGender;
}
/*******GetMyGender��������*******/

/*******GetMyTel������ʼ*******/
long long BankAccount::GetMyTel()
{
	return MyTel;
}
/*******GetMyTel��������*******/

/*******GetMyDeposit������ʼ*******/
double BankAccount::GetMyDeposit()
{
	return MyDeposit;
}
/*******GetMyDeposit��������*******/

/*******ModifyDeposit������ʼ*******/
void BankAccount::ModifyDeposit(double tem)
{
	MyDeposit += tem;
}
/*******ModifyDeposit��������*******/

/*******SetTel������ʼ*******/
void BankAccount::SetTel(long long AfferentTel)
{
	MyTel = AfferentTel;
}
/*******SetTel��������*******/

/*******Transfer������ʼ*******/
void BankAccount::Transfer(BankAccount& OtherBankAccount, double tem)
{
	OtherBankAccount.ModifyDeposit(tem);
	this->ModifyDeposit(-tem);
}
/*******Transfer��������*******/

/*******cin���뺯����ʼ*******/
std::istream& operator>>(std::istream& i, BankAccount& tem)
{
	i >> tem.MyAccount >> tem.MyPassword >> tem.MyName >> tem.MyGender >> tem.MyTel;
	i.ignore();
	return i;
}
/*******cin���뺯������*******/

/*******ifstream���뿪ʼ*******/
std::ifstream& operator>>(std::ifstream& i, BankAccount& tem)
{
	i >> tem.MyAccount >> tem.MyPassword >> tem.MyName >> tem.MyGender >> tem.MyTel >> tem.MyDeposit>> tem.NumDepositChange>> tem.NumDepositInOut;
	i.ignore();
	return i;
}
/*******ifstream�������*******/

/*******ofstreamд�뿪ʼ*******/
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
/*******ofstreamд�����*******/

/*******cout�����ʼ*******/
std::ostream& operator<<(std::ostream& o, BankAccount& tem)
{
	o << std::left << std::setw(15) << tem.MyAccount
		<< std::left << std::setw(15) << tem.MyPassword
		<< std::left << std::setw(15) << tem.MyName 
		<< std::left << std::setw(15) << ((tem.MyGender==1)?"��":"Ů")
		<< std::left << std::setw(15) << tem.MyTel
		<< std::left << std::fixed<<std::setprecision(2)<<std::setw(15) << tem.MyDeposit 
		<< std::endl;
	return o;
}
/*******cout�������*******/

/*******��ȡ����Ϣ�ṹ���캯����ʼ*******/
NumDepositChangeNode::NumDepositChangeNode(double TheMoney, double TheCurrentDeposit):Money(TheMoney), CurrentDeposit(TheCurrentDeposit)
{

}
/*******��ȡ����Ϣ�ṹ���캯������*******/

/*******ת����Ϣ�ṹ���캯����ʼ*******/
NumDepositInOutNode::NumDepositInOutNode(double TheMoney, double TheCurrentDeposit, std::string TheOtherAccount) :Money(TheMoney), CurrentDeposit(TheCurrentDeposit), OtherAccount(TheOtherAccount)
{

}
/*******��ȡ����Ϣ�ṹ���캯������*******/