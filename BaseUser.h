#pragma once
#include<string>
#include<iostream>
#include<fstream>
#include<iomanip>
class BaseUser
{
protected://��Ա����

	std::string MyAccount;
	std::string MyName;
	std::string MyPassword;

public://��Ա����
    /***���캯����ʼ����Ա����***/
	BaseUser(const std::string& AfferentAccount="", const  std::string& AfferentPassword = "", const  std::string& AfferentName = "");

	/***���ƹ��캯����ʼ����Ա����***/
	BaseUser(const BaseUser& OtherBaseUser);

	/***�޸�����***/
	void SetPassword(const std::string& NewPassword);

	/***��ó�Ա����MyAccountֵ***/
	std::string GetMyAccount();

	/***��ó�Ա����MyPasswordֵ***/
	std::string GetMyPassword();

	/***��ó�Ա����MyNameֵ***/
	std::string GetMyName();

	/***��������***/
	~BaseUser();
};