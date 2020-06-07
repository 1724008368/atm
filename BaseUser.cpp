#include "BaseUser.h"
/*���캯��ʹ�ó�ʼ���б��ʼ��,ͬʱʹ�ó�����������Ϊ��ʽ����,�����ڴ����Դռ��*/
/*���캯�������������ĺ������Ϊ��*/

/*******���캯����ʼ*******/
BaseUser::BaseUser(const std::string& AfferentAccount, const  std::string& AfferentPassword , const std::string& AfferentName ) :MyAccount(AfferentAccount), MyName(AfferentName), MyPassword(AfferentPassword)
{}
/*******���캯������*******/

/*******���ƹ��캯����ʼ*******/
BaseUser::BaseUser(const BaseUser& OtherBaseUser):MyAccount(OtherBaseUser.MyAccount), MyName(OtherBaseUser.MyName), MyPassword(OtherBaseUser.MyPassword)
{}
/*******���ƹ��캯������*******/

/*******SetPassword������ʼ*******/
void BaseUser::SetPassword(const std::string& NewPassword)
{
	MyPassword = NewPassword;
}
/*******SetPassword��������*******/

/*******SetName������ʼ*******/
void BaseUser::SetName(const std::string& NewName)
{
	MyName = NewName;
}
/*******SetName��������*******/

/*******GetMyAccount������ʼ*******/
std::string BaseUser::GetMyAccount()
{
	return MyAccount;
}
/*******GetMyAccount��������*******/

/*******GetMyName������ʼ*******/
std::string BaseUser::GetMyName()
{
	return MyName;
}
/*******GetMyNamet��������*******/

/*******GetMyPassword������ʼ*******/
std::string BaseUser::GetMyPassword()
{
	return MyPassword;
}
/*******GetMyPassword��������*******/

/*******����������ʼ*******/
BaseUser::~BaseUser()
{}
/*******������������*******/