#include "../include/UI.h"

void help_menu() {
    puts("1---����Ա��¼");
    puts("2---ѧ����¼");
    puts("3---��ʾ����");
    puts("4---�˳�\n");
}

void help_admin_service() {
	puts("1---����ѧ��");
	puts("2---�Ƴ�ѧ��");
	puts("q---�˳�\n");
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
    puts("q---�˳�\n");
}

void admin_service() {
	char flag = '0';
    cout << endl << "��ӭ�������Աϵͳ! " << endl;
    help_admin_service();
    
    while (flag != 'q') {
    	do {
			cout << "[admin]";
    		scanf("%c", &flag);
		}while(flag == '\n');
		
		switch(flag) {
			case '1': {
				create_student();
				break;
			}
			case '2': {
				int id;
				printf("������Ҫ�Ƴ���ѧ��ѧ��: ");
				scanf("%d", &id);
				getchar();
				
				Student* tmp = find_student(id);
				if (tmp == NULL) {
					puts("��Ǹ����ѧ��������!\n");
				}
				else {
					tmp->delete_student();
					printf("ѧ�� %d �ѱ��ɹ��Ƴ�\n\n", id);
				}
				break;
			}
			
			case 'q': {
				getchar();
				puts("�ɹ��˳����ݰ�����~\n");
				break;
			}
			
			default: {
				getchar();
				puts("�Ƿ�������������룡\n");
				help_admin_service();
				break;
			}
		}
	}
}

void student_service(Student *s) {
    char flag = '0';
    cout << endl << "��ӭ! " << s->get_name() << endl;
    help_student_service();
    while (flag != 'q') {
    	do {
			cout << "[student]";
    		scanf("%c", &flag);
		}while(flag == '\n');
    	
        switch (flag) {
        case '1': {
            double amount;
            cout << "�������ֵ��";
            getchar();
            cin >> amount;
            getchar();
            s->recharge(amount);
            break;
        }
        case '2': {
        	getchar();
            printf("����У԰��ʣ����Ϊ��%.2lfԪ\n\n", s->find_card()->get_remain());
            break;
        }
        case '3': {
            double amount;
            cout << "���������ѽ�";
            cin >> amount;
            getchar();
            s->expense(amount);
            break;
        }
        case '4': {
        	getchar();
            s->loss();
            break;
        }
        case '5': {
        	getchar();
            s->find();
            break;
        }
        case '6': {
        	getchar();
            s->replace();
            break;
        }
        case '7': {
        	getchar();
            s->check_charge_record();
            break;
        }
        case '8': {
        	getchar();
            s->check_expense_record();
            break;
        }
        case '9': {
            string password;
            cout << "�����������룺";
            cin >> password;
            getchar();
            s->find_card()->set_password(password);
            break;
        }
        case 'q': {
        	getchar();
            puts("�ɹ��˳����ݰ�����~\n");
            break;
        }
        case '\n': {
        	
			break;
		}
        default: {
        	getchar();
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
    	
    	do {
    		printf("[menu]");
    		scanf("%c", &flag);
		}while(flag == '\n');
    	
        switch(flag) {
            case '1': {
                string password;
                printf("���������Ա����: ");
                cin >> password;
                getchar();
                if (password != "admin") {
                	puts("����Ա�������\n");
				}
				else {
					admin_service();
				}
                break;
            }
            case '2': {
                int id;
                string password;

                cout << "������ѧ�ţ�";
                cin >> id;
				getchar();
                if (find_student(id) == NULL) {
                    puts("��ѧ�Ų����ڣ�\n");
                    break;
                }

                Student* s = find_student(id);
                cout << "���������룺";
                cin >> password;
                getchar();
                if (s->find_card()->get_password() != password) {
                    puts("���������������볢�����µ�½��\n");
                    break;
                }
                student_service(s);
                break;
            }
            case '3': {
            	getchar();
            	help_menu();
                break;
            }
            case '4': {
                puts("�ɹ��˳����ݰ�����~\n");
                break;
            }
            case '\n': {
				break;
			}

            default:{
            	getchar();
                puts("�Ƿ��������������\n");
                help_menu();
                break;
            }
        }
    }
}
