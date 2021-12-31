#define _CRT_SECURE_NO_WARNINGS
#include "kulender.h"


int main(void) {
	int checkDir1 = _access("kulender", 0); // 기존 파일 존재 유무 채크
	if (checkDir1 == -1) { // 기존에 파일이 존재하지 않을때
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
		printf("1. 로그인\n");
		printf("2. 회원가입\n");
		printf("3. 시스템 종료\n");
		printf("------------------------------------\n");
		printf("메뉴 선택 : ");

		int num = chooseNumber(1, 3);

		switch (num) {
		case 1: 
			if (login() == -1)
				return 0;
			else
				break;
		case 2:	makeAccount(); break;
		case 3: return 0; //시스템 종료 -> 메모리 leak..
		}
		

	}
}