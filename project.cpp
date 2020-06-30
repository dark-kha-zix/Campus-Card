#include "project.h"

/*
@constructor
*/
Student::Student(string name, string academy, string cllass, string major, Card* card = NULL, int id) {
	_name = name;
	_academy = academy;
	_class = cllass;
	_major = major;
	_id = id;	
}

/*
*@充值成功，卡没有挂失时，即充值金额大于0小于等于500返回true，否则返回false
*/
void Student::recharge(int amount) {
	_card->recharge(amount);
}	

/*
*@卡没有挂失时，消费金额大于0小于等于500并且小于当前余额返回true，否则返回false
*/
void Student::Student::expense(int amount) {
	_card->expense(amount);
}

/*
*@查看自己校园卡的状态
*/
bool Student::check_status() {
return 
}					

/*
*@挂失，不能挂失已经挂失的卡
*/
bool Student::loss() {
	
}						

/*
*@找到了卡，不能卡在自己手上但是又找到了
*/
bool Student::find() {

}

/*
*@重新补办卡
*/
void Student::replace();

/*
*@查看充值记录
*/
void Student::check_charge_record();

/*
*@查看消费记录
*/
void Student::check_expense_record();
/*
*@学生和卡绑定
*/
void Student::bind_card();

/*
*@
*/
int Student::get_id();

/*
*@
*/
Card::Card(int id, int remain = 0, string password, bool flag = 0, Student* stu = NULL); {
	this->_id = id;
	this->_remain = remain;
	this->_password = password; 
}

/*
*@卡不想要了
*/
Card::~Card() {

}

/*
*@充值
*/
bool Card::recharge(int amount) {
	this->_remain += amount;
	_charge.
}

/*
*@消费
*/
bool Card::expense(int amount) {
	this->_remain -= amount;
}

/*
*@挂失与解挂失传入的这个参数和当前_flag相反时才能设置成功
*/
bool Card::set_flag(int flag) {
	if (flag == !this->_flag) {
		this->_flag = flag;
	}
}

/*
*@返回余额
*/
int Card::get_remain() {
	return this->_remain;
}

/*
*@返回挂失状态
*/
bool Card::get_flag() {
	return this->_flag;
}

/*
*@卡和学生绑定
*/
void Card::bind_stu() {

}

/*
*@返回充值记录
*/
vector<record> Card::get_charge_record() {
	
}

/*
*@返回消费记录
*/
vector<record> Card::get_consume_record() {

}