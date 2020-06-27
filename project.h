#pragma once

#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

#define MAX_LIMIT 500				//���ѡ���ֵ�޶�
#define LOSS_STATE 1				//�����ڶ�ʧ״̬
#define GET_STATE 0					//����������

class Student {
public:
	Student(string name, string academy, string cllass, string major, Card* card = NULL);
	~Student();						//��ѧ����
	bool recharge(int amount);		//��ֵ�ɹ�����û�й�ʧʱ������ֵ������0С�ڵ���500����true�����򷵻�false
	bool expense(int amount);		//��û�й�ʧʱ�����ѽ�����0С�ڵ���500����С�ڵ�ǰ����true�����򷵻�false
	void check_status();					//�鿴�Լ�У԰����״̬
	bool loss();						//��ʧ�����ܹ�ʧ�Ѿ���ʧ�Ŀ�
	bool find();						//�ҵ��˿������ܿ����Լ����ϵ������ҵ���
	void replace();						//���²��쿨
	void check_charge_record();			//�鿴��ֵ��¼
	void check_expense_record();			//�鿴���Ѽ�¼
	void bind_card();						//ѧ���Ϳ���

private:
	Card* _card;
	string _name, _academy, _class, _major;
	int _id;
	//���֣�ѧԺ���༶��רҵ��ѧ��
};

class Card {
public:
	Card(int id, int remain = 0, bool flag = 0, Student* stu = NULL);
	~Card();							//������Ҫ��
	bool recharge(int amount);			//��ֵ
	bool expense(int amount);			//����
	bool set_flag(int flag);			//��ʧ����ʧ�������������͵�ǰ_flag�෴ʱ�������óɹ�
	int get_remain();					//�������
	bool get_flag();					//���ع�ʧ״̬
	void bind_stu();						//����ѧ����
	vector<int> get_charge_record();	//���س�ֵ��¼
	vector<int> get_consume_record();	//�������Ѽ�¼

private:
	Student* _stu;						//����ѧ��
	int _id, _remain;					//���ţ����
	vector <int> _charge, _consume;		//��ֵ�����Ѽ�¼	
	bool _flag;							//�Ƿ�Ϊ��ʧ
	//���ţ�����ֵ��¼�����Ѽ�¼��У԰��״̬
};

vector <Student> students;				//����Ա�������ȫУ��ѧ����Ϣ
vector <Card> cards;					//����Ա�������ȫУ��У԰����Ϣ

bool create_student();					//����Ա����ѧ��

bool create_card();						//����Ա����У԰��

