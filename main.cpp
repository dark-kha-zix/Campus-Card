#include "project.h"

void help_menu() {
    puts("1---创建学生");
    puts("2---学生登录");
    puts("3---显示帮助");
    puts("4---退出");
}

void help_student_service() {
    puts("1---充值");
    puts("2---余额查询");
    puts("3---消费");
    puts("4---挂失");
    puts("5---解除挂失");
    puts("6---补办新卡");
    puts("7---查询充值记录");
    puts("8---查询消费记录");
    puts("9---修改密码");
    puts("q---退出\n");
}

void student_service(Student *s) {
    char flag = '0';
    cout << endl << "欢迎! " << s->get_name() << endl;
    help_student_service();
    while (flag != 'q') {
    	do {
			cout << "[student]";
    		scanf("%c", &flag);
		}while(flag == '\n');
    	
        switch (flag) {
        case '1': {
            double amount;
            cout << "请输入充值金额：";
            getchar();
            cin >> amount;
            getchar();
            s->recharge(amount);
            break;
        }
        case '2': {
        	getchar();
            printf("您的校园卡剩余金额为：%.2lf元\n\n", s->find_card()->get_remain());
            break;
        }
        case '3': {
            double amount;
            cout << "请输入消费金额：";
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
            cout << "请输入新密码：";
            cin >> password;
            getchar();
            s->find_card()->set_password(password);
            break;
        }
        case 'q': {
        	getchar();
            puts("成功退出！拜拜您嘞~\n");
            break;
        }
        case '\n': {
        	
			break;
		}
        default: {
            puts("非法命令！请重新输入");
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
                create_student();
                break;
            }
            case '2': {
                int id;
                string password;

                cout << "请输入学号：";
                cin >> id;

                if (find_student(id) == NULL) {
                    puts("该学号不存在！\n");
                    break;
                }

                Student* s = find_student(id);
                cout << "请输入密码：";
                cin >> password;
                getchar();
                if (s->find_card()->get_password() != password) {
                    puts("您输入的密码错误，请尝试重新登陆！\n");
                    break;
                }
                student_service(s);
                break;
            }
            case '3': {
            	help_menu();
                break;
            }
            case '4': {
                puts("成功退出！拜拜您嘞~\n");
                break;
            }
            case '\n': {
				break;
			}

            default:{
                puts("非法命令！请重新输入\n");
                help_menu();
                break;
            }
        }
    }
}

int main() {
	puts("--------欢迎来到校园卡管理系统----------\n");
    UI();
}

