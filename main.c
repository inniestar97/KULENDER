#define _CRT_SECURE_NO_WARNINGS
#include "kulender.h"


int main(void) {
	int checkDir1 = _access("kulender", 0); // ���� ���� ���� ���� äũ
	if (checkDir1 == -1) { // ������ ������ �������� ������
		if (_mkdir("kulender") != 0) {
			printf("Cannot make dir \"Kulender\"\n");
			return 0;
		}
	}
	int checkDir2 = _access("kulender\\users", 0);
	if (checkDir2 == -1) {
		if (_mkdir("kulender\\users") != 0) {
			printf("Cannot make dir \"Kulender\\users\"\n");
			return 0;
		}
	}
	int checkDir3 = _access("kulender\\groups", 0);
	if (checkDir3 == -1) {
		if (_mkdir("kulender\\groups") != 0) {
			printf("Cannot make dir \"Kulender\\groups\"\n");
			return 0;
		}
	}

	while (1) {
		system("cls");
		printf("--------------KULENDER--------------\n");
		printf("1. �α���\n");
		printf("2. ȸ������\n");
		printf("3. �ý��� ����\n");
		printf("------------------------------------\n");
		printf("�޴� ���� : ");

		int num = chooseNumber(1, 3);

		switch (num) {
		case 1: 
			if (login() == -1)
				return 0;
			else
				break;
		case 2:	makeAccount(); break;
		case 3: return 0; //�ý��� ���� -> �޸� leak..
		}
		

	}
}