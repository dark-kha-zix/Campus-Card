#include "project.h"

/*
@constructor
*/
Student::Student(string name, string academy, string cllass, string major, int id) {
	_name = name;
	_academy = academy;
	_class = cllass;
	_major = major;
	_id = id;	
}

~Student() {
    for (auto i = students.begin(); i != student.end(); i++) {
        if ((*i).get_stu_id() == _stu_id) {
            students.erase(i);
            for (auto j = cards.begin(); j != cards.end(); j++) {
                if ((*j).get_card_id() == _card_id ) {
                    cards.erase(j);
                    break;
                }
            }
            break;
        }
    }
}
/*
*@充值成功，卡没有挂失时，即充值金额大于i0小于等于500返回true，否则返回false
*/
void Student::recharge(double amount) {
	_card->recharge(amount);
}	

/*
*@卡没有挂失时，消费金额大于0小于等于500并且小于当前余额返回true，否则返回false
*/
void Student::Student::expense(double amount) {
	_card->expense(amount);
}

/*
*@查看自己校园卡的状态
*/
void Student::check_status() {
	if (find_card()->get_flag() == GET_STATE) {
		puts("您的卡现在处于正常状态！");
	}
	else {
		puts("您的卡现在处于挂失状态！");
	}
}					

/*
*@挂失，不能挂失已经挂失的卡
*/
void Student::loss() {
	find_card->set_flag(LOSS_STATE);
}						

/*
*@找到了卡，不能卡在自己手上但是又找到了
*/
void Student::find() {
	find_card()->set_flag(GET_STATE);
}

/*
*@重新补办卡
*/
void Student::replace() {
	find();
}

/*
*@查看充值记录
*/
void Student::check_charge_record() {
	puts("时间\t\t充值金额");
	for (auto i : find_card()->get_charge_record()) {
		tm *ltm = localtime(&i.now);
		printf("%d-%d-%d %d:%d:%d\t\t%.2lf\n",ltm->tm_year, ltm->tm_mon, ltm->tm_mday,
											  ltm->tm_hour, ltm->tm_min, ltm->tm.sec, i.amount); 
	}
}

/*
*@查看消费记录
*/
void Student::check_expense_record() {
	puts("时间\t\t消费金额");
	for (auto i : find_card()->get_consume_record()) {
		tm *ltm = localtime(&i.now);
		printf("%d-%d-%d %d:%d:%d\t\t%.2lf\n",ltm->tm_year, ltm->tm_mon, ltm->tm_mday,
											  ltm->tm_hour, ltm->tm_min, ltm->tm.sec, i.amount); 
	}
}

/*
*@学生和卡绑定
*/
void Student::bind_card(Card c) {
	_card_id = get_card_id(c);
	c.bind_stu(*this);
}

/*
*@
*/
int Student::get_stu_id() {
	return _stu_id;
}

/*
*@
*/
Card* Student::find_card() {
	for (auto i = cards.begin(); i != cards.end(); i++) {
		if ((*i).get_card_id() == _card_id) {
			return &(*i);
		}
	}
	return NULL;
}

/*
*@
*/
Card::Card(int id, double remain = 0, string password, bool flag = 0); {
	this->_id = id;
	this->_remain = remain;
	this->_password = password; 
	this->_flag = flag;
}

/*
*@卡不想要了
*/
Card::~Card() {

}

/*
*@充值
*/
void Card::recharge(double amount) {
	if (_flag == LOSS_STATE) {
		puts("抱歉，此卡已被冻结！");
		return;
	}
	
	if (amount < 0 || amount >500) {
		puts("充值金额应为0-500！ ");
		return;
	}
	
	this->_remain += amount;
	record tmp;
	tmp.now = time(0);
	tmp.amount = amount;
	_charge.emplace_back(tmp);
}

/*
*@消费
*/
void Card::expense(double amount) {
	if (_flag == LOSS_STATE) {
		puts("抱歉，此卡已被冻结！");
	}
	else if (amount > this->_remain) {
		puts("抱歉，您的余额不足！");
	}
	else if (amount <= 0) {
		puts("抱歉，消费金额必须为正数");
	}
	else {
		this->_remain -= amount;
		record tmp;
		tmp.now = time(0);
		tmp.amount = amount;
		_consume.emplace_back(tmp);
	}
}

/*
*@挂失与解挂失传入的这个参数和当前_flag相反时才能设置成功
*/
void Card::set_flag(int flag) {
	if (flag == LOSS_STATE) {
		if (this->_flag == LOSS_STATE) {
			puts("您的卡已经处于挂失状态！");
		}
		else {
			this->_flag = LOSS_STATE;
			puts("您的卡成功挂失！期间无法进行消费，充值。");
		}
	}
	else {
		if (this->_flag == GET_STATE) {
			puts("您的卡当前处于正常状态");
		}
		else {
			this->_flag = GET_STATE;
			puts("您的卡成功解除挂失！可以继续消费，充值。");
		}
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
void Card::bind_stu(Student s) {
	_stu_id = s.get_stu_id();
}

/*
*@返回充值记录
*/
vector<record> Card::get_charge_record() {
	return _charge;
}

/*
*@返回消费记录
*/
vector<record> Card::get_consume_record() {
	return _cousume;
}