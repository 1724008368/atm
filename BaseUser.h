#pragma once
#include<string>
#include<iostream>
#include<fstream>
#include<iomanip>
class BaseUser
{
protected://成员变量

	std::string MyAccount;
	std::string MyName;
	std::string MyPassword;

public://成员函数
    /***构造函数初始化成员变量***/
	BaseUser(const std::string& AfferentAccount="", const  std::string& AfferentPassword = "", const  std::string& AfferentName = "");

	/***复制构造函数初始化成员变量***/
	BaseUser(const BaseUser& OtherBaseUser);

	/***修改密码***/
	void SetPassword(const std::string& NewPassword);

	/***获得成员变量MyAccount值***/
	std::string GetMyAccount();

	/***获得成员变量MyPassword值***/
	std::string GetMyPassword();

	/***获得成员变量MyName值***/
	std::string GetMyName();

	/***析构函数***/
	~BaseUser();
};