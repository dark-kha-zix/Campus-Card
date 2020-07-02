#pragma once

#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <ctime>
using namespace std;

#define MAX_LIMIT 500;				//消费、充值限额
//卡处于丢失状态
//卡在手里面

const int LOSS_STATE = 1, GET_STATE = 0;

typedef struct record {
	time_t now;
	double amount;
} record;

class Card {
public:
	Card(int id, double remain, string password, bool flag = GET_STATE);
	~Card();							//卡不想要了
	void recharge(double amount);			//充值
	void expense(double amount);			//消费
	void set_flag(int flag);			//挂失与解挂失传入的这个参数和当前_flag相反时才能设置成功
	double get_remain();					//返回余额
	bool get_flag();					//返回挂失状态
	void bind_stu(int id);						//卡和学生绑定
	int get_card_id();
	void set_password(string);
	string get_password();
	vector<record> get_charge_record();	//返回充值记录
	vector<record> get_consume_record();	//返回消费记录

private:

	int _stu_id;						//所属学生
	string _password;					//密码
	int _card_id;
	double _remain;					//卡号，余额
	vector<record> _charge, _consume;		//充值，消费记录	
	bool _flag;							//是否为挂失
	//卡号，余额，充值记录，消费记录，校园卡状态
};

class Student {
public:
	Student(string name, string academy, string cllass, string major, int id);
	~Student();						//退学处理
	void recharge(double amount);		//充值成功，卡没有挂失时，即充值金额大于0小于等于500返回true，否则返回false
	void expense(double amount);		//卡没有挂失时，消费金额大于0小于等于500并且小于当前余额返回true，否则返回false
	void check_status();					//查看自己校园卡的状态
	void loss();						//挂失，不能挂失已经挂失的卡
	void find();						//找到了卡，不能卡在自己手上但是又找到了
	void replace();						//重新补办卡
	void check_charge_record();			//查看充值记录
	void check_expense_record();			//查看消费记录
	void bind_card(Card&);						//学生和卡绑定
	void delete_student();
	string get_name();
	Card* find_card();
	int get_stu_id();

private:
	int _card_id;
	string _name, _academy, _class, _major;
	int _stu_id;
	//名字，学院，班级，专业，学号
};

extern vector<Student> students;				//管理员所储存的全校的学生信息
extern vector<Card> cards;					//管理员所储存的全校的校园卡信息

bool create_student();					//管理员创建学生
bool create_card();						//管理员创建校园卡
Student* find_student(int id);
