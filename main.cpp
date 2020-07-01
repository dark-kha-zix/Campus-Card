#include "project.h"

void help_menu() {
    puts("1---����ѧ��");
    puts("2---ѧ����¼");
    puts("3---��ʾ����");
    puts("4---�˳�");
}

void help_student_service() {
    puts("1---��ֵ");
    puts("2---����ѯ");
    puts("3---����");
    puts("4---��ʧ");
    puts("5---�����ʧ");
    puts("6---�����¿�");
    puts("7---��ѯ��ֵ��¼");
    puts("8---��ѯ���Ѽ�¼");
    puts("9---�޸�����");
    puts("10---�˳�");
}

void student_service(Student *s) {
    char flag = '0';
    cout << "��ӭ! " << s->get_name() << endl;
    help_student_service();
    while (flag != '9') {
    	scanf("%c", &flag);
        switch (flag) {
        case '1': {
            double amount;
            cout << "�������ֵ��";
            cin >> amount;
            s->recharge(amount);
            break;
        }
        case '2': {
            printf("����У԰��ʣ����Ϊ��%.2lfԪ\n", s->find_card()->get_remain());
            break;
        }
        case '3': {
            double amount;
            cout << "���������ѽ�";
            cin >> amount;
            s->expense(amount);
            break;
        }
        case '4': {
            s->loss();
            break;
        }
        case '5': {
            s->find();
            break;
        }
        case '6': {
            s->replace();
            break;
        }
        case '7': {
            s->check_charge_record();
            break;
        }
        case '8': {
            s->check_expense_record();
            break;
        }
        case '9': {
            string password;
            cout << "�����������룺";
            cin >> password;
            s->find_card()->set_password(password);
            break;
        }
        case 'q': {
            puts("�ɹ��˳����ݰ�����~");
            break;
        }
        default: {
            puts("�Ƿ��������������");
            help_student_service();
            break;
        }
        }
    }
}

void UI() {
    char flag = '0';
    help_menu();
    while (flag != '4') {
        flag = getchar();
        switch(flag) {
            case '1': {
                create_student();
                break;
            }
            case '2': {
                int id;
                string password;

                cout << "������ѧ�ţ�";
                cin >> id;

                if (find_student(id) == NULL) {
                    puts("��ѧ�Ų����ڣ�");
                    break;
                }

                Student* s = find_student(id);
                cout << "���������룺";
                cin >> password;
                if (s->find_card()->get_password() != password) {
                    puts("���������������볢�����µ�½��");
                }
                student_service(s);
                break;
            }
            case '3': {
                break;
            }
            case '4': {
                puts("�ɹ��˳����ݰ�����~");
                break;
            }

            default:{
                puts("�Ƿ��������������");
                help_menu();
                break;
            }
        }
    }
}

int main() {
    UI();
}

