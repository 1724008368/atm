#include "BaseUser.h"
/*构造函数使用初始化列表初始化,同时使用常引用类型作为形式参数,减少内存和资源占用*/
/*构造函数和析构函数的函数体均为空*/

/*******构造函数开始*******/
BaseUser::BaseUser(const std::string& AfferentAccount, const  std::string& AfferentPassword , const std::string& AfferentName ) :MyAccount(AfferentAccount), MyName(AfferentName), MyPassword(AfferentPassword)
{}
/*******构造函数结束*******/

/*******复制构造函数开始*******/
BaseUser::BaseUser(const BaseUser& OtherBaseUser):MyAccount(OtherBaseUser.MyAccount), MyName(OtherBaseUser.MyName), MyPassword(OtherBaseUser.MyPassword)
{}
/*******复制构造函数结束*******/

/*******SetPassword函数开始*******/
void BaseUser::SetPassword(const std::string& NewPassword)
{
	MyPassword = NewPassword;
}
/*******SetPassword函数结束*******/

/*******SetName函数开始*******/
void BaseUser::SetName(const std::string& NewName)
{
	MyName = NewName;
}
/*******SetName函数结束*******/

/*******GetMyAccount函数开始*******/
std::string BaseUser::GetMyAccount()
{
	return MyAccount;
}
/*******GetMyAccount函数结束*******/

/*******GetMyName函数开始*******/
std::string BaseUser::GetMyName()
{
	return MyName;
}
/*******GetMyNamet函数结束*******/

/*******GetMyPassword函数开始*******/
std::string BaseUser::GetMyPassword()
{
	return MyPassword;
}
/*******GetMyPassword函数结束*******/

/*******析构函数开始*******/
BaseUser::~BaseUser()
{}
/*******析构函数结束*******/