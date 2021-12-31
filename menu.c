#include "kulender.h"
#define _CRT_SECURE_NO_WARNINGS

// ��Ŵ� �޴� �����ϴ°̴ϴ� 1~5������ �޴� ������ �����ϴ°� ����ó������ �Ѱ̴ϴ� �̰� ���� ���ø���
int chooseNumber(int min, int max) {

	char choice;
	int num;
	while (1) {
		choice = getchar();
		if (getchar() != '\n') {
			printf("�߸� �ԷµǾ����ϴ�.");
			while (getchar() != '\n');
			continue;
		}
		num = choice - '0';
		if (num < min || num > max) {
			printf("��Ϲ��� ������ �����ϼ���.\n");
			continue;
		}
		else {
			return num;
		}
	}
}

//���� �޴� -> while������ �����߽��ϴ�. �ٸ��Լ����� ȣ���� �ʿ� ���� �׳� return�ϸ� �˴ϴ�.
int mainMenu() {
	
	while (1) {
		system("cls");
		printf("---------------MAIN MENU----------------\n");
		printf("1. ���� �޴�\n");
		printf("2. �׷� �޴�\n");
		printf("3. ȸ�� Ż��\n");
		printf("4. �α׾ƿ�\n");
		printf("5. �ý��� ����\n");
		printf("�޴� ���� : ");

		int num = chooseNumber(1, 5);

		switch (num) {
		case 1: calenderMenu(); break;
		case 2: groupMenu(); break;
		case 3: 
			if (deleteAccount() == 0)
				return 0;
			break;
		case 4: return 0;
		case 5: return -1;
		}
	}
}

int calenderMenu() {
	system("cls");
	printf("------------CALENDER MENU--------------\n");
	printf("1. ���� ��ȸ\n");
	printf("2. ���� �߰�\n");
	printf("3. ���� ����\n");
	printf("4. ���� ����\n");
	printf("5. ���θ޴�\n");
	printf("�޴� ���� : ");
	
	int num = chooseNumber(1, 5);
	
	switch (num) {
		case 1: 
			lookUpCalendar();
			break;
		case 2: 
			addSchedule();
			break;
		case 3: 
			editSchedule();
			break;
		case 4: 
			deleteSchedule();
			break;
		case 5: 
			mainMenu();
			return 0;
	}
}

void groupMenu() {
	while (1) {
		system("cls");
		printf("-------------GROUP MENU--------------\n");
		printf("1. �׷� ����\n");
		printf("2. �׷� Ż��\n");
		printf("3. �׷� ����\n");
		printf("4. �׷� ����\n");
		printf("5. ���θ޴�\n");
		printf("�޴� ���� : ");

		int num = chooseNumber(1, 5);

		switch (num) {
		case 1:
			joinGroup();
			break;
		case 2:
			exitGroup();
			break;
		case 3:
			makeGroup();
			break;
		case 4:
			manageGroup();
			break;
		case 5:
			return;
		}
	}
}

//ȸ�� Ż��
int deleteAccount(){
	system("cls");
	char path[70];
	strcpy(path, "kulender\\users\\");
	strcat(path, USER_id);
	strcat(path, ".txt");

	if(getGroupOwnerNum(path) > 0 || getGroupMemberNum(path) > 0) {
		printf("----------------------------------------------\n");
		printf("         ���� ��� �׷��� Ż���ϼ���\n");
		printf("----------------------------------------------\n");
		Sleep(1500);
		return;
	}

	printf("--------------------------------------------------\n");
	printf("���� Ż���Ͻ÷��� ������ ��й�ȣ�� �Է����ּ��� \n");
	printf("--------------------------------------------------\n");
	
	//��й�ȣ Ȯ�� �� ��ġ���� ������� return, ��ġ�� ��� ���� ����
	char user_pass[PASSWORD_LEN + 1];
	user_pass[0] = '\0';
	printf("��й�ȣ : ");
	gets(user_pass);
	if (strcmp(user_pass, USER_password) != 0) {
		printf("��й�ȣ�� Ʋ�Ƚ��ϴ�.\n");
		Sleep(1500);
		return;
	} 

	if (remove(path) == 0) {
		printf("���������� �����Ǿ����ϴ�. ���� �޴��� ���ư��ϴ�.\n");
		Sleep(1500);
		return 0;
	}
	else {
		printf("���� �ȵ�\n"); 
	}
	Sleep(1500);

	return;
}