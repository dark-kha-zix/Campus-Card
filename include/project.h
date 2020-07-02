#pragma once

#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <ctime>
using namespace std;

#define MAX_LIMIT 500;				//���ѡ���ֵ�޶�
//�����ڶ�ʧ״̬
//����������

const int LOSS_STATE = 1, GET_STATE = 0;

typedef struct record {
	time_t now;
	double amount;
} record;

class Card {
public:
	Card(int id, double remain, string password, bool flag = GET_STATE);
	~Card();							//������Ҫ��
	void recharge(double amount);			//��ֵ
	void expense(double amount);			//����
	void set_flag(int flag);			//��ʧ����ʧ�������������͵�ǰ_flag�෴ʱ�������óɹ�
	double get_remain();					//�������
	bool get_flag();					//���ع�ʧ״̬
	void bind_stu(int id);						//����ѧ����
	int get_card_id();
	void set_password(string);
	string get_password();
	vector<record> get_charge_record();	//���س�ֵ��¼
	vector<record> get_consume_record();	//�������Ѽ�¼

private:

	int _stu_id;						//����ѧ��
	string _password;					//����
	int _card_id;
	double _remain;					//���ţ����
	vector<record> _charge, _consume;		//��ֵ�����Ѽ�¼	
	bool _flag;							//�Ƿ�Ϊ��ʧ
	//���ţ�����ֵ��¼�����Ѽ�¼��У԰��״̬
};

class Student {
public:
	Student(string name, string academy, string cllass, string major, int id);
	~Student();						//��ѧ����
	void recharge(double amount);		//��ֵ�ɹ�����û�й�ʧʱ������ֵ������0С�ڵ���500����true�����򷵻�false
	void expense(double amount);		//��û�й�ʧʱ�����ѽ�����0С�ڵ���500����С�ڵ�ǰ����true�����򷵻�false
	void check_status();					//�鿴�Լ�У԰����״̬
	void loss();						//��ʧ�����ܹ�ʧ�Ѿ���ʧ�Ŀ�
	void find();						//�ҵ��˿������ܿ����Լ����ϵ������ҵ���
	void replace();						//���²��쿨
	void check_charge_record();			//�鿴��ֵ��¼
	void check_expense_record();			//�鿴���Ѽ�¼
	void bind_card(Card&);						//ѧ���Ϳ���
	void delete_student();
	string get_name();
	Card* find_card();
	int get_stu_id();

private:
	int _card_id;
	string _name, _academy, _class, _major;
	int _stu_id;
	//���֣�ѧԺ���༶��רҵ��ѧ��
};

extern vector<Student> students;				//����Ա�������ȫУ��ѧ����Ϣ
extern vector<Card> cards;					//����Ա�������ȫУ��У԰����Ϣ

bool create_student();					//����Ա����ѧ��
bool create_card();						//����Ա����У԰��
Student* find_student(int id);
