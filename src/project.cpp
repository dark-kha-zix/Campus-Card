#include "../include/project.h"

vector<Student> students;				//����Ա�������ȫУ��ѧ����Ϣ
vector<Card> cards;					//����Ա�������ȫУ��У԰����Ϣ

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
*@��ֵ�ɹ�����û�й�ʧʱ������ֵ������i0С�ڵ���500����true�����򷵻�false
*/
void Student::recharge(double amount) {
	find_card()->recharge(amount);
}	

/*
*@��û�й�ʧʱ�����ѽ�����0С�ڵ���500����С�ڵ�ǰ����true�����򷵻�false
*/
void Student::expense(double amount) {
	find_card()->expense(amount);
}

/*
*@�鿴�Լ�У԰����״̬
*/
void Student::check_status() {
	if (find_card()->get_flag() == GET_STATE) {
		puts("���Ŀ����ڴ�������״̬��\n");
	}
	else {
		puts("���Ŀ����ڴ��ڹ�ʧ״̬��\n");
	}
}					

/*
*@��ʧ�����ܹ�ʧ�Ѿ���ʧ�Ŀ�
*/
void Student::loss() {
	find_card()->set_flag(LOSS_STATE);
}						

/*
*@�ҵ��˿������ܿ����Լ����ϵ������ҵ���
*/
void Student::find() {
	find_card()->set_flag(GET_STATE);
}

/*
*@���²��쿨
*/
void Student::replace() {
	cout << "���� " << _stu_id << " �ѳɹ����죬�ָ�����ʹ��\n" << endl;
	if (find_card()->get_flag() == LOSS_STATE) {
		find();
	}
}

/*
*@�鿴��ֵ��¼
*/
void Student::check_charge_record() {
	puts("\tʱ��\t\t\t��ֵ���");
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
*@�鿴���Ѽ�¼
*/
void Student::check_expense_record() {
	puts("\tʱ��\t\t\t���ѽ��");
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
*@ѧ���Ϳ���
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
*@������Ҫ��
*/
Card::~Card() {
}

/*
*@��ֵ
*/
void Card::recharge(double amount) {
	if (_flag == LOSS_STATE) {
		puts("��Ǹ���˿��ѱ����ᣡ\n");
		return;
	}
	
	if (amount < 0 || amount >500) {
		puts("��ֵ���ӦΪ0-500�� \n");
		return;
	}
	
	this->_remain += amount;
	record tmp;
	tmp.now = time(0);
	tmp.amount = amount;
	_charge.emplace_back(tmp);
	printf("���� %d �ɹ���ֵ %.2lf Ԫ\n\n", _card_id, amount);
}

/*
*@��ȡ����
*/
int Card::get_card_id() {
	return _card_id;
}

/*
*@�޸Ŀ���
*/
void Card::set_password(string password) {
	_password = password;
	cout << "�����ѱ��޸�Ϊ " << _password << endl << endl;
}

/*
*@��ȡ����
*/
string Card::get_password() {
	return _password;
}

/*
*@����
*/
void Card::expense(double amount) {
	if (_flag == LOSS_STATE) {
		puts("��Ǹ���˿��ѱ����ᣡ\n");
	}
	else if (amount > this->_remain) {
		puts("��Ǹ���������㣡\n");
	}
	else if (amount <= 0) {
		puts("��Ǹ�����ѽ�����Ϊ����\n");
	}
	else {
		this->_remain -= amount;
		record tmp;
		tmp.now = time(0);
		tmp.amount = amount;
		_consume.emplace_back(tmp);
		printf("���� %d �ɹ����� %.2lf Ԫ\n\n", _card_id, amount);
	}
}

/*
*@��ʧ����ʧ�������������͵�ǰ_flag�෴ʱ�������óɹ�
*/
void Card::set_flag(int flag) {
	if (flag == LOSS_STATE) {
		if (this->_flag == LOSS_STATE) {
			puts("���Ŀ��Ѿ����ڹ�ʧ״̬��\n");
		}
		else {
			this->_flag = LOSS_STATE;
			puts("���Ŀ��ɹ���ʧ���ڼ��޷��������ѣ���ֵ��\n");
		}
	}
	else {
		if (this->_flag == GET_STATE) {
			puts("���Ŀ���ǰ��������״̬\n");
		}
		else {
			this->_flag = GET_STATE;
			puts("���Ŀ��ɹ������ʧ�����Լ������ѣ���ֵ��\n");
		}
	}
}

/*
*@�������
*/
double Card::get_remain() {
	return this->_remain;
}

/*
*@���ع�ʧ״̬
*/
bool Card::get_flag() {
	return this->_flag;
}

/*
*@����ѧ����
*/
void Card::bind_stu(int id) {
	_stu_id = id;
	_password = to_string(_stu_id);
}

/*
*@���س�ֵ��¼
*/
vector<record> Card::get_charge_record() {
	return _charge;
}

/*
*@�������Ѽ�¼
*/
vector<record> Card::get_consume_record() {
	return _consume;
}

bool create_student() {
	string name,academy,cllass,major;
	int _stu_id;
	cout << "������ѧ��ѧ�ţ�";
	cin >> _stu_id;
	for(auto i = students.begin(); i != students.end(); i++) {
		if ((*i).get_stu_id() == _stu_id) {
			cout << "��ѧ���Ѵ��ڣ�\n" << endl;
			return false;
		}
	}
	cout << "������ѧ��������";
	cin >> name;
	cout << "������ѧ������ѧԺ��";
	cin >> academy;
	cout << "������ѧ�������༶��";
	cin >> cllass;
	cout << "������ѧ��רҵ��";
	cin >> major;
	getchar();

	Student* t = new Student(name, academy, cllass, major, _stu_id);
	cout << "�ɹ�����ѧ��:\n����: " << name << " \nѧ��: " << _stu_id << " \nѧԺ: " << academy << "\n�༶: " << cllass << "\nרҵ: " << major << endl << endl;
	Card *c = new Card(_stu_id, 0, to_string(_stu_id));
	
	(*t).bind_card(*c);
	students.emplace_back(*t);
	cards.emplace_back(*c);
	
	return true;
}					//����Ա����ѧ��

