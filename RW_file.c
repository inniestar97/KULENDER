#define _CRT_SECURE_NO_WARNINGS
#include "kulender.h"

//�ѱ������Ͽ� ���ڿ� ���� ���ϴ� �Լ�
int GetStringLength(const char* string) {
	int count = 0;
	while (*string) {
		if (*string >> 7) {
			string++;
		}
		string++;
		count++;
	}
	return count;
}
    
// �ϼ�
int login() {
	system("cls");
	char user_id[ID_LEN + 1] = "";
	char path[PATH_LEN] = "";
	FILE* fin;

	while (1) {
		printf("���̵� : ");
		int check = checkID(user_id); // �Է¹��� id ����üũ
		if (check == 1)  // ���̵� �ٽ� �Է¹ޱ�
			continue;
		else if (check == 2)  // ����ȭ�����ε��ư���
			return 0;
		else {				// �ùٸ� ����
			strcpy(path, "kulender\\users\\");
			strcat(path, user_id);
			strcat(path, ".txt");
			fin = fopen(path, "r");

			if (fin == NULL) { // ���̵� ���� ���� üũ
				printf("�������� �ʴ� ���̵��Դϴ�.\n");
				if (reset() == 1) {// ���̵� �ٽ� �Է�
					path[0] = '\0'; //�ʱ�ȭ
					for (int i = 0; i < strlen(path); i++) {
						path[i] = 0;
					}
					continue;
				}
				else {
					return 0;
				}
			}
			fclose(fin);
			break;
		}
	}

	// ���Ͽ� �����ϴ� password
	char password[PASSWORD_LEN + 2] = "";
	readInform(password, user_id, 0);

	// ����� �Է� password
	char user_pass[PASSWORD_LEN + 1] = "";
	while (1) {
		checkPass(user_pass);

		if (strcmp(user_pass, password) != 0) {
			printf("�α��� ����\n");
			if (reset() == 1) {
				continue; // �ٽ��Է�
			}

			fclose(fin);
			return 0; // ����ȭ������ ���ư���
		}
		else {
			break;
		}
	}
    printf("----------------------------------\n");
	printf("�α��� ����!!\n");

    strcpy(USER_id, user_id);
	strcpy(USER_password, password);

	readInform(USER_name, user_id, 1);
	readInform(USER_birthday, user_id, 2);

	Sleep(1500);

	if (mainMenu() == -1) { // �ý�������
		exit(0);
	}
	else { // �α׾ƿ�
		USER_id[0] = "\0";
		USER_password[0] = "\0";
		USER_name[0] = "\0";
		USER_birthday[0] = "\0";
		return 0;
	}
}

int checkSpace(char* str) {
	int len = strlen(str);

	int i = 0;
	for (i = 0; i < len; i++) {
		if (str[i] == ' ') {
			return 1;
		}
	}

	return 0;
}

// �ϼ�
int reset() {
	printf("1. �ٽ� �Է�\n2. ���α׷� ����ȭ��\n");
	printf("�޴� ���� : ");

	int num = chooseNumber(1, 2);
	if (num == 1) {
		return 1;
	}
	else {
		return 2;
	}
}

int checkID(char* str) {
	char id[1024] = { 0, };

	gets(id);
	int idCheck = GetStringLength(id);
    
    int i = 0;
    while (id[i] != '\0') {
        if ((65 <= id[i] && id[i] <= 90 || 97 <= id[i] && id[i] <= 122) || (48 <= id[i] && id[i] <= 57)) {
            i++;
            continue;
        }
        printf("���̵� ���� ���Ŀ� ��߳��ϴ�.\n");
		if (reset() == 1)  // ���̵� ���Է�
            return 1;    
        else            //���α׷� ����ȭ��
            return 2;

    }

	if (idCheck > 20 || idCheck < 6) {
		printf("���̵��� ���̰� ���� ���Ŀ� ��߳��ϴ�.\n");
		if (reset() == 1) { // ���̵� ���Է�
			return 1;
		}
		else {            //���α׷� ����ȭ��
			return 2;
		}
	}
	else {
		strcpy(str, id);
		return 0;
	}
}

// �ϼ�
void checkPass(char* str) {
	char pw[1024] = { 0, };

	while (1) {
		printf("��й�ȣ : ");
		gets(pw);
		int pwCheck = GetStringLength(pw);
		if (pwCheck > PASSWORD_LEN || pwCheck < 8 || checkSpace(str) != 0) {
			printf("��й�ȣ ���� ���Ŀ� ��߳��ϴ�.\n�ٽ� �Է����ּ���.\n");
			continue;
		}
		else {
			strcpy(str, pw);
			return 0;
		}
	}
}

// ���� Ȯ����
void checkName(char* str) {
    char name[1024] = { 0, };

    while (1) {
        int flag = 0;
        printf("����� �̸� : ");
        gets(name);
        int nameCheck = GetStringLength(name);
        
        int i = 0;

	    while (name[i] != '\0') {
		    if (name[i] & 0x80) {
			    i++;
			    continue;
		    }
		    else {
			    flag = 1;
                break;
		    }
	    }


        if (flag == 1) {

            printf("�̸��� ���� ���Ŀ� ��߳��ϴ�. �ѱ۷� �Է����ּ���.\n");
            continue;
        }

        else if (nameCheck > NAME_LEN / 2 || nameCheck < 2 || checkSpace(str) != 0) {
            printf("�̸��� ���̰� ���� ���Ŀ� ��߳��ϴ�. 2���� �̻� 6���� ���� �ѱ۷� �Է����ּ���.\n");
            continue;
        }

        else {
            strcpy(str, name);
            break;
        }
    }
}

int checkBirth() {
   char birth[1024] = { 0, };

   while (1) {

      printf("����� : ");

      gets(birth);
      int birthCheck = GetStringLength(birth);

      //���� if������ ������ �����߽��ϴ�.
      int input;
      int year;
      int month;
      int day;


      if (birthCheck == 6) { // YYMMDD ����
         input = atoi(birth);
         year = input / 10000;
         month = (input % 10000) / 100;
         day = ((input % 10000) % 100);
         if (year >= 22 && year <= 99) {
            //19YY�� ���
            if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
               if (day >= 1 && day <= 31) {
                  return year * 10000 + month * 100 + day;
               }
               else {
                  printf("day error 1");
               }
            }
            else if (month == 4 || month == 6 || month == 9 || month == 11) {
               if (day >= 1 && day <= 30) {
                  return year * 10000 + month * 100 + day;
               }
               else {
                  printf("day error 2");
               }
            }
            else if (month == 2) {
               //���� ����� ���� ����
               year = 1900 + year;
               if (year % 4 == 0 && year % 100 == 0 && year % 400 == 0) {
                  //����
                  if (day >= 1 && day <= 29) {
                     return year * 10000 + month * 100 + day;
                  }
                  else {
                     printf("day error 3");
                  }
               }
               else if (year % 4 == 0 && year % 100 == 0) {
                  //���
                  if (day >= 1 && day <= 28) {
                     return year * 10000 + month * 100 + day;
                  }
                  else {
                     printf("day error 4");
                  }
               }
               else if (year % 4 == 0) {
                  //����
                  if (day >= 1 && day <= 29) {
                     return year * 10000 + month * 100 + day;
                  }
                  else {
                     printf("day error 5");
                  }
               }
               else {
                  //���
                  if (day >= 1 && day <= 28) {
                     return year * 10000 + month * 100 + day;
                  }
                  else {
                     printf("day error 6");
                  }
               }
            }
            else {
               printf("month error 1");
            }
         }
         else {
            //20YY�� ���
            if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
               if (day >= 1 && day <= 31) {
                  return year * 10000 + month * 100 + day;
               }
               else {
                  printf("day error 7");
               }
            }
            else if (month == 4 || month == 6 || month == 9 || month == 11) {
               if (day >= 1 && day <= 30) {
                  return year * 10000 + month * 100 + day;
               }
               else {
                  printf("day error 8");
               }
            }
            else if (month == 2) {
               //���� ����� ���� ����
               year = 2000 + year;
               if (year % 4 == 0 && year % 100 == 0 && year % 400 == 0) {
                  //����
                  if (day >= 1 && day <= 29) {
                     return year * 10000 + month * 100 + day;
                  }
                  else {
                     printf("day error 9");
                  }
               }
               else if (year % 4 == 0 && year % 100 == 0) {
                  //���
                  if (day >= 1 && day <= 28) {
                     return year * 10000 + month * 100 + day;
                  }
                  else {
                     printf("day error 10");
                  }
               }
               else if (year % 4 == 0) {
                  //����
                  if (day >= 1 && day <= 29) {
                     return year * 10000 + month * 100 + day;
                  }
                  else {
                     printf("day error 11");
                  }
               }
               else {
                  //���
                  if (day >= 1 && day <= 28) {
                     return year * 10000 + month * 100 + day;
                  }
                  else {
                     printf("day error 12");
                  }
               }
            }
            else {
               printf("month error 2");
            }
         }
      }
      else if (birthCheck == 8) { // YY-MM-DD or YYYYMMDD
         if (isdigit(birth[2])) {
            // YYYYMMDD�� ���
            input = atoi(birth);
            year = input / 10000;
            month = (input % 10000) / 100;
            day = ((input % 10000) % 100);
            if (year >= 1922 && year <= 2021) {
               if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
                  if (day >= 1 && day <= 31) {
                     return (year % 100) * 10000 + month * 100 + day;
                  }
                  else {
                     printf("day error 13");
                  }
               }
               else if (month == 4 || month == 6 || month == 9 || month == 11) {
                  if (day >= 1 && day <= 30) {
                     return (year % 100) * 10000 + month * 100 + day;
                  }
                  else {
                     printf("day error 14");
                  }
               }
               else if (month == 2) {
                  if (year % 4 == 0 && year % 100 == 0 || year % 400 == 0) {
                     //����
                     if (day >= 1 && day <= 29) {
                        return (year % 100) * 10000 + month * 100 + day;
                     }
                     else {
                        printf("day error 15");
                     }
                  }
                  else if (year % 4 == 0 && year % 100 == 0) {   
                     //���
                     if (day >= 1 && day <= 28) {
                        return (year % 100) * 10000 + month * 100 + day;
                     }
                     else {
                        printf("day error 16");
                     }
                  }
                  else if (year % 4 == 0) {
                     //����
                     if (day >= 1 && day <= 29) {
                        return (year % 100) * 10000 + month * 100 + day;
                     }
                     else {
                        printf("day error 17");
                        continue;
                     }
                  }
                  else {
                     //���
                     if (day >= 1 && day <= 28) {
                        return (year % 100) * 10000 + month * 100 + day;
                     }
                     else {
                        printf("day error 18");
                     }
                  }
               }
               else {
                  printf("month error 3");
               }
            }
            else {
               printf("year error 1");
            }
         }
         else {
            // YY-MM-DD�� ���
            if (birth[2] == birth[5]) {
               char* context;
               char check[] = { birth[2] };
               char* y = strtok_s(birth, check, &context);
               char* m = strtok_s(NULL, check, &context);
               char* d = strtok_s(NULL, check, &context);
               year = atoi(y);
               month = atoi(m);
               day = atoi(d);
               if (year >= 22 && year <= 99) {
                  //19YY�� ���
                  if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
                     if (day >= 1 && day <= 31) {
                        return year * 10000 + month * 100 + day;
                     }
                     else {
                        printf("day error 1");
                     }
                  }
                  else if (month == 4 || month == 6 || month == 9 || month == 11) {
                     if (day >= 1 && day <= 30) {
                        return year * 10000 + month * 100 + day;
                     }
                     else {
                        printf("day error 19");
                     }
                  }
                  else if (month == 2) {
                     //���� ����� ���� ����
                     year = 1900 + year;
                     if (year % 4 == 0 && year % 100 == 0 && year % 400 == 0) {
                        //����
                        if (day >= 1 && day <= 29) {
                           return year * 10000 + month * 100 + day;
                        }
                        else {
                           printf("day error 20");
                        }
                     }
                     else if (year % 4 == 0 && year % 100 == 0) {
                        //���
                        if (day >= 1 && day <= 28) {
                           return year * 10000 + month * 100 + day;
                        }
                        else {
                           printf("day error 21");
                        }
                     }
                     else if (year % 4 == 0) {
                        //����
                        if (day >= 1 && day <= 29) {
                           return year * 10000 + month * 100 + day;
                        }
                        else {
                           printf("day error 22");
                        }
                     }
                     else {
                        //���
                        if (day >= 1 && day <= 28) {
                           return year * 10000 + month * 100 + day;
                        }
                        else {
                           printf("day error 23");
                        }
                     }
                  }
                  else {
                     printf("month error 4");
                  }
               }
               else {
                  //20YY�� ���
                  if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
                     if (day >= 1 && day <= 31) {
                        return year * 10000 + month * 100 + day;
                     }
                     else {
                        printf("day error 24");
                     }
                  }
                  else if (month == 4 || month == 6 || month == 9 || month == 11) {
                     if (day >= 1 && day <= 30) {
                        return year * 10000 + month * 100 + day;
                     }
                     else {
                        printf("day error 25");
                     }
                  }
                  else if (month == 2) {
                     //���� ����� ���� ����
                     year = 2000 + year;
                     if (year % 4 == 0 && year % 100 == 0 && year % 400 == 0) {
                        //����
                        if (day >= 1 && day <= 29) {
                           return year * 10000 + month * 100 + day;
                        }
                        else {
                           printf("day error 26");
                        }
                     }
                     else if (year % 4 == 0 && year % 100 == 0) {
                        //���
                        if (day >= 1 && day <= 28) {
                           return year * 10000 + month * 100 + day;
                        }
                        else {
                           printf("day error 27");
                        }
                     }
                     else if (year % 4 == 0) {
                        //����
                        if (day >= 1 && day <= 29) {
                           return year * 10000 + month * 100 + day;
                        }
                        else {
                           printf("day error 28");
                        }
                     }
                     else {
                        //���
                        if (day >= 1 && day <= 28) {
                           return year * 10000 + month * 100 + day;
                        }
                        else {
                           printf("day error 29");
                        }
                     }
                  }
                  else {
                     printf("month error 5");
                  }
               }
            }
            else {
               printf("year-month-day 1");
            }
         }
      }
      else if (birthCheck == 10) { // YYYY-MM-DD
         if (birth[4] == birth[7]) {
            char* context;
            char check[] = { birth[4] };
            char* y = strtok_s(birth, check, &context);
            char* m = strtok_s(NULL, check, &context);
            char* d = strtok_s(NULL, check, &context);
            year = atoi(y);
            month = atoi(m);
            day = atoi(d);
            if (year >= 1922 && year <= 2021) {


               if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
                  if (day >= 1 && day <= 31) {
                     return (year % 100) * 10000 + month * 100 + day;
                  }
                  else {
                     printf("day error 30");
                  }
               }
               else if (month == 4 || month == 6 || month == 9 || month == 11) {
                  if (day >= 1 && day <= 30) {
                     return (year % 100) * 10000 + month * 100 + day;
                  }
                  else {
                     printf("day error 31");
                  }
               }
               else if (month == 2) {
                  if (year % 4 == 0 && year % 100 == 0 && year % 400 == 0) {
                     //����
                     if (day >= 1 && day <= 29) {
                        return (year % 100) * 10000 + month * 100 + day;
                     }
                     else {
                        printf("day error 32");
                     }
                  }
                  else if (year % 4 == 0 && year % 100 == 0) {
                     //���
                     if (day >= 1 && day <= 28) {
                        return (year % 100) * 10000 + month * 100 + day;
                     }
                     else {
                        printf("day error 33");
                     }
                  }
                  else if (year % 4 == 0) {
                     //����
                     if (day >= 1 && day <= 29) {
                        return (year % 100) * 10000 + month * 100 + day;
                     }
                     else {
                        printf("day error 34");
                     }
                  }
                  else {
                     //���
                     if (day >= 1 && day <= 28) {
                        return (year % 100) * 10000 + month * 100 + day;
                     }
                     else {
                        printf("day error 35");
                     }
                  }
               }
               else {
                  printf("month error 6");
               }
            }
            else {
               printf("year error 2");
            }
         }
         else {
            printf("year-month-day error 2");
         }
      }
      printf("\n������� ���� �� �����ϴ�.\n�ùٸ� �������� �Է��� �ּ���.\n");
   }

}

// �ϼ�
void makeAccount() {
	char path[PATH_LEN]="";
	char user_id[ID_LEN + 1]="";
	char user_pass[PASSWORD_LEN + 1]="";
	char user_name[NAME_LEN + 1]="";
	char user_birth[BIRTHDAY_LEN + 1]="";

	while (1) {
		system("cls");
		printf("���̵� : ");

		int check = checkID(user_id, 0, 20);
		if (check == 1) {
			continue;
		}
		else if (check == 2) {
			return;
		}
		
		user_id[ID_LEN] = '\0'; // ����� ����

		// ��� �� txt���ϻ���
		strcpy(path, "kulender\\users\\");
		strcat(path, user_id);
		strcat(path, ".txt");

		if (_access(path, 0) != -1) {
			printf("�̹� �����ϴ� ���̵��Դϴ�.\n");
			if (reset() == 1)
				continue;
			else
				return;
		}

		if (check == 0) {
			break;
		}
	}

	FILE* fout = fopen(path, "w");

	if (fout == 0) {
		printf("���� ���� ����.\n");
		return;
	}

	// ����� ��й�ȣ 
	checkPass(user_pass);
	fputs(user_pass, fout);
	fputs("\n", fout);

	// ����� �̸�
	checkName(user_name);
	fputs(user_name, fout);
	fputs("\n", fout);
	
	// ������� ����ó��
	printf("��������� �Է��մϴ�.\n");
	int day = checkBirth("");	
	char temp[BIRTHDAY_LEN + 1] = "00";

	if (!(day / 10000)) {
		_itoa(day, user_birth, 10);
		strcat(temp, user_birth);
	}
	else if (!(day / 100000)) {
		_itoa(day, user_birth, 10);
		temp[1] = NULL;
		strcat(temp, user_birth);
	}
	else {
		_itoa(day, user_birth, 10);
		temp[0] = NULL;
		temp[1] = NULL;
		strcat(temp, user_birth);
	}
	
	fputs(temp, fout);
	fputs("\n", fout);

	// ��������: 0, �׷��� �׷� ����: 0, �׷�� �׷� ����: 0
	for (int i = 0; i < 3; i++) {
		fputs("0", fout);
		fputs("\n", fout);
	}

	// ȸ������-> ���ϻ��� �� �������� ���� ��!
	fclose(fout);
	
	Sleep(1500);
}
