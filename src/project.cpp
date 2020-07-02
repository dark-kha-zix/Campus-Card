#include "../include/project.h"

vector<Student> students;				//管理员所储存的全校的学生信息
vector<Card> cards;					//管理员所储存的全校的校园卡信息

/*
@constructor
*/
Student::Student(string name, string academy, string cllass, string major, int id) {
	_name = name;
	_academy = academy;
	_class = cllass;
	_major = major;
	_stu_id = id;	
}

Student::~Student() {
	
}

void Student::delete_student() {
	int temp = _stu_id;

	for(auto i = students.begin(); i != students.end(); i++) {
		if ((*i).get_stu_id() == temp) {
			students.erase(i);
			for (auto j = cards.begin(); j != cards.end(); j++) {
				if ((*j).get_card_id() == temp ) {
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
	find_card()->recharge(amount);
}	

/*
*@卡没有挂失时，消费金额大于0小于等于500并且小于当前余额返回true，否则返回false
*/
void Student::expense(double amount) {
	find_card()->expense(amount);
}

/*
*@查看自己校园卡的状态
*/
void Student::check_status() {
	if (find_card()->get_flag() == GET_STATE) {
		puts("您的卡现在处于正常状态！\n");
	}
	else {
		puts("您的卡现在处于挂失状态！\n");
	}
}					

/*
*@挂失，不能挂失已经挂失的卡
*/
void Student::loss() {
	find_card()->set_flag(LOSS_STATE);
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
	cout << "卡号 " << _stu_id << " 已成功补办，恢复正常使用\n" << endl;
	if (find_card()->get_flag() == LOSS_STATE) {
		find();
	}
}

/*
*@查看充值记录
*/
void Student::check_charge_record() {
	puts("\t时间\t\t\t充值金额");
	for (auto i : find_card()->get_charge_record()) {
		tm *ltm = localtime(&i.now);
		printf("%d-%d-%d %d:%d:%d\t\t",ltm->tm_year, ltm->tm_mon, ltm->tm_mday,
											  ltm->tm_hour, ltm->tm_min, ltm->tm_sec); 
		if (ltm->tm_sec < 10) {
			printf("\t");
		}
		
		printf("%.2lf\n", i.amount);
	}
	puts("");
}

/*
*@查看消费记录
*/
void Student::check_expense_record() {
	puts("\t时间\t\t\t消费金额");
	for (auto i : find_card()->get_consume_record()) {
		tm *ltm = localtime(&i.now);
		printf("%d-%d-%d %d:%d:%d\t\t",ltm->tm_year, ltm->tm_mon, ltm->tm_mday,
											  ltm->tm_hour, ltm->tm_min, ltm->tm_sec); 
		if (ltm->tm_sec < 10 || ltm->tm_hour < 10 || ltm->tm_min < 10) {
			printf("\t");
		}
		printf("%.2lf\n", i.amount);
	}
	puts("");
}

/*
*@学生和卡绑定
*/
void Student::bind_card(Card &c)	 {
	_card_id = c.get_card_id();
	c.bind_stu(_card_id);
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

string Student::get_name() {
	return this->_name;
}

Student* find_student(int id) {
	for (auto i = students.begin(); i != students.end(); i++) {
		
		if ((*i).get_stu_id() == id) {
			return &(*i);
		}
	}
	return NULL;
}

/*
*@
*/
Card::Card(int id,  double remain, string password, bool flag) {
	this->_card_id = id;
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
		puts("抱歉，此卡已被冻结！\n");
		return;
	}
	
	if (amount < 0 || amount >500) {
		puts("充值金额应为0-500！ \n");
		return;
	}
	
	this->_remain += amount;
	record tmp;
	tmp.now = time(0);
	tmp.amount = amount;
	_charge.emplace_back(tmp);
	printf("卡号 %d 成功充值 %.2lf 元\n\n", _card_id, amount);
}

/*
*@获取卡号
*/
int Card::get_card_id() {
	return _card_id;
}

/*
*@修改卡密
*/
void Card::set_password(string password) {
	_password = password;
	cout << "密码已被修改为 " << _password << endl << endl;
}

/*
*@获取卡密
*/
string Card::get_password() {
	return _password;
}

/*
*@消费
*/
void Card::expense(double amount) {
	if (_flag == LOSS_STATE) {
		puts("抱歉，此卡已被冻结！\n");
	}
	else if (amount > this->_remain) {
		puts("抱歉，您的余额不足！\n");
	}
	else if (amount <= 0) {
		puts("抱歉，消费金额必须为正数\n");
	}
	else {
		this->_remain -= amount;
		record tmp;
		tmp.now = time(0);
		tmp.amount = amount;
		_consume.emplace_back(tmp);
		printf("卡号 %d 成功消费 %.2lf 元\n\n", _card_id, amount);
	}
}

/*
*@挂失与解挂失传入的这个参数和当前_flag相反时才能设置成功
*/
void Card::set_flag(int flag) {
	if (flag == LOSS_STATE) {
		if (this->_flag == LOSS_STATE) {
			puts("您的卡已经处于挂失状态！\n");
		}
		else {
			this->_flag = LOSS_STATE;
			puts("您的卡成功挂失！期间无法进行消费，充值。\n");
		}
	}
	else {
		if (this->_flag == GET_STATE) {
			puts("您的卡当前处于正常状态\n");
		}
		else {
			this->_flag = GET_STATE;
			puts("您的卡成功解除挂失！可以继续消费，充值。\n");
		}
	}
}

/*
*@返回余额
*/
double Card::get_remain() {
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
void Card::bind_stu(int id) {
	_stu_id = id;
	_password = to_string(_stu_id);
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
	return _consume;
}

bool create_student() {
	string name,academy,cllass,major;
	int _stu_id;
	cout << "请输入学生学号：";
	cin >> _stu_id;
	for(auto i = students.begin(); i != students.end(); i++) {
		if ((*i).get_stu_id() == _stu_id) {
			cout << "该学号已存在！\n" << endl;
			return false;
		}
	}
	cout << "请输入学生姓名：";
	cin >> name;
	cout << "请输入学生所属学院：";
	cin >> academy;
	cout << "请输入学生所属班级：";
	cin >> cllass;
	cout << "请输入学生专业：";
	cin >> major;
	getchar();

	Student* t = new Student(name, academy, cllass, major, _stu_id);
	cout << "成功创建学生:\n姓名: " << name << " \n学号: " << _stu_id << " \n学院: " << academy << "\n班级: " << cllass << "\n专业: " << major << endl << endl;
	Card *c = new Card(_stu_id, 0, to_string(_stu_id));
	
	(*t).bind_card(*c);
	students.emplace_back(*t);
	cards.emplace_back(*c);
	
	return true;
}					//管理员创建学生

