#include "kulender.h"
#define _CRT_SECURE_NO_WARNINGS

// 요거는 메뉴 선택하는겁니다 1~5번까지 메뉴 있으면 선택하는거 예외처리까지 한겁니다 이거 갖다 쓰시면대요
int chooseNumber(int min, int max) {

	char choice;
	int num;
	while (1) {
		choice = getchar();
		if (getchar() != '\n') {
			printf("잘못 입력되었습니다.");
			while (getchar() != '\n');
			continue;
		}
		num = choice - '0';
		if (num < min || num > max) {
			printf("목록범위 내에서 선택하세요.\n");
			continue;
		}
		else {
			return num;
		}
	}
}

//메인 메뉴 -> while문으로 수정했습니다. 다른함수에서 호출할 필요 없이 그냥 return하면 됩니다.
int mainMenu() {
	
	while (1) {
		system("cls");
		printf("---------------MAIN MENU----------------\n");
		printf("1. 일정 메뉴\n");
		printf("2. 그룹 메뉴\n");
		printf("3. 회원 탈퇴\n");
		printf("4. 로그아웃\n");
		printf("5. 시스템 종료\n");
		printf("메뉴 선택 : ");

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
	printf("1. 일정 조회\n");
	printf("2. 일정 추가\n");
	printf("3. 일정 변경\n");
	printf("4. 일정 삭제\n");
	printf("5. 메인메뉴\n");
	printf("메뉴 선택 : ");
	
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
		printf("1. 그룹 가입\n");
		printf("2. 그룹 탈퇴\n");
		printf("3. 그룹 생성\n");
		printf("4. 그룹 관리\n");
		printf("5. 메인메뉴\n");
		printf("메뉴 선택 : ");

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

//회원 탈퇴
int deleteAccount(){
	system("cls");
	char path[70];
	strcpy(path, "kulender\\users\\");
	strcat(path, USER_id);
	strcat(path, ".txt");

	if(getGroupOwnerNum(path) > 0 || getGroupMemberNum(path) > 0) {
		printf("----------------------------------------------\n");
		printf("         먼저 모든 그룹을 탈퇴하세요\n");
		printf("----------------------------------------------\n");
		Sleep(1500);
		return;
	}

	printf("--------------------------------------------------\n");
	printf("정말 탈퇴하시려면 본인의 비밀번호를 입력해주세요 \n");
	printf("--------------------------------------------------\n");
	
	//비밀번호 확인 후 일치하지 않을경우 return, 일치할 경우 파일 삭제
	char user_pass[PASSWORD_LEN + 1];
	user_pass[0] = '\0';
	printf("비밀번호 : ");
	gets(user_pass);
	if (strcmp(user_pass, USER_password) != 0) {
		printf("비밀번호가 틀렸습니다.\n");
		Sleep(1500);
		return;
	} 

	if (remove(path) == 0) {
		printf("정상적으로 삭제되었습니다. 메인 메뉴로 돌아갑니다.\n");
		Sleep(1500);
		return 0;
	}
	else {
		printf("삭제 안됨\n"); 
	}
	Sleep(1500);

	return;
}